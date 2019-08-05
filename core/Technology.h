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



#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include "../utils/constants.h"
#include "../utils/functions.h"

#include "../parser/JsonAssist.h"

#include "../expandedBoostUnits/Units/rramSpec_units.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

class Technology
{

private:
  bu::quantity<rrs::nanometer_unit> technologyNode;

  bu::quantity<rrs::volt_unit> vcc;

  // Metal (WLs and BLs) parameters
  bu::quantity<rrs::nanometer_unit> metalHalfPitch;
  bu::quantity<rrs::nanometer_unit> metalThickness;

  bu::quantity<rrs::ohm_meter_unit> metalResistivity;
  bu::quantity<rrs::ohm_unit> metalSheetResistance;
  bu::quantity<rrs::ohm_per_nanometer_unit> metalResistancePerLength;


  // Substrate parameters (for capacitances calculation)
  bu::quantity<rrs::nanofarad_per_meter_unit> metalCapacitancePerLength;
  bu::quantity<rrs::dimensionless> substrateRelativePermittivity;
  bu::quantity<rrs::picofarad_per_meter_unit> substrateAbsolutePermittivity;

  // Array periphery transistor parameters
  bu::quantity<rrs::volt_unit> breakdownVoltage;

  bu::quantity<rrs::nanometer_unit> minPMOSChannelLength;
  bu::quantity<rrs::nanometer_unit> minPMOSChannelWidth;
  bu::quantity<rrs::nanometer_unit> minNMOSChannelLength;
  bu::quantity<rrs::nanometer_unit> minNMOSChannelWidth;

  bu::quantity<rrs::nanoohm_meter_unit> nMOSResistanceWidthProduct;
  bu::quantity<rrs::nanoohm_meter_unit> pMOSResistanceWidthProduct;

  // Technology design rules
  bu::quantity<rrs::nanometer_unit> gateExtensionOfActive;
  bu::quantity<rrs::nanometer_unit> polyToPolySpacing;
  bu::quantity<rrs::nanometer_unit> activeExtensionOfPoly;
  bu::quantity<rrs::nanometer_unit> activeToActiveSpacing;


  // Private setters
  void setMetalSheetResistance(bu::quantity<rrs::ohm_meter_unit>,
                               bu::quantity<rrs::nanometer_unit>);
  void setSubsAbsPermtvt(bu::quantity<rrs::dimensionless>);

public:
  Technology();
  Technology(const char*);
  ~Technology();

  void initialize();
  void buildFromTechFile(const char*);

  void setTechnologyNode(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getTechnologyNode() const;
  void setVcc(bu::quantity<rrs::volt_unit>);
  bu::quantity<rrs::volt_unit> const &getVcc() const;
  void setMetalHalfPitch(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMetalHalfPitch() const;
  void setMetalThickness(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMetalThickness() const;

  void setMetalResistivity(bu::quantity<rrs::ohm_meter_unit>);
  bu::quantity<rrs::ohm_meter_unit> const &getMetalResistivity() const;
  void setMetalSheetResistance(bu::quantity<rrs::ohm_unit>,
                               settingOptions setOpt = normal_opt);
  bu::quantity<rrs::ohm_unit> const &getMetalSheetResistance() const;
  void setMetalResistancePerLength(
      bu::quantity<rrs::ohm_per_nanometer_unit>,
      settingOptions setOpt = normal_opt);
  bu::quantity<rrs::ohm_per_nanometer_unit>
      const &getMetalResistancePerLength() const;

  void setMetalCapacitancePerLength(
      bu::quantity<rrs::nanofarad_per_meter_unit>);
  bu::quantity<rrs::nanofarad_per_meter_unit>
      const &getMetalCapacitancePerLength() const;

  void setSubsRelPermtvt(bu::quantity<rrs::dimensionless>);
  bu::quantity<rrs::dimensionless> const &getSubsRelPermtvt() const;
  void setSubsAbsPermtvt(bu::quantity<rrs::picofarad_per_meter_unit>,
                         settingOptions setOpt = normal_opt);
  bu::quantity<rrs::picofarad_per_meter_unit> const &getSubsAbsPermtvt() const;

  // Thick oxide transistor parameters
  void setBreakdownVoltage(bu::quantity<rrs::volt_unit>);
  bu::quantity<rrs::volt_unit> const &getBreakdownVoltage() const;

  void setMinPMOSChannelLength(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMinPMOSChannelLength() const;
  void setMinPMOSChannelWidth(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMinPMOSChannelWidth() const;
  void setMinNMOSChannelLength(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMinNMOSChannelLength() const;
  void setMinNMOSChannelWidth(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getMinNMOSChannelWidth() const;

  void setNMOSResWidthProduct(bu::quantity<rrs::microohm_meter_unit>);
  bu::quantity<rrs::nanoohm_meter_unit> const &getNMOSResWidthProduct() const;
  void setPMOSResWidthProduct(bu::quantity<rrs::microohm_meter_unit>);
  bu::quantity<rrs::nanoohm_meter_unit> const &getPMOSResWidthProduct() const;

  void setGateExtensionOfActive(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getGateExtensionOfActive() const;
  void setPolyToPolySpacing(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getPolyToPolySpacing() const;
  void setActiveExtensionOfPoly(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getActiveExtensionOfPoly() const;
  void setActiveToActiveSpacing(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getActiveToActiveSpacing() const;

};
#endif //TECHNOLOGY_H


















