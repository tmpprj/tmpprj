TARGET = SearchGUI
DESTDIR = ../bin
TEMPLATE = app
POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a \
    ../lib/libPdf.a
CONFIG += no_keywords
SOURCES += ./src/main.cc \
           ./src/qsearchwindow.cc \
           ./src/qsettingswindow.cc \
           ./src/qfilestable.cc \
           ./src/qsettingstable.cc \
           ./src/qjournalwindow.cc
HEADERS += ./src/qsearchwindow.h \
           ./src/qsettingswindow.h \
           ./src/qfilestable.h \
           ./src/qsettingstable.h \ 
           ./src/qjournalwindow.h
FORMS += ./src/searchwindow.ui \
         ./src/settingswindow.ui \
         ./src/journalwindow.ui
DEPENDPATH += ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include 
RESOURCES += ../libMsWord/charsets.qrc
INCLUDEPATH += ../external/boost \
    ./include \
    ./src \
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
            -lMsWord \
            -lCommon \
            -lPdf \
            -lboost_thread-mt \
            -lboost_signals-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic 

