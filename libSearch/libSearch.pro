# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Search
TEMPLATE = lib
CONFIG += staticlib \
    debug
SOURCES += src/filesearcher.cc \
    src/searchfacade.cc \
    src/cplaintextextractor.cc
HEADERS += ./include/searchfacade.h \
    ./include/searchdefines.h \
    ./include/filesearcher.h \
    include/cplaintextextractor.h
INCLUDEPATH += ../external/boost \
    ./include \
    ../libCommon/include
