#include <QDebug>
#include <QQmlContext>
#include "MainApplication.h"
#include "../Libraries/RobotCommand.h"
#include "../Libraries/RobotState.h"
#include "../Libraries/Simulator.h"

int main(int argc, char *argv[])
{
    MainApplication app(argc, argv);
    return app.exec();
}
