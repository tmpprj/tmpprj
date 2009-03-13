#-------------------------------------------------
#
# Project created by QtCreator 2009-03-11T23:59:06
#
#-------------------------------------------------

QT       -= gui

TARGET = PlainTextExtractorTest
POST_TARGETDEPS += ../../../lib/libSearch.a ../../../lib/libChardet.a ../../../lib/libCommon.a
CONFIG   += console debug
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lChardet \
            -lCommon \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 


SOURCES += main.cc
