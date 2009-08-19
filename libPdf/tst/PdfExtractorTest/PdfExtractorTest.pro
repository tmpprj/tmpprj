#-------------------------------------------------
#
# Project created by QtCreator 2009-05-21T16:46:07
#
#-------------------------------------------------

QT       -= gui

TARGET = PdfExtractorTest
CONFIG   += console
CONFIG   -= app_bundle

unix {
POST_TARGETDEPS += ../../../lib/libPdf.a
}
win32 {
POST_TARGETDEPS += ../../../lib/Pdf.lib
}
DEPENDPATH += ../../include
INCLUDEPATH += ../../include ../../../external/boost
RESOURCES += ../../../libMsWord/charsets.qrc
TEMPLATE = app

QMAKE_LIBDIR += ../../../external/boost/stage/lib ../../../lib
unix {
LIBS +=     -Wl,-Bstatic \
            -lPdf \
            -lCommon \
            -lboost_thread-mt \
            -lboost_system-mt \
            -Wl,-Bdynamic
}
win32 {
LIBS +=     Pdf.lib \
            Common.lib \
            libboost_thread.lib \
            libboost_system.lib
}
SOURCES += main.cpp
