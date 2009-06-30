#-------------------------------------------------
#
# Project created by QtCreator 2009-05-21T16:46:07
#
#-------------------------------------------------

QT       -= gui

TARGET = PdfExtractorTest
CONFIG   += console
CONFIG   -= app_bundle

POST_TARGETDEPS += ../../../lib/libPdf.a
DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lPdf \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic

SOURCES += main.cpp
