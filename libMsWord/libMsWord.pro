# -------------------------------------------------
# Project created by QtCreator 2009-03-16T22:23:45
# -------------------------------------------------
QT -= gui
TARGET = MsWord
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib

unix {
POST_TARGETDEPS += ../lib/libCommon.a
}
win32 {
POST_TARGETDEPS += ../lib/Common.lib
}

DEPENDPATH += ./include \
    ../libCommon/include
INCLUDEPATH += ./include \
    ../libCommon/include \
    ../external/boost
SOURCES += src/mswordextractor.cc \
    src/xlsparse.cc \
    src/writer.cc \
    src/strftime.cc \
    src/sheet.cc \
    src/rtfread.cc \
    src/reader.cc \
    src/pptparse.cc \
    src/ole.cc \
    src/numutils.cc \
    src/langinfo.cc \
    src/fileutil.cc \
    src/charsets.cc \
    src/analyze.cc
HEADERS += include/mswordextractor.h \
    include/xltypes.h \
    include/xls.h \
    include/strftime.h \
    include/ppttypes.h \
    include/ppt.h \
    include/ole.h \
    include/langinfo.h \
    include/catdoc.h
RESOURCES += charsets.qrc

#for msvs 2005
DEFINES += _CRT_SECURE_NO_DEPRECATE
#for msvs 2008
DEFINES += _CRT_SECURE_NO_WARNINGS
