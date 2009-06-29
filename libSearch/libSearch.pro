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
    src/qsearchfacade.cc \
    src/libsearch_common.cc \
    src/search_conf.cc
HEADERS += ./include/searchfacade.h \
    ./include/filesearcher.h \
    include/plaintextextractor.h \
    include/txttextextractor.h \
    include/multipatternsearcher.h \
    include/patternmatcher.h \
    include/mswordtextextractor.h \
    include/pdftextextractor.h \
    include/datahandler.hpp \
    include/qsearchfacade.h \
    src/libsearch_common.h \
    src/search_conf.h
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
