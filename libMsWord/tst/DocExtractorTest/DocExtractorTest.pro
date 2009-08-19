#-------------------------------------------------
#
# Project created by QtCreator 2009-03-16T22:51:10
#
#-------------------------------------------------

QT       -= gui

TARGET = DocExtractorTest
CONFIG   += console
CONFIG   -= app_bundle

win32 {
POST_TARGETDEPS += ../../../lib/MsWord.lib
}
unix {
POST_TARGETDEPS += ../../../lib/libMsWord.a
}

DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app

QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
unix {
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
