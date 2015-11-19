#pragma once
#ifndef ROBOT_COMMAND_H
#define ROBOT_COMMAND_H

enum class Command
{
    Accelerate,
    Reset,
    Test,
};

class RobotCommand
{
public:
    RobotCommand();
    ~RobotCommand();

    Command command;
    int accelerate_x;
    int accelerate_y;

};

#endif // ROBOT_COMMAND_H
