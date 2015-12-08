#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T16:28:58
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Libraries
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y

SOURCES += \
    RobotCommand.cpp \
    RobotState.cpp \
    Simulator.cpp \
    TcpCommunication/TcpCommunication.cpp \
    TcpCommunication/TcpSocketClient.cpp \
    TcpCommunication/TcpSocketServer.cpp

HEADERS += \
    Simulator.h \
    RobotCommand.h \
    RobotState.h \
    TcpCommunication/TcpCommunication.h \
    TcpCommunication/TcpSocketClient.h \
    TcpCommunication/TcpSocketServer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
