#pragma once
#ifndef TCP_SOCKET_CLIENT_H
#define TCP_SOCKET_CLIENT_H

#include "TcpCommunication.h"

/** @brief QTcpSocket alapú kommunikáció kliens oldala. */
class TcpSocketClient : public TcpCommunication
{
public:
    /** Konstruktor */
    TcpSocketClient();

    virtual ~TcpSocketClient() = default;

    /** Kapcsolat felépítése. */
    void connect(QString url, int port);

private:
    /** A belső QTcpSocket példány. */
    QTcpSocket socket;

};
#endif // TCP_SOCKET_CLIENT_H
