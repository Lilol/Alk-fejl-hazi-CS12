#pragma once
#ifndef MAIN_APPLICATION_H
#define MAIN_APPLICATION_H

#include "TcpCommunication/TcpSocketClient.h"
#include "Simulator.h"
#include "RobotProxy.h"
#include "MainWindowsEventHandling.h"
#include "RobotStateHistory.h"
#include <QApplication>
#include <QQmlApplicationEngine>

/**
 * @brief Alkalmazás osztály. A main() példányosítja és indítja el.
 *
 * A konstruktor elvégzi az alapvető példányosításokat és a signalok összekapcsolását.
 */
class MainApplication : public QApplication
{
public:
    /** Konstruktor. Alapvető példányosítások és signal bekötések. */
    MainApplication(int argc, char *argv[]);
    ~MainApplication() = default;

private:
    Simulator simulator;
    QQmlApplicationEngine engine;
    RobotStateHistory history;
    TcpSocketClient communication;
    RobotProxy robot;
    MainWindowsEventHandling handler;
};
#endif // MAIN_APPLICATION_H
