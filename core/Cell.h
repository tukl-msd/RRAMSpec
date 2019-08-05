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



#ifndef CELL_H
#define CELL_H

#include "../utils/constants.h"
#include "../utils/functions.h"

#include "../parser/JsonAssist.h"

#include "../expandedBoostUnits/Units/rramSpec_units.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

class Cell
{
private:
  // Memory device parameters
  bu::quantity<rrs::ohm_unit> memDevHRSResistance;
  bu::quantity<rrs::ohm_unit> memDevLRSResistance;
  ebool memDevResistanceState;
  bu::quantity<rrs::ohm_unit> memDevInstantResistance;


  // Selector device model
  enum selDevModels { semiIdeal, IxV, INVALID_MODEL };
  selDevModels selDevModel;

  // Selector device parameters - Semi-ideal model
  bu::quantity<rrs::volt_unit> selDevSnapVoltage;
  bu::quantity<rrs::nanoampere_unit> selDevLeakageCurrent;
  bu::quantity<rrs::nanoampere_unit> selDevMaxCurrent;

  // Selector device parameters - IxV curve model
  vector<bu::quantity<rrs::volt_unit>> selVoltageDataPoints;
  vector<bu::quantity<rrs::nanoampere_unit>> selCurrentDataPoints;

  // Precision parameters
  bu::quantity<rrs::dimensionless> maxCurrentRelativeError;

  // Cell electrical parameters
  vector<vector<bu::quantity<rrs::volt_unit>>> cellVoltageDataPoints;
  vector<vector<bu::quantity<rrs::nanoampere_unit>>> cellCurrentDataPoints;

  bu::quantity<rrs::volt_unit> setVoltage;
  bu::quantity<rrs::nanoampere_unit> setCurrent;
  bu::quantity<rrs::nanoampere_unit> setComplianceCurrent;
  bu::quantity<rrs::volt_unit> resetVoltage;
  bu::quantity<rrs::nanoampere_unit> resetCurrent;
  bu::quantity<rrs::volt_unit> readVoltage;
  bu::quantity<rrs::nanoampere_unit> readCurrent;
  bu::quantity<rrs::dimensionless> readCurrentRatio;

  // Cell timing parameters
  bu::quantity<rrs::nanosecond_unit> setTime;
  bu::quantity<rrs::nanosecond_unit> resetTime;
  bu::quantity<rrs::nanosecond_unit> setTimeC;
  bu::quantity<rrs::per_volt_unit> setTimeK;
  bu::quantity<rrs::nanosecond_unit> resetTimeC;
  bu::quantity<rrs::per_volt_unit> resetTimeK;

  // Cell mechanical parameters
  //  Width - in the wordlines (rows) direction
  bu::quantity<rrs::nanometer_unit> cellWidth;
  //  Height - in the bitlines (columns) direction
  bu::quantity<rrs::nanometer_unit> cellHeight;
  //  Spacing in between cells
  bu::quantity<rrs::nanometer_unit> cellToCellSpacing;
  //  Thickness - in the die thickness direction
  bu::quantity<rrs::nanometer_unit> cellThickness;

public:
  Cell();
  Cell(const char* cellFileName);
  ~Cell();

  void initialize();
  void buildFromCellFile(const char* cellFileName);

  // Set/Get memory device maximum resistance (High Resistance State)
  void setMemDevHRSResistance(bu::quantity<rrs::ohm_unit>);
  bu::quantity<rrs::ohm_unit> const &getMemDevHRSResistance() const;
  // Set/Get memory device minimum resistance (Low Resistance State)
  void setMemDevLRSResistance(bu::quantity<rrs::ohm_unit>);
  bu::quantity<rrs::ohm_unit> const &getMemDevLRSResistance()  const;
  // Set/Get memory device resistance state (0 to HRS and 1 to LRS)
  void setMemDevResistanceState(ebool);
  ebool const &getMemDevResistanceState() const ;
  // Returns memory device instant (at the moment) resistance
  bu::quantity<rrs::ohm_unit> const &getMemDevInstantResistance() const;


  // Defines which selector model is to be used
  void setSelDevModel(string, settingOptions = normal_opt);
  string getSelDevModel();

  // Semi-ideal selector model
  // Threshold voltage of selector device (VSnap)
  void setSelDevSnapVoltage(bu::quantity<rrs::volt_unit>);
  bu::quantity<rrs::volt_unit> const &getSelDevSnapVoltage() const;
  // Selector device leakage current (ISel @ VSel < VSnap)
  void setSelDevLeakageCurrent(bu::quantity<rrs::nanoampere_unit>);
  bu::quantity<rrs::nanoampere_unit> const &getSelDevLeakageCurrent() const;
  // Maximum selector device current (max ISel @ VSel >= VSnap)
  void setSelDevMaxCurrent(bu::quantity<rrs::nanoampere_unit>);
  bu::quantity<rrs::nanoampere_unit> const &getSelDevMaxCurrent() const;

  // Selector device model based on I x V curve data points
  //  For a voltage drop of selVoltageDataPoints.at(i) at the selector
  //    a current of selCurrentDataPoints.at(i) must be flowing,
  //    for i = [0, selVoltageDataPoints.size())
  //  Both selVoltageDataPoints and selCurrentDataPoints must be in
  //    ascending order (I x V curve must be monotonically increasing)
  //  For voltage drop value in between two given data points,
  //    some kind of interplolation might be used.
  void setSelVoltageDataPoint(bu::quantity<rrs::volt_unit>);
  vector<bu::quantity<rrs::volt_unit>> const &getSelVoltageDataPoints() const;
  void setSelCurrentDataPoint(bu::quantity<rrs::nanoampere_unit>);
  vector<bu::quantity<rrs::nanoampere_unit>>
                                       const &getSelCurrentDataPoints() const;


  // Set/Get maximum current relative error
  void setMaxCurrentRelativeError(bu::quantity<rrs::dimensionless>);
  bu::quantity<rrs::dimensionless> const &getMaxCurrentRelativeError() const;


  // Set/Get cell main (voltage, current) pairs
  void setCellSetVoltage(bu::quantity<rrs::volt_unit>,
                         settingOptions opt = normal_opt);
  bu::quantity<rrs::volt_unit> const &getCellSetVoltage() const;
  void setCellSetCurrent(bu::quantity<rrs::nanoampere_unit>,
                         settingOptions opt = normal_opt);
  bu::quantity<rrs::nanoampere_unit> const &getCellSetCurrent() const;
  void setCellSetComplianceCurrent(bu::quantity<rrs::nanoampere_unit>);
  bu::quantity<rrs::nanoampere_unit> const &getCellSetComplianceCurrent() const;

  void setCellResetVoltage(bu::quantity<rrs::volt_unit>,
                           settingOptions opt = normal_opt);
  bu::quantity<rrs::volt_unit> const &getCellResetVoltage() const;
  void setCellResetCurrent(bu::quantity<rrs::nanoampere_unit>,
                           settingOptions opt = normal_opt);
  bu::quantity<rrs::nanoampere_unit> const &getCellResetCurrent() const;

  void setCellReadVoltage(bu::quantity<rrs::volt_unit>,
                          settingOptions opt = normal_opt);
  bu::quantity<rrs::volt_unit> const &getCellReadVoltage() const;
  void setCellReadCurrent(bu::quantity<rrs::nanoampere_unit>,
                          settingOptions opt = normal_opt);
  bu::quantity<rrs::nanoampere_unit> const &getCellReadCurrent() const;
  void setCellReadCurrentRatio(bu::quantity<rrs::dimensionless>,
                               settingOptions opt = normal_opt);
  bu::quantity<rrs::dimensionless> const &getCellReadCurrentRatio() const;

  //Set/Get set/reset time
  void setCellSetTime(bu::quantity<rrs::nanosecond_unit>);
  void setCellSetTime(bu::quantity<rrs::volt_unit>);
  bu::quantity<rrs::nanosecond_unit> const &getCellSetTime() const;
  void setCellResetTime(bu::quantity<rrs::nanosecond_unit>);
  void setCellResetTime(bu::quantity<rrs::volt_unit>);
  bu::quantity<rrs::nanosecond_unit> const &getCellResetTime() const;

  //Set/Get set/reset time scaling factors
  void setCellSetTimeC(bu::quantity<rrs::nanosecond_unit>);
  bu::quantity<rrs::nanosecond_unit> const &getCellSetTimeC() const;
  void setCellSetTimeK(bu::quantity<rrs::per_volt_unit>);
  bu::quantity<rrs::per_volt_unit> const &getCellSetTimeK() const;

  void setCellResetTimeC(bu::quantity<rrs::nanosecond_unit>);
  bu::quantity<rrs::nanosecond_unit> const &getCellResetTimeC() const;
  void setCellResetTimeK(bu::quantity<rrs::per_volt_unit>);
  bu::quantity<rrs::per_volt_unit> const &getCellResetTimeK() const;


  //Set/Get cell mechanical parameters
  void setCellWidth(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getCellWidth() const;

  void setCellHeight(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getCellHeight() const;

  void setCellToCellSpacing(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getCellToCellSpacing() const;

  void setCellThickness(bu::quantity<rrs::nanometer_unit>);
  bu::quantity<rrs::nanometer_unit> const &getCellThickness() const;


  // Calculates current through selector device given applied voltage
  // Made public simply to enable testing - NOT TO USE ELSEWHERE!
  bu::quantity<rrs::nanoampere_unit> calcSelCurrent(
      bu::quantity<rrs::volt_unit>);

  // Calculates current through cell (memory + selector devices)
  //  given applied voltage
  bu::quantity<rrs::nanoampere_unit> calcCellCurrent(
      bu::quantity<rrs::volt_unit>,
      bu::quantity<rrs::dimensionless> relError = INVALID_DOUBLE);

  // Calculates voltage across cell given current flow
  // Made public simply to enable testing - NOT TO USE ELSEWHERE!
  bu::quantity<rrs::volt_unit> calcCellVoltage(
      bu::quantity<rrs::nanoampere_unit>);

  void buildCellIxV(bu::quantity<rrs::volt_unit> vStep = 1e-6 * rrs::volts,
                    bu::quantity<rrs::dimensionless> maxRelError = 1e-3);
  bu::quantity<rrs::nanoampere_unit> getCellCurrent(
      bu::quantity<rrs::volt_unit> cellVoltage);
  bu::quantity<rrs::nanoampere_unit> getCellCurrent(
      bu::quantity<rrs::volt_unit> cellVoltage,
      ebool state);
  bu::quantity<rrs::volt_unit> getCellVoltage(
      bu::quantity<rrs::nanoampere_unit> cellCurrent);
  bu::quantity<rrs::volt_unit> getCellVoltage(
      bu::quantity<rrs::nanoampere_unit> cellCurrent,
      ebool state);





};
#endif //CELL_H
