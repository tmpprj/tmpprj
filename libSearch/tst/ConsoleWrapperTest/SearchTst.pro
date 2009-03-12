# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = SearchTest
TEMPLATE = app
CONFIG += console debug
SOURCES += searchtst.cc
INCLUDEPATH += ../../../external/boost ../../include ../../../libCommon/include
LIBS +=     -L../ \
            -L../../../lib \
            -L../../../external/boost/stage/lib \
            -Wl,-Bstatic \
            -lSearch \
            -lChardet \
            -lCommon \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 
            
