# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = Search
TEMPLATE = app
CONFIG += console
SOURCES += searchtst.cc
INCLUDEPATH += /home/bolotin/projects/antispam/external/boost ../
LIBS += -L../ -lSearch -L/home/bolotin/projects/antispam/external/boost/stage/lib -lboost_thread-mt
DEPENDPATH += ../
