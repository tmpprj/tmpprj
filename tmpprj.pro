TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = \
	libCommon\
        libChardet \
        libMsWord \
        libMsWord/tst/DocExtractorTest \
        libMsWord/tst/XlsExtractorTest \
        libMsWord/tst/PptExtractorTest \
        libSearch \
	libSearch/tst/ConsoleWrapperTest \
	libSearch/tst/PlainTextExtractorTest \
    SearchGUI

              
