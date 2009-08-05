QT       -= gui

TARGET = FileSearcherTest
DESTDIR = ../../../bin
POST_TARGETDEPS += ../../../lib/libSearch.a ../../../lib/libCommon.a 
CONFIG   += console
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 


SOURCES += main.cc
