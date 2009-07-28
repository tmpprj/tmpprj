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
    ./src/guicommon.cc \
    ./src/searchgui_conf.cc \
    ./src/contextmenu.cc
HEADERS += ./src/qsearchwindow.h \
    ./src/qsettingswindow.h \
    ./src/qfilestable.h \
    ./src/qsettingstable.h \
    ./src/guicommon.h \
    ./src/searchgui_conf.h \
    ./src/contextmenu.h \
    src/menuwrapper.hpp \
    src/comwrapper.hpp
FORMS += ./src/searchwindow.ui \
    ./src/settingswindow.ui
DEPENDPATH += ./include \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include
RESOURCES += ../libMsWord/charsets.qrc \
    res/SearchGUI.qrc
INCLUDEPATH += ../external/boost \
    ./include \
    ./src \
    ../libCommon/include \
    ../libChardet/include \
    ../libMsWord/include \
    ../libSearch/include
LIBS += -L../ \
    -L../lib \
    -L../external/boost/stage/lib \
    -Wl,-Bstatic \
    -lSearch \
    -lChardet \
    -lMsWord \
    -lCommon \
    -lPdf \
    -lboost_thread-mt \
    -lboost_system-mt \
    -Wl,-Bdynamic
DEFINES += REVISION=\"\\\"$$quote( $$system( git tag -l ) )\\\"\"
