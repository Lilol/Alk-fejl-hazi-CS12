#include "RobotCommand.h"



RobotCommand::RobotCommand(Command command, int accelerate_x, int accelerate_y)
    : _command(command), _accelerate_x(accelerate_x), _accelerate_y(accelerate_y)
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
