#-------------------------------------------------
#
# Project created by QtCreator 2009-03-11T23:59:06
#
#-------------------------------------------------

QT       -= gui

TARGET = unit_tests
POST_TARGETDEPS += ../../../lib/libSearch.a ../../../lib/libChardet.a ../../../lib/libCommon.a ../../../lib/libMsWord.a
CONFIG   += console
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../../external/UnitTest++/src ../../include ../../../libCommon/include
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -L../../../external/UnitTest++ \
            -Wl,-Bstatic \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -lUnitTest++ \
            -Wl,-Bdynamic 


SOURCES += test.cc \
           mt_queue_test.cc
