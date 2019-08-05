# Copyright (c) 2019, University of Kaiserslautern
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors: Andr'e L. Chinazzo, Deepak M. Mathew, Christian Weis

CONFIG += c++11

mac {
    CONFIG -= app_bundle
    INCLUDEPATH += /opt/boost/include
}

# Path to the newest version of Boost Library
#INCLUDEPATH += /path/to/boost_x_xx_x

#RERAMSpec License
OTHER_FILES += License

#RERAMSpec HEADERS
HEADERS += utils/constants.h
HEADERS += utils/globalStructs.h
HEADERS += utils/functions.h
HEADERS += utils/Param.h

HEADERS += parser/ArgumentsParser.h
HEADERS += parser/JsonAssist.h

HEADERS += core/Cell.h
HEADERS += core/Technology.h
HEADERS += core/XPointArray.h
HEADERS += core/Bank.h

HEADERS += parser/RramSpec.h

HEADERS += expandedBoostUnits/DerivedDimensions/*
HEADERS += expandedBoostUnits/Units/*
HEADERS += expandedBoostUnits/*

#RRAMSpec SOURCE files
SOURCES += utils/functions.cpp
SOURCES += utils/Param.cpp

SOURCES += parser/ArgumentsParser.cpp
SOURCES += parser/JsonAssist.cpp
SOURCES += parser/RramSpec.cpp

SOURCES += core/Cell.cpp
SOURCES += core/Technology.cpp
SOURCES += core/XPointArray.cpp
SOURCES += core/Bank.cpp


#Choose output directories
# and source files to be compiled
# according to the compilation mode
CONFIG(release, debug|release) {
    message(Release build!) #See messege at "General Messages" tab
    DESTDIR = build/release
    OBJECTS_DIR = build/release/.obj
    MOC_DIR = build/release/.moc
    RCC_DIR = build/release/.rcc
    UI_DIR = build/release/.ui

    QMAKE_CXXFLAGS += -Wextra -Wall

    SOURCES += main.cpp

    TARGET = rramspec
}

CONFIG(debug, debug|release) {
    message(Debug build!) #See messege at "General Messages" tab
    DESTDIR = build/debug
    OBJECTS_DIR = build/debug/.obj
    MOC_DIR = build/debug/.moc
    RCC_DIR = build/debug/.rcc
    UI_DIR = build/debug/.ui

    QMAKE_CXXFLAGS += -w

    #UNIT TEST using Boost/Test HEADERS and SOURCE files // Degub only
    SOURCES += tests/classTests/FunctionsTest.cpp
    SOURCES += tests/classTests/ParamTest.cpp

    SOURCES += tests/classTests/ArgumentsParserTest.cpp
    SOURCES += tests/classTests/JsonAssistTest.cpp

    SOURCES += tests/classTests/CellTest.cpp
    SOURCES += tests/classTests/TechnologyTest.cpp
    SOURCES += tests/classTests/XPointArrayTest.cpp

    SOURCES += tests/testsRunner.cpp

    OTHER_FILES += tests/configs/*
    OTHER_FILES += tests/cells/*
    OTHER_FILES += tests/techs/*
    OTHER_FILES += tests/archs/*

    TARGET = rramspec_test

}


OTHER_FILES += configs/*
OTHER_FILES += cells/*
OTHER_FILES += techs/*
OTHER_FILES += archs/*

OTHER_FILES += .gitignore
OTHER_FILES += .gitmodules
OTHER_FILES += Makefile
OTHER_FILES += README.md
OTHER_FILES += runTests.sh
OTHER_FILES += buildRRAMSpec.sh
