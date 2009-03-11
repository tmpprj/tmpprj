# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = SearchTest
TEMPLATE = app
CONFIG += console debug
SOURCES += searchtst.cc
INCLUDEPATH += ../../external/boost ../include ../../libCommon/include
LIBS += -L../ -lSearch -L../../external/boost/stage/lib ../../external/boost/stage/lib/libboost_thread-mt.a ../../external/boost/stage/lib/libboost_signals-mt.a ../../external/boost/stage/lib/libboost_system-mt.a
