#-------------------------------------------------
#
# Project created by QtCreator 2009-04-23T20:05:02
#
#-------------------------------------------------
QT       -= gui

TARGET = PptExtractorTest
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS_DEBUG += -O0
POST_TARGETDEPS += ../../../lib/libMsWord.a
DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app
linux {
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lMsWord \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic
}
win32 {
QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
LIBS +=     MsWord.lib \
            Common.lib \
            libboost_thread.lib \
            libboost_system.lib
}

SOURCES += main.cpp
