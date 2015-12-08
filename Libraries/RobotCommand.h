#pragma once
#ifndef ROBOT_COMMAND_H
#define ROBOT_COMMAND_H
#include <QDataStream>

/**
@brief A robotnak küldött parancsokat beburkoló osztály.
Tartalmazza a robot irányításához szükséges parancs típusát, és gyorsítási parancs esetén a gyorsulás nagyságát.
*/
class RobotCommand : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief A robotnak küldött parancs jellege.*/
    enum class Command
    {
        /** Gyorsítási parancs
        @warning Ilyenkor a gyorsulás Y és X-irányú összetevőjét is be kell állítani a setAccelerationX() és setAccelerationY() metódusok segítségével.*/
        Accelerate = 0,
        /** Robot alapállapotba állítása.*/
        Reset = 1,
        /** Öntesztelés indítása.*/
        Test = 2,
        /** Megállási parancs küldése. */
        Stopping = 3,
        /** Debuggoláshoz, teszteléshez használható. Nincs hatása a szimulátorra. */
        Default = 4,
    };

    RobotCommand();
    RobotCommand(Command command, int accelerate_x, int accelerate_y);

    ~RobotCommand() = default;

    /**
     * @brief Command változó beállítása.
     */
    void setStatus(RobotCommand::Command command);

    /**
     * @brief X irányú gyorsulás beállítása.
     */
    void setAccelerationX(int a_x);

    /**
     * @brief Y irányú gyorsulás beállítása.
     */
    void setAccelerationY(int a_y);

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
    void accelerate_xChanged();
    void accelerate_yChanged();

private:
    Command _command;
    int _accelerate_x;
    int _accelerate_y;
};

/** Beburkolja a RobotCommand.WriteTo metódust. */
QDataStream &operator<<(QDataStream &, const RobotCommand &);

/** Beburkolja a RobotCommand.ReadFrom metódust. */
QDataStream &operator>>(QDataStream &, RobotCommand &);

#endif // ROBOT_COMMAND_H
