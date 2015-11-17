#include <QTimer>
#include "TcpCommunication.h"

TcpCommunication::TcpCommunication()
    :receiveStream(nullptr), currentMessageSize(0), socket(nullptr)
{
}

TcpCommunication::~TcpCommunication()
{
    if (receiveStream != nullptr)
    {
        // (Ha volt korábbi érték, az most megszűnik a unique_ptr miatt.)
        receiveStream = nullptr;
    }
}

void TcpCommunication::setSocket(QTcpSocket *newSocket)
{
    // Slotok csatlakoztatása az új sockethez
    if (socket != nullptr && newSocket != socket)
    {
        QObject::disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(TcpCommunication::handleError(QAbstractSocket::SocketError)));
        QObject::disconnect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    }
    socket = newSocket;
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    // Alsóbb réteg (ősosztály) csatlakoztatása a sockethez
    TcpCommunication::connectToDevice(socket);
}

bool TcpCommunication::isConnected() const
{
    if (socket == nullptr)
    {
        return false;
    }
    return socket->state() == QTcpSocket::ConnectedState;
}

void TcpCommunication::disconnect()
{
    if (socket != nullptr)
    {
        socket->disconnectFromHost();
    }
}

void TcpCommunication::sendBufferContent()
{
    if (socket == nullptr)
    {
        emit errorOccurred(QString("HIBA: Adatküldés socket nélkül."));
        return;
    }
    if (!isConnected())
    {
        emit errorOccurred(QString("HIBA: Adatküldés nyitott socket nélkül."));
        return;
    }

    qDebug() << "TcpCommunication::send() " << sendBuffer.size() << " bájt:\n" << sendBuffer.toHex();
    socket->write(sendBuffer);
    sendBuffer.clear();
}

void TcpCommunication::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit this->errorOccurred(socket->errorString());
}

void TcpCommunication::connectToDevice(QIODevice *device)
{
    // A fogadási adatfolyam csatlakozatotása az eszközhöz (pl. sockethez)
    // (Ha volt korábbi, az most megszűnik a unique_ptr miatt.)
    receiveStream = std::make_unique<QDataStream>(device);
}

std::unique_ptr<QDataStream> TcpCommunication::getSendStream()
{
    return std::unique_ptr<QDataStream>(new QDataStream(&sendBuffer, QIODevice::WriteOnly));
}

QDataStream *TcpCommunication::getReceiveStream()
{
    return receiveStream.get();
}

void TcpCommunication::dataReceived()
{
    // Addig olvasunk, amíg nem jön meg egy egész üzenet.
    //  Utána kiadunk egy TcpCommunication::dataReady signalt.
    QDataStream &inStream = *getReceiveStream();
    QIODevice *socket = inStream.device();

    if (currentMessageSize == 0) {
        // Új üzenet kezdődik
        // Még nem tudjuk a csomag méretét
        if (socket->bytesAvailable() < (int) sizeof(qint32)) {
            // Még a csomag mérete sem jött meg.
            return;
        }

        // Üzenet hosszának beolvasása
        inStream >> currentMessageSize;
    }

    // Már tudjuk a csomag méretét.

    if (socket->bytesAvailable() < (int) (currentMessageSize - sizeof(qint32))) {
        // Nem jött még meg az egész csomag.
        return;
    }

    /* Jelezzük, hogy van új adat. Amit átadunk, az az id és méret utáni adattartalom.
     * Tömb esetében a QVector úgy szerializálja ki magát, hogy abban benne van a méret is. */
    emit dataReady(inStream);

    // Lehet, hogy még egy következő üzenet elejét is megkaptuk.
    currentMessageSize = 0;
    if (socket->bytesAvailable() > 0) {
        /* A QTimer-t használva még egyszer belelövünk
         * ebbe a slotba, hogy feldolgozza a maradék fogadott bytokat is. */
        QTimer::singleShot(0, this, SLOT(dataReceived()));
    }
}
