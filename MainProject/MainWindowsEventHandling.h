#pragma once
#ifndef MAIN_WINDOWS_EVENT_HANDLING_H
#define MAIN_WINDOWS_EVENT_HANDLING_H
#include <QObject>
#include <QDebug>

class RobotProxy;
class QQmlContext;
class RobotStateHistory;

class QQuickItem;
class QQmlApplicationEngine;

/**
 * @brief Ez az osztály tartalmazza a felhasználó felület (GUI) eseménykezelőit.
 *
 * A függőségeit a konstruktoron kereszül kapja meg és kapcsolódik a GUI
 * signaljaihoz.
 *
 * A ConnectQmlSignals() metódust meg kell hívni a QML gyökér objektummal, hogy
 * a megfelelő signalokat be tudja kötni.
 */
class MainWindowsEventHandling : public QObject
{
    Q_OBJECT

public:
    /** Konstruktor
     * @param robot A robot proxy példány
     * @param qmlContext    A QML context objektum
     * @param history   A használt RobotStateHistory objektum.
     */
    MainWindowsEventHandling(RobotProxy& robot, QQmlContext &qmlContext, RobotStateHistory &history);

    ~MainWindowsEventHandling() = default;

    /** Csatlakoztatja a QML oldali signalokat. Az után kell meghívni, hogy a QML környezet felállt.
     * @param rootObject    A QML gyökérelem.
     */
    void ConnectQmlSignals(QObject *rootObject);

public slots:
    /** @brief X-irányú gyorsulási parancsot küld a robotnak. A gyorsítási nyomógomb eseménykezelője. */
    void accelerateXCommand();

    /** @brief Y-irányú gyorsulási parancsot küld a robotnak. A gyorsítási nyomógomb eseménykezelője. */
    void accelerateYCommand();

    /** @brief X-irányú gyorsulási parancsot küld a robotnak. A gyorsítási nyomógomb eseménykezelője. */
    void slowDownXCommand();

    /** @brief Y-irányú gyorsulási parancsot küld a robotnak. A gyorsítási nyomógomb eseménykezelője. */
    void slowDownYCommand();

    /** @brief A Stop nyomógomb eseménykezelője. */
    void stopCommand();

    /** @brief A Reset nyomógomb eseménykezelője. */
    void resetCommand();

    /** @brief A Test nyomógomb eseménykezelője. */
    void testCommand();

    /** @brief */
    void defaultCommand();

    /** @brief
     * Azt jelzi, hogy változott az állapot history. (Tipikusan mert új állapot érkezett a robottól.)
     * Frissíti a QML számára elérhetővé tett, C++ oldali változókat (propertyket) és
     * kiváltja a historyContextUpdated() signalt.
    */
    void historyChanged();

signals:
    /** @brief
     * Jelzi, hogy változott a megjelenítés számára az adatmodell.
     * Ilyenkor az érintett QML elemek (a grafikon) újrarajzolják magukat.
     */
    void historyContextUpdated();

private:
    /** A használt robot proxy. */
    RobotProxy& robot;

    /** \addtogroup hivatkozas Hivatkozások adatkötéshez
     *  @{
     */
    /** QML context a robot adatok frissítéséhez. */
    QQmlContext &qmlContext;
    /** A history objektum. */
    RobotStateHistory &history;
    /** @}*/

    /** Segédfüggvény QML elemek rekurzív megkeresésére.
     * @param rootObject A QML gyökérelem, amivel a keresést kezdjük.
     * @param name Az objectName (QML elemek tulajdonsága), amit keresünk.
     */
    static QQuickItem* FindItemByName(QObject *rootObject, const QString& name);

    /** Segédfüggvény QML elemek rekurzív megkeresésére.
     * A FindItemByName(QObject *rootObject, const QString& name) használja.
     * @param nodes Azon node-ok listája, melyekben (rekurzívan) az adott nevű elemet keressük.
     * @param name  Az objectName (QML elemek tulajdonsága), amit keresünk.
     */
    static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name);
};

#endif // MAINWINDOWSEVENTHANDLING_H
