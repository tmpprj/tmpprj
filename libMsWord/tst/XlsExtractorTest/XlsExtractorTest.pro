#-------------------------------------------------
#
# Project created by QtCreator 2009-03-27T14:35:59
#
#-------------------------------------------------
QT       -= gui

TARGET = XlsExtractorTest
CONFIG   += console
CONFIG   -= app_bundle
POST_TARGETDEPS += ../../../lib/libMsWord.a
DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app
linux {
QMAKE_CXXFLAGS_DEBUG += -O0
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
