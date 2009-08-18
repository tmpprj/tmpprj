#-------------------------------------------------
#
# Project created by QtCreator 2009-03-11T23:59:06
#
#-------------------------------------------------

QT       -= gui

TARGET = SearchFacadeTest
DESTDIR = ../../../bin
POST_TARGETDEPS += ../../../lib/libSearch.a ../../../lib/libChardet.a ../../../lib/libCommon.a ../../../lib/libMsWord.a
CONFIG   += console
CONFIG   -= app_bundle
DEPENDPATH += ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app
linux {
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lChardet \
            -lMsWord \
            -lCommon \
            -lPdf \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 
}
win32 {
QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
LIBS +=     Search.lib \
            Common.lib \
            MsWord.lib \
            Chardet.lib \
            Pdf.lib \
            libboost_thread.lib \
            libboost_system.lib
}

SOURCES += main.cc
