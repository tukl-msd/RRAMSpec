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



#ifndef XPOINTARRAYTEST_CPP
#define XPOINTARRAYTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../core/XPointArray.h"

#include "../../parser/ArgumentsParser.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

BOOST_AUTO_TEST_SUITE( testXPointArray )

BOOST_AUTO_TEST_CASE( checkXPointArray_Initialization )
{
  XPointArray myXPointArray;

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLMetalWidth() ),
                      "Wordline metal width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLMetalWidth() ),
                      "Bitline metal width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getHeightwiseCellPitch() ),
                      "Heighthwise cell pitch"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWidthwiseCellPitch() ),
                       "Widthwise cell pitch"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getArea4F2() ),
                      "4F2 array area"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getArea() ),
                      "Total array area"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getHeight() ),
                      "Array height"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWidth() ),
                      "Array width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getAreaEfficiency() ),
                      "Array area efficiency"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getNCols() ),
                      "Number of columns in the array"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getNRows() ),
                      "Number of rows in the array"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getCapacity() ),
                      "Capacity the array"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLResistancePerCell() ),
                      "Wordline resistance per cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLResistancePerCell() ),
                      "Bitline resistance per cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLCapacitancePerCell() ),
                      "Wordline capacitance per cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLCapacitancePerCell() ),
                      "Bitline capacitance per cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLResistancePerLength() ),
                      "Wordline resistance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLResistancePerLength() ),
                      "Bitline resistance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLCapacitancePerLength() ),
                      "Wordline capacitance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLCapacitancePerLength() ),
                      "Bitline capacitance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLWriteDriverResistance() ),
                      "Resistance of wordline driver for write operation"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLWriteDriverResistance() ),
                      "Resistance of bitline driver for write operation"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getWLReadDriverResistance() ),
                      "Resistance of wordline driver for read operation"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myXPointArray.getBLReadDriverResistance() ),
                      "Resistance of bitline driver for read operation"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getHalfBiasDriverResistance()),
                      "Resistance of half bisiang driver"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getWriteVoltage()),
                      "Array write voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadVoltage()),
                      "Array read voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getAdjWLDelay()),
                      "Adjacent wordline delay"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getAdjBLDelay()),
                      "Adjacent bitline delay"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getAdjLineMaxDelay()),
                      "Maximum delay of adjacent lines"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getWLDelay()),
                      "Wordline delay"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getBLDelay()),
                      "Bitline delay"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getLineMaxDelay()),
                      "Maximum delay of lines"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getPrechargeTime()),
                      "Array precharge time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getCalibrationDelay()),
                      "Array calibration delay"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getSetTime()),
                      "Array set time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getResetTime()),
                      "Array reset time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getWriteTime()),
                      "Array write time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadTime()),
                      "Array read time"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getPrechargeCurrent()),
                      "Array precharge current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getSetSCCurrent()),
                      "Array set current at selected cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getSetSPCurrent()),
                      "Array set current at half selected cells"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getSetCurrent()),
                      "Array set current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getResetSCCurrent()),
                      "Array reset current at selected cell"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getResetSPCurrent()),
                      "Array reset current at half selected cells"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getResetCurrent()),
                      "Array reset current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getWriteCurrent()),
                      "Array write current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadHRSSCCurrent()),
                      "Array read current at selected cell if SC at HRS"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadHRSSPCurrent()),
                      "Array read current at half-selected cell if SC at HRS"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadLRSSCCurrent()),
                      "Array read current at selected cell if SC at LRS"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadLRSSPCurrent()),
                      "Array read current at half-selected cell if SC at LRS"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadCurrent()),
                      "Array read current"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getPrechargeEnergy()),
                      "Array precharge energy"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getWriteEnergy()),
                      "Array write energy"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid(myXPointArray.getReadEnergy()),
                      "Array read energy"
                       << " was not correctly initialized.");

}

BOOST_AUTO_TEST_CASE( checkXPointArray_Setters_and_Getters_Values )
{
  XPointArray myXPointArray;

  double expDouble = INVALID_DOUBLE;
  ebool expFlag = INVALID_EBOOL;
  string expString = INVALID_STRING;

  expDouble = 1;
  myXPointArray.setNCols( expDouble );

  expDouble++;
  myXPointArray.setNRows( expDouble );

  expDouble++;
  myXPointArray.setWLMetalWidth( expDouble * rrs::nanometers, forced );

  expDouble++;
  myXPointArray.setBLMetalWidth( expDouble * rrs::nanometers, forced );

  expDouble++;
  myXPointArray.setArea( expDouble*rrs::square_nanometers, forced );

  expDouble = 1;
  BOOST_CHECK_MESSAGE( myXPointArray.getNCols()
                        == expDouble,
                       "Number of columns in the array"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << myXPointArray.getNCols());

  expDouble++;
  BOOST_CHECK_MESSAGE( myXPointArray.getNRows()
                        == expDouble,
                       "Number of rows in the array"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << myXPointArray.getNRows());

  expDouble++;
  BOOST_CHECK_MESSAGE( myXPointArray.getWLMetalWidth()
                        == expDouble * rrs::nanometers ,
                       "Wordline metal width"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myXPointArray.getWLMetalWidth());

  expDouble++;
  BOOST_CHECK_MESSAGE( myXPointArray.getBLMetalWidth()
                        == expDouble * rrs::nanometers ,
                       "Bitline metal width"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myXPointArray.getBLMetalWidth());

  expDouble++;
  BOOST_CHECK_MESSAGE( myXPointArray.getArea()
                        == expDouble * rrs::square_nanometers,
                       "Crosspoint array area"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::square_nanometers
                       << "\nGot: " << myXPointArray.getArea());

}

BOOST_AUTO_TEST_CASE( checkXPointArray_Setters_and_Getters_Errors )
{
  double expDouble = INVALID_DOUBLE;
  ebool expFlag = INVALID_EBOOL;
  string expString = INVALID_STRING;

  string exceptionMsg("No exception.");
  string expectedThrownMsg("No exception.");

  expDouble = 1.1;
  exceptionMsg = "No exception.";
  try {
    XPointArray myXPointArray;
    myXPointArray.setNCols( expDouble );
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Number of columns in the array must be an");
  expectedThrownMsg.append(" integer. Tried to set it to ");
  expectedThrownMsg.append(to_string((double)expDouble));
  expectedThrownMsg.append(".");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  exceptionMsg = "No exception.";
  try {
    XPointArray myXPointArray;
    myXPointArray.setNRows( expDouble );
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Number of rows in the array must be an");
  expectedThrownMsg.append(" integer. Tried to set it to ");
  expectedThrownMsg.append(to_string((double)expDouble));
  expectedThrownMsg.append(".");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of rows"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expDouble = 50;
  exceptionMsg = "No exception.";
  try {
    XPointArray myXPointArray;
    myXPointArray.tech.setMetalHalfPitch( expDouble * rrs::nanometers );
    myXPointArray.setWLMetalWidth( expDouble/2. * rrs::nanometers );
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Wordline metal width (");
  expectedThrownMsg.append(to_string( expDouble/2. * rrs::nanometers ));
  expectedThrownMsg.append(") is too narrow for");
  expectedThrownMsg.append(" given technology and cell.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of rows"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expDouble = 50;
  exceptionMsg = "No exception.";
  try {
    XPointArray myXPointArray;
    myXPointArray.tech.setMetalHalfPitch( expDouble * rrs::nanometers );
    myXPointArray.setBLMetalWidth( expDouble/2. * rrs::nanometers );
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Bitline metal width (");
  expectedThrownMsg.append(to_string( expDouble/2. * rrs::nanometers ));
  expectedThrownMsg.append(") is too narrow for");
  expectedThrownMsg.append(" given technology and cell.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of rows"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  expDouble = 50;
  exceptionMsg = "No exception.";
  try {
    XPointArray myXPointArray;
    myXPointArray.tech.setMetalHalfPitch( expDouble * rrs::nanometers );
    myXPointArray.setNRows( expDouble );
    myXPointArray.setNCols( expDouble );
    myXPointArray.setWLMetalWidth( expDouble * rrs::nanometers );
    myXPointArray.setBLMetalWidth( expDouble * rrs::nanometers );
    myXPointArray.updateHeightwiseCellPitch();
    myXPointArray.updateWidthwiseCellPitch();
    myXPointArray.updateArea();
    myXPointArray.setArea( expDouble * rrs::square_nanometers );
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Crosspoint array area given (");
  expectedThrownMsg.append(to_string( expDouble * rrs::square_nanometers ));
  expectedThrownMsg.append(") is too small");
  expectedThrownMsg.append(" to fit a ");
  expectedThrownMsg.append(to_string((int)expDouble));
  expectedThrownMsg.append(" x ");
  expectedThrownMsg.append(to_string((int)expDouble));
  expectedThrownMsg.append(" cells array (");
  expectedThrownMsg.append(to_string(4*pow(expDouble,4)*rrs::square_nanometer));
  expectedThrownMsg.append(").");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of rows"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkXPointArray_test_config )
{

  int sim_argc = 3;
  char* sim_argv[] = {"./executable",
                      "-conf",
                      "../../tests/configs/test_config.txt"};

  ArgumentsParser argParser(sim_argc, sim_argv);

  string exceptionMsg("No exception.");
  string expectedThrownMsg("No exception.");

  exceptionMsg = "No exception.";
  try {
    argParser.runArgParser();
  }catch (string exceptionMsgThrown){
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "No exception.";
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from arguments parser run"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  XPointArray myXPointArray;

  exceptionMsg = "No exception.";
  try {
    myXPointArray = XPointArray(argParser.configs.at(0));
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "No exception.";
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from crosspoint array constructor"
                       << " different from the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  string expString;

  double expDouble;

  bu::quantity<rrs::dimensionless> gotDimensionless;
  bu::quantity<rrs::nanometer_unit> gotLength;
  bu::quantity<rrs::square_nanometer_unit> gotArea;
  bu::quantity<rrs::ohm_unit> gotResistance;
  bu::quantity<rrs::volt_unit> gotVoltage;

  expDouble = 2048;
  myXPointArray.setNCols(expDouble);
  gotDimensionless = myXPointArray.getNCols();
  BOOST_CHECK_MESSAGE( gotDimensionless == expDouble,
                       "Number of columns in the array"
                       << " different from the expected."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << gotDimensionless);

  expDouble = 1024;
  myXPointArray.setNRows(expDouble);
  gotDimensionless = myXPointArray.getNRows();
  BOOST_CHECK_MESSAGE( gotDimensionless == expDouble,
                       "Number of rows in the array"
                       << " different from the expected."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << gotDimensionless);

  myXPointArray.updateXPointArray();

  expDouble = 40;
  gotLength = round(myXPointArray.getWLMetalWidth(), 6);
  BOOST_CHECK_MESSAGE( gotLength == expDouble * rrs::nanometers,
                       setprecision(6)
                       << "Wordline metal width"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << gotLength);

  expDouble = 40;
  gotLength = round(myXPointArray.getBLMetalWidth(), 6);
  BOOST_CHECK_MESSAGE( gotLength == expDouble * rrs::nanometers,
                       setprecision(6)
                       << "Bitline metal width"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << gotLength);

  expDouble = 80;
  gotLength = round(myXPointArray.getHeightwiseCellPitch(), 6);
  BOOST_CHECK_MESSAGE( gotLength == expDouble * rrs::nanometers,
                       setprecision(6)
                       << "Heighthwise cell pitch"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << gotLength);

  expDouble = 80;
  gotLength = round(myXPointArray.getWidthwiseCellPitch(), 6);
  BOOST_CHECK_MESSAGE( gotLength == expDouble * rrs::nanometers,
                       setprecision(6)
                       << "Widthwise cell pitch"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << gotLength);

  expDouble = 1.34218e10;
  gotArea = round(myXPointArray.getArea(), 6);
  BOOST_CHECK_MESSAGE( gotArea == expDouble * rrs::square_nanometers,
                       setprecision(6)
                       << "Crosspoint array area"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::square_nanometers
                       << "\nGot: " << gotArea);

  expDouble = 2;
  gotResistance = round(myXPointArray.getWLResistancePerCell(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Wordline resistance per cell"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 2;
  gotResistance = round(myXPointArray.getBLResistancePerCell(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Bitline resistance per cell"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 1761.96;
  gotResistance = round(myXPointArray.getWLWriteDriverResistance(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Resistance of wordline driver for write operation"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 1761.96;
  gotResistance = round(myXPointArray.getBLWriteDriverResistance(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Resistance of bitline driver for write operation"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 1761.96;
  gotResistance = round(myXPointArray.getWLReadDriverResistance(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Resistance of wordline driver for read operation"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 1761.96;
  gotResistance = round(myXPointArray.getBLReadDriverResistance(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Resistance of bitline driver for read operation"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);

  expDouble = 1761.96;
  gotResistance = round(myXPointArray.getHalfBiasDriverResistance(), 6);
  BOOST_CHECK_MESSAGE( gotResistance == expDouble * rrs::ohms,
                       setprecision(6)
                       << "Resistance of half biasing driver"
                       << " different from the expected."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << gotResistance);


}


BOOST_AUTO_TEST_SUITE_END()

#endif // XPOINTARRAYTEST_CPP
