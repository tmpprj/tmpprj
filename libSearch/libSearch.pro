# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Search
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib \
    debug
SOURCES += src/filesearcher.cc \
    src/searchfacade.cc \
    src/plaintextextractor.cc \
    src/txttextextractor.cc
HEADERS += ./include/searchfacade.h \
    ./include/searchdefines.h \
    ./include/filesearcher.h \
    include/plaintextextractor.h \
    include/txttextextractor.h
INCLUDEPATH += ../external/boost \
    ./include \
    ../libCommon/include \
    ../libChardet/include

LIBS += -L../lib \
        -Wl,-Bstatic \
        -lChardet \
        -Wl,-Bdynamic
