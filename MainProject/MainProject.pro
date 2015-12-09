#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T19:57:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainProject
TEMPLATE = app

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y

QT += qml quick widgets
QT += network

# Default rules for deployment.
include(../deployment.pri)
RESOURCES += qml.qrc

SOURCES += main.cpp\
    MainApplication.cpp \
    MainWindowsEventHandling.cpp \
    RobotProxy.cpp \
    RobotStateHistory.cpp

HEADERS  += \
    MainApplication.h \
    MainWindowsEventHandling.h \
    RobotProxy.h \
    RobotStateHistory.h

FORMS    += MainWindow.ui

DISTFILES += \
    main.qml \
    KeyHandler.qml \
    Buttons.qml \
    help_window.qml \
    HistoryGraph.qml \
    LogList.qml \
    MapImage.qml \
    SpeedMeter.qml

win32:CONFIG(release, debug|release): LIBS += -L../Libraries/release/ -lLibraries
else:win32:CONFIG(debug, debug|release): LIBS += -L../Libraries/debug/ -lLibraries
