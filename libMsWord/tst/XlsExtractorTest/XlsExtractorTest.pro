#-------------------------------------------------
#
# Project created by QtCreator 2009-03-27T14:35:59
#
#-------------------------------------------------
QT       -= gui

TARGET = XlsExtractorTest
CONFIG   += console
CONFIG   -= app_bundle

unix {
POST_TARGETDEPS += ../../../lib/libMsWord.a
}
win32 {
POST_TARGETDEPS += ../../../lib/MsWord.lib
}

DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app

QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
unix {
QMAKE_CXXFLAGS_DEBUG += -O0
LIBS +=     -Wl,-Bstatic \
            -lMsWord \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic
}
win32 {
LIBS +=     MsWord.lib \
            Common.lib \
            libboost_thread.lib \
            libboost_system.lib
}

SOURCES += main.cpp
