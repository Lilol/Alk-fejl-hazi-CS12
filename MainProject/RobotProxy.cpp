#include "RobotProxy.h"
#include "RobotStateHistory.h"
#include "TcpCommunication/TcpCommunication.h"
#include "RobotState.h"
#include "RobotCommand.h"

RobotProxy::RobotProxy(RobotStateHistory& history, TcpCommunication &communication)
    : history(history), communication(communication)
{
    // Jelzést kérünk, ha új robot állapot (RobotState) érkezik.
    QObject::connect(&communication, SIGNAL(dataReady(QDataStream&)), this, SLOT(dataReady(QDataStream&)));
}

void RobotProxy::dataReady(QDataStream &stream)
{
    // Új robot állapot érkezett, elmentjük a historyba.
    //  (Onnan vesszük majd azt is, hogy mi az aktuális állapot.)
    RobotState state;
    state.ReadFrom(stream);
    history.Add(state);
}

void RobotProxy::reset()
{
    // Reset parancs küldése.
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Reset);
    communication.send(newState);
    qDebug() << "Reset parancs elküldve.";
}

void RobotProxy::accelerate_x(int a_x)
{
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Accelerate);
    newState.setAccelerationX(a_x);
    newState.setAccelerationY(0);
    communication.send(newState);
    qDebug() << "X-irányú gyorsítási parancs elküldve.";
}

void RobotProxy::accelerate_y(int a_y)
{
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Accelerate);
    newState.setAccelerationX(0);
    newState.setAccelerationY(a_y);
    communication.send(newState);
    qDebug() << "Y-irányú gyorsítási parancs elküldve.";
}

void RobotProxy::stop()
{
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Stopping);
    communication.send(newState);
    qDebug() << "Stop parancs elküldve.";
}

void RobotProxy::test()
{
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Test);
    communication.send(newState);
    qDebug() << "Tesztelési parancs elküldve.";
}

void RobotProxy::defaultCommand()
{
    RobotCommand newState;
    newState.setStatus(RobotCommand::Command::Default);
    communication.send(newState);
    qDebug() << "Default parancs elküldve.";
}
