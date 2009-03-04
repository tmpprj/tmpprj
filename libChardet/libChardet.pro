# -------------------------------------------------
# Project created by QtCreator 2009-03-01T22:56:42
# -------------------------------------------------
QT -= core \
    gui
TARGET = libChardet
TEMPLATE = lib
CONFIG += staticlib
SOURCES += src/ccharsetdetector.cc \
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
HEADERS += src/ccharsetdetector.h \
    src/prtypes.h \
    src/nsUTF8Prober.h \
    src/nsUniversalDetector.h \
    src/nsSJISProber.h \
    src/nsSBCSGroupProber.h \
    src/nsSBCharSetProber.h \
    src/nsPkgInt.h \
    src/nsMBCSGroupProber.h \
    src/nsLatin1Prober.h \
    src/nsHebrewProber.h \
    src/nsGB2312Prober.h \
    src/nsEUCTWProber.h \
    src/nsEUCKRProber.h \
    src/nsEUCJPProber.h \
    src/nsEscCharsetProber.h \
    src/nsCodingStateMachine.h \
    src/nsCharSetProber.h \
    src/nsBig5Prober.h \
    src/JpCntx.h \
    src/CharDistribution.h
OTHER_FILES += src/Makefile.in \
    src/JISFreq.tab \
    src/GB2312Freq.tab \
    src/EUCTWFreq.tab \
    src/EUCKRFreq.tab \
    src/Big5Freq.tab
