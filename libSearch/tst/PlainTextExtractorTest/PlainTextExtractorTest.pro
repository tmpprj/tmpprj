#-------------------------------------------------
#
# Project created by QtCreator 2009-03-11T23:59:06
#
#-------------------------------------------------

QT       -= gui

TARGET = PlainTextExtractorTest
CONFIG   += console debug
CONFIG   -= app_bundle
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
TEMPLATE = app
LIBS += -static \
            -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -lSearch \
            -lChardet \
            -lCommon \
            -llibboost_thread-mt \
            -llibboost_signals-mt \
            -llibboost_system-mt


SOURCES += main.cc
