#include <QDebug>
#include <QQmlContext>
#include "MainApplication.h"
#include "RobotCommand.h"
#include "RobotState.h"
#include "Simulator.h"

#define SOCKET_PORT 12345

int main(int argc, char *argv[])
{
    //MainApplication app(argc, argv);
    //return app.exec();
    Simulator simulator(SOCKET_PORT);
    TcpSocketClient communication;
    RobotCommand command(RobotCommand::Command::Test, 0, 0);
    simulator.start(1.0F);
    communication.connect(QStringLiteral("localhost"), SOCKET_PORT);
    while(1)
    {
        if(communication.isConnected())
        {
            communication.send(command);
            break;
        }
    }
    return 0;
}
