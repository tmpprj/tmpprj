# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = SearchTest
TEMPLATE = app
POST_TARGETDEPS += ../../../lib/libMsWord.a ../../../lib/libSearch.a ../../../lib/libChardet.a ../../../lib/libCommon.a
CONFIG += console debug
SOURCES += searchtst.cc
DEPENDPATH +=  ../../include ../../../libCommon/include
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
RESOURCES += ../../../libMsWord/charsets.qrc
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lChardet \
            -lCommon \
            -lMsWord \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 
            
