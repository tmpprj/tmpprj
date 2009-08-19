# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Common
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib
SOURCES += src/log.cc \
           src/settings.cc \
           src/common.cc \
           src/common_conf.cc
HEADERS += include/log.h \
           include/mt_queue.hpp \
           include/singleton.hpp \
           include/settings.h \
           include/common.h \
           src/common_conf.h
INCLUDEPATH += ../external/boost \
    ./include 
