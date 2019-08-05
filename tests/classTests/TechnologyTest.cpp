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



#ifndef TECHNOLOGYTEST_CPP
#define TECHNOLOGYTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../core/Technology.h"

#include "../../parser/ArgumentsParser.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

BOOST_AUTO_TEST_SUITE( testTechnology )

BOOST_AUTO_TEST_CASE( checkTechnology_Initialization )
{
  Technology myTechnology;

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalHalfPitch() ),
                      "Metal half pitch"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalThickness() ),
                      "Metal thickness"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalResistivity() ),
                      "Metal resistivity"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalSheetResistance() ),
                      "Metal sheet resistance"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalResistancePerLength() ),
                      "Metal resistance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMetalCapacitancePerLength() ),
                      "Metal capacitance per length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getSubsRelPermtvt() ),
                      "Substrate relative permittivity"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getSubsAbsPermtvt() ),
                      "Substrate absolute permittivity"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getBreakdownVoltage() ),
                      "MOS breakdown voltage"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMinPMOSChannelLength() ),
                      "Minimum PMOS channel length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMinPMOSChannelWidth() ),
                      "Minimum PMOS channel width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMinNMOSChannelLength() ),
                      "Minimum NMOS channel length"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getMinNMOSChannelWidth() ),
                      "Minimum NMOS channel width"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getNMOSResWidthProduct() ),
                      "NMOS resistance-width product"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getPMOSResWidthProduct() ),
                      "PMOS resistance-width product"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getGateExtensionOfActive() ),
                      "Gate extension of active layer"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getPolyToPolySpacing() ),
                      "Poly to poly spacing"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getActiveExtensionOfPoly() ),
                      "Active layer extension of poly"
                       << " was not correctly initialized.");

  BOOST_CHECK_MESSAGE( isInvalid( myTechnology.getActiveToActiveSpacing() ),
                      "Active layer to active layer spacing"
                       << " was not correctly initialized.");



}

BOOST_AUTO_TEST_CASE( checkTechnology_Setters_and_Getters_Values )
{
  Technology myTechnology;

  double expDouble = INVALID_DOUBLE;
  ebool flag_ = INVALID_EBOOL;
  string expString = INVALID_STRING;

  expDouble = 1;
  myTechnology.setMetalHalfPitch( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setMetalThickness( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setMetalResistivity( expDouble * rrs::ohm_meters );

  expDouble++;
  myTechnology.setMetalSheetResistance( expDouble * rrs::ohms, forced );

  expDouble++;
  myTechnology.setMetalResistancePerLength( expDouble * rrs::ohms_per_nanometer,
                                            forced );

  expDouble++;
  myTechnology.setMetalCapacitancePerLength(
        expDouble * rrs::nanofarads_per_meter );

  expDouble++;
  myTechnology.setSubsRelPermtvt( expDouble );

  expDouble++;
  myTechnology.setSubsAbsPermtvt(expDouble*rrs::picofarads_per_meter, forced );

  expDouble++;
  myTechnology.setBreakdownVoltage( expDouble * rrs::volts );

  expDouble++;
  myTechnology.setMinPMOSChannelLength( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setMinPMOSChannelWidth( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setMinNMOSChannelLength( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setMinNMOSChannelWidth( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setNMOSResWidthProduct( expDouble * rrs::microohm_meters );

  expDouble++;
  myTechnology.setPMOSResWidthProduct( expDouble * rrs::microohm_meters );

  expDouble++;
  myTechnology.setGateExtensionOfActive( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setPolyToPolySpacing( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setActiveExtensionOfPoly( expDouble * rrs::nanometers );

  expDouble++;
  myTechnology.setActiveToActiveSpacing( expDouble * rrs::nanometers );

  expDouble = 1;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalHalfPitch()
                        == expDouble * rrs::nanometers,
                       "Metal half pitch"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMetalHalfPitch());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalThickness()
                        == expDouble * rrs::nanometers,
                       "Metal thickness"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMetalThickness());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalResistivity()
                        == expDouble * rrs::ohm_meters,
                       "Metal resistivity"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohm_meters
                       << "\nGot: " << myTechnology.getMetalResistivity());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalSheetResistance()
                        == expDouble * rrs::ohms,
                       "Metal sheet resistance"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myTechnology.getMetalSheetResistance());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalResistancePerLength()
                        == expDouble * rrs::ohms_per_nanometer,
                       "Metal resistance per length"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms_per_nanometer
                       << "\nGot: "
                       << myTechnology.getMetalResistancePerLength());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalCapacitancePerLength()
                        == expDouble * rrs::nanofarads_per_meter,
                       "Metal capacitance per length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanofarads_per_meter
                       << "\nGot: "
                       << myTechnology.getMetalCapacitancePerLength());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getSubsRelPermtvt()
                        == expDouble,
                       "Substrate relative permittivity"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << myTechnology.getSubsRelPermtvt());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getSubsAbsPermtvt()
                        == expDouble * rrs::picofarads_per_meter,
                       "Substrate absolute permittivity"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::picofarads_per_meter
                       << "\nGot: " << myTechnology.getSubsAbsPermtvt());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getBreakdownVoltage()
                        == expDouble * rrs::volts,
                       "MOS breakdown voltage"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::volts
                       << "\nGot: " << myTechnology.getBreakdownVoltage());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMinPMOSChannelLength()
                        == expDouble * rrs::nanometers,
                       "Minimum PMOS channel length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinPMOSChannelLength());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMinPMOSChannelWidth()
                        == expDouble * rrs::nanometers,
                       "Minimum PMOS channel width"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinPMOSChannelWidth());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMinNMOSChannelLength()
                        == expDouble * rrs::nanometers,
                       "Minimum NMOS channel length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinNMOSChannelLength());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getMinNMOSChannelWidth()
                        == expDouble * rrs::nanometers,
                       "Minimum NMOS channel width"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinNMOSChannelWidth());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getNMOSResWidthProduct()
                        == 1000 * expDouble * rrs::nanoohm_meters,
                       "NMOS resistance-width product"
                       << " was not correctly set."
                       << "\nExpected: "
                       << 1000 * expDouble * rrs::nanoohm_meters
                       << "\nGot: " << myTechnology.getNMOSResWidthProduct());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getPMOSResWidthProduct()
                        == 1000 * expDouble * rrs::nanoohm_meters,
                       "PMOS resistance-width product"
                       << " was not correctly set."
                       << "\nExpected: "
                       << 1000 * expDouble * rrs::nanoohm_meters
                       << "\nGot: " << myTechnology.getPMOSResWidthProduct());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getGateExtensionOfActive()
                        == expDouble * rrs::nanometers,
                       "Gate extension of active layer"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getGateExtensionOfActive());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getPolyToPolySpacing()
                        == expDouble * rrs::nanometers,
                       "Poly to poly spacing"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getPolyToPolySpacing());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getActiveExtensionOfPoly()
                        == expDouble * rrs::nanometers,
                       "Active layer extension of poly"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getActiveExtensionOfPoly());

  expDouble++;
  BOOST_CHECK_MESSAGE( myTechnology.getActiveToActiveSpacing()
                        == expDouble * rrs::nanometers,
                       "Active layer to active layer spacing"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getActiveToActiveSpacing());

}

BOOST_AUTO_TEST_CASE( checkTechnology_Setters_and_Getters_Errors )
{
  string exceptionMsg("No exception.");
  string expectedThrownMsg("No exception.");

  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setMetalSheetResistance( INVALID_DOUBLE * rrs::ohms );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Metal sheet resistance is unknown.\n");
  expectedThrownMsg.append("Please include either:\n");
  expectedThrownMsg.append("\"Metal thickness [nm]\":<value>");
  expectedThrownMsg.append(" and ");
  expectedThrownMsg.append("\"Metal resistivity [Ohm m]\":<value>");
  expectedThrownMsg.append("\nor:\n");
  expectedThrownMsg.append("\"Metal sheet resistance [Ohm]\":<value>");
  expectedThrownMsg.append("\nto your technology description file.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setMetalResistivity( 1. * rrs::ohm_meters );
    myTechnology.setMetalSheetResistance( INVALID_DOUBLE * rrs::ohms );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Metal sheet resistance is unknown.\n");
  expectedThrownMsg.append("Please include either:\n");
  expectedThrownMsg.append("\"Metal thickness [nm]\":<value>");
  expectedThrownMsg.append(" and ");
  expectedThrownMsg.append("\"Metal resistivity [Ohm m]\":<value>");
  expectedThrownMsg.append("\nor:\n");
  expectedThrownMsg.append("\"Metal sheet resistance [Ohm]\":<value>");
  expectedThrownMsg.append("\nto your technology description file.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setMetalThickness( 1. * rrs::nanometers );
    myTechnology.setMetalSheetResistance( INVALID_DOUBLE * rrs::ohms );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Metal sheet resistance is unknown.\n");
  expectedThrownMsg.append("Please include either:\n");
  expectedThrownMsg.append("\"Metal thickness [nm]\":<value>");
  expectedThrownMsg.append(" and ");
  expectedThrownMsg.append("\"Metal resistivity [Ohm m]\":<value>");
  expectedThrownMsg.append("\nor:\n");
  expectedThrownMsg.append("\"Metal sheet resistance [Ohm]\":<value>");
  expectedThrownMsg.append("\nto your technology description file.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setMetalResistivity( 10. * rrs::ohm_meters );
    myTechnology.setMetalThickness( 2. * rrs::nanometers );
    myTechnology.setMetalSheetResistance( 1. * rrs::ohms );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Inconsistent data.");
  expectedThrownMsg.append(" Metal sheet resistance given (");
  expectedThrownMsg.append(to_string( 1. * rrs::ohms ));
  expectedThrownMsg.append(") does not match with calculated (");
  expectedThrownMsg.append(to_string(10. / 2e-9 * rrs::ohms));
  expectedThrownMsg.append(") based on the metal resistivity (");
  expectedThrownMsg.append(to_string( 10. * rrs::ohm_meters ));
  expectedThrownMsg.append(") and the metal thickness (");
  expectedThrownMsg.append(to_string( 2. * rrs::nanometers ));
  expectedThrownMsg.append("). Difference is ");
  expectedThrownMsg.append(to_string( 1. * rrs::ohms  - 10./2e-9 * rrs::ohms));
  expectedThrownMsg.append(".");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setSubsAbsPermtvt( INVALID_DOUBLE*rrs::picofarads_per_meter );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Substrate permittivity is unknown.\n");
  expectedThrownMsg.append("Please include either:\n");
  expectedThrownMsg.append("\"Substrate relative permittivity []\"");
  expectedThrownMsg.append(":<value>\nor:\n");
  expectedThrownMsg.append("\"Substrate absolute permittivity [pF/m]\":");
  expectedThrownMsg.append(":<value>\nor:\n");
  expectedThrownMsg.append("\"Metal capacitance per length [fF/um]\":");
  expectedThrownMsg.append("<value>\nto your technology description file.");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);

  exceptionMsg = "No exception.";
  try {
    Technology myTechnology;
    myTechnology.setSubsRelPermtvt( 1. );
    myTechnology.setSubsAbsPermtvt( 1.*rrs::picofarads_per_meter );
  }catch (string exceptionMsgThrown) {
    exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg = "[ERROR] ";
  expectedThrownMsg.append("Inconsistent data.");
  expectedThrownMsg.append(" Substrate absolute permittivity given (");
  expectedThrownMsg.append(to_string(1.*rrs::picofarads_per_meter));
  expectedThrownMsg.append(") does not match with calculated (");
  expectedThrownMsg.append(to_string(8.85419*rrs::picofarads_per_meter));
  expectedThrownMsg.append(") based on the relative permittivity (");
  expectedThrownMsg.append(to_string( SCALE_QUANTITY(1., rrs::dimensionless) ));
  expectedThrownMsg.append("). Difference is ");
  expectedThrownMsg.append(to_string((1. - 8.85419)*rrs::picofarads_per_meter));
  expectedThrownMsg.append(".");
  BOOST_CHECK_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from setting number of columns"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


}


BOOST_AUTO_TEST_CASE( checkTechnology_Test_input )
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

  Technology myTechnology;
  exceptionMsg.clear();
  exceptionMsg.append("No exception.");
  try {
    myTechnology = Technology(argParser.configs.at(0).techFileName.c_str());
  }catch (string exceptionMsgThrown){
      exceptionMsg = exceptionMsgThrown;
  }
  expectedThrownMsg.clear();
  expectedThrownMsg.append("No exception.");
  BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedThrownMsg,
                       "Exception message from technology constructor"
                       << " different for the expected."
                       << "\nExpected: " << expectedThrownMsg
                       << "\nGot: " << exceptionMsg);


  double expDouble = INVALID_DOUBLE;

  expDouble = 40;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMetalHalfPitch(), 6)
                        == expDouble * rrs::nanometers,
                       "Metal half pitch"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMetalHalfPitch());

  expDouble = 100;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMetalThickness(), 6)
                        == expDouble * rrs::nanometers,
                       "Metal thickness"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMetalThickness());

  expDouble = 10e-8;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMetalResistivity(), 6)
                        == expDouble * rrs::ohm_meters,
                       "Metal resistivity"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohm_meters
                       << "\nGot: " << myTechnology.getMetalResistivity());

  expDouble = 1;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMetalSheetResistance(), 6)
                        == expDouble * rrs::ohms,
                       "Metal sheet resistance"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms
                       << "\nGot: " << myTechnology.getMetalSheetResistance());

  expDouble = 0.025;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMetalResistancePerLength(), 6)
                        == expDouble * rrs::ohms_per_nanometer,
                       "Metal resistance per length"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble * rrs::ohms_per_nanometer
                       << "\nGot: "
                       << myTechnology.getMetalResistancePerLength());

  expDouble = .2;
  BOOST_CHECK_MESSAGE( myTechnology.getMetalCapacitancePerLength()
                        == expDouble * rrs::nanofarads_per_meter,
                       "Metal capacitance per length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanofarads_per_meter
                       << "\nGot: "
                       << myTechnology.getMetalCapacitancePerLength());

  expDouble = 5;
  BOOST_CHECK_MESSAGE( round(myTechnology.getSubsRelPermtvt(), 6)
                        == expDouble,
                       "Substrate relative permittivity"
                       << " was not correctly set."
                       << "\nExpected: " << expDouble
                       << "\nGot: " << myTechnology.getSubsRelPermtvt());

  expDouble = 44.2709;
  BOOST_CHECK_MESSAGE( round(myTechnology.getSubsAbsPermtvt(), 6)
                        == expDouble * rrs::picofarads_per_meter,
                       "Substrate absolute permittivity"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::picofarads_per_meter
                       << "\nGot: " << myTechnology.getSubsAbsPermtvt());

  expDouble = 5;
  BOOST_CHECK_MESSAGE( round(myTechnology.getBreakdownVoltage(), 6)
                        == expDouble * rrs::volts,
                       "MOS breakdown voltage"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::volts
                       << "\nGot: " << myTechnology.getBreakdownVoltage());

  expDouble = 400;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMinPMOSChannelLength(), 6)
                        == expDouble * rrs::nanometers,
                       "Minimum PMOS channel length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinPMOSChannelLength());

  expDouble = 320;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMinPMOSChannelWidth(), 6)
                        == expDouble * rrs::nanometers,
                       "Minimum PMOS channel width"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinPMOSChannelWidth());

  expDouble = 500;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMinNMOSChannelLength(), 6)
                        == expDouble * rrs::nanometers,
                       "Minimum NMOS channel length"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinNMOSChannelLength());

  expDouble = 320;
  BOOST_CHECK_MESSAGE( round(myTechnology.getMinNMOSChannelWidth(), 6)
                        == expDouble * rrs::nanometers,
                       "Minimum NMOS channel width"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getMinNMOSChannelWidth());

  expDouble = 2600000;
  BOOST_CHECK_MESSAGE( round(myTechnology.getNMOSResWidthProduct(), 6)
                        == expDouble * rrs::nanoohm_meters,
                       "NMOS resistance-width product"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanoohm_meters
                       << "\nGot: " << myTechnology.getNMOSResWidthProduct());

  expDouble = 5000000;
  BOOST_CHECK_MESSAGE( round(myTechnology.getPMOSResWidthProduct(), 6)
                        == expDouble * rrs::nanoohm_meters,
                       "PMOS resistance-width product"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanoohm_meters
                       << "\nGot: " << myTechnology.getPMOSResWidthProduct());

  expDouble = 120;
  BOOST_CHECK_MESSAGE( round(myTechnology.getGateExtensionOfActive(), 6)
                        == expDouble * rrs::nanometers,
                       "Gate extension of active layer"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getGateExtensionOfActive());

  expDouble = 120;
  BOOST_CHECK_MESSAGE( round(myTechnology.getPolyToPolySpacing(), 6)
                        == expDouble * rrs::nanometers,
                       "Poly to poly spacing"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getPolyToPolySpacing());

  expDouble = 90;
  BOOST_CHECK_MESSAGE( round(myTechnology.getActiveExtensionOfPoly(), 6)
                        == expDouble * rrs::nanometers,
                       "Active layer extension of poly"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getActiveExtensionOfPoly());

  expDouble = 120;
  BOOST_CHECK_MESSAGE( round(myTechnology.getActiveToActiveSpacing(), 6)
                        == expDouble * rrs::nanometers,
                       "Active layer to active layer spacing"
                       << " was not correctly set."
                       << "\nExpected: "
                       << expDouble * rrs::nanometers
                       << "\nGot: " << myTechnology.getActiveToActiveSpacing());
}


BOOST_AUTO_TEST_SUITE_END()

#endif // TECHNOLOGYTEST_CPP
