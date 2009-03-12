# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
QT -= core \
    gui
TARGET = Chardet
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += ../external/boost \
                ./include
SOURCES += src/charsetdetector.cc \
    src/nsUTF8Prober.cpp \
    src/nsUniversalDetector.cpp \
    src/nsSJISProber.cpp \
    src/nsSBCSGroupProber.cpp \
    src/nsSBCharSetProber.cpp \
    src/nsMBCSSM.cpp \
    src/nsMBCSGroupProber.cpp \
    src/nsLatin1Prober.cpp \
    src/nsHebrewProber.cpp \
    src/nsGB2312Prober.cpp \
    src/nsEUCTWProber.cpp \
    src/nsEUCKRProber.cpp \
    src/nsEUCJPProber.cpp \
    src/nsEscSM.cpp \
    src/nsEscCharsetProber.cpp \
    src/nsCharSetProber.cpp \
    src/nsBig5Prober.cpp \
    src/LangThaiModel.cpp \
    src/LangHungarianModel.cpp \
    src/LangHebrewModel.cpp \
    src/LangGreekModel.cpp \
    src/LangCyrillicModel.cpp \
    src/LangBulgarianModel.cpp \
    src/JpCntx.cpp \
    src/CharDistribution.cpp
HEADERS += include/charsetdetector.h \
    include/prtypes.h \
    include/nsUTF8Prober.h \
    include/nsUniversalDetector.h \
    include/nsSJISProber.h \
    include/nsSBCSGroupProber.h \
    include/nsSBCharSetProber.h \
    include/nsPkgInt.h \
    include/nsMBCSGroupProber.h \
    include/nsLatin1Prober.h \
    include/nsHebrewProber.h \
    include/nsGB2312Prober.h \
    include/nsEUCTWProber.h \
    include/nsEUCKRProber.h \
    include/nsEUCJPProber.h \
    include/nsEscCharsetProber.h \
    include/nsCodingStateMachine.h \
    include/nsCharSetProber.h \
    include/nsBig5Prober.h \
    include/JpCntx.h \
    include/CharDistribution.h
OTHER_FILES += src/Makefile.in \
    src/JISFreq.tab \
    src/GB2312Freq.tab \
    src/EUCTWFreq.tab \
    src/EUCKRFreq.tab \
    src/Big5Freq.tab
