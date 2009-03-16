# -------------------------------------------------
# Project created by QtCreator 2009-03-16T22:23:45
# -------------------------------------------------
QT -= core \
    gui
TARGET = MsWord
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ./include
SOURCES += src/mswordextractor.cpp \
    src/xlsparse.c \
    src/xls2csv.c \
    src/writer.c \
    src/substmap.c \
    src/strftime.c \
    src/sheet.c \
    src/rtfread.c \
    src/reader.c \
    src/pptparse.c \
    src/ole.c \
    src/numutils.c \
    src/langinfo.c \
    src/fileutil.c \
    src/confutil.c \
    src/charsets.c \
    src/catppt.c \
    src/catdoc.c \
    src/analyze.c
HEADERS += include/mswordextractor.h \
    include/xltypes.h \
    include/xls.h \
    include/unistd.h \
    include/strftime.h \
    include/ppttypes.h \
    include/ppt.h \
    include/ole.h \
    include/langinfo.h \
    include/catdoc.h
