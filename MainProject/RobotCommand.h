#pragma once
#ifndef ROBOT_COMMAND_H
#define ROBOT_COMMAND_H
#include <QDataStream>


enum class Command
{
    Accelerate = 0,
    Reset = 1,
    Test = 2,
};

class RobotCommand
{
public:
    RobotCommand();
    ~RobotCommand();




    /** Sorosítja az objektumot a megadott streambe. */
    void WriteTo(QDataStream& stream) const;

    /** Beolvassa az objektumot a streamből. */
    void ReadFrom(QDataStream& stream);


private:
    Command _command;
    int _accelerate_x;
    int _accelerate_y;

};

#endif // ROBOT_COMMAND_H
