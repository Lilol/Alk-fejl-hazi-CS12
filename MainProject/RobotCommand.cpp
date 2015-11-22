#include "RobotCommand.h"

RobotCommand::RobotCommand()
{

}

RobotCommand::~RobotCommand()
{

}


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
