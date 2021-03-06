#-------------------------------------------------
#
# Project created by QtCreator 2009-03-11T23:59:06
#
#-------------------------------------------------

QT       -= gui

TARGET = unit_tests

unix {
POST_TARGETDEPS += ../../../lib/libCommon.a
}
win32 {
POST_TARGETDEPS += ../../../lib/Common.lib
}

CONFIG   += console
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../../external/UnitTest++/src ../../include ../../../libCommon/include
TEMPLATE = app

QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib ../../../external/UnitTest++
unix {
LIBS +=     -Wl,-Bstatic \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -lUnitTest++ \
            -Wl,-Bdynamic 
}
win32 {
LIBS +=     Common.lib \
            libboost_thread.lib \
            libboost_system.lib \
            UnitTest++.lib
}

SOURCES += test.cc \
           mt_queue_test.cc
