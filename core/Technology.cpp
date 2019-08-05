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



#include "Technology.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

void
Technology::initialize()
{
  technologyNode = INVALID_DOUBLE * rrs::nanometers;

  vcc = INVALID_DOUBLE * rrs::volts;

  metalHalfPitch = INVALID_DOUBLE * rrs::nanometers;
  metalThickness = INVALID_DOUBLE * rrs::nanometers;

  metalResistivity = INVALID_DOUBLE * rrs::ohm_meters;
  metalSheetResistance = INVALID_DOUBLE * rrs::ohms;
  metalResistancePerLength = INVALID_DOUBLE * rrs::ohms_per_nanometer;

  metalCapacitancePerLength = INVALID_DOUBLE * rrs::nanofarads_per_meter;

  substrateRelativePermittivity = INVALID_DOUBLE;
  substrateAbsolutePermittivity = INVALID_DOUBLE * rrs::picofarads_per_meter;

  breakdownVoltage = INVALID_DOUBLE * rrs::volts;

  minPMOSChannelLength = INVALID_DOUBLE * rrs::nanometers;
  minPMOSChannelWidth = INVALID_DOUBLE * rrs::nanometers;
  minNMOSChannelLength = INVALID_DOUBLE * rrs::nanometers;
  minNMOSChannelWidth = INVALID_DOUBLE * rrs::nanometers;

  nMOSResistanceWidthProduct = INVALID_DOUBLE * rrs::nanoohm_meters;
  pMOSResistanceWidthProduct = INVALID_DOUBLE * rrs::nanoohm_meters;

  gateExtensionOfActive = INVALID_DOUBLE * rrs::nanometers;
  polyToPolySpacing = INVALID_DOUBLE * rrs::nanometers;
  activeExtensionOfPoly = INVALID_DOUBLE * rrs::nanometers;
  activeToActiveSpacing = INVALID_DOUBLE * rrs::nanometers;

}


void
Technology::setTechnologyNode(bu::quantity<rrs::nanometer_unit> node)
{
  technologyNode = node;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getTechnologyNode() const
{
  return this->technologyNode;
}

void
Technology::setVcc(bu::quantity<rrs::volt_unit> _vcc)
{
  vcc = _vcc;
}

bu::quantity<rrs::volt_unit> const &
Technology::getVcc() const
{
  return this->vcc;
}

void
Technology::setMetalHalfPitch(bu::quantity<rrs::nanometer_unit> halfPitch)
{
  metalHalfPitch = halfPitch;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMetalHalfPitch() const
{
  return this->metalHalfPitch;
}

void
Technology::setMetalThickness(bu::quantity<rrs::nanometer_unit> thickness)
{
  metalThickness = thickness;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMetalThickness() const
{
  return this->metalThickness;
}


void
Technology::setMetalResistivity(bu::quantity<rrs::ohm_meter_unit> resistivity)
{
  metalResistivity = resistivity;
}

bu::quantity<rrs::ohm_meter_unit> const &
Technology::getMetalResistivity() const
{
  return this->metalResistivity;
}

void
Technology::setMetalSheetResistance(bu::quantity<rrs::ohm_unit> resistance,
                                    settingOptions setOpt)
{
  metalSheetResistance = resistance;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }

  // Not enough information
  // TODO: Re-do tests to account for metal resistance per length
  if ( isInvalid(resistance) && !areValid(metalResistivity, metalThickness) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Metal sheet resistance is unknown.\n");
    exceptionMsgThrown.append("Please include either:\n");
    exceptionMsgThrown.append("\"Metal thickness [nm]\":<value>");
    exceptionMsgThrown.append(" and ");
    exceptionMsgThrown.append("\"Metal resistivity [Ohm m]\":<value>");
    exceptionMsgThrown.append("\nor:\n");
    exceptionMsgThrown.append("\"Metal sheet resistance [Ohm]\":<value>");
    exceptionMsgThrown.append("\nto your technology description file.");
    throw exceptionMsgThrown;
  }

  // More than enough information
  if ( areValid(metalResistivity, metalThickness, resistance) ) {
    setMetalSheetResistance(metalResistivity, metalThickness);
    auto derivedRes = metalSheetResistance;

    if ( !areEqual(derivedRes, resistance) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Inconsistent data.");
      exceptionMsgThrown.append(" Metal sheet resistance given (");
      exceptionMsgThrown.append(to_string(resistance));
      exceptionMsgThrown.append(") does not match with calculated (");
      exceptionMsgThrown.append(to_string(derivedRes));
      exceptionMsgThrown.append(") based on the metal resistivity (");
      exceptionMsgThrown.append(to_string(metalResistivity));
      exceptionMsgThrown.append(") and the metal thickness (");
      exceptionMsgThrown.append(to_string(metalThickness));
      exceptionMsgThrown.append("). Difference is ");
      exceptionMsgThrown.append(to_string(resistance - derivedRes));
      exceptionMsgThrown.append(".");
      throw exceptionMsgThrown;
    }
  }
  // Just enough information
  else if ( isValid(resistance) ) {
    metalSheetResistance = resistance;
  }
  else if ( areValid( metalResistivity, metalThickness ) ) {
    setMetalSheetResistance( metalResistivity, metalThickness );
  }
  else {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("no condition satisfied during");
    exceptionMsgThrown.append(" metal sheet resistance set.");
    throw exceptionMsgThrown;
  }

  setMetalResistancePerLength( metalSheetResistance / metalHalfPitch );

}

void
Technology::setMetalSheetResistance(
    bu::quantity<rrs::ohm_meter_unit> resistivity,
    bu::quantity<rrs::nanometer_unit> thickness)
{
  if ( !areValid( resistivity, thickness ) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to calculate the metal sheet resistance");
    exceptionMsgThrown.append(" based on the its resistivity and thickness");
    exceptionMsgThrown.append(" but one or both of this parameters were");
    exceptionMsgThrown.append(" not valid.");
    throw exceptionMsgThrown;
  }
  metalSheetResistance = resistivity
                         / SCALE_QUANTITY(thickness, rrs::meter_unit);
}

bu::quantity<rrs::ohm_unit> const &
Technology::getMetalSheetResistance() const
{
  return this->metalSheetResistance;
}

void
Technology::setMetalResistancePerLength(
    bu::quantity<rrs::ohm_per_nanometer_unit> resL,
    settingOptions setOpt)
{
  if ( isInvalid(resL) ) { return; }

  metalResistancePerLength = resL;
  if ( setOpt == forced ) { return; }


  //TODO: Re-do tests instead of hard overwrite
  metalSheetResistance = metalResistancePerLength * metalHalfPitch;
}

bu::quantity<rrs::ohm_per_nanometer_unit> const &
Technology::getMetalResistancePerLength() const
{
  return this->metalResistancePerLength;
}



void
Technology::setMetalCapacitancePerLength(
    bu::quantity<rrs::nanofarad_per_meter_unit> capL)
{
  metalCapacitancePerLength = capL;
}

bu::quantity<rrs::nanofarad_per_meter_unit> const &
Technology::getMetalCapacitancePerLength() const
{
  return this->metalCapacitancePerLength;
}



void
Technology::setSubsRelPermtvt
(bu::quantity<rrs::dimensionless> relPermittivity)
{
  substrateRelativePermittivity = relPermittivity;
}

bu::quantity<rrs::dimensionless> const &
Technology::getSubsRelPermtvt() const
{
  return this->substrateRelativePermittivity;
}

void
Technology::setSubsAbsPermtvt (
    bu::quantity<rrs::picofarad_per_meter_unit> absPermittivity,
    settingOptions setOpt)
{
  // If forced, ignore all tests
  if ( setOpt == forced ) {
    substrateAbsolutePermittivity = absPermittivity;
    return;
  }


  // Not enough information
  // TODO: Re-do tests to account for capacitance per length
  if ( areInvalid(absPermittivity,
                  substrateRelativePermittivity,
                  metalCapacitancePerLength)) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Substrate permittivity is unknown.\n");
    exceptionMsgThrown.append("Please include either:\n");
    exceptionMsgThrown.append("\"Substrate relative permittivity []\"");
    exceptionMsgThrown.append(":<value>\nor:\n");
    exceptionMsgThrown.append("\"Substrate absolute permittivity [pF/m]\":");
    exceptionMsgThrown.append(":<value>\nor:\n");
    exceptionMsgThrown.append("\"Metal capacitance per length [fF/um]\":");
    exceptionMsgThrown.append("<value>\nto your technology description file.");
    throw exceptionMsgThrown;
  }

  // More than enough information
  if (areValid(substrateRelativePermittivity, absPermittivity)) {
    setSubsAbsPermtvt(substrateRelativePermittivity);
    auto derivedPermtvt = substrateAbsolutePermittivity;

    if ( !areEqual(derivedPermtvt, absPermittivity) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Inconsistent data.");
      exceptionMsgThrown.append(" Substrate absolute permittivity given (");
      exceptionMsgThrown.append(to_string(absPermittivity));
      exceptionMsgThrown.append(") does not match with calculated (");
      exceptionMsgThrown.append(to_string(derivedPermtvt));
      exceptionMsgThrown.append(") based on the relative permittivity (");
      exceptionMsgThrown.append(to_string(substrateRelativePermittivity));
      exceptionMsgThrown.append("). Difference is ");
      exceptionMsgThrown.append(to_string(absPermittivity - derivedPermtvt));
      exceptionMsgThrown.append(".");
      throw exceptionMsgThrown;
    }
  }
  // Just enough information
  else if ( isValid(absPermittivity) ) {
    substrateAbsolutePermittivity = absPermittivity;
  }
  else if ( isValid( substrateRelativePermittivity ) ) {
    setSubsAbsPermtvt( substrateRelativePermittivity );
  }
  else {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("no condition satisfied during ");
    exceptionMsgThrown.append(" substrate absolute permittivity set.");
    throw exceptionMsgThrown;
  }

}

void
Technology::setSubsAbsPermtvt(bu::quantity<rrs::dimensionless> relPer)
{
  if ( isInvalid( relPer ) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to calculate the substrate absolute");
    exceptionMsgThrown.append(" permittivity based on its relative");
    exceptionMsgThrown.append(" permitivitty, which was");
    exceptionMsgThrown.append(" not valid.");
    throw exceptionMsgThrown;
  }
  substrateAbsolutePermittivity = relPer * 8.8541878*rrs::picofarads_per_meter;
}


bu::quantity<rrs::picofarad_per_meter_unit> const &
Technology::getSubsAbsPermtvt() const
{
  return this->substrateAbsolutePermittivity;
}



void
Technology::setBreakdownVoltage(bu::quantity<rrs::volt_unit> voltage)
{
  breakdownVoltage = voltage;
}

bu::quantity<rrs::volt_unit> const &
Technology::getBreakdownVoltage() const
{
  return this->breakdownVoltage;
}



void
Technology::setMinPMOSChannelLength(bu::quantity<rrs::nanometer_unit> length)
{
  minPMOSChannelLength = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMinPMOSChannelLength() const
{
  return this->minPMOSChannelLength;
}

void
Technology::setMinPMOSChannelWidth(bu::quantity<rrs::nanometer_unit> width)
{
  minPMOSChannelWidth = width;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMinPMOSChannelWidth() const
{
  return this->minPMOSChannelWidth;
}

void
Technology::setMinNMOSChannelLength(bu::quantity<rrs::nanometer_unit> length)
{
  minNMOSChannelLength = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMinNMOSChannelLength() const
{
  return this->minNMOSChannelLength;
}

void
Technology::setMinNMOSChannelWidth(bu::quantity<rrs::nanometer_unit> width)
{
  minNMOSChannelWidth = width;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getMinNMOSChannelWidth() const
{
  return this->minNMOSChannelWidth;
}



void
Technology::setNMOSResWidthProduct(bu::quantity<rrs::microohm_meter_unit> prod)
{
  nMOSResistanceWidthProduct = SCALE_QUANTITY(prod, rrs::nanoohm_meter_unit);
}

bu::quantity<rrs::nanoohm_meter_unit> const &
Technology::getNMOSResWidthProduct() const
{
  return this->nMOSResistanceWidthProduct;
}

void
Technology::setPMOSResWidthProduct(bu::quantity<rrs::microohm_meter_unit> prod)
{
  pMOSResistanceWidthProduct = SCALE_QUANTITY(prod, rrs::nanoohm_meter_unit);
}

bu::quantity<rrs::nanoohm_meter_unit> const &
Technology::getPMOSResWidthProduct() const
{
  return this->pMOSResistanceWidthProduct;
}


void
Technology::setGateExtensionOfActive(bu::quantity<rrs::nanometer_unit> length)
{
  gateExtensionOfActive = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getGateExtensionOfActive() const
{
  return this->gateExtensionOfActive;
}

void
Technology::setPolyToPolySpacing(bu::quantity<rrs::nanometer_unit> length)
{
  polyToPolySpacing = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getPolyToPolySpacing() const
{
  return this->polyToPolySpacing;
}

void
Technology::setActiveExtensionOfPoly(bu::quantity<rrs::nanometer_unit> length)
{
  activeExtensionOfPoly = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getActiveExtensionOfPoly() const
{
  return this->activeExtensionOfPoly;
}

void
Technology::setActiveToActiveSpacing(bu::quantity<rrs::nanometer_unit> length)
{
  activeToActiveSpacing = length;
}

bu::quantity<rrs::nanometer_unit> const &
Technology::getActiveToActiveSpacing() const
{
  return this->activeToActiveSpacing;
}



void
Technology::buildFromTechFile(const char* techFileName)
{
  JsonAssist jsonTech(techFileName);

  double magnitude = INVALID_DOUBLE;

  magnitude = jsonTech.getJSONNumber("Technology node [nm]",
                                        mandatory);
  setTechnologyNode( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Vcc [V]",
                                        mandatory);
  setVcc( magnitude * rrs::volts );

  magnitude = jsonTech.getJSONNumber("Metal half pitch [nm]",
                                        mandatory);
  setMetalHalfPitch( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Metal thickness [nm]",
                                        mandatory);
  setMetalThickness( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Metal resistivity [Ohm m]",
                                        optional);
  setMetalResistivity( magnitude * rrs::ohm_meters );

  magnitude = jsonTech.getJSONNumber("Metal sheet resistance [Ohm]",
                                        optional);
  setMetalSheetResistance( magnitude * rrs::ohms );

  magnitude = jsonTech.getJSONNumber("Metal resistance per length [Ohm/nm]",
                                        optional);
  setMetalResistancePerLength( magnitude * rrs::ohms_per_nanometer );

  magnitude = jsonTech.getJSONNumber("Metal capacitance per length [aF/nm]",
                                        optional);
  setMetalCapacitancePerLength( magnitude * rrs::nanofarads_per_meter );

  magnitude = jsonTech.getJSONNumber("Substrate relative permittivity []",
                                        optional);
  setSubsRelPermtvt( magnitude );

  magnitude = jsonTech.getJSONNumber("Substrate absolute permittivity [pF/m]",
                                        optional);
  setSubsAbsPermtvt( magnitude * rrs::picofarads_per_meter );

  magnitude = jsonTech.getJSONNumber("MOS breakdown voltage [V]",
                                        mandatory);
  setBreakdownVoltage( magnitude * rrs::volts );

  magnitude = jsonTech.getJSONNumber("Minimum PMOS channel length [nm]",
                                        mandatory);
  setMinPMOSChannelLength( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Minimum PMOS channel width [nm]",
                                        mandatory);
  setMinPMOSChannelWidth( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Minimum NMOS channel length [nm]",
                                        mandatory);
  setMinNMOSChannelLength( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Minimum NMOS channel width [nm]",
                                        mandatory);
  setMinNMOSChannelWidth( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber(
        "Minimum length NMOS resistance-width product"
        " [kohm_nm]",
        mandatory);
  setNMOSResWidthProduct( magnitude * rrs::microohm_meters );

  magnitude = jsonTech.getJSONNumber(
        "Minimum length PMOS resistance-width product"
        " [kohm_nm]",
        mandatory);
  setPMOSResWidthProduct( magnitude * rrs::microohm_meters );

  magnitude = jsonTech.getJSONNumber("Gate extension of active layer [nm]",
                                        mandatory);
  setGateExtensionOfActive( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Poly to poly spacing [nm]",
                                        mandatory);
  setPolyToPolySpacing( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Active layer extension of poly [nm]",
                                        mandatory);
  setActiveExtensionOfPoly( magnitude * rrs::nanometers );

  magnitude = jsonTech.getJSONNumber("Active to active spacing [nm]",
                                        mandatory);
  setActiveToActiveSpacing( magnitude * rrs::nanometers );

}



Technology::Technology()
{
  initialize();
}

Technology::Technology(const char* techFileName)
{
  initialize();

  try {
    buildFromTechFile(techFileName);
  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

Technology::~Technology()
{

}












