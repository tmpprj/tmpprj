# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Search
DESTDIR = ../lib
TEMPLATE = lib

unix {
POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a \
    ../lib/libPdf.a
}
win32 {
POST_TARGETDEPS += ../lib/Chardet.lib \
    ../lib/Common.lib \
    ../lib/MsWord.lib \
    ../lib/Pdf.lib
}

CONFIG += no_keywords staticlib
SOURCES += src/filesearcher.cc \
    src/searchfacade.cc \
    src/plaintextextractor.cc \
    src/txttextextractor.cc \
    src/multipatternsearcher.cc \
    src/mswordtextextractor.cc \
    src/pdftextextractor.cc \
    src/qsearchfacade.cc \
    src/libsearch_common.cc \
    src/documentchecker.cc \
    src/patterncounter.cc \
    src/search_conf.cc
HEADERS += ./include/searchfacade.h \
    ./include/filesearcher.h \
    include/plaintextextractor.h \
    include/txttextextractor.h \
    include/multipatternsearcher.h \
    include/mswordtextextractor.h \
    include/pdftextextractor.h \
    include/datahandler.hpp \
    include/qsearchfacade.h \
    src/libsearch_common.h \
    include/documentchecker.h \
    include/patterncounter.h \
    src/search_conf.h \
    include/searchoptions.h
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
#for msvs 2005
DEFINES += _CRT_SECURE_NO_DEPRECATE
#for msvs 2008
DEFINES += _CRT_SECURE_NO_WARNINGS
