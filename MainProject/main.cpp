#include <QDebug>
#include <QQmlContext>
#include "MainApplication.h"
#include "RobotCommand.h"
#include "RobotState.h"
#include "Simulator.h"

#define SOCKET_PORT 12345

int main(int argc, char *argv[])
{
    MainApplication app(argc, argv);
    return app.exec();
}
