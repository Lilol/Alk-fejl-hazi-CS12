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
QT += serialport

# Default rules for deployment.
# include(deployment.pri)

SOURCES += main.cpp\
        RobotState.cpp \
        RobotCommand.cpp \
        TcpCommunication/TcpCommunication.cpp \
    TcpCommunication/TcpSocketClient.cpp \
    TcpCommunication/TcpSocketServer.cpp \
    MainApplication.cpp

HEADERS  += \
            RobotState.h \
            RobotCommand.h \
            TcpCommunication/TcpCommunication.h \
    TcpCommunication/TcpSocketClient.h \
    TcpCommunication/TcpSocketServer.h \
    MainApplication.h

FORMS    += MainWindow.ui
