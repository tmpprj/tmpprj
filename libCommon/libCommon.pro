# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Common
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib
SOURCES += src/globwrap.cc src/log.cc
HEADERS += ./include/globwrap.h
INCLUDEPATH += ../external/boost \
    ./include 
