#include "RobotCommand.h"

RobotCommand::RobotCommand()
:_command(RobotCommand::Command::Default), _accelerate_x(0), _accelerate_y(0)
{}

RobotCommand::RobotCommand(Command command, int accelerate_x, int accelerate_y)
    : _command(command), _accelerate_x(accelerate_x), _accelerate_y(accelerate_y)
{}

void RobotCommand::WriteTo(QDataStream& stream) const
{
    stream << (qint32)_command;
    stream << _accelerate_x;
    stream << _accelerate_y;
}

void RobotCommand::ReadFrom(QDataStream& stream)
{
    qint32 tmpQint32;
    stream >> tmpQint32;
    _command = (Command)tmpQint32;
    stream >> _accelerate_x;
    stream >> _accelerate_y;
}

QDataStream &operator<<(QDataStream& stream, const RobotCommand& command)
{
    command.WriteTo(stream);
    return stream;
}

QDataStream &operator>>(QDataStream& stream, RobotCommand& command)
{
    command.ReadFrom(stream);
    return stream;
}

void RobotCommand::setStatus(RobotCommand::Command command)
{
    _command = command;
}

void RobotCommand::setAccelerationX(int a_x)
{
     _accelerate_x = a_x;
}

void RobotCommand::setAccelerationY(int a_y)
{
    _accelerate_y = a_y;
}
