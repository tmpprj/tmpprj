#-------------------------------------------------
#
# Project created by QtCreator 2009-03-16T22:51:10
#
#-------------------------------------------------

QT       -= gui

TARGET = DocExtractor
CONFIG   += console
CONFIG   -= app_bundle

POST_TARGETDEPS += ../../../lib/libMsWord.a
DEPENDPATH += ../../include
INCLUDEPATH += ../../include
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -Wl,-Bstatic \
            -lMsWord \
            -Wl,-Bdynamic

SOURCES += main.cpp
