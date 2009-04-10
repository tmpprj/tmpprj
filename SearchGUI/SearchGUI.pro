TARGET = SearchGUI
DESTDIR = ../bin
TEMPLATE = app
POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a
CONFIG += debug
SOURCES += src/main.cc \
           src/window.cc
HEADERS += ./src/window.h
DEPENDPATH += ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include 
INCLUDEPATH += ../external/boost \
    ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include
