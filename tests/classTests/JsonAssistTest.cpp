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



#ifndef JSONASSISTTEST_CPP
#define JSONASSISTTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../parser/JsonAssist.h"

using namespace std;

BOOST_AUTO_TEST_SUITE( testJsonAssist )

BOOST_AUTO_TEST_CASE( checkJsonBuild_badfiles )
{

  JsonAssist jsonAssist;

  char* fileName = "../../tests/cells/not_test_cell.json";

  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not open file: ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append("!\n");

  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    jsonAssist = JsonAssist(fileName);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist builder"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  fileName = "../../tests/cells/test_cell.notjson";

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not parse ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append(" as a JSON document.\n");

  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    jsonAssist = JsonAssist(fileName);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist builder"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkJsonBuild_badvalues )
{

  JsonAssist jsonAssist;

  char* fileName = "../../tests/cells/test_cell_badvalues.json";

  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;

  try {
    jsonAssist = JsonAssist(fileName);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist builder"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Member \"");
  expectedThrownMsg.append("Cell set voltage [V]");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append(" is expected to be a number!\n");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONNumber("Cell set voltage [V]", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Member \"");
  expectedThrownMsg.append("Selector model []");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append(" is expected to be a string!\n");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONString("Selector model []", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append("!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append(" is always mandatory.");
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONNumber("Not a member", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append("!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append(" is mandatory in this case because ");
  expectedThrownMsg.append("reasons");
  expectedThrownMsg.append(".");
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONNumber("Not a member", mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append("!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append(" is always mandatory.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONString("Not a member", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append(fileName);
  expectedThrownMsg.append("!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append("Not a member");
  expectedThrownMsg.append(" is mandatory in this case because ");
  expectedThrownMsg.append("reasons");
  expectedThrownMsg.append(".");
  exceptionMsg.append("No exception.");
  try {
    jsonAssist.getJSONString("Not a member", mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
}

BOOST_AUTO_TEST_CASE( checkJson_nonmemberErrors )
{

  JsonAssist jsonAssist;

  char* fileName = "../../tests/cells/test_json.json";

  string memberName = "No member name";
  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;
  try {
    jsonAssist = JsonAssist(fileName);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist builder"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  double expectedDouble = INVALID_DOUBLE;
  double gotDouble = INVALID_DOUBLE;

  memberName = "Mandatory numeric non-member";
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append("../../tests/cells/test_json.json!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append(" is always mandatory.");
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber(memberName.c_str(), mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = INVALID_DOUBLE;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  memberName = "Mandatory by reasons numeric non-member";
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append("../../tests/cells/test_json.json!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append(" is mandatory in this case because reasons.");
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber(memberName.c_str(), mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = INVALID_DOUBLE;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  memberName = "Optional numeric non-member";
  expectedThrownMsg = "No exception.";
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber(memberName.c_str(), optional);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = INVALID_DOUBLE;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);



  string expectedStr = INVALID_STRING;
  string gotStr = INVALID_STRING;

  memberName = "Mandatory text non-member";
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append("../../tests/cells/test_json.json!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append(" is always mandatory.");
  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString(memberName.c_str(), mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = INVALID_STRING;
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

  memberName = "Mandatory by reasons text non-member";
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Could not find member \"");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append("\" in JSON document ");
  expectedThrownMsg.append("../../tests/cells/test_json.json!\n");
  expectedThrownMsg.append("Member ");
  expectedThrownMsg.append(memberName);
  expectedThrownMsg.append(" is mandatory in this case because reasons.");
  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString(memberName.c_str(), mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = INVALID_STRING;
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

  memberName = "Optional text non-member";
  expectedThrownMsg = "No exception.";
  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString(memberName.c_str(), optional);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = INVALID_STRING;
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

}

BOOST_AUTO_TEST_CASE( checkJson_getvalues )
{

  JsonAssist jsonAssist;

  char* fileName = "../../tests/cells/test_json.json";

  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;
  try {
    jsonAssist = JsonAssist(fileName);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist builder"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  double expectedDouble = INVALID_DOUBLE;
  double gotDouble = INVALID_DOUBLE;

  expectedThrownMsg = "No exception.";
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber("Mandatory numeric member", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = 2;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  expectedThrownMsg = "No exception.";
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber("Mandatory by reasons numeric member",
                                 mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = 3;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  expectedThrownMsg = "No exception.";
  exceptionMsg = "No exception.";
  try {
    gotDouble =
        jsonAssist.getJSONNumber("Optional numeric member", optional);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedDouble = 4;
  BOOST_CHECK_MESSAGE( gotDouble == expectedDouble,
                      "Value returned from json assist get number"
                       << " different for the expected."
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);



  string expectedStr = INVALID_STRING;
  string gotStr = INVALID_STRING;

  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString("Mandatory text member", mandatory);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = "5";
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString("Mandatory by reasons text member",
                                      mandatory, "reasons");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = "6";
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

  exceptionMsg = "No exception.";
  try {
    gotStr = jsonAssist.getJSONString("Optional text member", optional);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);
  expectedStr = "7";
  BOOST_CHECK_MESSAGE( gotStr == expectedStr,
                      "Value returned from json assist get string"
                       << " different for the expected."
                       << "\nExpected: " << expectedStr
                       << "\nGot: " << gotStr);

}

BOOST_AUTO_TEST_SUITE_END()

#endif // JSONASSISTTEST_CPP
