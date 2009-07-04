TARGET = UnitTest++
DESTDIR = ./
TEMPLATE = lib
CONFIG += staticlib
SOURCES += src/TestReporterStdout.cpp \
        src/Win32/TimeHelpers.cpp \
        src/DeferredTestReporter.cpp \
        src/TimeConstraint.cpp \
        src/ReportAssert.cpp \
        src/MemoryOutStream.cpp \
        src/AssertException.cpp \
        src/XmlTestReporter.cpp \
        src/TestDetails.cpp \
        src/TestResults.cpp \
        src/TestList.cpp \
        src/Test.cpp \
        src/TestRunner.cpp \
        src/TestReporter.cpp \
        src/Checks.cpp \
        src/DeferredTestResult.cpp \
        src/CurrentTest.cpp

HEADERS += src/XmlTestReporter.h \
        src/CurrentTest.h \
        src/TestSuite.h \
        src/Win32/TimeHelpers.h \
        src/tests/ScopedCurrentTest.h \
        src/tests/RecordingReporter.h \
        src/TestMacros.h \
        src/AssertException.h \
        src/MemoryOutStream.h \
        src/Config.h \
        src/DeferredTestReporter.h \
        src/ExecuteTest.h \
        src/TestRunner.h \
        src/UnitTest++.h \
        src/ReportAssert.h \
        src/DeferredTestResult.h \
        src/TestReporterStdout.h \
        src/TimeConstraint.h \
        src/TimeHelpers.h \
        src/TestResults.h \
        src/TestReporter.h \
        src/Test.h \
        src/TestDetails.h \
        src/TestList.h \
        src/Checks.h \
        src/CheckMacros.h
