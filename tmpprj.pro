TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = \
	libCommon\
        libChardet \
        libMsWord \
        libMsWord/tst/DocExtractorTest \
        libSearch \
	libSearch/tst/ConsoleWrapperTest \
	libSearch/tst/PlainTextExtractorTest

              
