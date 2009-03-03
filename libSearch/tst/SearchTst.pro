# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = SearchTest
TEMPLATE = app
CONFIG += console debug
SOURCES += searchtst.cc
INCLUDEPATH += /home/bolotin/projects/antispam/external/boost ../include ../../libCommon/include
LIBS += -L../ -lSearch -L/home/bolotin/projects/antispam/external/boost/stage/lib /home/bolotin/projects/antispam/external/boost/stage/lib/libboost_thread-mt.a /home/bolotin/projects/antispam/external/boost/stage/lib/libboost_signals-mt.a

DEPENDPATH += ../
