# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Common
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib
SOURCES += src/globwrap.cc \
           src/log.cc \
           src/settings.cc \
           src/common.cc
HEADERS += include/globwrap.h \
           include/log.hpp \
           include/mt_queue.hpp \
           include/singleton.hpp \
           include/settings.h \
           include/common.h
INCLUDEPATH += ../external/boost \
    ./include 
