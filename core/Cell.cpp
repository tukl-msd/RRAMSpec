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



#include "Cell.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

void
Cell::initialize()
{
  memDevHRSResistance = INVALID_DOUBLE * rrs::ohms;
  memDevLRSResistance = INVALID_DOUBLE * rrs::ohms;
  memDevResistanceState = INVALID_EBOOL;
  memDevInstantResistance = INVALID_DOUBLE * rrs::ohms;

  selDevModel = INVALID_MODEL;

  selDevSnapVoltage = INVALID_DOUBLE * rrs::volts;
  selDevLeakageCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  selDevMaxCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  selVoltageDataPoints.push_back(INVALID_DOUBLE * rrs::volts);
  selCurrentDataPoints.push_back(INVALID_DOUBLE * rrs::nanoamperes);

  // HRS (0) and LRS (1)
  cellVoltageDataPoints.resize(2);
  cellCurrentDataPoints.resize(2);
  cellVoltageDataPoints.at(0).push_back(INVALID_DOUBLE * rrs::volts);
  cellCurrentDataPoints.at(0).push_back(INVALID_DOUBLE * rrs::nanoamperes);
  cellVoltageDataPoints.at(1).push_back(INVALID_DOUBLE * rrs::volts);
  cellCurrentDataPoints.at(1).push_back(INVALID_DOUBLE * rrs::nanoamperes);

  setVoltage = INVALID_DOUBLE * rrs::volts;
  setCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  setComplianceCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  resetVoltage = INVALID_DOUBLE * rrs::volts;
  resetCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readVoltage = INVALID_DOUBLE * rrs::volts;
  readCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readCurrentRatio = INVALID_DOUBLE;

  setTime = INVALID_DOUBLE * rrs::nanoseconds;
  setTimeC = INVALID_DOUBLE * rrs::nanoseconds;
  setTimeK = INVALID_DOUBLE * rrs::per_volt;
  resetTime = INVALID_DOUBLE * rrs::nanoseconds;
  resetTimeC = INVALID_DOUBLE * rrs::nanoseconds;
  resetTimeK = INVALID_DOUBLE * rrs::per_volt;

  cellWidth = INVALID_DOUBLE * rrs::nanometers;
  cellHeight = INVALID_DOUBLE * rrs::nanometers;
  cellToCellSpacing = INVALID_DOUBLE * rrs::nanometers;
  cellThickness = INVALID_DOUBLE * rrs::nanometers;

  maxCurrentRelativeError = INVALID_DOUBLE;
}


void
Cell::setMemDevHRSResistance(bu::quantity<rrs::ohm_unit> HRS)
{
  memDevHRSResistance = HRS;
  if (memDevResistanceState == 0) {
    memDevInstantResistance = memDevHRSResistance;
  }
}

bu::quantity<rrs::ohm_unit> const &
Cell::getMemDevHRSResistance() const
{
  return this->memDevHRSResistance;
}


void
Cell::setMemDevLRSResistance(bu::quantity<rrs::ohm_unit> LRS)
{
  memDevLRSResistance = LRS;
  if (memDevResistanceState == 1) {
    memDevInstantResistance = memDevLRSResistance;
  }
}

bu::quantity<rrs::ohm_unit> const &
Cell::getMemDevLRSResistance() const
{
  return this->memDevLRSResistance;
}


void
Cell::setMemDevResistanceState(ebool state)
{
  memDevResistanceState = state;
  if (memDevResistanceState == 0) {
    memDevInstantResistance = memDevHRSResistance;
  }
  else if (memDevResistanceState == 1) {
    memDevInstantResistance = memDevLRSResistance;
  }
  else {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("tried to set a flag to");
      exceptionMsgThrown.append(" a value different from");
      exceptionMsgThrown.append(" 0 (false) or 1 (true)");
      exceptionMsgThrown.append(" while setting memory");
      exceptionMsgThrown.append(" device state.");
      throw exceptionMsgThrown;
  }
}

ebool const &
Cell::getMemDevResistanceState() const
{
  return this->memDevResistanceState;
}


bu::quantity<rrs::ohm_unit> const &
Cell::getMemDevInstantResistance() const
{
  return this->memDevInstantResistance;
}



void
Cell::setSelDevModel(string selModelStr, settingOptions setOpt)
{
  if ( selModelStr == "semiIdeal" ) {
    selDevModel = semiIdeal;

    // Ignore tests if is forced
    if ( setOpt == forced ) {
      return;
    }
    // Tests
    if (!areValid(selDevSnapVoltage, selDevLeakageCurrent, selDevMaxCurrent)) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("Tried to set semi ideal selector model,");
      exceptionMsgThrown.append(" but one or more of the following");
      exceptionMsgThrown.append(" parameters were invalid:");
      exceptionMsgThrown.append("\nSelector snap voltage;");
      exceptionMsgThrown.append("\nSelector leakage current;");
      exceptionMsgThrown.append("\nSelector maximum current.");
      throw exceptionMsgThrown;
    }
  }
  else if ( selModelStr == "IxV" ) {
    selDevModel = IxV;
    // Ignore tests if is forced
    if ( setOpt == forced ) {
      return;
    }
    // Tests
    if ( selVoltageDataPoints.size() != selCurrentDataPoints.size() ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("IxV curve based selector model");
      exceptionMsgThrown.append(" needs same number of");
      exceptionMsgThrown.append(" voltage and current data points.");
      throw exceptionMsgThrown;
    }
    if ( !is_sorted(selVoltageDataPoints.begin(),
                    selVoltageDataPoints.end())
         || !is_sorted(selCurrentDataPoints.begin(),
                       selCurrentDataPoints.end())
       )
    {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("IxV curve based selector model");
      exceptionMsgThrown.append(" needs the data points");
      exceptionMsgThrown.append(" (both voltage and current)");
      exceptionMsgThrown.append(" to be sorted and, therefore,");
      exceptionMsgThrown.append(" monotonic.");
      throw exceptionMsgThrown;
    }
    bool found_0_0 = false;
    for (size_t i = 0; i < selVoltageDataPoints.size(); ++i) {
      if ( selVoltageDataPoints.at(i) == 0 * rrs::volts
           && selCurrentDataPoints.at(i) == 0 * rrs::nanoamperes ) {
        found_0_0 = true;
        break;
      }
    }
    if ( found_0_0 == false ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("IxV curve based selector model");
      exceptionMsgThrown.append(" must include origin point, i.e.,");
      exceptionMsgThrown.append(" (0 V, 0 A), since cells are not capable");
      exceptionMsgThrown.append(" of generating energy (AFAIK).");
      throw exceptionMsgThrown;
    }
  }
  else {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Tried to set a selector model, \"");
      exceptionMsgThrown.append(selModelStr);
      exceptionMsgThrown.append("\", different from the ones supported:\n");
      exceptionMsgThrown.append("  \"semiIdeal\"\n");
      exceptionMsgThrown.append("  \"IxV\"\n");
      throw exceptionMsgThrown;
  }
}

string
Cell::getSelDevModel()
{
  string selModelStr;
  switch (selDevModel) {
    case semiIdeal:     selModelStr = "semiIdeal";    break;
    case IxV:           selModelStr = "IxV";          break;
    case INVALID_MODEL: selModelStr = INVALID_STRING; break;

    default:            selModelStr = "UNLISTED";     break;
  }

  if ( selModelStr == "UNLISTED" ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to get selector device model,");
    exceptionMsgThrown.append(" but its value is not listed.");
    throw exceptionMsgThrown;
  }

  return selModelStr;
}


void
Cell::setSelDevSnapVoltage(bu::quantity<rrs::volt_unit> vSnap)
{
  selDevSnapVoltage = vSnap;
  selDevModel = INVALID_MODEL;
}

bu::quantity<rrs::volt_unit> const &
Cell::getSelDevSnapVoltage() const
{
  return this->selDevSnapVoltage;
}


void
Cell::setSelDevLeakageCurrent(bu::quantity<rrs::nanoampere_unit> iLeak)
{
  selDevLeakageCurrent = iLeak;
  selDevModel = INVALID_MODEL;
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getSelDevLeakageCurrent() const
{
  return this->selDevLeakageCurrent;
}


void
Cell::setSelDevMaxCurrent(bu::quantity<rrs::nanoampere_unit> iSelMax)
{
  selDevMaxCurrent = iSelMax;
  selDevModel = INVALID_MODEL;
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getSelDevMaxCurrent() const
{
  return this->selDevMaxCurrent;
}



void
Cell::setSelVoltageDataPoint(bu::quantity<rrs::volt_unit> vPoint)
{
  if ( selVoltageDataPoints.empty() ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Selector device voltage data points vector");
    exceptionMsgThrown.append(" for IxV curve based model");
    exceptionMsgThrown.append(" was not correctly initialized or got");
    exceptionMsgThrown.append(" cleared (should not happen!).");
    throw exceptionMsgThrown;
  }
  if ( isInvalid( selVoltageDataPoints.back() ) ) {
    selVoltageDataPoints.pop_back();
  }
  selVoltageDataPoints.push_back(vPoint);
  selDevModel = INVALID_MODEL;
}

vector<bu::quantity<rrs::volt_unit>> const &
Cell::getSelVoltageDataPoints() const
{
  return this->selVoltageDataPoints;
}


void
Cell::setSelCurrentDataPoint(bu::quantity<rrs::nanoampere_unit> iPoint)
{
  if ( selVoltageDataPoints.empty() ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Selector device current data points vector");
    exceptionMsgThrown.append(" for IxV curve based model");
    exceptionMsgThrown.append(" was not correctly initialized or got");
    exceptionMsgThrown.append(" cleared (should not happen!).");
    throw exceptionMsgThrown;
  }
  if ( isInvalid ( selCurrentDataPoints.back() ) ) {
    selCurrentDataPoints.pop_back();
  }
  selCurrentDataPoints.push_back(iPoint);
  selDevModel = INVALID_MODEL;
}

vector<bu::quantity<rrs::nanoampere_unit>> const &
Cell::getSelCurrentDataPoints() const
{
  return this->selCurrentDataPoints;
}

void
Cell::setMaxCurrentRelativeError(bu::quantity<rrs::dimensionless> maxIRelErr)
{
  maxCurrentRelativeError = maxIRelErr;
}

bu::quantity<rrs::dimensionless> const &
Cell::getMaxCurrentRelativeError() const
{
  return this->maxCurrentRelativeError;
}



void
Cell::setCellSetVoltage(bu::quantity<rrs::volt_unit> vSet,
                        settingOptions opt)
{
  if ( isInvalid(vSet) ) { return; }
  setVoltage = vSet;
  if ( opt == only_set ) { return; }
  setCellSetTime(setVoltage);
  setCellSetCurrent(getCellCurrent(setVoltage, false), only_set);
}

bu::quantity<rrs::volt_unit> const &
Cell::getCellSetVoltage() const
{
  return this->setVoltage;
}

void
Cell::setCellSetCurrent(bu::quantity<rrs::nanoampere_unit> iSet,
                        settingOptions opt)
{
  if ( isInvalid(iSet) ) { return; }
  setCurrent = iSet;
  if ( opt == only_set ) { return; }
  setCellSetVoltage(getCellVoltage(iSet, false));
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getCellSetCurrent() const
{
  return this->setCurrent;
}

void
Cell::setCellSetComplianceCurrent(bu::quantity<rrs::nanoampere_unit> icc)
{
  setComplianceCurrent = icc;
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getCellSetComplianceCurrent() const
{
  return this->setComplianceCurrent;
}

void
Cell::setCellSetTime(bu::quantity<rrs::nanosecond_unit> tSet)
{
  if ( isInvalid(tSet) ) { return; }
  setTime = tSet;
  if ( areValid( setTimeC, setTimeK ) ) {
    setCellSetVoltage(-log(tSet / setTimeC) / setTimeK);
  }
}

void
Cell::setCellSetTime(bu::quantity<rrs::volt_unit> VSet)
{
  if ( areValid( setTimeC, setTimeK ) ) {
    setTime = setTimeC * exp(-setTimeK * VSet);
  }
}

bu::quantity<rrs::nanosecond_unit> const &
Cell::getCellSetTime() const
{
  return this->setTime;
}


void
Cell::setCellResetVoltage(bu::quantity<rrs::volt_unit> vReset,
                        settingOptions opt)
{
  if ( isInvalid(vReset) ) { return; }
  resetVoltage = vReset;
  if ( opt == only_set ) { return; }
  setCellResetTime(resetVoltage);
  setCellResetCurrent(getCellCurrent(resetVoltage, true), only_set);
}

bu::quantity<rrs::volt_unit> const &
Cell::getCellResetVoltage() const
{
  return this->resetVoltage;
}

void
Cell::setCellResetCurrent(bu::quantity<rrs::nanoampere_unit> iReset,
                          settingOptions opt)
{
  if ( isInvalid(iReset) ) { return; }
  resetCurrent = iReset;
  if ( opt == only_set ) { return; }
  setCellResetVoltage(getCellVoltage(iReset, true));
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getCellResetCurrent() const
{
  return this->resetCurrent;
}

void
Cell::setCellResetTime(bu::quantity<rrs::nanosecond_unit> tReset)
{
  if ( isInvalid(tReset) ) { return; }
  resetTime = tReset;
  if ( areValid( resetTimeC, resetTimeK ) ) {
    setCellResetVoltage(-log(tReset / resetTimeC) / resetTimeK);
  }
}

void
Cell::setCellResetTime(bu::quantity<rrs::volt_unit> vReset)
{
  if ( areValid( resetTimeC, resetTimeK ) ) {
    resetTime = resetTimeC * exp(-resetTimeK * vReset);
  }
}

bu::quantity<rrs::nanosecond_unit> const &
Cell::getCellResetTime() const
{
  return this->resetTime;
}


void
Cell::setCellReadVoltage(bu::quantity<rrs::volt_unit> vRead,
                        settingOptions opt)
{
  if ( isInvalid(vRead) ) { return; }
  readVoltage = vRead;
  if ( opt == only_set ) { return; }
  setCellReadCurrent(getCellCurrent(readVoltage, memDevResistanceState),
                      only_set);
}

bu::quantity<rrs::volt_unit> const &
Cell::getCellReadVoltage() const
{
  return this->readVoltage;
}

void
Cell::setCellReadCurrent(bu::quantity<rrs::nanoampere_unit> iRead,
                         settingOptions opt)
{
  if ( isInvalid(iRead) ) { return; }
  readCurrent = iRead;
  if ( opt == only_set ) { return; }
  setCellReadVoltage(getCellVoltage(iRead, memDevResistanceState));
}

bu::quantity<rrs::nanoampere_unit> const &
Cell::getCellReadCurrent() const
{
  return this->readCurrent;
}

void
Cell::setCellReadCurrentRatio(bu::quantity<rrs::dimensionless> iRatio,
                              settingOptions opt)
{
  if ( isInvalid(iRatio) ) { return; }
  readCurrentRatio = iRatio;
  if ( opt == only_set ) { return; }
//  setCellReadVoltage(getCellVoltage(iRatio, memDevResistanceState));
}

bu::quantity<rrs::dimensionless> const &
Cell::getCellReadCurrentRatio() const
{
  return this->readCurrentRatio;
}


void
Cell::setCellSetTimeC(bu::quantity<rrs::nanosecond_unit> setC)
{
  setTimeC = setC;
}

bu::quantity<rrs::nanosecond_unit> const &
Cell::getCellSetTimeC() const
{
  return this->setTimeC;
}

void
Cell::setCellSetTimeK(bu::quantity<rrs::per_volt_unit> setK)
{
  setTimeK = setK;
}

bu::quantity<rrs::per_volt_unit> const &
Cell::getCellSetTimeK() const
{
  return this->setTimeK;
}


void
Cell::setCellResetTimeC(bu::quantity<rrs::nanosecond_unit> resetC)
{
  resetTimeC = resetC;
}

bu::quantity<rrs::nanosecond_unit> const &
Cell::getCellResetTimeC() const
{
  return this->resetTimeC;
}

void
Cell::setCellResetTimeK(bu::quantity<rrs::per_volt_unit> resetK)
{
  resetTimeK = resetK;
}

bu::quantity<rrs::per_volt_unit> const &
Cell::getCellResetTimeK() const
{
  return this->resetTimeK;
}



void
Cell::setCellWidth(bu::quantity<rrs::nanometer_unit> width)
{
  cellWidth = width;
}

bu::quantity<rrs::nanometer_unit> const &
Cell::getCellWidth() const
{
  return this->cellWidth;
}

void
Cell::setCellHeight(bu::quantity<rrs::nanometer_unit> height)
{
  cellHeight = height;
}

bu::quantity<rrs::nanometer_unit> const &
Cell::getCellHeight() const
{
  return this->cellHeight;
}

void
Cell::setCellToCellSpacing(bu::quantity<rrs::nanometer_unit> spacing)
{
  cellToCellSpacing = spacing;
}

bu::quantity<rrs::nanometer_unit> const &
Cell::getCellToCellSpacing() const
{
  return this->cellToCellSpacing;
}

void
Cell::setCellThickness(bu::quantity<rrs::nanometer_unit> thickness)
{
  cellThickness = thickness;
}

bu::quantity<rrs::nanometer_unit> const &
Cell::getCellThickness() const
{
  return this->cellThickness;
}



bu::quantity<rrs::nanoampere_unit>
Cell::calcSelCurrent(bu::quantity<rrs::volt_unit> selVoltage)
{
  if (selDevModel == semiIdeal)
  {
    auto ISel = selDevLeakageCurrent;
    if (selVoltage == 0. * rrs::volts) {
      return 0. * rrs::nanoamperes;
    }
    else if (abs(selVoltage) < selDevSnapVoltage) {
      ISel = selDevLeakageCurrent;
    }
    else {
      ISel = selDevMaxCurrent;
    }
    if(selVoltage < 0 * rrs::volts) {
      return -ISel;
    }
    return ISel;
  }
  else if (selDevModel == IxV ) {
    auto firstGreaterIndex =
          findLowestGreater(selVoltageDataPoints, abs(selVoltage));

    // If selVoltage >= max(selVoltageDataPoints), get highest current
    auto ISel = selCurrentDataPoints.at(firstGreaterIndex - 1);

    // Linear interpolation between two (V,I) pairs
    if ( firstGreaterIndex < selVoltageDataPoints.size() ) {
      auto x0 = selVoltageDataPoints.at(firstGreaterIndex - 1);
      auto x1 = selVoltageDataPoints.at(firstGreaterIndex);
      auto y0 = selCurrentDataPoints.at(firstGreaterIndex - 1);
      auto y1 = selCurrentDataPoints.at(firstGreaterIndex);

      ISel = (abs(selVoltage) - x0) * (y1 - y0) / (x1 - x0) + y0;
    }
    // Assume symmetrical IxV curve
    if(selVoltage < 0 * rrs::volts) {
      return -ISel;
    }
    return ISel;
  }
  else {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to USE a selector model ");
    exceptionMsgThrown.append("different from the ones supported.");
    exceptionMsgThrown.append(" Likely, some selector parameter(s) were");
    exceptionMsgThrown.append(" changed after the model was set, or the");
    exceptionMsgThrown.append(" the model was never set.");
    throw exceptionMsgThrown;
  }
}

bu::quantity<rrs::nanoampere_unit>
Cell::calcCellCurrent(bu::quantity<rrs::volt_unit> cellVoltage,
                      bu::quantity<rrs::dimensionless> relError)
{
  if ( selDevModel == semiIdeal ) {
    auto absCellVoltage = abs(cellVoltage);
    bu::quantity<rrs::nanoampere_unit> absCellCurrent;
    absCellCurrent = absCellVoltage /
                  SCALE_QUANTITY(memDevInstantResistance, rrs::gigaohm_unit);
    // Voltage is small enough not to force ILeak through memRes
    if ( absCellCurrent < selDevLeakageCurrent ) {
      if ( cellVoltage > 0 * rrs::volts ) {
        return absCellCurrent;
      }
      else {
        return -absCellCurrent;
      }
    }

    // Voltage is large enough to force ILeak through memRes
    //  but smaller than the snap voltage
    if ( absCellVoltage < selDevSnapVoltage ) {
      if ( cellVoltage > 0 * rrs::volts ) {
        return selDevLeakageCurrent;
      }
      else {
        return -selDevLeakageCurrent;
      }
    }

    // Voltage is larger than the snap voltage
    absCellCurrent = (absCellVoltage - selDevSnapVoltage) /
                  SCALE_QUANTITY(memDevInstantResistance, rrs::gigaohm_unit);
    // Voltage is only slightly higher than the snap voltage
    if ( absCellCurrent < selDevLeakageCurrent ) {
      if ( cellVoltage > 0 * rrs::volts ) {
        return selDevLeakageCurrent;
      }
      else {
        return -selDevLeakageCurrent;
      }
    }
    // Voltage is higher than the snap voltage, but selector can
    //  "provide" the current
    if ( absCellCurrent < selDevMaxCurrent ) {
      if ( cellVoltage > 0 * rrs::volts ) {
        return absCellCurrent;
      }
      else {
        return -absCellCurrent;
      }
    }
    // Voltage is much higher than the snap voltage, so selector
    //  clips the current
    else {
      if ( cellVoltage > 0 * rrs::volts ) {
        return selDevMaxCurrent;
      }
      else {
        return -selDevMaxCurrent;
      }
    }
    // Should never get to this point
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Was unable to calculate cell current ");
    exceptionMsgThrown.append("using semi ideal selector model.");
    throw exceptionMsgThrown;
    return INVALID_DOUBLE * rrs::nanoamperes;
  }
  else if ( selDevModel == IxV ) {
    bu::quantity<rrs::volt_unit> memDevVoltage = cellVoltage/2.0;
    bu::quantity<rrs::volt_unit> selVoltage = cellVoltage/2.0;

    bu::quantity<rrs::nanoampere_unit> memDevCurrent;
    memDevCurrent = SCALE_QUANTITY(memDevVoltage/memDevInstantResistance,
                                   rrs::nanoampere_unit);

    bu::quantity<rrs::nanoampere_unit> selCurrent = calcSelCurrent(selVoltage);

    // Voltage resolution starts high (half of VSet)
    //  and decreases exponetially (binary search)
    bu::quantity<rrs::volt_unit> voltageResolution = abs(cellVoltage)/2.0;
    if ( isInvalid(relError) ) {
      relError = maxCurrentRelativeError;
    }
    while (!fastAreEqual(memDevCurrent, selCurrent, relError)) {
      voltageResolution /= 2;
      if ( memDevCurrent > selCurrent ) {
        memDevVoltage -= voltageResolution;
        selVoltage    += voltageResolution;
      } else {
        memDevVoltage += voltageResolution;
        selVoltage    -= voltageResolution;
      }
      memDevCurrent = SCALE_QUANTITY(memDevVoltage/memDevInstantResistance,
                                     rrs::nanoampere_unit);
      selCurrent = calcSelCurrent(selVoltage);
    }

    return (memDevCurrent + selCurrent) / 2.0;
  }
  else {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to USE a selector model ");
    exceptionMsgThrown.append("different from the ones supported.");
    exceptionMsgThrown.append(" Likely, some selector parameter(s) were");
    exceptionMsgThrown.append(" changed after the model was set, or the");
    exceptionMsgThrown.append(" the model was never set.");
    throw exceptionMsgThrown;
  }
}

bu::quantity<rrs::volt_unit>
Cell::calcCellVoltage(bu::quantity<rrs::nanoampere_unit> cellCurrent)
{
  bu::quantity<rrs::volt_unit> initVoltage = 5 * rrs::volts;
  if ( cellCurrent > 0 * rrs::nanoamperes ) {
    initVoltage = initVoltage;
  }
  else if ( cellCurrent < 0 * rrs::nanoamperes ) {
    initVoltage = -initVoltage;
  }
  else {
    return 0 * rrs::volts;
  }

  while ( abs(calcCellCurrent(initVoltage)) < abs(cellCurrent)  ) {
    initVoltage += initVoltage;
  }


  bu::quantity<rrs::volt_unit> estCellVoltage;
  estCellVoltage = initVoltage;
  bu::quantity<rrs::nanoampere_unit> estCellCurrent;
  estCellCurrent = calcCellCurrent(estCellVoltage);

  bu::quantity<rrs::volt_unit> voltageResolution = abs(estCellVoltage)/2.0;
  while (!fastAreEqual(cellCurrent, estCellCurrent, maxCurrentRelativeError)) {

    if (estCellCurrent > cellCurrent) {
      estCellVoltage -= voltageResolution;
    }
    else {
      estCellVoltage += voltageResolution;
    }
    estCellCurrent = calcCellCurrent(estCellVoltage);

    voltageResolution /= 2.;
    if ( voltageResolution < 1e-15 * rrs::volts ) {
      // TODO: Write some warning
      return estCellVoltage;
    }
  }

  return estCellVoltage;
}

void
Cell::buildCellIxV(bu::quantity<rrs::volt_unit> vStep,
                   bu::quantity<rrs::dimensionless> maxRelError)
{
  // Builds paired vectors of cell voltage and current,
  //  dynamically choosing the voltage step based on the interpolation error.
  // Stops when current reachs the selector maximum current.
  auto maxCurrent = selDevMaxCurrent;
  if (selDevModel == semiIdeal)
  {
    maxCurrent = selDevMaxCurrent;
  }
  else if (selDevModel == IxV ) {
    maxCurrent = selCurrentDataPoints.back();
  }

  auto vStepBkup = vStep;
  auto stateBkup = getMemDevResistanceState();
  setMemDevResistanceState(false);
  for ( auto stateCnt = 0; stateCnt < 2; ++stateCnt ) {
    auto vCells = cellVoltageDataPoints.at(0);
    auto iCells = cellCurrentDataPoints.at(0);
    vCells.resize(2);
    iCells.resize(2);

    size_t i = 0;
    vCells.at(i) = 0. * rrs::volts;
    auto vCell = vCells.at(i);
    iCells.at(i) = calcCellCurrent(vCell, 1e-12);
    ++i;
    vCells.at(i) = vCells.at(i-1) + vStep;
    vCell = vCells.at(i);
    iCells.at(i) = calcCellCurrent(vCell, 1e-12);
    ++i;
    vCells.push_back(INVALID_DOUBLE * rrs::volts);
    iCells.push_back(INVALID_DOUBLE * rrs::nanoamperes);
    while (iCells.at(i-1) < maxCurrent) {
     vCells.at(i) = vCells.at(i-1) + vStep;
      vCell = vCells.at(i);
      iCells.at(i) = calcCellCurrent(vCell, 1e-12);

      auto iHat = iCells.at(i-2);
      iHat +=  (vCells.at(i-1) - vCells.at(i-2))
              *(iCells.at(i) - iCells.at(i-2))
              /(vCells.at(i) - vCells.at(i-2));
      auto relError =   (iHat - iCells.at(i-1))
                      / iCells.at(i-1);
      if ( abs(relError) < maxRelError ) {
        vStep *= 2;
        ++i;
        vCells.push_back(INVALID_DOUBLE * rrs::volts);
        iCells.push_back(INVALID_DOUBLE * rrs::nanoamperes);
      }
      else {
        vStep /= 2;
        i = i; // Just to make clear it doesn't change
      }
    }
    if ( isInvalid(vCells.back()) ) { // Isnt it always? Anyway.
      vCells.pop_back();
      iCells.pop_back();
    }
    cellVoltageDataPoints.at(stateCnt).pop_back();
    cellVoltageDataPoints.at(stateCnt) = vCells;
    cellCurrentDataPoints.at(stateCnt).pop_back();
    cellCurrentDataPoints.at(stateCnt) = iCells;
    setMemDevResistanceState(true);
    vStep = vStepBkup;
  }
  setMemDevResistanceState(false);
  setMemDevResistanceState(stateBkup);
}

bu::quantity<rrs::nanoampere_unit>
Cell::getCellCurrent(bu::quantity<rrs::volt_unit> cellVoltage) {
  return getCellCurrent(cellVoltage, memDevResistanceState);
}

bu::quantity<rrs::nanoampere_unit>
Cell::getCellCurrent(bu::quantity<rrs::volt_unit> cellVoltage,
                     ebool state)
{
  auto firstGreaterIndex =
        findLowestGreater(cellVoltageDataPoints.at(state), abs(cellVoltage));

  // If cellVoltage >= max(cellVoltageDataPoints), get highest current
  auto iCell = cellCurrentDataPoints.at(state).at(firstGreaterIndex - 1);

  // Linear interpolation between two (V,I) pairs
  if ( firstGreaterIndex < cellVoltageDataPoints.at(state).size() ) {
    auto x0 = cellVoltageDataPoints.at(state).at(firstGreaterIndex - 1);
    auto x1 = cellVoltageDataPoints.at(state).at(firstGreaterIndex);
    auto y0 = cellCurrentDataPoints.at(state).at(firstGreaterIndex - 1);
    auto y1 = cellCurrentDataPoints.at(state).at(firstGreaterIndex);

    iCell = (abs(cellVoltage) - x0) * (y1 - y0) / (x1 - x0) + y0;
  }
  // Assume symmetrical IxV curve
  if(cellVoltage < 0 * rrs::volts) {
    return -iCell;
  }
  return iCell;
}

bu::quantity<rrs::volt_unit>
Cell::getCellVoltage(bu::quantity<rrs::nanoampere_unit> cellCurrent)
{
  return getCellVoltage(cellCurrent, memDevResistanceState);
}

bu::quantity<rrs::volt_unit>
Cell::getCellVoltage(bu::quantity<rrs::nanoampere_unit> cellCurrent,
                     ebool state)
{
  auto firstGreaterIndex =
        findLowestGreater(cellCurrentDataPoints.at(state), abs(cellCurrent));

  // If cellCurrent >= max(cellCurrentDataPoints), throw error
  if ( firstGreaterIndex >= cellVoltageDataPoints.at(state).size() ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Tried to assess the voltage in the cell ");
    exceptionMsgThrown.append("for a current (");
    exceptionMsgThrown.append(to_string(cellCurrent));
    exceptionMsgThrown.append(") greater than the maximum cell current (");
  exceptionMsgThrown.append(to_string(cellCurrentDataPoints.at(state).back()));
    exceptionMsgThrown.append(").");
    throw exceptionMsgThrown;
  }

  // Linear interpolation between two (V,I) pairs
  auto x0 = cellCurrentDataPoints.at(state).at(firstGreaterIndex - 1);
  auto x1 = cellCurrentDataPoints.at(state).at(firstGreaterIndex);
  auto y0 = cellVoltageDataPoints.at(state).at(firstGreaterIndex - 1);
  auto y1 = cellVoltageDataPoints.at(state).at(firstGreaterIndex);

  auto vCell = (abs(cellCurrent) - x0) * (y1 - y0) / (x1 - x0) + y0;
  // Assume symmetrical IxV curve
  if(cellCurrent < 0 * rrs::nanoamperes) {
    return -vCell;
  }
  return vCell;
}

void
Cell::buildFromCellFile(const char* cellFileName)
{
  try {
    JsonAssist jsonAssist(cellFileName);

    double magnitude = INVALID_DOUBLE;
    string auxStr = INVALID_STRING;

    // Memory device parameters
    magnitude = jsonAssist.getJSONNumber("Memory device HRS resistance [Ohm]",
                                          mandatory);
    setMemDevHRSResistance(magnitude * rrs::ohms);

    magnitude = jsonAssist.getJSONNumber("Memory device LRS resistance [Ohm]",
                                          mandatory);
    setMemDevLRSResistance(magnitude * rrs::ohms);

    setMemDevResistanceState( 1 );

    // Selector device parameters
    auxStr = jsonAssist.getJSONString("Selector model []",
                                       mandatory);
    setSelDevModel(auxStr, forced);
    if ( selDevModel == semiIdeal ) {
      magnitude = jsonAssist.getJSONNumber("Selector snap voltage [V]",
                                            mandatory);
      setSelDevSnapVoltage(magnitude * rrs::volts);

      magnitude = jsonAssist.getJSONNumber("Selector leakage current [nA]",
                                            mandatory);
      setSelDevLeakageCurrent(magnitude * rrs::nanoamperes);

      magnitude = jsonAssist.getJSONNumber("Selector maximum current [nA]",
                                            mandatory);
      setSelDevMaxCurrent(magnitude * rrs::nanoamperes);
    }
    else if ( selDevModel == IxV ) {
      // Mandatory: at least one data points pair
      double voltageMag;
      voltageMag = jsonAssist.getJSONNumber("Selector voltage point 0 [V]",
                                            mandatory);
      setSelVoltageDataPoint(voltageMag * rrs::volts);

      double currentMag;
      currentMag = jsonAssist.getJSONNumber("Selector current point 0 [nA]",
                                            mandatory);
      setSelCurrentDataPoint(currentMag * rrs::nanoamperes);

      // Searchs in order until there is no member in json file
      size_t cnt = 1;
      while ( areValid( voltageMag, currentMag ) ) {
        auxStr = "Selector voltage point ";
        auxStr.append(to_string(cnt));
        auxStr.append(" [V]");
        voltageMag = jsonAssist.getJSONNumber(auxStr.c_str(),
                                              optional);
        if ( isValid( voltageMag ) ) {
          setSelVoltageDataPoint(voltageMag * rrs::volts);
        }

        auxStr = "Selector current point ";
        auxStr.append(to_string(cnt));
        auxStr.append(" [nA]");
        currentMag = jsonAssist.getJSONNumber(auxStr.c_str(),
                                              optional);
        if ( isValid( currentMag ) ) {
          setSelCurrentDataPoint(currentMag * rrs::nanoamperes);
        }

        cnt++;
      }
    }
    // Rewrite selector device model to be used
    auxStr = jsonAssist.getJSONString("Selector model []",
                                       mandatory);
    setSelDevModel(auxStr);

    // Precision parameters
    magnitude = jsonAssist.getJSONNumber("Maximum current error []",
                                          optional);
    if ( isInvalid ( magnitude ) ) {
      magnitude = 1e-6; // Default max. current error value
    }
    setMaxCurrentRelativeError(magnitude);

    // Build paired IxV vectors for both LRS and HRS
    buildCellIxV();

    // Write & read
    magnitude = jsonAssist.getJSONNumber("Cell set time C [ns]",
                                         optional);
    setCellSetTimeC(magnitude * rrs::nanoseconds );

    magnitude = jsonAssist.getJSONNumber("Cell set time K [V^-1]",
                                         optional);
    setCellSetTimeK(magnitude * rrs::per_volt );

    magnitude = jsonAssist.getJSONNumber("Cell set time [ns]",
                                         optional);
    setCellSetTime(magnitude * rrs::nanoseconds );

    if ( isInvalid(setTime) && !areValid(setTimeC, setTimeK) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Cell set time parameters are unknown.\n");
      exceptionMsgThrown.append("Please include either:\n");
      exceptionMsgThrown.append("\"Cell set time [ns]\":<value>");
      exceptionMsgThrown.append("\nor:\n");
      exceptionMsgThrown.append("\"Cell set time C [ns]\":<value>");
      exceptionMsgThrown.append("\n  and:\n");
      exceptionMsgThrown.append("\"Cell set time K [V^-1]\":<value>");
      exceptionMsgThrown.append("\nto your cell description file.");
      throw exceptionMsgThrown;
    }

    magnitude = jsonAssist.getJSONNumber("Cell set compliance current [nA]",
                                         mandatory);
    setCellSetComplianceCurrent(magnitude * rrs::nanoamperes );

    magnitude = jsonAssist.getJSONNumber("Cell set current [nA]",
                                         optional);
    setCellSetCurrent(magnitude * rrs::nanoamperes );

    magnitude = jsonAssist.getJSONNumber("Cell set voltage [V]",
                                         optional);
    setCellSetVoltage(magnitude * rrs::volts );


    magnitude = jsonAssist.getJSONNumber("Cell reset time C [ns]",
                                         optional);
    setCellResetTimeC(magnitude * rrs::nanoseconds );

    magnitude = jsonAssist.getJSONNumber("Cell reset time K [V^-1]",
                                         optional);
    setCellResetTimeK(magnitude * rrs::per_volt );

    magnitude = jsonAssist.getJSONNumber("Cell reset time [ns]",
                                         optional);
    setCellResetTime(magnitude * rrs::nanoseconds );

    if ( isInvalid(resetTime) && !areValid(resetTimeC, resetTimeK) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Cell reset time parameters are unknown.\n");
      exceptionMsgThrown.append("Please include either:\n");
      exceptionMsgThrown.append("\"Cell reset time [ns]\":<value>");
      exceptionMsgThrown.append("\nor:\n");
      exceptionMsgThrown.append("\"Cell reset time C [ns]\":<value>");
      exceptionMsgThrown.append("\n  and:\n");
      exceptionMsgThrown.append("\"Cell reset time K [V^-1]\":<value>");
      exceptionMsgThrown.append("\nto your cell description file.");
      throw exceptionMsgThrown;
    }

    magnitude = jsonAssist.getJSONNumber("Cell reset current [nA]",
                                         optional);
    setCellResetCurrent(magnitude * rrs::nanoamperes );

    magnitude = jsonAssist.getJSONNumber("Cell reset voltage [V]",
                                         optional);
    setCellResetVoltage(magnitude * rrs::volts );


    magnitude = jsonAssist.getJSONNumber("Cell read voltage [V]",
                                         optional);
    setCellReadVoltage(magnitude * rrs::volts );

    magnitude = jsonAssist.getJSONNumber("Cell read current [nA]",
                                         optional);
    setCellReadCurrent(magnitude * rrs::nanoamperes );

    magnitude = jsonAssist.getJSONNumber("LRS/HRS read current ratio []",
                                         optional);
    setCellReadCurrentRatio(magnitude);

    if ( areInvalid(readVoltage, readCurrent, readCurrentRatio) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Cell read parameters are unknown.");
      exceptionMsgThrown.append("\nPlease include either:\n");
      exceptionMsgThrown.append("\"Cell read voltage [V]\":<value>");
      exceptionMsgThrown.append("\nor:\n");
      exceptionMsgThrown.append("\"Cell read current [nA]\":<value>");
      exceptionMsgThrown.append("\nor:\n");
      exceptionMsgThrown.append("\"LRS/HRS read current ratio []\":<value>");
      exceptionMsgThrown.append("\nto your cell description file.");
      throw exceptionMsgThrown;
    }

    // Mechanical dimensions
    magnitude = jsonAssist.getJSONNumber("Cell width [nm]",
                                         optional);
    setCellWidth(magnitude * rrs::nanometers );

    magnitude = jsonAssist.getJSONNumber("Cell height [nm]",
                                         optional);
    setCellHeight(magnitude * rrs::nanometers );

    magnitude = jsonAssist.getJSONNumber("Cell to cell spacing [nm]",
                                         optional);
    setCellHeight(magnitude * rrs::nanometers );

    magnitude = jsonAssist.getJSONNumber("Cell thickness [nm]",
                                         optional);
    setCellThickness(magnitude * rrs::nanometers );

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

Cell::Cell()
{
  initialize();
}

Cell::Cell(const char* cellFileName)
{
  initialize();

  try {
    buildFromCellFile(cellFileName);

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

Cell::~Cell()
{

}












