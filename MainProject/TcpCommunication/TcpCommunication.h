#pragma once
#ifndef TCP_COMMUNICATION_H
#define TCP_COMMUNICATION_H

#include <memory>
#include <QDataStream>
#include <QDateTime>
#include <QAbstractSocket>
#include <QTcpSocket>

/**
 * @brief TCP socket alapú kommunikációs osztály*/
class TcpCommunication: public QObject
{
    Q_OBJECT

public:
    /** Konstruktor */
    TcpCommunication();
    virtual ~TcpCommunication();

    /** Csatlakozás egy eszközhöz (Pl. QTcpSocket), amit használni fog. */
    void connectToDevice(QIODevice *device);

    /**
     * @brief Beállítja a használt socketet.
     * @param newSocket Az új socket, amihez az adat fogadást csatlakoztatni kell.
     *  nullptr esetén leválasztja a signalokat a belső socketről.
     */
    void setSocket(QTcpSocket *newSocket);

    /** Visszaad egy pointert az adatfogadási folyamra. */
    QDataStream *getReceiveStream();

    /** Visszaadja, hogy van-e kapcsolat. */
    bool isConnected() const ;

    /** Kapcsoat bontása. */
    void disconnect();

    /** Egy objektum tartalmát elküldi: kiírja a sendBuffer-be, majd meghívja
     * a sendBufferContent() metódust.
     */
    template<typename T>
    void send(const T& toSendObject)
    {
        auto stream = getSendStream();

        // Elmentjük a jelenlegi stream pozíciót
        const qint64 startPos = stream->device()->size();
        qint32 msgSize = 0;
        // Ideiglenesen az elejére méretnek 0-t írunk. Majd
        //  ha már le tudjuk mérni az üzenet hosszát, visszajövünk ide és
        //  beírjuk a tényleges értéket.
        *stream << msgSize;
        // A tényleges adattartalom sorosítása
        *stream << toSendObject;
        const qint64 endPos = stream->device()->size();

        // Visszaugrunk és beírjuk a helyes üzenet méretet.
        stream->device()->seek(startPos);
        msgSize = endPos - startPos;
        *stream << msgSize;
        // Visszaugrunk az üzenet végére
        stream->device()->seek(endPos);

        // Ténylegesen elküldjük az üzenetet.
        //  (Ez absztrakt metódus, majd minden protokoll implementálja, ahogy kell.)
        sendBufferContent();
    }

signals:
    /** Hibajelzés. */
    void errorOccurred(const QString&);

    /** Egy teljes üzenet megérkezett. */
    void dataReady(QDataStream& stream);

protected:
    /** Tényleges küldés előtt ide kerül be minden küldendő adat.
     * A getSendStream() metódussal lehet elérni. */
    QByteArray sendBuffer;

    /** Az adat fogadási stream. A connectToDevice() állítja be. */
    std::unique_ptr<QDataStream> receiveStream;

    /** A belső küldési buffer tartalmát elküldi. Akkor kell meghívni, miután az üzenet bekerült a bufferbe. */
    void sendBufferContent() ;

    /** Visszaad egy streamet, ami a tényleges adatküldéshez a sendBuffer-be beírja a
    * küldendő adatokat. Utána már csaa a sendBufferContent() metódust kell meghívni.
    * Kívülről a send() metódust kell használni, az tovább hív ide. */
    std::unique_ptr<QDataStream> getSendStream();

protected slots:
    /** Adat érkezett, de nem feltétlenül egy egész üzenet.
     * A leszármazott osztályok ezen kereszül jelzik, hogy van új adat.
     */
    void dataReceived();

private:
    /** Az éppen fogadott üzenet mérete. A dataReceived() használja. */
    qint32 currentMessageSize;

    /** Ha van felépült kapcsolat, arra mutató pointer. Egyébként nullptr. */
    QTcpSocket *socket;

private slots:
    /** Továbbítja a hibajelzést. */
    void handleError(QAbstractSocket::SocketError socketError);
};

#endif // TCP_COMMUNICATION_H
