# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Search
DESTDIR = ../lib
TEMPLATE = lib
POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a \
    ../lib/libPdf.a
CONFIG += no_keywords staticlib
SOURCES += src/filesearcher.cc \
    src/searchfacade.cc \
    src/plaintextextractor.cc \
    src/txttextextractor.cc \
    src/multipatternsearcher.cc \
    src/patternmatcher.cc \
    src/mswordtextextractor.cc \
    src/pdftextextractor.cc \
    src/settings.cc \
    src/qsearchfacade.cc
HEADERS += ./include/searchfacade.h \
    ./include/searchdefines.h \
    ./include/filesearcher.h \
    include/plaintextextractor.h \
    include/txttextextractor.h \
    include/multipatternsearcher.h \
    include/patternmatcher.h \
    include/mswordtextextractor.h \
    include/pdftextextractor.h \
    include/settings.h \
    include/datahandler.hpp \
    include/qsearchfacade.h
DEPENDPATH += ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include
INCLUDEPATH += ../external/boost \
    ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libPdf/include
