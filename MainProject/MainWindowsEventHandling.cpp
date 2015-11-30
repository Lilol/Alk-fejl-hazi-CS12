#include "MainWindowsEventHandling.h"
#include "RobotProxy.h"
#include <QQmlContext>
#include "RobotStateHistory.h"

#include <QQuickItem>
#include <QQmlApplicationEngine>

MainWindowsEventHandling::MainWindowsEventHandling(
        RobotProxy &robot, QQmlContext& qmlContext, RobotStateHistory& history)
    : robot(robot), qmlContext(qmlContext), history(history)
{
    QObject::connect(&history, SIGNAL(historyChanged()), this, SLOT(historyChanged()));
}

void MainWindowsEventHandling::accelerateXCommand()
{
    robot.accelerate_x(1);
}

void MainWindowsEventHandling::accelerateYCommand()
{
    robot.accelerate_y(1);
}

void MainWindowsEventHandling::stopCommand()
{
    robot.stop();
}

void MainWindowsEventHandling::resetCommand()
{
    robot.reset();
}

void MainWindowsEventHandling::testCommand()
{
    robot.test();
}

void MainWindowsEventHandling::defaultCommand()
{
    robot.defaultCommand();
}

void MainWindowsEventHandling::historyChanged()
{
    // Ahhoz, hogy frissüljenek a QML oldali adatok, frissíteni kell a változók összekapcsolását.
    qmlContext.setContextProperty(QStringLiteral("historyModel"), QVariant::fromValue(history.stateList));
    qmlContext.setContextProperty(QStringLiteral("currentState"), QVariant::fromValue(history.currentState));

    qmlContext.setContextProperty(QStringLiteral("historyGraphTimestamps"), QVariant::fromValue(history.graphTimestamps));
    qmlContext.setContextProperty(QStringLiteral("historyGraphVelocityX"), QVariant::fromValue(history.graphVelocitiesX));
    qmlContext.setContextProperty(QStringLiteral("historyGraphVelocityY"), QVariant::fromValue(history.graphVelocitiesY));
    qmlContext.setContextProperty(QStringLiteral("historyGraphAccelerationX"), QVariant::fromValue(history.graphAccelerationsX));
    qmlContext.setContextProperty(QStringLiteral("historyGraphAccelerationY"), QVariant::fromValue(history.graphAccelerationsY));

    qmlContext.setContextProperty(QStringLiteral("currentPositionY"), QVariant::fromValue(history.graphPositionsY[history.graphPositionsX.length()-1]));
    qmlContext.setContextProperty(QStringLiteral("currentPositionX"), QVariant::fromValue(history.graphPositionsX[history.graphPositionsY.length()-1]));
    qmlContext.setContextProperty(QStringLiteral("currentSpeedX"), QVariant::fromValue(history.graphVelocitiesX[history.graphVelocitiesX.length()-1]));
    qmlContext.setContextProperty(QStringLiteral("currentSpeedY"), QVariant::fromValue(history.graphVelocitiesY[history.graphVelocitiesY.length()-1]));
    qmlContext.setContextProperty(QStringLiteral("currentAccelerationX"), QVariant::fromValue(history.graphAccelerationsY[history.graphAccelerationsY.length()-1]));
    qmlContext.setContextProperty(QStringLiteral("currentAccelerationY"), QVariant::fromValue(history.graphAccelerationsX[history.graphAccelerationsX.length()-1]));

    // Jelzünk a QML controloknak, hogy újrarajzolhatják magukat, beállítottuk az új értékeket.
    emit historyContextUpdated();
}

QQuickItem* MainWindowsEventHandling::FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        // Node keresése
        if (nodes.at(i) && nodes.at(i)->objectName() == name)
        {
            return dynamic_cast<QQuickItem*>(nodes.at(i));
        }
        // Gyerekekben keresés
        else if (nodes.at(i) && nodes.at(i)->children().size() > 0)
        {
            QQuickItem* item = FindItemByName(nodes.at(i)->children(), name);
            if (item)
                return item;
        }
    }
    // Nem találtuk.
    return nullptr;
}

QQuickItem* MainWindowsEventHandling::FindItemByName(QObject *rootObject, const QString& name)
{
    return FindItemByName(rootObject->children(), name);
}

void MainWindowsEventHandling::ConnectQmlSignals(QObject *rootObject)
{
    QQuickItem *historyGraph = FindItemByName(rootObject,QString("historyGraph"));
    if (historyGraph)
    {
        QObject::connect(this, SIGNAL(historyContextUpdated()), historyGraph, SLOT(requestPaint()));
    }
    else
    {
        qDebug() << "HIBA: Nem találom a historyGraph objektumot a QML környezetben.";
    }
}
