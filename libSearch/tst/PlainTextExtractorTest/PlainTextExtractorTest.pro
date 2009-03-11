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
LIBS += -static -L../../../external/boost/stage/lib \
                 ../../debug/libSearch.a \
                 -llibboost_thread-mt \
                 -llibboost_signals-mt \
                 -llibboost_system-mt \
                 ../../../libChardet/debug/libChardet.a


SOURCES += main.cc
