TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = \
	libCommon\
        libChardet \
        libMsWord \
        libMsWord/tst/DocExtractorTest \
        libMsWord/tst/XlsExtractorTest \
        libSearch \
	libSearch/tst/ConsoleWrapperTest \
	libSearch/tst/PlainTextExtractorTest

              
