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



#include "ArgumentsParser.h"

using namespace std;

ArgumentsParser::ArgumentsParser(int argc, char** argv)
{
  cpargc = argc;
  for ( int it = 0; it < argc; it++ ) {
    cpargv.push_back(argv[it]);
  }
  argvID = 1;
  nConfigurations = 0;
  IOTerminationCurrentFlag = false;
  printAllVariables = false;
}

void ArgumentsParser::runArgParser()
{
  if ( argvID >= cpargc ) {
    // Help run (no arguments)
    if ( cpargc == 1 ) {
      helpStrStream << helpMessage;
    }
    // Or end of parsing
    return;
  }

  // Help run (by argument)
  if ( cpargv[argvID] == "-h" ) {
    helpStrStream << helpMessage;
    return;
  }

  // Normal run
  bool badArgumentFlag = false;
  if( cpargv[argvID] == "-conf" ) {
    argvID++;
    if( readConfFileName() == false ) {
      badArgumentFlag = true;
    }
  }
  else if( cpargv[argvID] == "-cell" ) {
    argvID++; 
    if( storeCellFileName() == false ) {
      badArgumentFlag = true;
    }
  }
  else if( cpargv[argvID] == "-tech" ) {
    argvID++;
    if( storeTechFileName() == false ) {
      badArgumentFlag = true;
    }
  }
  else if( cpargv[argvID] == "-arch" ) {
    argvID++;
    if( storeArchFileName() == false ) {
      badArgumentFlag = true;
    }
  }
  else if( cpargv[argvID] == "-term" ) {
    IOTerminationCurrentFlag = true;
    argvID++;
    runArgParser();
  }
  else if( cpargv[argvID] == "-printAll") {
    printAllVariables = true;
    argvID++;
    runArgParser();
  }
  else {
    badArgumentFlag = true;
  }

  if ( badArgumentFlag == true ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected argument \'");
    exceptionMsgThrown.append(cpargv[argvID]);
    exceptionMsgThrown.append("\'\n");
    exceptionMsgThrown.append(helpMessage);
    throw exceptionMsgThrown;
  }

  if( cellFileNames.size() == techFileNames.size()
      && cellFileNames.size() == archFileNames.size() )
  {
    nConfigurations = cellFileNames.size();
  }
  else  {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Number of cell files (");
    exceptionMsgThrown.append(to_string(cellFileNames.size()));
    exceptionMsgThrown.append(") is different from ");
    exceptionMsgThrown.append("the number of technology files (");
    exceptionMsgThrown.append(to_string(techFileNames.size()));
    exceptionMsgThrown.append(") or the number of architecture files (");
    exceptionMsgThrown.append(to_string(archFileNames.size()));
    exceptionMsgThrown.append("). Could not proceed.");
    throw exceptionMsgThrown;
  }

  if ( nConfigurations == 0 ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("No input file provided!\n");
    exceptionMsgThrown.append(helpMessage);
    throw exceptionMsgThrown;
  }

  for (size_t configIt = 0; configIt < nConfigurations; ++configIt) {
    Config config;
    config.cellFileName = cellFileNames.at(configIt);
    config.techFileName = techFileNames.at(configIt);
    config.archFileName = archFileNames.at(configIt);

    configs.push_back(config);
  }

}

bool ArgumentsParser::readConfFileName()
{
  while (argvID < cpargc) {

    if( cpargv[argvID] == "-cell") {
      argvID++;
      return storeCellFileName();
    }
    else if( cpargv[argvID] == "-tech") {
      argvID++;
      return storeTechFileName();
    }
    else if( cpargv[argvID] == "-arch") {
      argvID++;
      return storeArchFileName();
    }
    else if( cpargv[argvID] == "-term") {
      IOTerminationCurrentFlag = true;
      argvID++;
      return readConfFileName();
    }
    else if( cpargv[argvID] == "-printAll") {
      printAllVariables = true;
      argvID++;
      return readConfFileName();
    }
    else if (cpargv[argvID][0] == '-') {
      return false;
    }
    else {
      ifstream confFile;
      confFile.open(cpargv[argvID]);
      if ( confFile.is_open() == false ) {
        string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Could not find the configuration file: ");
        exceptionMsgThrown.append(cpargv[argvID]);
        exceptionMsgThrown.append("\n");
        throw exceptionMsgThrown;
      }

      string arg;
      while ( confFile >> arg ) {
        cpargv.push_back( arg );
        cpargc++;
      }
      confFile.close();

      argvID++;
      return readConfFileName();
    }

    argvID++;
  }

  return true;
}

bool ArgumentsParser::storeCellFileName()
{
  while (argvID < cpargc) {

    if( cpargv[argvID] == "-conf") {
      argvID++;
      return readConfFileName();
    }
    else if( cpargv[argvID] == "-tech") {
      argvID++;
      return storeTechFileName();
    }
    else if( cpargv[argvID] == "-arch") {
      argvID++;
      return storeArchFileName();
    }
    else if( cpargv[argvID] == "-term") {
      IOTerminationCurrentFlag = true;
      argvID++;
      return storeCellFileName();
    }
    else if( cpargv[argvID] == "-printAll") {
      printAllVariables = true;
      argvID++;
      return storeCellFileName();
    }
    else if (cpargv[argvID][0] == '-') {
      return false;
    }
    else {
      cellFileNames.push_back(cpargv[argvID]);
      argvID++;
      return storeCellFileName();
    }

    argvID++;
  }

  return true;
}

bool ArgumentsParser::storeTechFileName()
{
  while (argvID < cpargc) {

    if( cpargv[argvID] == "-conf") {
      argvID++;
      return readConfFileName();
    }
    else if( cpargv[argvID] == "-cell") {
      argvID++;
      return storeCellFileName();
    }
    else if( cpargv[argvID] == "-arch") {
      argvID++;
      return storeArchFileName();
    }
    else if( cpargv[argvID] == "-term") {
      IOTerminationCurrentFlag = true;
      argvID++;
      return storeTechFileName();
    }
    else if( cpargv[argvID] == "-printAll") {
      printAllVariables = true;
      argvID++;
      return storeTechFileName();
    }
    else if (cpargv[argvID][0] == '-') {
      return false;
    }
    else {
      techFileNames.push_back(cpargv[argvID]);
      argvID++;
      return storeTechFileName();
    }

    argvID++;
  }

  return true;
}

bool ArgumentsParser::storeArchFileName()
{
  while (argvID < cpargc) {

    if( cpargv[argvID] == "-conf") {
      argvID++;
      return readConfFileName();
    }
    else if( cpargv[argvID] == "-cell") {
      argvID++;
      return storeCellFileName();
    }
    else if( cpargv[argvID] == "-tech") {
      argvID++;
      return storeTechFileName();
    }
    else if( cpargv[argvID] == "-term") {
      IOTerminationCurrentFlag = true;
      argvID++;
      return storeArchFileName();
    }
    else if( cpargv[argvID] == "-printAll") {
      printAllVariables = true;
      argvID++;
      return storeArchFileName();
    }
    else if (cpargv[argvID][0] == '-') {
      return false;
    }
    else {
      archFileNames.push_back(cpargv[argvID]);
      argvID++;
      return storeArchFileName();
    }

    argvID++;
  }

  return true;
}
