#include <QDebug>
#include <QQmlContext>
#include "MainApplication.h"
#include "RobotCommand.h"
#include "RobotState.h"
#include "Simulator.h"

int main(int argc, char *argv[])
{
    //MainApplication app(argc, argv);
    //return app.exec();
    Simulator simulator(3333);
    TcpSocketClient communication;
    RobotCommand command(RobotCommand::Command::Test, 0, 0);
    simulator.start(1.0F);
    communication.connect(QStringLiteral("localhost"),3333);
    communication.send(command);
    return 0;
}
