TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = \
	libCommon\
    libCommon/tst/unit_tests \
    libChardet \
    libMsWord \
    libMsWord/tst/DocExtractorTest \
    libMsWord/tst/XlsExtractorTest \
    libMsWord/tst/PptExtractorTest \
    libPdf \
    libPdf/tst/PdfExtractorTest \
    libSearch \
    libSearch/tst/PlainTextExtractorTest \
    SearchGUI

          
