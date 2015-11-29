#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T19:57:16
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

QT += network

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y

TARGET = tst_UnitTests
CONFIG   += console
CONFIG   -= app_bundle

include(../deployment.pri)

TEMPLATE = app

SOURCES += \
    SimulatorTester.cpp \
    CommunicationTester.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"


