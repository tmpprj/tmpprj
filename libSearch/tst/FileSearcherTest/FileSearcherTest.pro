QT       -= gui

TARGET = FileSearcherTest
DESTDIR = ../../../bin

win32 {
POST_TARGETDEPS += ../../../lib/Search.lib ../../../lib/Common.lib 
}
unix {
POST_TARGETDEPS += ../../../lib/libSearch.a ../../../lib/libCommon.a 
}

CONFIG   += console
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
TEMPLATE = app

QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
unix {
LIBS +=     -Wl,-Bstatic \
            -lSearch \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 
}

win32 {
LIBS +=     Search.lib \
            Common.lib \
            libboost_thread.lib \
            libboost_system.lib
}


SOURCES += main.cc
