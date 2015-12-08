#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T19:57:16
#
#-------------------------------------------------

QT      += testlib
QT      -= gui
QT      += network

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y
CONFIG += static

TARGET = UnitTests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += testcase

include(../deployment.pri)

TEMPLATE = app

SOURCES += \
    SimulatorTester.cpp \

win32:CONFIG(release, debug|release): LIBS += -L../Libraries/release/ -lLibraries
else:win32:CONFIG(debug, debug|release): LIBS += -L../Libraries/debug/ -lLibraries

