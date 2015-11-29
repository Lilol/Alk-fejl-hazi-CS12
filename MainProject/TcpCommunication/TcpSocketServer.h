#pragma once
#ifndef TCP_SOCKET_SERVER_H
#define TCP_SOCKET_SERVER_H

#include <QTcpServer>
#include "TcpCommunication.h"

/**
 * @brief TCP/IP szerver socket.
 *
 * Inicializálása után a megadott porton hallgatózik és fogadja az új kapcsolatokat.
 *
 * @warning Inicializálás után be kell kötni a Communication-től örökölt signalokat, hogy
 * a bejövő üzenetekről értesítést adjon.
 */
class TcpSocketServer : public TcpCommunication
{
    Q_OBJECT

public:
    /** Konstruktor */
    TcpSocketServer(int port);
    virtual ~TcpSocketServer() = default;

private:
    /** A belső QTcpServer példány. */
    QTcpServer serverSocket;

private slots:
    /** A szerver sockethez új kapcsolatot érkezett.
     * Beköti az adatfogadási signalt és előkészíti az adat fogadást.
     * Ezt a slotot a konstruktor köti be.
     */
    void newConnection();

    /** A kapcsolat lezárult. */
    void disconnected();
};

#endif // TCP_SOCKET_SERVER_H
