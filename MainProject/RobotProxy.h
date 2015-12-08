#pragma once
#ifndef ROBOT_PROXY_H
#define ROBOT_PROXY_H
#include <QObject>
#include "../Libraries/RobotState.h"
#include "../Libraries/TcpCommunication/TcpCommunication.h"

class RobotStateHistory;
class TcpCommunication;

/**
 * @brief A robot proxyja.
 *
 * Ezen kereszül lehet adatok küldeni és állapotjelzéseket fogadni a robottól.
 * A korábbi állapotokat a kapott RobotStateHistory objektumban tárolja.
 *
 * A konstruktor köti a dataReady() slotot a kommunikációs objektumhoz és kezeli az adatfogadást.
 */
class RobotProxy : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor.
     * @param history   A használandó RobotStateHistory példány.
     * @param communication A használandó kommunikációs objektum.
     */
    RobotProxy(RobotStateHistory& history, TcpCommunication& communication);
    ~RobotProxy() = default;

    /**
     * @brief Reseteli a robotot.
     */
    void reset();

    /**
     * @brief X-irányú gyorsítási parancsot küld a robotnak.
     */
    void accelerate_x(int a_x);

    /**
     * @brief Y-irányú gyorsítási parancsot küld a robotnak.
     */
    void accelerate_y(int a_y);

    /**
     * @brief Megállási parancs a robotnak.
     */
    void stop();

    /**
     * @brief Öntesztelés parancs küldése a robotnak.
     */
    void test();

    /**
     * @brief Default parancs küldése (debuggoláshoz, teszteléshez).
     */
    void defaultCommand();

public slots:
    /**
     * Akkor hívódik, ha új állapot érkezett a robottól.
     * Feldolgozza és eltárolja az üzenetet.
     *
     * A konstruktor köti a kommunikációs objektum üzenet beérkezést jelző
     * signaljához.
     *
     * @param stream    A bejövő adatfolyam, amiből az állapotot ki kell olvasni.
     */
    void dataReady(QDataStream& stream);

private:
    /** A korábbi és aktuális állapotot tároló RobotStateHistory példány. */
    RobotStateHistory& history;

    /** A kommunikációs objektum */
    TcpCommunication& communication;
};

#endif // ROBOTPROXY_H
