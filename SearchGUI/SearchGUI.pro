TARGET = SearchGUI
DESTDIR = ../bin
TEMPLATE = app
POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a \
    ../lib/libPdf.a
CONFIG += debug no_keywords
SOURCES += src/main.cc \
           src/window.cc \
           src/filestable.cc
HEADERS += ./src/window.h \
           ./src/filestable.h
DEPENDPATH += ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include 
RESOURCES += ../libMsWord/charsets.qrc
INCLUDEPATH += ../external/boost \
    ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include
LIBS +=     -L../ \
            -L../lib \
            -L../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lChardet \
            -lCommon \
            -lMsWord \
            -lPdf \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 

