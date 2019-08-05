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

#include "JsonAssist.h"

double
JsonAssist::getJSONNumber(const char* memberName,
                          jsonMemberTypes memberType,
                          string errorComplement)
{
  if ( jsonDoc.HasMember( memberName ) == false )
  {
    if ( memberType == mandatory ) {
      string exceptionMsgThrown;
      exceptionMsgThrown.append("[ERROR] ");
      exceptionMsgThrown.append("Could not find member \"");
      exceptionMsgThrown.append(memberName);
      exceptionMsgThrown.append("\" in JSON document ");
      exceptionMsgThrown.append(fileName);
      exceptionMsgThrown.append("!\n");
      exceptionMsgThrown.append("Member ");
      exceptionMsgThrown.append(memberName);
      if (errorComplement.empty()) {
        exceptionMsgThrown.append(" is always mandatory.");
      }
      else {
        exceptionMsgThrown.append(" is mandatory in this case because ");
        exceptionMsgThrown.append(errorComplement);
        exceptionMsgThrown.append(".");
      }
      throw exceptionMsgThrown;
    }
    else if ( memberType == optional ) {
      return INVALID_DOUBLE;
    }
  }
  if ( jsonDoc[ memberName ].IsNumber() == false )
  {
    string exceptionMsgThrown;
    exceptionMsgThrown.append("[ERROR] ");
    exceptionMsgThrown.append("Member \"");
    exceptionMsgThrown.append(memberName);
    exceptionMsgThrown.append("\" in JSON document ");
    exceptionMsgThrown.append(fileName);
    exceptionMsgThrown.append(" is expected to be a number!\n");
    throw exceptionMsgThrown;
  }

  return jsonDoc[ memberName ].GetDouble();
}

string
JsonAssist::getJSONString(const char* memberName,
                          jsonMemberTypes memberType,
                          string errorComplement)
{
  if ( jsonDoc.HasMember( memberName ) == false )
  {
    if ( memberType == mandatory ) {
      string exceptionMsgThrown;
      exceptionMsgThrown.append("[ERROR] ");
      exceptionMsgThrown.append("Could not find member \"");
      exceptionMsgThrown.append(memberName);
      exceptionMsgThrown.append("\" in JSON document ");
      exceptionMsgThrown.append(fileName);
      exceptionMsgThrown.append("!\n");
      exceptionMsgThrown.append("Member ");
      exceptionMsgThrown.append(memberName);
      if (errorComplement.empty()) {
        exceptionMsgThrown.append(" is always mandatory.");
      }
      else {
        exceptionMsgThrown.append(" is mandatory in this case because ");
        exceptionMsgThrown.append(errorComplement);
        exceptionMsgThrown.append(".");
      }
      throw exceptionMsgThrown;
    }
    else if ( memberType == optional ) {
      return INVALID_STRING;
    }
  }
  if ( jsonDoc[ memberName ].IsString() == false )
  {
    string exceptionMsgThrown;
    exceptionMsgThrown.append("[ERROR] ");
    exceptionMsgThrown.append("Member \"");
    exceptionMsgThrown.append(memberName);
    exceptionMsgThrown.append("\" in JSON document ");
    exceptionMsgThrown.append(fileName);
    exceptionMsgThrown.append(" is expected to be a string!\n");
    throw exceptionMsgThrown;
  }

  return jsonDoc[ memberName ].GetString();
}

void 
JsonAssist::buildJsonDoc(const char* fileName_)
{

  fileName = fileName_;
  ifstream file(fileName);
  if ( file.is_open() == false ) {
    string exceptionMsgThrown;
    exceptionMsgThrown.append("[ERROR] ");
    exceptionMsgThrown.append("Could not open file: ");
    exceptionMsgThrown.append(fileName);
    exceptionMsgThrown.append("!\n");
    throw exceptionMsgThrown;
  }

  // Find length of the file
  int fileLength;
  file.seekg(0, ios::end);
  fileLength = file.tellg();
  file.seekg(0, ios::beg);

  // Create an internal copy as a C-style string
  char* fileText = new char[fileLength + 1];
  file.read(fileText, fileLength);
  fileText[ fileLength ] = '\0';

  // Close the file
  file.close();

  // Parse the file as a JSON Document
  jsonDoc.Parse(fileText);
  if ( jsonDoc.HasParseError() ) {
    string exceptionMsgThrown;
    exceptionMsgThrown.append("[ERROR] ");
    exceptionMsgThrown.append("Could not parse ");
    exceptionMsgThrown.append(fileName);
    exceptionMsgThrown.append(" as a JSON document.\n");
    delete[] fileText;
    throw exceptionMsgThrown;
  }

  delete[] fileText;

}

JsonAssist::JsonAssist(const char* fileName)
{
  try {
    buildJsonDoc(fileName);
  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }
}

JsonAssist::JsonAssist()
{}
