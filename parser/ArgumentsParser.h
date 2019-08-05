/*
 * Copyright (c) 2019, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Andr'e L. Chinazzo, Deepak M. Mathew, Christian Weis
 */


#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Config {
  string cellFileName;
  string techFileName;
  string archFileName;
};

class ArgumentsParser {
public:
  ArgumentsParser(int argc, char** argv);

  vector<Config> configs;
  bool IOTerminationCurrentFlag;
  bool printAllVariables;

  ostringstream helpStrStream;
  const char* helpMessage =
          "  Mandatory:\n"
          "    OR:\n"
          "    -conf    <path/to/configurationfile.json> "
            "(Specify the configuration file containing cell, tech, "
              "and arch description files path to be used.)\n"
          "    OR:\n"
          "    -cell    <path/to/cellfile.json>          "
            "(Specify which technology description file should be used.)\n"
          "    -tech    <path/to/technologyfile.json>    "
            "(Specify which technology description file should be used.)\n"
          "    -arch    <path/to/architecturefile.json>  "
            "(Specify which architecture description file should be used.)\n"
          "  Optional:\n"
          "    -term                                     "
            "(Include IO termination currents for read and write operations.)"
            "\n"
          "    -printAll                                 "
            "(Enable print out of all internal variables.)\n"
          "For more information, see README.md.\n";

  void runArgParser();

private:
  int cpargc;
  vector<string> cpargv;
  int argvID;

  vector<string> cellFileNames;
  vector<string> techFileNames;
  vector<string> archFileNames;
  size_t nConfigurations;

  bool readConfFileName();
  bool storeCellFileName();
  bool storeTechFileName();
  bool storeArchFileName();

};

#endif // ARGUMENTSPARSER_H
