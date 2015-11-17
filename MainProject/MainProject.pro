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

SOURCES += main.cpp\
        MainWindow.cpp \
    RobotState.cpp

HEADERS  += MainWindow.h \
    RobotState.h

FORMS    += MainWindow.ui
