#pragma once
#ifndef ROBOT_COMMAND_H
#define ROBOT_COMMAND_H
#include <QDataStream>




class RobotCommand : public QObject
{
    Q_OBJECT

public:
    enum class Command
    {
        Accelerate = 0,
        Reset = 1,
        Test = 2,
    };


    RobotCommand();
    RobotCommand(Command command, int accelerate_x, int accelerate_y);

    ~RobotCommand() = default;



    /** Parancs */
    Q_PROPERTY(Command command READ command WRITE setCommand MEMBER _command NOTIFY commandChanged)
    Command command() const { return _command; }
    void setCommand(const Command command) { _command = command; }

    /** gyorsítás X irányban */
    Q_PROPERTY(int accelerate_x READ accelerate_x WRITE setAccelerate_x MEMBER _accelerate_x NOTIFY accelerate_xChanged)
    int accelerate_x() const { return _accelerate_x; }
    void setAccelerate_x(int accelerate_x) { _accelerate_x = accelerate_x; }

    /** gyorsítás Y irányban */
    Q_PROPERTY(int accelerate_y READ accelerate_y WRITE setAccelerate_y MEMBER _accelerate_y NOTIFY accelerate_yChanged)
    int accelerate_y() const { return _accelerate_y; }
    void setAccelerate_y(int accelerate_y) { _accelerate_y = accelerate_y; }

    /** Sorosítja az objektumot a megadott streambe. */
    void WriteTo(QDataStream& stream) const;

    /** Beolvassa az objektumot a streamből. */
    void ReadFrom(QDataStream& stream);

signals:
    void commandChanged();

private:
    Command _command;
    int _accelerate_x;
    int _accelerate_y;

};

#endif // ROBOT_COMMAND_H
