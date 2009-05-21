# -------------------------------------------------
# Project created by QtCreator 2009-05-14T19:19:34
# -------------------------------------------------
QT -= gui
TARGET = Pdf
TEMPLATE = lib
CONFIG += staticlib debug
DESTDIR = ../lib
POST_TARGETDEPS += ../lib/libCommon.a
DEPENDPATH += ./include \
    ../libCommon/include
INCLUDEPATH += ./include \
    ../libCommon/include \
    ../external/boost
SOURCES += src/XRef.cc \
    src/XPDFTree.cc \
    src/XpdfPluginAPI.cc \
    src/UnicodeTypeTable.cc \
    src/UnicodeMap.cc \
    src/TextOutputDev.cc \
    src/Stream.cc \
    src/SecurityHandler.cc \
    src/PSTokenizer.cc \
    src/PreScanOutputDev.cc \
    src/PDFDocEncoding.cc \
    src/PDFDoc.cc \
    src/Parser.cc \
    src/Page.cc \
    src/OutputDev.cc \
    src/Outline.cc \
    src/Object.cc \
    src/NameToCharCode.cc \
    src/Link.cc \
    src/Lexer.cc \
    src/JPXStream.cc \
    src/JBIG2Stream.cc \
    src/JArithmeticDecoder.cc \
    src/ImageOutputDev.cc \
    src/GString.cc \
    src/gmempp.cc \
    src/gmem.cc \
    src/GlobalParams.cc \
    src/GList.cc \
    src/GHash.cc \
    src/GfxState.cc \
    src/GfxFont.cc \
    src/Gfx.cc \
    src/gfile.cc \
    src/Function.cc \
    src/FontEncodingTables.cc \
    src/FoFiType1C.cc \
    src/FoFiType1.cc \
    src/FoFiTrueType.cc \
    src/FoFiEncodings.cc \
    src/FoFiBase.cc \
    src/FixedPoint.cc \
    src/Error.cc \
    src/Dict.cc \
    src/Decrypt.cc \
    src/CMap.cc \
    src/CharCodeToUnicode.cc \
    src/Catalog.cc \
    src/BuiltinFontTables.cc \
    src/BuiltinFont.cc \
    src/Array.cc \
    src/Annot.cc \
    src/pdfextractor.cc
HEADERS += include/XRef.h \
    include/XPDFTreeP.h \
    include/XPDFTree.h \
    include/XpdfPluginAPI.h \
    include/vms_unix_time.h \
    include/vms_sys_dirent.h \
    include/vms_dirent.h \
    include/UTF8.h \
    include/UnicodeTypeTable.h \
    include/UnicodeMapTables.h \
    include/UnicodeMap.h \
    include/TextOutputDev.h \
    include/Stream-CCITT.h \
    include/Stream.h \
    include/SecurityHandler.h \
    include/PSTokenizer.h \
    include/PreScanOutputDev.h \
    include/PDFDocEncoding.h \
    include/PDFDoc.h \
    include/Parser.h \
    include/parseargs.h \
    include/Page.h \
    include/OutputDev.h \
    include/Outline.h \
    include/Object.h \
    include/NameToUnicodeTable.h \
    include/NameToCharCode.h \
    include/Link.h \
    include/Lexer.h \
    include/JPXStream.h \
    include/JBIG2Stream.h \
    include/JArithmeticDecoder.h \
    include/ImageOutputDev.h \
    include/gtypes.h \
    include/GString.h \
    include/GMutex.h \
    include/gmem.h \
    include/GlobalParams.h \
    include/GList.h \
    include/GHash.h \
    include/GfxState.h \
    include/GfxFont.h \
    include/Gfx.h \
    include/gfile.h \
    include/Function.h \
    include/FontEncodingTables.h \
    include/FoFiType1C.h \
    include/FoFiType1.h \
    include/FoFiTrueType.h \
    include/FoFiEncodings.h \
    include/FoFiBase.h \
    include/FixedPoint.h \
    include/ErrorCodes.h \
    include/Error.h \
    include/Dict.h \
    include/Decrypt.h \
    include/config.h \
    include/CompactFontTables.h \
    include/CMap.h \
    include/CharTypes.h \
    include/CharCodeToUnicode.h \
    include/Catalog.h \
    include/BuiltinFontTables.h \
    include/BuiltinFont.h \
    include/Array.h \
    include/Annot.h \
    include/aconf2.h \
    include/aconf.h \
    include/about-text.h \
    include/pdfextractor.h
