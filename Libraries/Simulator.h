#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "TcpCommunication/TcpSocketServer.h"
#include "RobotState.h"
#include "RobotCommand.h"

/**
 * @brief A robot szimulátor.
 *
 * Van egy belső, RobotState típusú állapota, melyet egy QTimer segítségével periodikusan frissít.
 * Létrehoz egy TcpSocketServer objektumot a kommunikációhoz, amihez lehet csatlakozni.
 * Minden szimulációs lépés után elküldi az állapotát.
 * Ha egy RobotState objektumot kap, azt parancsként értelmezi.
 */
class Simulator : public QObject
{
    Q_OBJECT

public:
    /** Konstruktor.
     * @param port  A port, amin a létrehozott szerver hallgatózik.
    */
    explicit Simulator(int port);

    /** Konstruktor a unit teszteléshez. Nincs szüksége portra.  */
    explicit Simulator();
    ~Simulator() = default;

    /** Elindítja a szimulátort.
     * @param intervalSec   A szimulátor periódusideje.
     */
    void start(float intervalSec);

private:
    /** @brief Belső szerver a kommunikációhoz. */
    TcpSocketServer communication;

    /** @brief Időzítő a tick() metódus periodikus hívására. */
    QTimer timer;

    /** @brief A periódus idő (másodpercben). */
    float dt;

    /** @brief A szimulátor pillanatnyi állapota. */
    RobotState state;

    void sendState();
    void showDebugInfo();

    /** @brief Az state változó beállítása a robot jelenlegi állapotától függően. */
    void processStateInfo();

    void saturateVelocity();
    void saturatePosition();
    void doSensorSimulation();
    void doPhisicalSimulation();

    int selfTest();

private slots:
    /** @brief A timer hívja meg, meghatározza a robot
     * állapotát a következő időpillanatban. */
    void tick();

    /** @brief Új üzenet fogadását jelzi. */
    void dataReady(QDataStream& inputStream);

signals:
    void stateSet(RobotState state);
};

#endif // SIMULATOR_H
