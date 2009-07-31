# -------------------------------------------------
# Project created by QtCreator 2009-07-30T18:01:23
# -------------------------------------------------
QT += core
TARGET = CustomWidgets
TEMPLATE = lib
CONFIG += designer plugin shared 
SOURCES += src/qrollframe.cc \
    src/qrollframeplugin.cc \
    src/qrollframefactory.cc \
    src/qrollframeextension.cc
HEADERS += include/qrollframe.h \
    include/qrollframeplugin.h \
    include/qrollframefactory.h \
    include/qrollframeextension.h
INCLUDEPATH += ./include/
