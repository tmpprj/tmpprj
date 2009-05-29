#-------------------------------------------------
#
# Project created by QtCreator 2009-03-27T14:35:59
#
#-------------------------------------------------
QT       -= gui

TARGET = XlsExtractorTest
CONFIG   += console debug
CONFIG   -= app_bundle
QMAKE_CXXFLAGS_DEBUG += -O0
POST_TARGETDEPS += ../../../lib/libMsWord.a
DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lMsWord \
            -lCommon \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic

SOURCES += main.cpp
