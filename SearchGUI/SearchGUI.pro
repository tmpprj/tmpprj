TARGET = SearchGUI
DESTDIR = ../bin
TEMPLATE = app
unix:POST_TARGETDEPS += ../lib/libChardet.a \
    ../lib/libCommon.a \
    ../lib/libMsWord.a \
    ../lib/libPdf.a
win32:POST_TARGETDEPS += ../lib/Chardet.lib \
    ../lib/Common.lib \
    ../lib/MsWord.lib \
    ../lib/Pdf.lib
CONFIG += no_keywords
SOURCES += ./src/main.cc \
    ./src/qsearchwindow.cc \
    ./src/qsettingswindow.cc \
    ./src/qfilestable.cc \
    ./src/qsettingstable.cc \
    ./src/guicommon.cc \
    ./src/searchgui_conf.cc \
    ./src/contextmenu.cc \
    ./src/qcomboboxext.cc \
    ../CustomWidgets/src/qrollframe.cc \
    ./src/qaboutdialog.cc \
    ./src/qregisterdialog.cc
HEADERS += ./src/qsearchwindow.h \
    ./src/qsettingswindow.h \
    ./src/qfilestable.h \
    ./src/qsettingstable.h \
    ./src/guicommon.h \
    ./src/searchgui_conf.h \
    ./src/contextmenu.h \
    ./src/menuwrapper.hpp \
    ./src/comwrapper.hpp \
    ./src/qcomboboxext.h \
    ../CustomWidgets/include/qrollframe.h \
    ./src/qaboutdialog.h \
    ./src/qregisterdialog.h
FORMS += ./src/searchwindow.ui \
    ./src/settingswindow.ui \
    ./src/aboutdialog.ui \
    ./src/qregisterdialog.ui
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
    ../libSearch/include \
    ../CustomWidgets/include
QMAKE_LIBDIR += ../external/boost/stage/lib \
    ../lib
unix:LIBS += -Wl,-Bstatic \
    -lSearch \
    -lChardet \
    -lMsWord \
    -lCommon \
    -lPdf \
    -lboost_thread-mt \
    -lboost_system-mt \
    -Wl,-Bdynamic
win32 { 
    INCLUDEPATH += ../ASProtect
    LIBS += Search.lib \
        Common.lib \
        MsWord.lib \
        Chardet.lib \
        Pdf.lib \
        libboost_thread.lib \
        libboost_system.lib \
        ..\ASProtect\aspr_ide.lib
}
DEFINES += REVISION=\"\\\"$$quote( $$system( git tag -l ) )\\\"\"
