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



#ifndef CELLTEST_CPP
#define CELLTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../core/Cell.h"

#include "../../parser/ArgumentsParser.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

BOOST_AUTO_TEST_SUITE( testCell )

BOOST_AUTO_TEST_CASE( checkCell_Initialization )
{
  Cell myCell;

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMemDevHRSResistance() ),
                      "Memory device maximum resistance"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMemDevLRSResistance() ),
                      "Memory device minimum resistance"
                      << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMemDevResistanceState() ),
                      "Memory device resistance state"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMemDevInstantResistance() ),
                      "Memory device instant resistance"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelDevModel() ),
                      "Selector device snap voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelDevSnapVoltage() ),
                      "Selector device snap voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelDevLeakageCurrent() ),
                      "Selector device leakage current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelDevMaxCurrent() ),
                      "Selector device maximum current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelVoltageDataPoints().at(0) ),
                      "Selector device voltage data points"
                       << " were not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getSelCurrentDataPoints().at(0) ),
                      "Selector device current data points"
                       << " were not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetVoltage() ),
                      "Cell set voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetCurrent() ),
                      "Cell set current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetComplianceCurrent() ),
                      "Cell set compliance current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetTime() ),
                      "Cell set time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetTimeC() ),
                      "Cell set time C"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellSetTimeK() ),
                      "Cell set time K"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellResetVoltage() ),
                      "Cell reset voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellResetCurrent() ),
                      "Cell reset current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellResetTime() ),
                      "Cell reset time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellResetTimeC() ),
                      "Cell reset time C"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellResetTimeK() ),
                      "Cell reset time K"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellReadVoltage() ),
                      "Cell read voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellReadCurrent() ),
                      "Cell read current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellWidth() ),
                      "Cell width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellHeight() ),
                      "Cell height"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellToCellSpacing() ),
                      "Cell to cell spacing"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getCellThickness() ),
                      "Cell thickness"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMaxCurrentRelativeError() ),
                      "Maximum current relative error"
                       << " was not correctly initialized.");

}

BOOST_AUTO_TEST_CASE( checkCell_Setters_and_Getters )
{
  Cell myCell;

  double expDouble = INVALID_DOUBLE;
  ebool flag_ = INVALID_EBOOL;


  expDouble = 1.;
  myCell.setMemDevHRSResistance( expDouble * rrs::ohms );
  BOOST_CHECK_MESSAGE( myCell.getMemDevHRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device maximum resistance"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevHRSResistance());


  ++expDouble;
  myCell.setMemDevLRSResistance( expDouble * rrs::ohms );
  BOOST_CHECK_MESSAGE( myCell.getMemDevLRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device minimum resistance"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevLRSResistance());


  flag_ = 1;
  myCell.setMemDevResistanceState( flag_ );
  BOOST_CHECK_MESSAGE( myCell.getMemDevResistanceState()
                        == flag_,
                      "Memory device resistance state"
                       << " was not correctly set."
                       << "\nExpected: " << flag_
                       << "\nGot: " << myCell.getMemDevResistanceState());

  // CAREFULL This test depends on the order of tests and value of cell state
  BOOST_CHECK_MESSAGE( myCell.getMemDevInstantResistance()
                        == expDouble * rrs::ohms,
                      "Memory device instant resistance"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevInstantResistance());


  string modelStr = "semiIdeal";
  myCell.setSelDevModel( modelStr, forced );
  BOOST_CHECK_MESSAGE( myCell.getSelDevModel() == modelStr,
                      "Selector device mathematical model"
                       << " was not correctly set."
                       << "\nExpected: " << modelStr
                       << "\nGot: " << myCell.getSelDevModel());

  modelStr = "IxV";
  myCell.setSelDevModel( modelStr, forced );
  BOOST_CHECK_MESSAGE( myCell.getSelDevModel() == modelStr,
                      "Selector device mathematical model"
                       << " was not correctly set."
                       << "\nExpected: " << modelStr
                       << "\nGot: " << myCell.getSelDevModel());

  ++expDouble;
  myCell.setSelDevSnapVoltage( expDouble * rrs::volts );
  BOOST_CHECK_MESSAGE( myCell.getSelDevSnapVoltage()
                        == expDouble * rrs::volts,
                      "Selector device snap voltage"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getSelDevSnapVoltage());


  ++expDouble;
  myCell.setSelDevLeakageCurrent( expDouble * rrs::nanoamperes );
  BOOST_CHECK_MESSAGE( myCell.getSelDevLeakageCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Selector device leakage current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getSelDevLeakageCurrent());


  ++expDouble;
  myCell.setSelDevMaxCurrent( expDouble * rrs::nanoamperes );
  BOOST_CHECK_MESSAGE( myCell.getSelDevMaxCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Selector device maximum current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getSelDevMaxCurrent());


  ++expDouble;
  myCell.setSelVoltageDataPoint( expDouble * rrs::volts );
  BOOST_CHECK_MESSAGE( myCell.getSelVoltageDataPoints().at(0)
                        == expDouble * rrs::volts,
                      "Selector device voltage data points"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getSelVoltageDataPoints().at(0));


  ++expDouble;
  myCell.setSelCurrentDataPoint( expDouble * rrs::nanoamperes );
  BOOST_CHECK_MESSAGE( myCell.getSelCurrentDataPoints().at(0)
                        == expDouble * rrs::nanoamperes,
                      "Selector device current data points"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getSelCurrentDataPoints().at(0));

  ++expDouble;
  myCell.setCellSetVoltage( expDouble * rrs::volts, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellSetVoltage()
                        == expDouble * rrs::volts,
                      "Cell set voltage"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getCellSetVoltage());

  ++expDouble;
  myCell.setCellSetCurrent( expDouble * rrs::nanoamperes, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellSetCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Cell set current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getCellSetCurrent());

  ++expDouble;
  myCell.setCellSetComplianceCurrent( expDouble * rrs::nanoamperes );
  BOOST_CHECK_MESSAGE( myCell.getCellSetComplianceCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Cell set compliance current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getCellSetComplianceCurrent());

  ++expDouble;
  myCell.setCellResetVoltage( expDouble * rrs::volts, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellResetVoltage()
                        == expDouble * rrs::volts,
                      "Cell reset voltage"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getCellResetVoltage());

  ++expDouble;
  myCell.setCellResetCurrent( expDouble * rrs::nanoamperes, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellResetCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Cell reset current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getCellResetCurrent());

  ++expDouble;
  myCell.setCellReadVoltage( expDouble * rrs::volts, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellReadVoltage()
                        == expDouble * rrs::volts,
                      "Cell read voltage"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getCellReadVoltage());

  ++expDouble;
  myCell.setCellReadCurrent( expDouble * rrs::nanoamperes, only_set );
  BOOST_CHECK_MESSAGE( myCell.getCellReadCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Cell read current"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getCellReadCurrent());

  ++expDouble;
  myCell.setCellWidth( expDouble * rrs::nanometers );
  BOOST_CHECK_MESSAGE( myCell.getCellWidth()
                        == expDouble * rrs::nanometers,
                      "Cell width"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myCell.getCellWidth());

  ++expDouble;
  myCell.setCellHeight( expDouble * rrs::nanometers );
  BOOST_CHECK_MESSAGE( myCell.getCellHeight()
                        == expDouble * rrs::nanometers,
                      "Cell height"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myCell.getCellHeight());

  ++expDouble;
  myCell.setCellToCellSpacing( expDouble * rrs::nanometers );
  BOOST_CHECK_MESSAGE( myCell.getCellToCellSpacing()
                        == expDouble * rrs::nanometers,
                      "Cell to cell spacing"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myCell.getCellToCellSpacing());

  ++expDouble;
  myCell.setCellThickness( expDouble * rrs::nanometers );
  BOOST_CHECK_MESSAGE( myCell.getCellThickness()
                        == expDouble * rrs::nanometers,
                      "Cell thickness"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myCell.getCellThickness());


  ++expDouble;
  myCell.setMaxCurrentRelativeError( expDouble );
  BOOST_CHECK_MESSAGE( myCell.getMaxCurrentRelativeError()
                        == expDouble,
                      "Maximum current relative error"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << myCell.getMaxCurrentRelativeError());

}

BOOST_AUTO_TEST_CASE( checkCell_MemoryDevice )
{
  Cell myCell;

  double expDouble = INVALID_DOUBLE;
  bool flag_ = INVALID_EBOOL;
  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;

  myCell.setMemDevHRSResistance(1e6 * rrs::ohms);
  myCell.setMemDevLRSResistance(1e3 * rrs::ohms);

  expDouble = 1e6;
  BOOST_CHECK_MESSAGE( myCell.getMemDevHRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device maximum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevHRSResistance());

  expDouble = 1e3;
  BOOST_CHECK_MESSAGE( myCell.getMemDevLRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device minimum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevLRSResistance());

  BOOST_CHECK_MESSAGE( isInvalid( myCell.getMemDevInstantResistance() ),
                      "Memory device instant resistance"
                       << " different for the expected."
                       << "\nExpected: " << "Invalid value"
                       << "\nGot: " << myCell.getMemDevInstantResistance());

  try {
    myCell.setMemDevResistanceState(0);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from memory device state setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expDouble = 1e6;
  BOOST_CHECK_MESSAGE( myCell.getMemDevHRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device maximum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevHRSResistance());

  expDouble = 1e3;
  BOOST_CHECK_MESSAGE( myCell.getMemDevLRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device minimum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevLRSResistance());

  expDouble = 1e6;
  BOOST_CHECK_MESSAGE( myCell.getMemDevInstantResistance()
                        == expDouble * rrs::ohms,
                      "Memory device instant resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevInstantResistance());

  try {
    myCell.setMemDevResistanceState(1);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from memory device state setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expDouble = 1e6;
  BOOST_CHECK_MESSAGE( myCell.getMemDevHRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device maximum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevHRSResistance());

  expDouble = 1e3;
  BOOST_CHECK_MESSAGE( myCell.getMemDevLRSResistance()
                        == expDouble * rrs::ohms,
                      "Memory device minimum resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevLRSResistance());

  expDouble = 1e3;
  BOOST_CHECK_MESSAGE( myCell.getMemDevInstantResistance()
                        == expDouble * rrs::ohms,
                      "Memory device instant resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myCell.getMemDevInstantResistance());


  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Unexpected behaviour - ");
  expectedThrownMsg.append("tried to set a flag to");
  expectedThrownMsg.append(" a value different from");
  expectedThrownMsg.append(" 0 (false) or 1 (true)");
  expectedThrownMsg.append(" while setting memory");
  expectedThrownMsg.append(" device state.");
  try {
    myCell.setMemDevResistanceState(2);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from memory device state setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkCell_IxV_model_erros_SelectorDevice )
{
  Cell myCell;

  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;

  myCell.setSelVoltageDataPoint( 0. * rrs::volts );
  myCell.setSelCurrentDataPoint( 0. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 1 * rrs::volts );
  myCell.setSelCurrentDataPoint( 2 * rrs::nanoamperes );

  // One voltage point more than current points
  myCell.setSelVoltageDataPoint( 3 * rrs::volts );
  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("IxV curve based selector model");
  expectedThrownMsg.append(" needs same number of");
  expectedThrownMsg.append(" voltage and current data points.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("IxV");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  // One voltage point more than current points
  myCell.setSelCurrentDataPoint( 4 * rrs::nanoamperes );
  myCell.setSelCurrentDataPoint( 5 * rrs::nanoamperes );
  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("IxV curve based selector model");
  expectedThrownMsg.append(" needs same number of");
  expectedThrownMsg.append(" voltage and current data points.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("IxV");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  // Out of order voltage vector
  myCell.setSelVoltageDataPoint( 2 * rrs::volts );
  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("IxV curve based selector model");
  expectedThrownMsg.append(" needs the data points");
  expectedThrownMsg.append(" (both voltage and current)");
  expectedThrownMsg.append(" to be sorted and, therefore,");
  expectedThrownMsg.append(" monotonic.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("IxV");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


}

BOOST_AUTO_TEST_CASE( checkCell_SelectorDevice )
{
  Cell myCell;

  double expDouble = INVALID_DOUBLE;
  bool flag_ = INVALID_EBOOL;
  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;


  // Semi-ideal model derived from selector published on
  //  "A Cross Point Cu-RRAM with a Novel OTS Selector ..."
  //  from Shuichiro Yasuda et al.
  myCell.setSelDevSnapVoltage(3.2 * rrs::volts);
  myCell.setSelDevLeakageCurrent(10. * rrs::nanoamperes);
  myCell.setSelDevMaxCurrent(40e3 * rrs::nanoamperes);

  expDouble = 3.2;
  BOOST_CHECK_MESSAGE( myCell.getSelDevSnapVoltage()
                        == expDouble * rrs::volts,
                      "Selector device snap (aka. threshold, turn on) voltage"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::volts
                       << "\nGot: " << myCell.getSelDevSnapVoltage());

  expDouble = 10.;
  BOOST_CHECK_MESSAGE( myCell.getSelDevLeakageCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Selector device leakage current"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getSelDevLeakageCurrent());

  expDouble = 40e3;
  BOOST_CHECK_MESSAGE( myCell.getSelDevMaxCurrent()
                        == expDouble * rrs::nanoamperes,
                      "Selector device maximum (saturation) current"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::nanoamperes
                       << "\nGot: " << myCell.getSelDevMaxCurrent());

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Unexpected behaviour - ");
  expectedThrownMsg.append("Tried to USE a selector model ");
  expectedThrownMsg.append("different from the ones supported.");
  expectedThrownMsg.append(" Likely, some selector parameter(s) were");
  expectedThrownMsg.append(" changed after the model was set, or the");
  expectedThrownMsg.append(" the model was never set.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.calcSelCurrent(1. * rrs::volts);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Tried to set a selector model, \"");
  expectedThrownMsg.append("notAModel");
  expectedThrownMsg.append("\", different from the ones supported:\n");
  expectedThrownMsg.append("  \"semiIdeal\"\n");
  expectedThrownMsg.append("  \"IxV\"\n");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("notAModel");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector device model setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Unexpected behaviour - ");
  expectedThrownMsg.append("Tried to USE a selector model ");
  expectedThrownMsg.append("different from the ones supported.");
  expectedThrownMsg.append(" Likely, some selector parameter(s) were");
  expectedThrownMsg.append(" changed after the model was set, or the");
  expectedThrownMsg.append(" the model was never set.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.calcSelCurrent(1. * rrs::volts);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("semiIdeal");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector device model setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  vector<double> selVs;
  vector<double> selIs;
  bu::quantity<rrs::nanoampere_unit> gotCurrent;

  size_t nSigFigs = 6;

  selVs = {0, 1, -1, 3.199, -3.199, 3.20001, -3.20001, 10, -10};
  selIs = {0, 10, -10, 10, -10, 40e3, -40e3, 40e3, -40e3};
  gotCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < selVs.size(); i++) {
    try {
      gotCurrent = myCell.calcSelCurrent(selVs.at(i) * rrs::volts);
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_REQUIRE_MESSAGE( round(gotCurrent, nSigFigs)
                          == selIs.at(i) * rrs::nanoamperes,
                         setprecision(nSigFigs)
                         << "Current from selector device current calculation"
                         << " different for the expected."
                         << "\nApplied voltage: " << selVs.at(i) * rrs::volts
                         << "\nExpected: " << selIs.at(i) * rrs::nanoamperes
                         << "\nGot: " << round(gotCurrent, nSigFigs));
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  // IxV model derived from selector published on
  //  "A Cross Point Cu-RRAM with a Novel OTS Selector ..."
  //  from Shuichiro Yasuda et al.
  myCell.setSelVoltageDataPoint( 0. * rrs::volts );
  myCell.setSelCurrentDataPoint( 0. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 0.1 * rrs::volts );
  myCell.setSelCurrentDataPoint( 0.12 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 1.6 * rrs::volts );
  myCell.setSelCurrentDataPoint( 0.12 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2 * rrs::volts );
  myCell.setSelCurrentDataPoint( 3.2 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.25 * rrs::volts );
  myCell.setSelCurrentDataPoint( 8. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.5 * rrs::volts );
  myCell.setSelCurrentDataPoint( 12. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.75 * rrs::volts );
  myCell.setSelCurrentDataPoint( 16. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.0 * rrs::volts );
  myCell.setSelCurrentDataPoint( 40. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.1 * rrs::volts );
  myCell.setSelCurrentDataPoint( 120. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.12 * rrs::volts );
  myCell.setSelCurrentDataPoint( 360. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.14 * rrs::volts );
  myCell.setSelCurrentDataPoint( 1.2e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.16 * rrs::volts );
  myCell.setSelCurrentDataPoint( 3.2e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.18 * rrs::volts );
  myCell.setSelCurrentDataPoint( 8e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.2 * rrs::volts );
  myCell.setSelCurrentDataPoint( 28e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 4.0 * rrs::volts );
  myCell.setSelCurrentDataPoint( 34e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 4.5 * rrs::volts );
  myCell.setSelCurrentDataPoint( 36e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 6 * rrs::volts );
  myCell.setSelCurrentDataPoint( 40e3 * rrs::nanoamperes );

  expectedThrownMsg.clear();
  expectedThrownMsg.append("[ERROR] ");
  expectedThrownMsg.append("Unexpected behaviour - ");
  expectedThrownMsg.append("Tried to USE a selector model ");
  expectedThrownMsg.append("different from the ones supported.");
  expectedThrownMsg.append(" Likely, some selector parameter(s) were");
  expectedThrownMsg.append(" changed after the model was set, or the");
  expectedThrownMsg.append(" the model was never set.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.calcSelCurrent(1. * rrs::volts);
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("IxV");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector device model setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  selVs = {0, 1, -1, 1.8, 2.9, 3.15, -3.15, 10, -10};
  selIs = {0, 0.12, -0.12, 1.66, 30.4, 2200, -2200, 40e3, -40e3};
  gotCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < selVs.size(); i++) {
    try {
      gotCurrent = myCell.calcSelCurrent(selVs.at(i) * rrs::volts);
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_REQUIRE_MESSAGE( round(gotCurrent, nSigFigs)
                          == selIs.at(i) * rrs::nanoamperes,
                         setprecision(nSigFigs)
                         << "Current from selector device current calculation"
                         << " different for the expected."
                         << "\nApplied voltage: " << selVs.at(i) * rrs::volts
                         << "\nExpected: " << selIs.at(i) * rrs::nanoamperes
                         << "\nGot: " << round(gotCurrent, nSigFigs));
  }
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);



}

BOOST_AUTO_TEST_CASE( checkCell_CellCurrent_and_Voltage )
{
  Cell myCell;

  double expDouble = INVALID_DOUBLE;
  bool flag_ = INVALID_EBOOL;
  string expectedThrownMsg = "No exception.";
  string exceptionMsg = expectedThrownMsg;


  myCell.setMemDevResistanceState(1);

  myCell.setMemDevHRSResistance(600000 * rrs::ohms);
  myCell.setMemDevLRSResistance(61224 * rrs::ohms);

  // Semi-ideal model derived from selector published on
  //  "A Cross Point Cu-RRAM with a Novel OTS Selector ..."
  //  from Shuichiro Yasuda et al.
  myCell.setSelDevSnapVoltage(3.2 * rrs::volts);
  myCell.setSelDevLeakageCurrent(10. * rrs::nanoamperes);
  myCell.setSelDevMaxCurrent(40e3 * rrs::nanoamperes);

  myCell.setMaxCurrentRelativeError( 1e-3 );

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("semiIdeal");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector device model setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  vector<double> cellVs;
  vector<double> cellIs;
  bu::quantity<rrs::volt_unit> gotVoltage;
  bu::quantity<rrs::nanoampere_unit> gotCurrent;

  size_t nSigFigs = 6;

  cellVs = {0, 1, -1, 3.2, -3.2, 3.21, -3.21, 5.7, -5.7};
  cellIs = {0, 10., -10., 10., -10., 163.335, -163.335, 40000, -40000};

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < cellVs.size(); i++) {
    try {
      gotCurrent = myCell.calcCellCurrent(cellVs.at(i) * rrs::volts);
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs)
                          == cellIs.at(i) * rrs::nanoamperes,
                         setprecision(nSigFigs)
                         << "Current from cell current calculation"
                         << " different for the expected."
                         << "\nApplied voltage: " << cellVs.at(i) * rrs::volts
                         << "\nExpected: " << cellIs.at(i) * rrs::nanoamperes
                         << "\nGot: " << round(gotCurrent, nSigFigs));
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  cellIs = {0, 0.15, -0.15, 30., 453, -453, 39950., -39950.};
  cellVs = {0, 9.18284e-6, -9.18284e-6, 3.20184, 3.22773,
            -3.22773, 5.64453, -5.64453};


  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < cellVs.size(); i++) {
    try {
      gotVoltage = myCell.calcCellVoltage( cellIs.at(i) * rrs::nanoamperes );
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs)
                          == cellVs.at(i) * rrs::volts,
                         setprecision(nSigFigs)
                         << "Voltage from cell voltage calculation"
                         << " different for the expected."
                         << "\nApplied current: "
                         << cellIs.at(i) * rrs::nanoamperes
                         << "\nExpected: " << cellVs.at(i) * rrs::volts
                         << "\nGot: " << round(gotVoltage, nSigFigs));
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  // IxV model derived from selector published on
  //  "A Cross Point Cu-RRAM with a Novel OTS Selector ..."
  //  from Shuichiro Yasuda et al.
  myCell.setSelVoltageDataPoint( 0. * rrs::volts );
  myCell.setSelCurrentDataPoint( 0. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 0.1 * rrs::volts );
  myCell.setSelCurrentDataPoint( 0.12 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 1.6 * rrs::volts );
  myCell.setSelCurrentDataPoint( 0.12 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2 * rrs::volts );
  myCell.setSelCurrentDataPoint( 3.2 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.25 * rrs::volts );
  myCell.setSelCurrentDataPoint( 8. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.5 * rrs::volts );
  myCell.setSelCurrentDataPoint( 12. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 2.75 * rrs::volts );
  myCell.setSelCurrentDataPoint( 16. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.0 * rrs::volts );
  myCell.setSelCurrentDataPoint( 40. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.1 * rrs::volts );
  myCell.setSelCurrentDataPoint( 120. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.12 * rrs::volts );
  myCell.setSelCurrentDataPoint( 360. * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.14 * rrs::volts );
  myCell.setSelCurrentDataPoint( 1.2e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.16 * rrs::volts );
  myCell.setSelCurrentDataPoint( 3.2e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.18 * rrs::volts );
  myCell.setSelCurrentDataPoint( 8e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 3.2 * rrs::volts );
  myCell.setSelCurrentDataPoint( 28e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 4.0 * rrs::volts );
  myCell.setSelCurrentDataPoint( 34e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 4.5 * rrs::volts );
  myCell.setSelCurrentDataPoint( 36e3 * rrs::nanoamperes );
  myCell.setSelVoltageDataPoint( 6 * rrs::volts );
  myCell.setSelCurrentDataPoint( 40e3 * rrs::nanoamperes );

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell.setSelDevModel("IxV");
  } catch(string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector device model setting"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  cellVs = {0, 1, -1, 1.8, 2.9, 3.15, -3.15, 10, -10};
  cellIs = {0, 0.119995, -0.119995, 1.65849, 30.2215,
            453.624, -453.624, 40018.1, -40018.1};
  gotCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < cellVs.size(); i++) {
    try {
      gotCurrent = myCell.calcCellCurrent(cellVs.at(i) * rrs::volts);
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs)
                          == cellIs.at(i) * rrs::nanoamperes,
                         setprecision(nSigFigs)
                         << "Current from cell current calculation"
                         << " different for the expected."
                         << setprecision(10)
                         << "\nApplied voltage: " << cellVs.at(i) * rrs::volts
                         << "\nExpected: " << cellIs.at(i) * rrs::nanoamperes
                         << "\nGot: " << round(gotCurrent, nSigFigs));

  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  cellIs = {0, 0.15, -0.15, 1.65, 30., 453, -453, 39950., -39950.};
  cellVs = {0, 1.60389, -1.60389, 1.79871, 2.89795,
            3.14995, -3.14995, 8.4375, -8.4375};

  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  for (size_t i = 0; i < cellVs.size(); i++) {
    try {
      gotVoltage = myCell.calcCellVoltage( cellIs.at(i) * rrs::nanoamperes );
    } catch(string exceptionMsgThrown) {
      exceptionMsg = exceptionMsgThrown;
    }
    BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs)
                          == cellVs.at(i) * rrs::volts,
                         setprecision(nSigFigs)
                         << "Voltage from cell voltage calculation"
                         << " different for the expected."
                         << "\nApplied current: "
                         << cellIs.at(i) * rrs::nanoamperes
                         << "\nExpected: " << cellVs.at(i) * rrs::volts
                         << "\nGot: " << round(gotVoltage, nSigFigs));
  }
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from selector current calculation"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkCell_BuildCell_IxV )
{

  int sim_argc = 3;
  char* sim_argv[] = {"./executable",
                      "-conf",
                      "../../tests/configs/test_config.txt"};

  ArgumentsParser argParser(sim_argc, sim_argv);

  string exceptionMsg("No exception.");
  try {
      argParser.runArgParser();
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  string expectedThrownMsg("No exception.");
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from arguments parser run"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  Cell myCell;
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell = Cell(argParser.configs.at(0).cellFileName.c_str());
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from cell constructor"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  string expString;

  double expDouble = INVALID_DOUBLE;

  bu::quantity<rrs::ohm_unit> gotResistance;

  size_t nSigFigs = 6;

  expDouble = 600e3;
  gotResistance = myCell.getMemDevHRSResistance();
  BOOST_CHECK_MESSAGE( round(gotResistance, nSigFigs)
                       == expDouble * rrs::ohms,
                       setprecision(nSigFigs)
                       << "Memory device high resistive state resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << round(gotResistance, nSigFigs));

  expDouble = 61224;
  gotResistance = myCell.getMemDevLRSResistance();
  BOOST_CHECK_MESSAGE( round(gotResistance, nSigFigs)
                       == expDouble * rrs::ohms,
                       setprecision(nSigFigs)
                       << "Memory device low resistive state resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << round(gotResistance, nSigFigs));

  expDouble = 61224;
  gotResistance = myCell.getMemDevInstantResistance();
  BOOST_CHECK_MESSAGE( round(gotResistance, nSigFigs)
                       == expDouble * rrs::ohms,
                       setprecision(nSigFigs)
                       << "Memory device instant resistance"
                       << " different for the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << round(gotResistance, nSigFigs));

  expString = "IxV";
  BOOST_CHECK_MESSAGE( myCell.getSelDevModel() == expString,
                       "Selector device mathematical model"
                       << " different for the expected."
                       << "\nExpected: " << expString
                       << "\nGot: " << myCell.getSelDevModel());


  vector<double> cellVs;
  cellVs = {0, 0.1, 1.6, 2, 2.25, 2.5, 2.75, 3, 3.1,
            3.12, 3.14, 3.16, 3.18, 3.2, 4, 4.5, 6};
  vector<double> cellIs;
  cellIs = {0, 0.12, 0.12, 3.2, 8, 12, 16, 40, 120,
            360, 1.2e3, 3.2e3, 8e3, 28e3, 34e3, 36e3, 40e3};

  bu::quantity<rrs::volt_unit> expVoltage;
  bu::quantity<rrs::volt_unit> gotVoltage;
  bu::quantity<rrs::nanoampere_unit> expCurrent;
  bu::quantity<rrs::nanoampere_unit> gotCurrent;
  gotVoltage = INVALID_DOUBLE * rrs::volts;
  gotCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  for (size_t i = 0; i < cellVs.size(); i++) {
    expVoltage = cellVs.at(i) * rrs::volts;
    gotVoltage = myCell.getSelVoltageDataPoints().at(i);
    BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
                         setprecision(nSigFigs)
                         << "Voltage point from selector device"
                         << " different for the expected."
                         << "\nPoint index:" << i
                         << "\nExpected: " << expVoltage
                         << "\nGot: " << round(gotVoltage, nSigFigs));

    expCurrent = cellIs.at(i) * rrs::nanoamperes;
    gotCurrent = myCell.getSelCurrentDataPoints().at(i);
    BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
                         setprecision(nSigFigs)
                         << "Current point from selector device"
                         << " different for the expected."
                         << "\nPoint index:" << i
                         << "\nExpected: " << expCurrent
                         << "\nGot: " << round(gotCurrent, nSigFigs));
  }

  double gotValue;
  expDouble = 1e-6;
  gotValue = myCell.getMaxCurrentRelativeError();
  BOOST_CHECK_MESSAGE( round(gotValue, nSigFigs)
                       == expDouble,
                       setprecision(nSigFigs)
                       << "Maximum cell current relative error"
                       << " different for the expected."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << round(gotValue, nSigFigs));


//  expVoltage = 4.25 * rrs::volts;
//  gotVoltage = myCell.getCellSetVoltage();
//  BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
//                       setprecision(nSigFigs)
//                       << "Cell set voltage"
//                       << " different for the expected."
//                       << "\nExpected: " << expVoltage
//                       << "\nGot: " << round(gotVoltage, nSigFigs));

//  expCurrent = 1839.34 * rrs::nanoamperes;
//  gotCurrent = myCell.getCellSetCurrent();
//  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
//                       setprecision(nSigFigs)
//                       << "Cell set current"
//                       << " different for the expected."
//                       << "\nExpected: " << expCurrent
//                       << "\nGot: " << round(gotCurrent, nSigFigs));

  expCurrent = 10000 * rrs::nanoamperes;
  gotCurrent = myCell.getCellSetComplianceCurrent();
  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
                       setprecision(nSigFigs)
                       << "Cell set compliance current"
                       << " different for the expected."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << round(gotCurrent, nSigFigs));

  bu::quantity<rrs::nanosecond_unit> expTime;
  bu::quantity<rrs::nanosecond_unit> gotTime;

//  expTime = 2 * rrs::nanoseconds;
//  gotTime = myCell.getCellSetTime();
//  BOOST_CHECK_MESSAGE( round(gotTime, nSigFigs) == expTime,
//                       setprecision(nSigFigs)
//                       << "Cell set time"
//                       << " different for the expected."
//                       << "\nExpected: " << expTime
//                       << "\nGot: " << round(gotTime, nSigFigs));

//  expVoltage = 3.99995 * rrs::volts;
//  gotVoltage = myCell.getCellResetVoltage();
//  BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
//                       setprecision(nSigFigs)
//                       << "Cell reset voltage"
//                       << " different for the expected."
//                       << "\nExpected: " << expVoltage
//                       << "\nGot: " << round(gotVoltage, nSigFigs));

//  expCurrent = 13306 * rrs::nanoamperes;
//  gotCurrent = myCell.getCellResetCurrent();
//  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
//                       setprecision(nSigFigs)
//                       << "Cell reset current"
//                       << " different for the expected."
//                       << "\nExpected: " << expCurrent
//                       << "\nGot: " << round(gotCurrent, nSigFigs));

//  expTime = 8 * rrs::nanoseconds;
//  gotTime = myCell.getCellResetTime();
//  BOOST_CHECK_MESSAGE( round(gotTime, nSigFigs) == expTime,
//                       setprecision(nSigFigs)
//                       << "Cell reset time"
//                       << " different for the expected."
//                       << "\nExpected: " << expTime
//                       << "\nGot: " << round(gotTime, nSigFigs));

  expDouble = 7.5;
  gotValue = myCell.getCellReadCurrentRatio();
  BOOST_CHECK_MESSAGE( round(gotValue, nSigFigs) == expDouble,
                       setprecision(nSigFigs)
                       << "LRS/HRS read current ratio []"
                       << " different for the expected."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << round(gotValue, nSigFigs));

  bu::quantity<rrs::nanometer_unit> expLength;
  bu::quantity<rrs::nanometer_unit> gotLength;

  expLength = 50 * rrs::nanometers;
  gotLength = myCell.getCellThickness();
  BOOST_CHECK_MESSAGE( round(gotLength, nSigFigs) == expLength,
                       setprecision(nSigFigs)
                       << "Cell thickness"
                       << " different for the expected."
                       << "\nExpected: " << expLength
                       << "\nGot: " << round(gotLength, nSigFigs));

}

BOOST_AUTO_TEST_CASE( checkCell_BuildCell_semiIdeal )
{

  int sim_argc = 3;
  char* sim_argv[] = {"./executable",
                      "-conf",
                      "../../tests/configs/test_config2.txt"};

  ArgumentsParser argParser(sim_argc, sim_argv);

  string exceptionMsg("No exception.");
  try {
      argParser.runArgParser();
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  string expectedThrownMsg("No exception.");
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from arguments parser run"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  Cell myCell;

  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myCell = Cell(argParser.configs.at(0).cellFileName.c_str());
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from cell constructor"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  string expString;

  bu::quantity<rrs::ohm_unit> expResistance;
  bu::quantity<rrs::ohm_unit> gotResistance;

  size_t nSigFigs = 6;

  expResistance = 600e3 * rrs::ohms;
  gotResistance = myCell.getMemDevHRSResistance();
  BOOST_CHECK_MESSAGE( round(gotResistance, nSigFigs) == expResistance,
                       setprecision(nSigFigs)
                       << "Memory device high resistive state resistance"
                       << " different for the expected."
                       << "\nExpected: " << expResistance
                       << "\nGot: " << round(gotResistance, nSigFigs));

  expResistance = 61224 * rrs::ohms;
  gotResistance = myCell.getMemDevLRSResistance();
  BOOST_CHECK_MESSAGE( round(gotResistance, nSigFigs) == expResistance,
                       setprecision(nSigFigs)
                       << "Memory device low resistive state resistance"
                       << " different for the expected."
                       << "\nExpected: " << expResistance
                       << "\nGot: " << round(gotResistance, nSigFigs));

  expString = "semiIdeal";
  BOOST_CHECK_MESSAGE( myCell.getSelDevModel() == expString,
                      "Selector device mathematical model"
                       << " different for the expected."
                       << "\nExpected: " << expString
                       << "\nGot: " << myCell.getSelDevModel());


  bu::quantity<rrs::volt_unit> expVoltage;
  bu::quantity<rrs::volt_unit> gotVoltage;

  expVoltage = 1. * rrs::volts;
  gotVoltage = myCell.getSelDevSnapVoltage();
  BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
                       setprecision(nSigFigs)
                       << "Selector device snap voltage"
                       << " different for the expected."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << round(gotVoltage, nSigFigs));


  bu::quantity<rrs::nanoampere_unit> expCurrent;
  bu::quantity<rrs::nanoampere_unit> gotCurrent;

  expCurrent = 10 * rrs::nanoamperes;
  gotCurrent = myCell.getSelDevLeakageCurrent();
  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
                       setprecision(nSigFigs)
                       << "Selector device leakage current"
                       << " different for the expected."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << round(gotCurrent, nSigFigs));


  expCurrent = 50e3 * rrs::nanoamperes;
  gotCurrent = myCell.getSelDevMaxCurrent();
  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
                       setprecision(nSigFigs)
                       << "Selector device maximum current"
                       << " different for the expected."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << round(gotCurrent, nSigFigs));


  bu::quantity<rrs::dimensionless> expValue;
  bu::quantity<rrs::dimensionless> gotValue;

  expValue = 1e-6;
  gotValue = myCell.getMaxCurrentRelativeError();
  BOOST_CHECK_MESSAGE( round(gotValue, nSigFigs) == expValue,
                       setprecision(nSigFigs)
                       << "Maximum cell current relative error"
                       << " different for the expected."
                       << "\nExpected: " << expValue
                       << "\nGot: " << round(gotValue, nSigFigs));


//  expVoltage = 1.57 * rrs::volts;
//  gotVoltage = myCell.getCellSetVoltage();
//  BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
//                       setprecision(nSigFigs)
//                       << "Cell set voltage"
//                       << " different for the expected."
//                       << "\nExpected: " << expVoltage
//                       << "\nGot: " << round(gotVoltage, nSigFigs));

//  expCurrent = 950 * rrs::nanoamperes;
//  gotCurrent = myCell.getCellSetCurrent();
//  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
//                       setprecision(nSigFigs)
//                       << "Cell set current"
//                       << " different for the expected."
//                       << "\nExpected: " << expCurrent
//                       << "\nGot: " << round(gotCurrent, nSigFigs));

  expCurrent = 30000 * rrs::nanoamperes;
  gotCurrent = myCell.getCellSetComplianceCurrent();
  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
                       setprecision(nSigFigs)
                       << "Cell set compliance current"
                       << " different for the expected."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << round(gotCurrent, nSigFigs));

  bu::quantity<rrs::nanosecond_unit> expTime;
  bu::quantity<rrs::nanosecond_unit> gotTime;

//  expTime = 23.0756 * rrs::nanoseconds;
//  gotTime = myCell.getCellSetTime();
//  BOOST_CHECK_MESSAGE( round(gotTime, nSigFigs) == expTime,
//                       setprecision(nSigFigs)
//                       << "Cell set time"
//                       << " different for the expected."
//                       << "\nExpected: " << expTime
//                       << "\nGot: " << round(gotTime, nSigFigs));

//  expVoltage = 1.5 * rrs::volts;
//  gotVoltage = myCell.getCellResetVoltage();
//  BOOST_CHECK_MESSAGE( round(gotVoltage, nSigFigs) == expVoltage,
//                       setprecision(nSigFigs)
//                       << "Cell reset voltage"
//                       << " different for the expected."
//                       << "\nExpected: " << expVoltage
//                       << "\nGot: " << round(gotVoltage, nSigFigs));

//  expCurrent = 8166.7 * rrs::nanoamperes;
//  gotCurrent = myCell.getCellResetCurrent();
//  BOOST_CHECK_MESSAGE( round(gotCurrent, nSigFigs) == expCurrent,
//                       setprecision(nSigFigs)
//                       << "Cell reset current"
//                       << " different for the expected."
//                       << "\nExpected: " << expCurrent
//                       << "\nGot: " << round(gotCurrent, nSigFigs));

//  expTime = 93.5799 * rrs::nanoseconds;
//  gotTime = myCell.getCellResetTime();
//  BOOST_CHECK_MESSAGE( round(gotTime, nSigFigs) == expTime,
//                       setprecision(nSigFigs)
//                       << "Cell reset time"
//                       << " different for the expected."
//                       << "\nExpected: " << expTime
//                       << "\nGot: " << round(gotTime, nSigFigs));

  expValue = 7.5;
  gotValue = myCell.getCellReadCurrentRatio();
  BOOST_CHECK_MESSAGE( round(expValue, nSigFigs) == gotValue,
                       setprecision(nSigFigs)
                       << "Cell read current ratio"
                       << " different for the expected."
                       << "\nExpected: " << expValue
                       << "\nGot: " << round(gotValue, nSigFigs));

  bu::quantity<rrs::nanometer_unit> expLength;
  bu::quantity<rrs::nanometer_unit> gotLength;

  expLength = 50 * rrs::nanometers;
  gotLength = myCell.getCellThickness();
  BOOST_CHECK_MESSAGE( round(gotLength, nSigFigs) == expLength,
                       setprecision(nSigFigs)
                       << "Cell thickness"
                       << " different for the expected."
                       << "\nExpected: " << expLength
                       << "\nGot: " << round(gotLength, nSigFigs));


}


BOOST_AUTO_TEST_SUITE_END()

#endif // CELLTEST_CPP
