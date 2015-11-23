#include "TcpSocketClient.h"
#include <QTcpSocket>

TcpSocketClient::TcpSocketClient(){}

void TcpSocketClient::connect(QString url, int port)
{
    socket.connectToHost(url, port, QIODevice::ReadWrite);
    //Csatlakozás a hosthoz.
    //Ha nem tud csatlakozni, a debug ablakban jelzi.
    if(socket.state() != QAbstractSocket::SocketState::ConnectedState)
    {
        qDebug() << "Error: Socket cannot connect to host!" << endl;
        emit socket.error();
    }
    setSocket(&socket);
}

