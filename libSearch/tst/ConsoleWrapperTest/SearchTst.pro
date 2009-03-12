# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
TARGET = SearchTest
TEMPLATE = app
CONFIG += console debug
SOURCES += searchtst.cc
INCLUDEPATH += ../../external/boost ../include ../../libCommon/include
LIBS += -static -L../ \
                -L../../external/boost/stage/lib \
                 ../debug/libSearch.a \
                 -llibboost_thread-mt \
                 -llibboost_signals-mt \
                 -llibboost_system-mt \
                 ../../libChardet/debug/libChardet.a
