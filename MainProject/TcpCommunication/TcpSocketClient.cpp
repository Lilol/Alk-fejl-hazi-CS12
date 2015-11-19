#include "TcpSocketClient.h"

TcpSocketClient::TcpSocketClient()
{

}

void TcpSocketClient::connect(QString url, int port)
{
    socket.connectToHost(url, port, QIODevice::ReadWrite);
    setSocket(&socket);
}

