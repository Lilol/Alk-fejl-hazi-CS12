TEMPLATE = subdirs
CONFIG += ordered
CONFIG += static

SUBDIRS += \
    Libraries \
    MainProject \
    UnitTests \

MainProject.depends = Libraries
UnitTests.depends = Libraries

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/Libraries/release/ -lLibraries
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/Libraries/debug/ -lLibraries
else:unix: LIBS += -L$$OUT_PWD/Libraries/ -lLibraries

INCLUDEPATH += $$PWD/Libraries
DEPENDPATH += $$PWD/Libraries

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/Libraries/release/libLibraries.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/Libraries/debug/libLibraries.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/Libraries/release/Libraries.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/Libraries/debug/Libraries.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/Libraries/libLibraries.a
