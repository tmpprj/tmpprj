TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = \
	libCommon\
        libChardet \
        libMsWord \
        libMsWord/tst/DocExtractorTest \
        libMsWord/tst/XlsExtractorTest \
        libMsWord/tst/PptExtractorTest \
        libPdf \
        libPdf/tst/PdfExtractorTest \
        libSearch \
	libSearch/tst/ConsoleWrapperTest \
	libSearch/tst/PlainTextExtractorTest \
	SearchGUI

              
