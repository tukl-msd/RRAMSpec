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



#include "XPointArray.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

void
XPointArray::initialize()
{
  WLMetalWidth = INVALID_DOUBLE * rrs::nanometers;
  BLMetalWidth = INVALID_DOUBLE * rrs::nanometers;

  heightwiseCellPitch = INVALID_DOUBLE * rrs::nanometers;
  widthwiseCellPitch = INVALID_DOUBLE * rrs::nanometers;
  area4F2 = INVALID_DOUBLE * rrs::square_nanometers;

  height = INVALID_DOUBLE * rrs::nanometers;
  width = INVALID_DOUBLE * rrs::nanometers;
  area = INVALID_DOUBLE * rrs::square_nanometers;
  areaEfficiency = INVALID_DOUBLE;

  nCols = INVALID_DOUBLE;
  nRows = INVALID_DOUBLE;

  capacity = INVALID_DOUBLE * rrs::bits;

  WLResistancePerCell = INVALID_DOUBLE * rrs::ohms;
  BLResistancePerCell = INVALID_DOUBLE * rrs::ohms;
  WLCapacitancePerCell = INVALID_DOUBLE * rrs::attofarads;
  BLCapacitancePerCell = INVALID_DOUBLE * rrs::attofarads;

  WLResistancePerLength = INVALID_DOUBLE * rrs::ohms_per_nanometer;
  BLResistancePerLength = INVALID_DOUBLE * rrs::ohms_per_nanometer;
  WLCapacitancePerLength = INVALID_DOUBLE * rrs::nanofarads_per_meter;
  BLCapacitancePerLength = INVALID_DOUBLE * rrs::nanofarads_per_meter;

  WLWriteDriverResistance = INVALID_DOUBLE * rrs::ohms;
  BLWriteDriverResistance = INVALID_DOUBLE * rrs::ohms;

  WLReadDriverResistance = INVALID_DOUBLE * rrs::ohms;
  BLReadDriverResistance = INVALID_DOUBLE * rrs::ohms;

  halfBiasDriverResistance = INVALID_DOUBLE * rrs::ohms;
  halfBiasDriverResistance = INVALID_DOUBLE * rrs::ohms;

  writeVoltage = INVALID_DOUBLE * rrs::volts;
  readVoltage = INVALID_DOUBLE * rrs::volts;

  adjWLDelay = INVALID_DOUBLE * rrs::nanoseconds;
  adjBLDelay = INVALID_DOUBLE * rrs::nanoseconds;
  adjLineMaxDelay = INVALID_DOUBLE * rrs::nanoseconds;
  WLDelay = INVALID_DOUBLE * rrs::nanoseconds;
  BLDelay = INVALID_DOUBLE * rrs::nanoseconds;
  lineMaxDelay = INVALID_DOUBLE * rrs::nanoseconds;

  prechargeTime = INVALID_DOUBLE * rrs::nanoseconds;
  calibrationDelay = INVALID_DOUBLE * rrs::nanoseconds;
  setTime = INVALID_DOUBLE * rrs::nanoseconds;
  resetTime = INVALID_DOUBLE * rrs::nanoseconds;
  writeTime = INVALID_DOUBLE * rrs::nanoseconds;
  readTime = INVALID_DOUBLE * rrs::nanoseconds;

  prechargeCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  setSCCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  setSPCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  setCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  resetSCCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  resetSPCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  resetCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  writeCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  readHRSSCCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readHRSSPCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readLRSSCCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readLRSSPCurrent = INVALID_DOUBLE * rrs::nanoamperes;
  readCurrent = INVALID_DOUBLE * rrs::nanoamperes;

  prechargeEnergy = INVALID_DOUBLE * rrs::picojoules;
  writeEnergy = INVALID_DOUBLE * rrs::picojoules;
  readEnergy = INVALID_DOUBLE * rrs::picojoules;

}

void
XPointArray::setWLMetalWidth(bu::quantity<rrs::nanometer_unit> width,
                             settingOptions setOpt)
{
  WLMetalWidth = width;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }

  if ( isInvalid(WLMetalWidth) ) { return; }

  updateWLMetalWidth(); // Get minimum width
  if ( width >= WLMetalWidth ) {
    WLMetalWidth = width;
  }
  else {
    WLMetalWidth = INVALID_DOUBLE * rrs::nanometers;

    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Wordline metal width (");
    exceptionMsgThrown.append(to_string(width));
    exceptionMsgThrown.append(") is too narrow");
    exceptionMsgThrown.append(" for given technology and cell.");
    throw exceptionMsgThrown;
  }
}

void
XPointArray::updateWLMetalWidth()
{
  if ( isValid( selectedCell.getCellHeight() ) ) {
    WLMetalWidth = max( tech.getMetalHalfPitch(),
                        selectedCell.getCellHeight() );
  }
  else {
    WLMetalWidth = tech.getMetalHalfPitch();
  }
}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getWLMetalWidth() const
{
  return this->WLMetalWidth;
}


void
XPointArray::setBLMetalWidth(bu::quantity<rrs::nanometer_unit> width,
                             settingOptions setOpt)
{
  BLMetalWidth = width;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }

  if ( isInvalid(BLMetalWidth) ) { return; }

  updateBLMetalWidth(); // Get minimum width
  if ( width >= tech.getMetalHalfPitch() ) {
    BLMetalWidth = width;
  }
  else {
    BLMetalWidth = INVALID_DOUBLE * rrs::nanometers;

    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Bitline metal width (");
    exceptionMsgThrown.append(to_string(width));
    exceptionMsgThrown.append(") is too narrow");
    exceptionMsgThrown.append(" for given technology and cell.");
    throw exceptionMsgThrown;
  }

}

void
XPointArray::updateBLMetalWidth()
{
  if ( isValid( selectedCell.getCellWidth() ) ) {
    BLMetalWidth = max( tech.getMetalHalfPitch(),
                        selectedCell.getCellWidth() );
  }
  else {
    BLMetalWidth = tech.getMetalHalfPitch();
  }
}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getBLMetalWidth() const
{
  return this->BLMetalWidth;
}



void
XPointArray::updateHeightwiseCellPitch()
{
  if ( !areValid(WLMetalWidth) ) {
    heightwiseCellPitch = INVALID_DOUBLE * rrs::nanometers;

    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append(" heightwise cell pitch");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameters was unknown:");
    exceptionMsgThrown.append("\n  WLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  heightwiseCellPitch = WLMetalWidth;
  if ( isValid(selectedCell.getCellToCellSpacing()) ) {
    heightwiseCellPitch += max(selectedCell.getCellToCellSpacing(),
                               tech.getMetalHalfPitch());
  }
  else {
    heightwiseCellPitch += tech.getMetalHalfPitch();
  }
}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getHeightwiseCellPitch() const
{
  return this->heightwiseCellPitch;
}

void
XPointArray::updateWidthwiseCellPitch()
{
  if ( !areValid(BLMetalWidth) ) {
    widthwiseCellPitch = INVALID_DOUBLE * rrs::nanometers;

    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append(" widthwise cell pitch");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameters was unknown:");
    exceptionMsgThrown.append("\n  BLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  widthwiseCellPitch = BLMetalWidth;
  if ( isValid(selectedCell.getCellToCellSpacing()) ) {
    widthwiseCellPitch += max(selectedCell.getCellToCellSpacing(),
                               tech.getMetalHalfPitch());
  }
  else {
    widthwiseCellPitch += tech.getMetalHalfPitch();
  }

}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getWidthwiseCellPitch() const
{
  return this->widthwiseCellPitch;
}

void
XPointArray::updateArea4F2()
{
  if ( !areValid(nRows, nCols, heightwiseCellPitch, widthwiseCellPitch) ) {
    area4F2 = INVALID_DOUBLE * rrs::square_nanometers;

    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the minimum (4F2)");
    exceptionMsgThrown.append("crosspoint array area");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  nRows");
    exceptionMsgThrown.append("\n  nCols");
    exceptionMsgThrown.append("\n  heightwiseCellPitch");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }
  width = nCols * widthwiseCellPitch;
  height = nRows * heightwiseCellPitch;
  area4F2 = width * height;
}

bu::quantity<rrs::square_nanometer_unit> const &
XPointArray::getArea4F2() const
{
  return this->area4F2;
}



void
XPointArray::setArea(bu::quantity<rrs::square_nanometer_unit> arrayArea,
                               settingOptions setOpt)
{
  area = arrayArea;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }

  if ( isInvalid(area) ) { return; }


  updateArea4F2();
  areaEfficiency = area4F2 / area;

  if ( isValid(area) ) {
    if ( areValid(nRows, nCols, area4F2) ) {
      // Test whether all cells fit in given array area
      if ( area4F2 <= area ) {
        area = arrayArea;
      }
      else {
        string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Crosspoint array area given (");
        exceptionMsgThrown.append(to_string(area));
        exceptionMsgThrown.append(") is too small");
        exceptionMsgThrown.append(" to fit a ");
        exceptionMsgThrown.append(to_string((int)nRows));
        exceptionMsgThrown.append(" x ");
        exceptionMsgThrown.append(to_string((int)nCols));
        exceptionMsgThrown.append(" cells array (");
        exceptionMsgThrown.append(to_string(area4F2));
        exceptionMsgThrown.append(").");

        area = INVALID_DOUBLE * rrs::square_nanometers;

        throw exceptionMsgThrown;
      }
    }
    else {
      area = arrayArea;
      width = sqrt(area/area4F2) * width;
      height = sqrt(area/area4F2) * height;
    }
  }
}

void
XPointArray::updateArea()
{
  updateArea4F2();
  area = area4F2;
  areaEfficiency = area4F2 / area;
}

bu::quantity<rrs::square_nanometer_unit> const &
XPointArray::getArea() const
{
  return this->area;
}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getHeight() const
{
  return this->height;
}

bu::quantity<rrs::nanometer_unit> const &
XPointArray::getWidth() const
{
  return this->width;
}

bu::quantity<rrs::dimensionless> const &
XPointArray::getAreaEfficiency() const
{
  return this->areaEfficiency;
}



void
XPointArray::setNCols(bu::quantity<rrs::dimensionless> _nCols,
                      settingOptions setOpt)
{
  nCols = _nCols;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }
  if ( isInvalid( nCols ) ) { return; }
  if ( !isInteger( nCols ) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Number of columns in the array must be an");
    exceptionMsgThrown.append(" integer. Tried to set it to ");
    exceptionMsgThrown.append(to_string((double)nCols));
    exceptionMsgThrown.append(".");
    nCols = INVALID_DOUBLE;
    throw exceptionMsgThrown;
  }
}

void
XPointArray::updateNCols()
{
  if ( !areValid(area, heightwiseCellPitch, widthwiseCellPitch, nRows) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append(" number of columns");
    exceptionMsgThrown.append(" in the crosspoint array");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameters was unknown:");
    exceptionMsgThrown.append("\n  arrayArea");
    exceptionMsgThrown.append("\n  lengthwiseCellPitch");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n  nRows");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  nCols = area / heightwiseCellPitch / widthwiseCellPitch / nRows;
  // Admiting only power of 2 arrays
  nCols = pow(2, floor(log2(nRows)));

}

bu::quantity<rrs::dimensionless> const &
XPointArray::getNCols() const
{
  return this->nCols;
}


void
XPointArray::setNRows(bu::quantity<rrs::dimensionless> _nRows,
                      settingOptions setOpt)
{
  nRows = _nRows;
  // If forced, ignore all tests
  if ( setOpt == forced ) { return; }
  if ( isInvalid( nRows ) ) { return; }
  if ( !isInteger( nRows ) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Number of rows in the array must be an");
    exceptionMsgThrown.append(" integer. Tried to set it to ");
    exceptionMsgThrown.append(to_string((double)nRows));
    exceptionMsgThrown.append(".");
    nRows = INVALID_DOUBLE;
    throw exceptionMsgThrown;
  }
}

void
XPointArray::updateNRows()
{
  if ( !areValid(area, heightwiseCellPitch, widthwiseCellPitch, nCols) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append(" number of rows");
    exceptionMsgThrown.append(" in the crosspoint array");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameters was unknown:");
    exceptionMsgThrown.append("\n  arrayArea");
    exceptionMsgThrown.append("\n  heightwiseCellPitch");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n  nCols");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  nRows = area / heightwiseCellPitch / widthwiseCellPitch / nCols;
  // Admiting only power of 2 arrays
  nRows = pow(2, floor(log2(nCols)));
}

bu::quantity<rrs::dimensionless> const &
XPointArray::getNRows() const
{
  return this->nRows;
}


void
XPointArray::updateNRowsAndNCols()
{
  if ( !areValid(area, heightwiseCellPitch, widthwiseCellPitch) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append(" number of rows and columns");
    exceptionMsgThrown.append(" in the crosspoint array");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameters was unknown:");
    exceptionMsgThrown.append("\n  arrayArea");
    exceptionMsgThrown.append("\n  heightwiseCellPitch");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  nRows = sqrt(area / heightwiseCellPitch / widthwiseCellPitch);
  // Admiting only power of 2 arrays
  nRows = pow(2, floor(log2(nRows)));
  nCols = nRows;

}


void
XPointArray::updateCapacity()
{
  capacity = nRows * nCols * rrs::bits;
}

bu::quantity<rrs::bit_unit> const &
XPointArray::getCapacity() const
{
  return this->capacity;
}



void
XPointArray::updateLinesElectricalParameters()
{
  updateWLResistancePerLength();
  updateBLResistancePerLength();
  updateWLCapacitancePerLength();
  updateBLCapacitancePerLength();

  updateWLResistancePerCell();
  updateBLResistancePerCell();
  updateWLCapacitancePerCell();
  updateBLCapacitancePerCell();
}

void
XPointArray::updateWLResistancePerLength()
{
  if ( !areValid(WLMetalWidth) ) {
    WLResistancePerLength = INVALID_DOUBLE * rrs::ohms_per_nanometer;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("wordline resistance per length");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  WLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  WLResistancePerLength = tech.getMetalSheetResistance() / WLMetalWidth;
}

bu::quantity<rrs::ohm_per_nanometer_unit> const &
XPointArray::getWLResistancePerLength() const
{
  return this->WLResistancePerLength;
}


void
XPointArray::updateBLResistancePerLength()
{
  if ( !areValid(BLMetalWidth) ) {
    BLResistancePerLength = INVALID_DOUBLE * rrs::ohms_per_nanometer;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("bitline resistance per length");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  BLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  BLResistancePerLength = tech.getMetalSheetResistance() / BLMetalWidth;
}

bu::quantity<rrs::ohm_per_nanometer_unit> const &
XPointArray::getBLResistancePerLength() const
{
  return this->BLResistancePerLength;
}


void
XPointArray::updateWLCapacitancePerLength()
{
  if ( !areValid(WLMetalWidth) ) {
    WLCapacitancePerLength = INVALID_DOUBLE * rrs::nanofarads_per_meter;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("wordline capacitance per length");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  WLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  WLCapacitancePerLength = tech.getMetalCapacitancePerLength()
                             * WLMetalWidth / tech.getMetalHalfPitch();
}

bu::quantity<rrs::nanofarad_per_meter_unit> const &
XPointArray::getWLCapacitancePerLength() const
{
  return this->WLCapacitancePerLength;
}


void
XPointArray::updateBLCapacitancePerLength()
{
  if ( !areValid(BLMetalWidth) ) {
    BLCapacitancePerLength = INVALID_DOUBLE * rrs::nanofarads_per_meter;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("bitline capacitance per Length");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  BLMetalWidth");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  BLCapacitancePerLength = tech.getMetalCapacitancePerLength()
                             * BLMetalWidth / tech.getMetalHalfPitch();
}

bu::quantity<rrs::nanofarad_per_meter_unit> const &
XPointArray::getBLCapacitancePerLength() const
{
  return this->BLCapacitancePerLength;
}



void
XPointArray::updateWLResistancePerCell()
{
  if ( !areValid(WLResistancePerLength, widthwiseCellPitch) ) {
    WLResistancePerCell = INVALID_DOUBLE * rrs::ohms;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("wordline resistance per cell");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  WLResistancePerLength");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  WLResistancePerCell = WLResistancePerLength * widthwiseCellPitch;
}

bu::quantity<rrs::ohm_unit> const &
XPointArray::getWLResistancePerCell() const
{
  return this->WLResistancePerCell;
}


void
XPointArray::updateBLResistancePerCell()
{
  if ( !areValid(BLResistancePerLength, heightwiseCellPitch) ) {
    BLResistancePerCell = INVALID_DOUBLE * rrs::ohms;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("bitline resistance per cell");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  BLResistancePerLength");
    exceptionMsgThrown.append("\n  lengthwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  BLResistancePerCell = BLResistancePerLength * heightwiseCellPitch;
}

bu::quantity<rrs::ohm_unit> const &
XPointArray::getBLResistancePerCell() const
{
  return this->BLResistancePerCell;
}


void
XPointArray::updateWLCapacitancePerCell()
{
  if ( !areValid(WLCapacitancePerLength, widthwiseCellPitch) ) {
    WLCapacitancePerCell = INVALID_DOUBLE * rrs::attofarads;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("wordline capacitance per cell");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  WLCapacitancePerLength");
    exceptionMsgThrown.append("\n  widthwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  WLCapacitancePerCell = WLCapacitancePerLength * widthwiseCellPitch;
}

bu::quantity<rrs::attofarad_unit> const &
XPointArray::getWLCapacitancePerCell() const
{
  return this->WLCapacitancePerCell;
}


void
XPointArray::updateBLCapacitancePerCell()
{
  if ( !areValid(BLCapacitancePerLength, heightwiseCellPitch) ) {
    BLCapacitancePerCell = INVALID_DOUBLE * rrs::attofarads;
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to update the");
    exceptionMsgThrown.append("bitline capacitance per cell");
    exceptionMsgThrown.append(", but at least one of the following");
    exceptionMsgThrown.append(" parameter was unknown:");
    exceptionMsgThrown.append("\n  BLCapacitancePerLength");
    exceptionMsgThrown.append("\n  heightwiseCellPitch");
    exceptionMsgThrown.append("\n");
    throw exceptionMsgThrown;
  }

  BLCapacitancePerCell = BLCapacitancePerLength * heightwiseCellPitch;
}

bu::quantity<rrs::attofarad_unit> const &
XPointArray::getBLCapacitancePerCell() const
{
  return this->BLCapacitancePerCell;
}




void
XPointArray::updateWLWriteDriverResistance()
{
  WLWriteDriverResistance = calcDriverResistance( write_op );
}

bu::quantity<rrs::ohm_unit> const &
XPointArray::getWLWriteDriverResistance() const
{
  return this->WLWriteDriverResistance;
}


void
XPointArray::updateBLWriteDriverResistance()
{
  BLWriteDriverResistance = calcDriverResistance( write_op );
}

bu::quantity<rrs::ohm_unit> const &
XPointArray::getBLWriteDriverResistance() const
{
  return this->BLWriteDriverResistance;
}



void
XPointArray::updateWLReadDriverResistance()
{
  WLReadDriverResistance = calcDriverResistance( read_op );
}

bu::quantity<rrs::ohm_unit> const &
XPointArray::getWLReadDriverResistance() const
{
  return this->WLReadDriverResistance;
}



bu::quantity<rrs::ohm_unit> const &
XPointArray::getBLReadDriverResistance() const
{
  return this->BLReadDriverResistance;
}

void
XPointArray::updateBLReadDriverResistance()
{
  BLReadDriverResistance = calcDriverResistance( read_op );
}



bu::quantity<rrs::ohm_unit> const &
XPointArray::getHalfBiasDriverResistance() const
{
  return this->halfBiasDriverResistance;
}

void
XPointArray::updateHalfBiasDriverResistance()
{
  halfBiasDriverResistance = calcDriverResistance( half_select );
}


bu::quantity<rrs::volt_unit> const &
XPointArray::getReadVoltage() const
{
  return this->readVoltage;
}

bu::quantity<rrs::volt_unit> const &
XPointArray::getWriteVoltage() const
{
  return this->writeVoltage;
}



void
XPointArray::updateAdjLineDelays()
{
  auto totalAdjWLRes = BLResistancePerLength * height;
  auto totalAdjWLCap = BLCapacitancePerLength * height;
  auto totalAdjBLRes = WLResistancePerLength * width;
  auto totalAdjBLCap = WLCapacitancePerLength * width;

  double percentage = 95.;
  adjWLDelay = tausToPercentLumpedRC(percentage) * totalAdjWLRes
      * SCALE_QUANTITY(totalAdjWLCap, rrs::nanofarad_unit);
  adjWLDelay += tausToPercentSingleRC(percentage) * LDOResistance
      * SCALE_QUANTITY(totalAdjWLCap, rrs::nanofarad_unit);
  adjBLDelay = tausToPercentLumpedRC(percentage) * totalAdjBLRes
      * SCALE_QUANTITY(totalAdjBLCap, rrs::nanofarad_unit);
  adjBLDelay += tausToPercentSingleRC(percentage) * LDOResistance
      * SCALE_QUANTITY(totalAdjBLCap, rrs::nanofarad_unit);
  adjLineMaxDelay = max(adjWLDelay, adjBLDelay);
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getAdjLineMaxDelay() const
{
  return this->adjLineMaxDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getAdjWLDelay() const
{
  return this->adjWLDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getAdjBLDelay() const
{
  return this->adjBLDelay;
}


void
XPointArray::updateLineDelays()
{
  auto totalAdjWLRes = BLResistancePerLength * height;
  auto totalAdjBLRes = WLResistancePerLength * width;
  auto totalWLRes = WLResistancePerLength * width;
  auto totalWLCap = WLCapacitancePerLength * width;
  auto totalBLRes = BLResistancePerLength * height;
  auto totalBLCap = BLCapacitancePerLength * height;

  double percentage = 95.;
  WLDelay = tausToPercentLumpedRC(percentage) * totalWLRes
      * SCALE_QUANTITY(totalWLCap, rrs::nanofarad_unit);
  WLDelay += tausToPercentSingleRC(percentage)
      * SCALE_QUANTITY(totalWLCap, rrs::nanofarad_unit)
      * ( LDOResistance + totalAdjWLRes + halfBiasDriverResistance );

  BLDelay = tausToPercentLumpedRC(percentage) * totalBLRes
      * SCALE_QUANTITY(totalBLCap, rrs::nanofarad_unit);
  BLDelay += tausToPercentSingleRC(percentage)
      * SCALE_QUANTITY(totalBLCap, rrs::nanofarad_unit)
      * ( LDOResistance + totalAdjBLRes + halfBiasDriverResistance );

  lineMaxDelay = max(WLDelay, BLDelay);
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getLineMaxDelay() const
{
  return this->lineMaxDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getWLDelay() const
{
  return this->WLDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getBLDelay() const
{
  return this->BLDelay;
}

void
XPointArray::updateCalibrationDelay()
{
  calibrationDelay = adjLineMaxDelay + lineMaxDelay + currentSensingDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getCalibrationDelay() const
{
  return this->calibrationDelay;
}



void
XPointArray::updatePrechargeTime()
{
  auto totalWLCap = WLCapacitancePerLength * width;
  auto totalBLCap = BLCapacitancePerLength * height;

  double percentage = 95.;
  // During precharge, the precharge LDO must provide current for all lines
  prechargeTime = tausToPercentSingleRC(percentage) * LDOResistance *
      ( SCALE_QUANTITY(totalWLCap * nRows, rrs::nanofarad_unit)
        + SCALE_QUANTITY(totalBLCap * nCols, rrs::nanofarad_unit) );
  prechargeTime += adjLineMaxDelay + lineMaxDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getPrechargeTime() const
{
  return this->prechargeTime;
}


void
XPointArray::updateWriteTime()
{
  setTime = resetTime = calibrationDelay + adjLineMaxDelay + lineMaxDelay;
  setTime += selectedCell.getCellSetTime();
  resetTime += selectedCell.getCellResetTime();

  writeTime = max(setTime, resetTime);
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getWriteTime() const
{
  return this->writeTime;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getSetTime() const
{
  return this->setTime;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getResetTime() const
{
  return this->resetTime;
}

void
XPointArray::updateReadTime()
{
  readTime = adjLineMaxDelay;
  readTime += lineMaxDelay;
  readTime += calibrationDelay;
  readTime += currentSensingDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
XPointArray::getReadTime() const
{
  return this->readTime;
}



void
XPointArray::updatePrechargeCurrent()
{
  auto vHalfWrite = writeVoltage/2.;
  auto vHalfRead = readVoltage/2.;
  auto deltaV = vHalfWrite - vHalfRead;
  auto totalWLCap = WLCapacitancePerLength * width;
  auto totalBLCap = BLCapacitancePerLength * height;
  auto totalCap = SCALE_QUANTITY(totalWLCap + totalBLCap, rrs::attofarad_unit);

  prechargeCurrent = totalCap * deltaV / prechargeTime;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getPrechargeCurrent() const
{
  return this->prechargeCurrent;
}


bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getSetSCCurrent() const
{
  return this->setSCCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getSetSPCurrent() const
{
  return this->setSPCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getSetCurrent() const
{
  return this->setCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getResetSCCurrent() const
{
  return this->resetSCCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getResetSPCurrent() const
{
  return this->resetSPCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getResetCurrent() const
{
  return this->resetCurrent;
}

void
XPointArray::updateWriteCurrent()
{
  auto iSCBeforeSet = setSCCurrent;
  auto iSCAfterSet = selectedCell.getCellSetComplianceCurrent();
  setCurrent = ( iSCBeforeSet * selectedCell.getCellSetTime()
                  + iSCAfterSet * (writeTime - selectedCell.getCellSetTime()) )
                / writeTime;
  setCurrent += setSPCurrent;

  resetCurrent = resetSCCurrent + resetSPCurrent;

  writeCurrent = max(setCurrent, resetCurrent);
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getWriteCurrent() const
{
  return this->writeCurrent;
}


bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getReadHRSSCCurrent() const
{
  return this->readHRSSCCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getReadHRSSPCurrent() const
{
  return this->readHRSSPCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getReadLRSSCCurrent() const
{
  return this->readLRSSCCurrent;
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getReadLRSSPCurrent() const
{
  return this->readLRSSPCurrent;
}

void
XPointArray::updateReadCurrent()
{
  auto readHRSCurrent = readHRSSCCurrent + readHRSSPCurrent;
  auto readLRSCurrent = readLRSSCCurrent + readLRSSPCurrent;
  readCurrent = max(readHRSCurrent, readLRSCurrent);
}

bu::quantity<rrs::nanoampere_unit> const &
XPointArray::getReadCurrent() const
{
  return this->readCurrent;
}



void
XPointArray::updatePrechargeEnergy()
{
  auto vHalfWriteSquared = writeVoltage/2. * writeVoltage/2.;
  auto vHalfReadSquared = readVoltage/2. * readVoltage/2.;
  auto deltaSquaredV = vHalfWriteSquared - vHalfReadSquared;
  auto totalWLsCap = WLCapacitancePerLength * width * nRows;
  auto totalBLsCap = BLCapacitancePerLength * height * nCols;
  auto totalCap = SCALE_QUANTITY(totalWLsCap+totalBLsCap, rrs::picofarad_unit);

  prechargeEnergy = totalCap * deltaSquaredV / 2.;
}

bu::quantity<rrs::picojoule_unit> const &
XPointArray::getPrechargeEnergy() const
{
  return this->prechargeEnergy;
}

void
XPointArray::updateWriteEnergy()
{
  auto totalAdjWLCap = BLCapacitancePerLength * height;
  auto totalAdjBLCap = WLCapacitancePerLength * width;
  auto totalWLCap = WLCapacitancePerLength * width;
  auto totalBLCap = BLCapacitancePerLength * height;
  auto totalLineCap = totalAdjWLCap + totalAdjBLCap + totalWLCap + totalBLCap;

  auto dynamicEnergy = SCALE_QUANTITY(totalLineCap, rrs::picofarad_unit) *
      (writeVoltage * writeVoltage - writeVoltage * writeVoltage/2.);
  auto writePower = writeCurrent * tech.getBreakdownVoltage();

  writeEnergy = dynamicEnergy;
  writeEnergy += SCALE_QUANTITY(writePower * writeTime, rrs::picojoule_unit);
}

bu::quantity<rrs::picojoule_unit> const &
XPointArray::getWriteEnergy() const
{
  return this->writeEnergy;
}

void
XPointArray::updateReadEnergy()
{
  auto totalAdjWLCap = BLCapacitancePerLength * height;
  auto totalAdjBLCap = WLCapacitancePerLength * width;
  auto totalWLCap = WLCapacitancePerLength * width;
  auto totalBLCap = BLCapacitancePerLength * height;
  auto totalLineCap = totalAdjWLCap + totalAdjBLCap + totalWLCap + totalBLCap;

  auto dynamicEnergy = SCALE_QUANTITY(totalLineCap, rrs::picofarad_unit) *
      (readVoltage * readVoltage - readVoltage * writeVoltage/2.);
  auto readPower = readCurrent * tech.getBreakdownVoltage();

  readEnergy = dynamicEnergy;
  readEnergy += SCALE_QUANTITY(readPower * readTime, rrs::picojoule_unit);
}

bu::quantity<rrs::picojoule_unit> const &
XPointArray::getReadEnergy() const
{
  return this->readEnergy;
}

void
XPointArray::buildFromConfigFiles()
{
  try {
    // Build "pure" cells
    selectedCell = Cell(cellFileName);
    HSCellPL = Cell(cellFileName);
    HSCellNL = Cell(cellFileName);

    // Get technology values
    tech = Technology(techFileName);

    // Get general values for the array
    JsonAssist jsonArch(archFileName);

    double magnitude = INVALID_DOUBLE;

    magnitude = jsonArch.getJSONNumber(
          "Wordline metal width [nm]", optional);
    setWLMetalWidth( magnitude * rrs::nanometers );

    magnitude = jsonArch.getJSONNumber(
          "Bitline metal width [nm]", optional);
    setBLMetalWidth( magnitude * rrs::nanometers );

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }


}


bu::quantity<rrs::ohm_unit>
XPointArray::calcDriverResistance( rramOperations op )
{

  if ( op == write_op ) {
    // Check validity of all dependencies
    if ( !areValid(area, nRows, nCols) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("Tried to calcultate the");
      exceptionMsgThrown.append(" write driver resistance");
      exceptionMsgThrown.append(" in the crosspoint array");
      exceptionMsgThrown.append(", but at least one of the following");
      exceptionMsgThrown.append(" parameters was unknown:");
      exceptionMsgThrown.append("\n  area");
      exceptionMsgThrown.append("\n  nRows");
      exceptionMsgThrown.append("\n  nCols");
      exceptionMsgThrown.append("\n");
      throw exceptionMsgThrown;
    }

    // Consider same analog-mux as Levisse et al 2017,
    // Architecture, Design and Technology Guidelines for Crosspoint Memories
    // However using a NMOS instead of PMOS for half biasing
    // In total 1 PMOS and 2 NMOS, both with thick oxides
    // Plus one Minimum inverter also with thick oxide
    // Disconsider interconnection overhead


    // TODO: ADD AS CLASS ATTRIBUTE WITH PROPER INTERFACE
    bu::quantity<rrs::square_nanometer_unit> arrayControlArea;
    arrayControlArea = 250e6 * rrs::square_nanometers;

    // Minimum sizings
    bu::quantity<rrs::nanometer_unit> lengthwisePMOSPitch;
    lengthwisePMOSPitch = tech.getMinPMOSChannelLength();
    lengthwisePMOSPitch += tech.getActiveExtensionOfPoly();
    lengthwisePMOSPitch += tech.getActiveToActiveSpacing();

    bu::quantity<rrs::nanometer_unit> lengthwiseNMOSPitch;
    lengthwiseNMOSPitch = tech.getMinPMOSChannelLength();
    lengthwiseNMOSPitch += tech.getActiveExtensionOfPoly();
    lengthwiseNMOSPitch += tech.getActiveToActiveSpacing();

    bu::quantity<rrs::nanometer_unit> widthwisePMOSOverhead;
    widthwisePMOSOverhead = tech.getGateExtensionOfActive();
    widthwisePMOSOverhead = tech.getPolyToPolySpacing();

    bu::quantity<rrs::nanometer_unit> widthwiseNMOSOverhead;
    widthwiseNMOSOverhead = tech.getGateExtensionOfActive();
    widthwiseNMOSOverhead = tech.getPolyToPolySpacing();


    bu::quantity<rrs::square_nanometer_unit> minPMOSArea;
    minPMOSArea = lengthwisePMOSPitch
        * (widthwisePMOSOverhead + tech.getMinPMOSChannelWidth());

    bu::quantity<rrs::square_nanometer_unit> minNMOSArea;
    minNMOSArea = lengthwiseNMOSPitch
        * (widthwiseNMOSOverhead + tech.getMinNMOSChannelWidth());

    bu::quantity<rrs::square_nanometer_unit> minInverterArea;
    minInverterArea = minPMOSArea + minNMOSArea;

    // Calculate Wp/Wn ratio to ensure same on-resistance
    //  for both 'analog' P- and NMOSes
    bu::quantity<rrs::dimensionless> PNWidthRatio;
    PNWidthRatio = tech.getPMOSResWidthProduct()/tech.getNMOSResWidthProduct();
    if ( PNWidthRatio < 1.0 ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("NMOS Resistance-width product (");
      exceptionMsgThrown.append(to_string(tech.getNMOSResWidthProduct()));
      exceptionMsgThrown.append(") is greater than that of PMOS (");
      exceptionMsgThrown.append(to_string(tech.getPMOSResWidthProduct()));
      exceptionMsgThrown.append(")! This should never be the case.");
      exceptionMsgThrown.append("\n");
      throw exceptionMsgThrown;
    }

    bu::quantity<rrs::nanometer_unit> minActPMOSWidth;
    bu::quantity<rrs::nanometer_unit> minActNMOSWidth;
    minActPMOSWidth = tech.getMinNMOSChannelWidth()*PNWidthRatio;
    minActNMOSWidth = tech.getMinNMOSChannelWidth();
    if ( minActPMOSWidth < tech.getMinPMOSChannelWidth() ) {
      minActNMOSWidth = minActNMOSWidth *
          tech.getMinPMOSChannelWidth() / minActPMOSWidth;
      minActPMOSWidth = tech.getMinPMOSChannelWidth();
    }

    minPMOSArea = lengthwisePMOSPitch
      * (widthwisePMOSOverhead + minActPMOSWidth);
    minNMOSArea = lengthwiseNMOSPitch
      * (widthwiseNMOSOverhead + minActNMOSWidth);

    bu::quantity<rrs::square_nanometer_unit> minSwitchArea;
    minSwitchArea += 1.0 * minPMOSArea;
    minSwitchArea += 2.0 * minNMOSArea;
    minSwitchArea += minInverterArea;

    bu::quantity<rrs::square_nanometer_unit> minPeripheryArea;
    minPeripheryArea = arrayControlArea + ( nCols + nRows ) * minSwitchArea;

    if ( area < minPeripheryArea ) {
      // Periphery do not fit underneath the array
      // TODO: Throw something, at least a warning
      PRINT_INFO("Minimum periphery area is greater than mem. array area!");
      setArea(minPeripheryArea);

      // Maximum AMUX resistance, given that P- and NMOS resitance are equal
      bu::quantity<rrs::ohm_unit>  maxPMOSResistance;
      maxPMOSResistance = tech.getPMOSResWidthProduct() / minActPMOSWidth;
      bu::quantity<rrs::ohm_unit>  maxNMOSResistance;
      maxNMOSResistance = tech.getNMOSResWidthProduct() / minActNMOSWidth;
      if ( !areEqual(maxPMOSResistance, maxNMOSResistance) ) {
        throw "crap!";
      }
    }

    // Area underneath the array available for switches
    bu::quantity<rrs::square_nanometer_unit> availableArea;
    availableArea = area - arrayControlArea;

    // Maximum area per AMUX
    bu::quantity<rrs::square_nanometer_unit> areaPerAMUX;
    areaPerAMUX = availableArea / ( nRows + nCols ) - minInverterArea;

    bu::quantity<rrs::square_nanometer_unit> actAreaPerAMUX;
    actAreaPerAMUX = availableArea / ( nRows + nCols );
    actAreaPerAMUX -= minInverterArea;
    actAreaPerAMUX -= widthwisePMOSOverhead * lengthwisePMOSPitch;
    actAreaPerAMUX -= 2.0 * widthwiseNMOSOverhead * lengthwiseNMOSPitch;

    bu::quantity<rrs::nanometer_unit> accMOSLengthPitch;
    accMOSLengthPitch = 2.0 * lengthwiseNMOSPitch;
    accMOSLengthPitch += PNWidthRatio * lengthwisePMOSPitch;

    bu::quantity<rrs::nanometer_unit> actNMOSWidth;
    actNMOSWidth = actAreaPerAMUX / accMOSLengthPitch;


    // NMOS resistance - PMOS should be the same, since size ratio was kept
    auto writeDriverRes = tech.getNMOSResWidthProduct() / actNMOSWidth;

    return writeDriverRes;
  }
  else if ( op == read_op ) {
    if ( !areValid(WLWriteDriverResistance, BLWriteDriverResistance) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("Tried to calcultate the");
      exceptionMsgThrown.append(" read driver resistance");
      exceptionMsgThrown.append(" in the crosspoint array");
      exceptionMsgThrown.append(", but at least one of the following");
      exceptionMsgThrown.append(" parameters was unknown:");
      exceptionMsgThrown.append("\n  WLWriteDriverResistance");
      exceptionMsgThrown.append("\n  BLWriteDriverResistance");
      exceptionMsgThrown.append("\n");
      throw exceptionMsgThrown;
    }

    // Reading uses the same amuxes as writting
    auto readDriverRes = (WLWriteDriverResistance + BLWriteDriverResistance)
                         / 2.0;
    return readDriverRes;
  }
  else if ( op == half_select ) {
    if ( !areValid(WLWriteDriverResistance, BLWriteDriverResistance) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("Tried to calcultate the");
      exceptionMsgThrown.append(" half bias driver resistance");
      exceptionMsgThrown.append(" in the crosspoint array");
      exceptionMsgThrown.append(", but at least one of the following");
      exceptionMsgThrown.append(" parameters was unknown:");
      exceptionMsgThrown.append("\n  WLWriteDriverResistance");
      exceptionMsgThrown.append("\n  BLWriteDriverResistance");
      exceptionMsgThrown.append("\n");
      throw exceptionMsgThrown;
    }

    // Half biasing NMOS has the same resistance as write transistors
    auto hbDriverRes = (WLWriteDriverResistance + BLWriteDriverResistance)
                         / 2.0;

    return hbDriverRes;
  }

  return INVALID_DOUBLE * rrs::ohms;

}

bu::quantity<rrs::volt_unit>
XPointArray::findBestVRead()
{
  auto designCurrentRatio = selectedCell.getCellReadCurrentRatio();

  auto bestVRead = INVALID_DOUBLE * rrs::volts;
  auto vRead = writeVoltage;
  auto vReadResolution = writeVoltage / 2.;
  bool foundGoodEnough = false;
  while ( !foundGoodEnough ) {
    calcVSelectedCell(vRead, writeVoltage/2., read_hrs_op);
    calcVSelectedCell(vRead, writeVoltage/2., read_lrs_op);

    // Iteration truth table:
    // isDisruptiveRead  ratio > desginRatio | outcome
    //      false             false          | increase vR
    //      false             true           | lower vR, there exists an optimal
    //      true              false          | Ratio is infeasible, exit
    //      true              true           | lower vR
    // Current ratio
    auto currentRatio = readLRSSCCurrent / readHRSSCCurrent;
    // isDisruptiveRead
    // Approximation to the read voltage at cell closest to drivers (no vDrop)
    HSCellNL.setCellSetVoltage(vRead);
    auto setWhileReadingTime = HSCellNL.getCellSetTime();
    // TODO: Add model to currentSensingDelay as f(I_RATIO)
    bool isDisruptiveRead =
        setWhileReadingTime < 1e6*currentSensingDelay ? true:false;
    if ( !isDisruptiveRead && !(currentRatio > designCurrentRatio) ) {
      vRead += vReadResolution;
      vReadResolution /= 2.;
    } else if ( !isDisruptiveRead && (currentRatio > designCurrentRatio) ) {
      bestVRead = vRead; // So far
      if ( fastAreEqual(currentRatio, designCurrentRatio, 1e-3) ) {
        foundGoodEnough = true;
      }
      vRead -= vReadResolution;
      vReadResolution /= 2.;
    } else if ( isDisruptiveRead && !(currentRatio > designCurrentRatio) ) {
      bestVRead = INVALID_DOUBLE * rrs::volts; // Unnecessary. Code clarity.
      string infoString("Could not find apropriate read voltage");
      infoString.append(" for a LRS/HRS read current ratio of ");
      infoString.append(to_string((double)designCurrentRatio));
      infoString.append(" on a ");
      infoString.append(to_string(nRows));
      infoString.append(" x ");
      infoString.append(to_string(nCols));
      infoString.append(" crosspoint array. The last ratio was ");
      infoString.append(to_string(currentRatio));
      infoString.append(" at a read voltage of ");
      infoString.append(to_string(vRead));
      infoString.append(" which already causes disruptive reading.");
      PRINT_INFO(infoString);
      break;
    } else {
      vRead -= vReadResolution;
      vReadResolution /= 2.;
    }
  }

  return bestVRead;
}

bu::quantity<rrs::volt_unit>
XPointArray::calcVEdge( bu::quantity<rrs::volt_unit> vSC,
                        rramOperations op )
{
  try {

    initializeIterativeVariables(op);

    // Current and voltage necessary on selected cell
    bu::quantity<rrs::ampere_unit> iSC;
    iSC = SCALE_QUANTITY( selectedCell.getCellCurrent(vSC), rrs::ampere_unit);
    iNLCells.at(0) = SCALE_QUANTITY(iSC, rrs::nanoampere_unit);
    iPLCells.at(nPLSegs-1) = SCALE_QUANTITY(iSC, rrs::nanoampere_unit);

    // PL AMUX 'input' voltage - yet to be found
    // NL AMUX 'input' voltage is considered to be grounded
    bu::quantity<rrs::volt_unit> vP(0 * rrs::volts);
    // 'Input' AMUX voltage for unselected lines, V/2 scheme
    bu::quantity<rrs::volt_unit> vHalf(0 * rrs::volts);

    /*** Voltage drop across lines due to selected cell current () ***/
    vNLSegs.at(nNLSegs-1) = iSC * accRNL.at(nNLSegs - 1);
    for (size_t NLSeg = nNLSegs-1; NLSeg-- > 0;) {
      vNLSegs.at(NLSeg) = vNLSegs.at(NLSeg+1) + NLResistancePerCell * iSC;
    }

    vPLSegs.at(nPLSegs-1) = vNLSegs.at(0) + vSC;
    for (size_t PLSeg = nPLSegs-1; PLSeg-- > 0;) {
      vPLSegs.at(PLSeg) = vPLSegs.at(PLSeg+1) + PLResistancePerCell * iSC;
    }

    vP = vPLSegs.at(0) + accRPL.at(0) * iSC;
    vHalf = vP / 2.;

    // PL AMUX voltage relative error between iterations
    bu::quantity<rrs::dimensionless> relError(1./0.);

    /*** ************************ Main algorithm ************************ ***/
    /* Updates sneak current while updating AMUX voltage */

    while ( abs(relError) >  1e-6 ) {
      auto lastVP = vP;
      bu::quantity<rrs::volt_unit> accDeltaV = 0 * rrs::volts;

      bu::quantity<rrs::nanoampere_unit> lastI;
      bu::quantity<rrs::nanoampere_unit> deltaI;
      bu::quantity<rrs::volt_unit> deltaV;
      // Update NL cell currents and next cell (and AMUX) voltage
      for (size_t NLSeg = nNLSegs-1; NLSeg >= 1; --NLSeg) {
        lastI = iNLCells.at(NLSeg);
        iNLCells.at(NLSeg) = HSCellNL.getCellCurrent(vHalf - vNLSegs.at(NLSeg));
        deltaI = iNLCells.at(NLSeg) - lastI;

        deltaV = accRNL.at(NLSeg) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vNLSegs.at(NLSeg - 1) += accDeltaV;
        vP += deltaV;
        vHalf = vP/2.;
      }

      deltaI = 0 * rrs::nanoamperes;
      bu::quantity<rrs::nanoampere_unit> accDeltaI = 0 * rrs::nanoamperes;
      // Update PL cell currents and "previous" cell (and AMUX) voltage
      vPLSegs.at(nPLSegs - 1) += accDeltaV;
      for (size_t PLSeg = nPLSegs-1; PLSeg-- > 0;) {
        deltaV = PLResistancePerCell
                  * SCALE_QUANTITY(accDeltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vP += accRPL.at(PLSeg+1)*SCALE_QUANTITY(deltaI, rrs::ampere_unit);
        vHalf = vP/2.;

        vPLSegs.at(PLSeg) += accDeltaV;

        lastI = iPLCells.at(PLSeg);
        iPLCells.at(PLSeg) = HSCellPL.getCellCurrent(vPLSegs.at(PLSeg) - vHalf);

        deltaI = iPLCells.at(PLSeg) - lastI;
        accDeltaI += deltaI;

      }
      vP += accRPL.at(0) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);
      vHalf = vP/2.;

      // Update NL segments voltages
      bu::quantity<rrs::ampere_unit> accINL = 0 * rrs::amperes;
      for(auto& INLCell : iNLCells) {
        accINL += SCALE_QUANTITY(INLCell, rrs::ampere_unit);
      }
      vNLSegs.at(nNLSegs-1) = accINL * (NAMUXResistance + NLResistancePerCell);
      for (size_t NLSeg = nNLSegs-1; NLSeg-- > 0; ) {
        accINL -= SCALE_QUANTITY(iNLCells.at(NLSeg+1), rrs::ampere_unit);
        vNLSegs.at(NLSeg) = vNLSegs.at(NLSeg+1) + accINL * NLResistancePerCell;
      }

      relError = (lastVP - vP) / vP;

    }

    if ( iNLCells.at(0) != iPLCells.back() ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("somthing worng with selected cell current.");
      throw exceptionMsgThrown;
    }
    auto zeroAmp = 0. * rrs::nanoamperes;
    auto SCCurrent = iNLCells.at(0);
    auto SPCurrent = accumulate(iPLCells.begin(), iPLCells.end()-1, zeroAmp);
    SPCurrent += accumulate(iNLCells.begin()+1, iNLCells.end(), zeroAmp);

    if ( op == set_op ) {
      setSCCurrent = SCCurrent;
      setSPCurrent = SPCurrent;
    }
    else if ( op == reset_op ) {
      resetSCCurrent = SCCurrent;
      resetSPCurrent = SPCurrent;
    }
    else if ( op == read_hrs_op ) {
      readHRSSCCurrent = SCCurrent;
      readHRSSPCurrent = SPCurrent;
    }
    else if ( op == read_lrs_op ) {
      readLRSSCCurrent = SCCurrent;
      readLRSSPCurrent = SPCurrent;
    }

    return vP;

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

bu::quantity<rrs::volt_unit>
XPointArray::calcVEdge( bu::quantity<rrs::volt_unit> vSC,
                        bu::quantity<rrs::volt_unit> vHalf,
                        rramOperations op )
{
  try {

    initializeIterativeVariables(op);

    // Current and voltage necessary on selected cell
    bu::quantity<rrs::ampere_unit> iSC;
    iSC = SCALE_QUANTITY( selectedCell.getCellCurrent(vSC), rrs::ampere_unit);
    iNLCells.at(0) = SCALE_QUANTITY(iSC, rrs::nanoampere_unit);
    iPLCells.at(nPLSegs-1) = SCALE_QUANTITY(iSC, rrs::nanoampere_unit);

    // PL AMUX 'input' voltage - yet to be found
    // NL AMUX 'input' voltage is considered to be grounded
    bu::quantity<rrs::volt_unit> vP(0 * rrs::volts);

    /*** Voltage drop across lines due to writing current () ***/
    vNLSegs.at(nNLSegs-1) = iSC * accRNL.at(nNLSegs - 1);
    for (size_t NLSeg = nNLSegs-1; NLSeg-- > 0;) {
      vNLSegs.at(NLSeg) = vNLSegs.at(NLSeg+1) + NLResistancePerCell * iSC;
    }

    vPLSegs.at(nPLSegs-1) = vNLSegs.at(0) + vSC;
    for (size_t PLSeg = nPLSegs-1; PLSeg-- > 0;) {
      vPLSegs.at(PLSeg) = vPLSegs.at(PLSeg+1) + PLResistancePerCell * iSC;
    }

    vP = vPLSegs.at(0) + accRPL.at(0) * iSC;

    // PL AMUX voltage relative error between iterations
    bu::quantity<rrs::dimensionless> relError(1./0.);

    /*** ************************ Main algorithm ************************ ***/
    /* Updates sneak current while updating AMUX voltage */

    while ( abs(relError) >  1e-6 ) {
      auto lastVP = vP;
      bu::quantity<rrs::volt_unit> accDeltaV = 0 * rrs::volts;

      bu::quantity<rrs::nanoampere_unit> lastI;
      bu::quantity<rrs::nanoampere_unit> deltaI;
      bu::quantity<rrs::volt_unit> deltaV;
      // Update NL cell currents and next cell (and AMUX) voltage
      for (size_t NLSeg = nNLSegs-1; NLSeg >= 1; --NLSeg) {
        lastI = iNLCells.at(NLSeg);
        iNLCells.at(NLSeg) = HSCellNL.getCellCurrent(vHalf - vNLSegs.at(NLSeg));
        deltaI = iNLCells.at(NLSeg) - lastI;

        deltaV = accRNL.at(NLSeg) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vNLSegs.at(NLSeg - 1) += accDeltaV;
        vP += deltaV;
      }

      deltaI = 0 * rrs::nanoamperes;
      bu::quantity<rrs::nanoampere_unit> accDeltaI = 0 * rrs::nanoamperes;
      // Update PL cell currents and "previous" cell (and AMUX) voltage
      vPLSegs.at(nPLSegs - 1) += accDeltaV;
      for (size_t PLSeg = nPLSegs-1; PLSeg-- > 0;) {
        deltaV = PLResistancePerCell
                  * SCALE_QUANTITY(accDeltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vP += accRPL.at(PLSeg+1)*SCALE_QUANTITY(deltaI, rrs::ampere_unit);

        vPLSegs.at(PLSeg) += accDeltaV;

        lastI = iPLCells.at(PLSeg);
        iPLCells.at(PLSeg) = HSCellPL.getCellCurrent(vPLSegs.at(PLSeg) - vHalf);

        deltaI = iPLCells.at(PLSeg) - lastI;
        accDeltaI += deltaI;

      }
      vP += accRPL.at(0) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);

      // Update NL segments voltages
      bu::quantity<rrs::ampere_unit> accINL = 0 * rrs::amperes;
      for(auto& INLCell : iNLCells) {
        accINL += SCALE_QUANTITY(INLCell, rrs::ampere_unit);
      }
      vNLSegs.at(nNLSegs-1) = accINL * (NAMUXResistance + NLResistancePerCell);
      for (size_t NLSeg = nNLSegs-1; NLSeg-- > 0; ) {
        accINL -= SCALE_QUANTITY(iNLCells.at(NLSeg+1), rrs::ampere_unit);
        vNLSegs.at(NLSeg) = vNLSegs.at(NLSeg+1) + accINL * NLResistancePerCell;
      }

      relError = (lastVP - vP) / vP;

    }

    if ( iNLCells.at(0) != iPLCells.back() ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("somthing worng with selected cell current.");
      throw exceptionMsgThrown;
    }
    auto zeroAmp = 0. * rrs::nanoamperes;
    auto SCCurrent = iNLCells.at(0);
    auto SPCurrent = accumulate(iPLCells.begin(), iPLCells.end()-1, zeroAmp);
    SPCurrent += accumulate(iNLCells.begin()+1, iNLCells.end(), zeroAmp);

    if ( op == set_op ) {
      setSCCurrent = SCCurrent;
      setSPCurrent = SPCurrent;
    }
    else if ( op == reset_op ) {
      resetSCCurrent = SCCurrent;
      resetSPCurrent = SPCurrent;
    }
    else if ( op == read_hrs_op ) {
      readHRSSCCurrent = SCCurrent;
      readHRSSPCurrent = SPCurrent;
    }
    else if ( op == read_lrs_op ) {
      readLRSSCCurrent = SCCurrent;
      readLRSSPCurrent = SPCurrent;
    }

    return vP;

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}


bu::quantity<rrs::volt_unit>
XPointArray::calcVSelectedCell( bu::quantity<rrs::volt_unit> vP,
                               rramOperations op)
{
  return calcVSelectedCell(vP, vP / 2., op);
}


bu::quantity<rrs::volt_unit>
XPointArray::calcVSelectedCell( bu::quantity<rrs::volt_unit> vP,
                                bu::quantity<rrs::volt_unit> vHalf,
                                rramOperations op)
{
  try {

    initializeIterativeVariables(op);

    // PL AMUX 'input' voltage - Given
    // HSC AMUX 'input' voltage - Given
    // NL AMUX 'input' voltage is either
    //  grounded during normal operations
    //  or at vHalf during calibration
    auto vN = 0. * rrs::volts;
    if ( op == set_op || op == reset_op ||
         op == read_hrs_op || op == read_lrs_op ) {
      vN = 0. * rrs::volts;
      for (auto& vPLSeg : vPLSegs ) { vPLSeg = vP; }
      for (auto& vNLSeg : vNLSegs ) { vNLSeg = vN; }
    }
    else if ( op == calib_wr_all_hrs_op || op == calib_wr_all_lrs_op ||
              op == calib_rd_all_hrs_op || op == calib_rd_all_lrs_op) {
      vN = vHalf;
      for (auto& vPLSeg : vPLSegs ) { vPLSeg = vP; }
      for (auto& vNLSeg : vNLSegs ) { vNLSeg = vN; }
    }
    else {
      throw op;
    }

    // Voltage across the selected cell
    // Index is the iteration - 0 for this, 1 for last, 2 for second last
    vector<bu::quantity<rrs::volt_unit>> vSC(3, 0. * rrs::volts);

    // Selected cell voltage relative error between iterations
    bu::quantity<rrs::dimensionless> relError(1./0.);

    // Factor to slow down vSC variation to improve convergence
    double slowDownFactor = 1.;


    /*** ************************ Main algorithm ************************ ***/
    /* Updates sneak current while updating driver voltage */
    while ( abs(relError) >  1e-6 ) {

      bu::quantity<rrs::nanoampere_unit> lastI;
      bu::quantity<rrs::nanoampere_unit> deltaI;
      bu::quantity<rrs::volt_unit> deltaV;
      bu::quantity<rrs::volt_unit> accDeltaV;

      // Update NL cell currents and next cell voltage
      accDeltaV = 0 * rrs::volts;
      for (size_t NLSeg = nNLSegs-1; NLSeg >= 1; --NLSeg) {
        lastI = iNLCells.at(NLSeg);
        iNLCells.at(NLSeg) = HSCellNL.getCellCurrent(vHalf - vNLSegs.at(NLSeg));
        deltaI = iNLCells.at(NLSeg) - lastI;

        deltaV = accRNL.at(NLSeg) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vNLSegs.at(NLSeg - 1) += accDeltaV;
      }

      // Update PL cell currents and next cell voltage
      accDeltaV = 0 * rrs::volts;
      for (size_t PLSeg = 0; PLSeg < nPLSegs-1; ++PLSeg) {
        lastI = iPLCells.at(PLSeg);
        iPLCells.at(PLSeg) = HSCellNL.getCellCurrent(vPLSegs.at(PLSeg) - vHalf);
        deltaI = iPLCells.at(PLSeg) - lastI;

        deltaV = accRPL.at(PLSeg) * SCALE_QUANTITY(deltaI, rrs::ampere_unit);
        accDeltaV += deltaV;

        vPLSegs.at(PLSeg + 1) -= accDeltaV;
      }

      vSC.at(2) = vSC.at(1);
      vSC.at(1) = vSC.at(0);
      vSC.at(0) = vPLSegs.at(nPLSegs-1) - vNLSegs.at(0);
      if ( areEqual(vSC.at(0), vSC.at(2), 1e-3) ) {
        if ( !areEqual(vSC.at(0), vSC.at(1), 1e-3) ) {
          slowDownFactor *= 2.;
        }
      }
      auto deltaVSelectedCell = vSC.at(0) - vSC.at(1);
      // Slow down voltage variation to improve convergence
      vSC.at(0) = vSC.at(1) + deltaVSelectedCell / slowDownFactor;
      iNLCells.at(0) = selectedCell.getCellCurrent(vSC.at(0));
      iPLCells.at(nPLSegs-1) = iNLCells.at(0);
      relError = (vSC.at(1) - vSC.at(0)) / vSC.at(0);

      // Update NL segments voltages
      bu::quantity<rrs::ampere_unit> accINL = 0 * rrs::amperes;
      for(auto& INLCell : iNLCells) {
        accINL += SCALE_QUANTITY(INLCell, rrs::ampere_unit);
      }
      vNLSegs.at(nNLSegs-1) = vN + accINL * (NAMUXResistance + NLResistancePerCell);
      for (size_t NLSeg = nNLSegs-1; NLSeg-- > 0; ) {
        accINL -= SCALE_QUANTITY(iNLCells.at(NLSeg+1), rrs::ampere_unit);
        vNLSegs.at(NLSeg) = vNLSegs.at(NLSeg+1) + accINL * NLResistancePerCell;
      }

      // Update PL segments voltages
      bu::quantity<rrs::ampere_unit> accIPL = 0 * rrs::amperes;
      for(auto& IPLCell : iPLCells) {
        accIPL += SCALE_QUANTITY(IPLCell, rrs::ampere_unit);
      }
      vPLSegs.at(0) = vP - accIPL * (PAMUXResistance + PLResistancePerCell);
      for (size_t PLSeg = 1; PLSeg < nPLSegs; ++PLSeg ) {
        accIPL -= SCALE_QUANTITY(iPLCells.at(PLSeg-1), rrs::ampere_unit);
        vPLSegs.at(PLSeg) = vPLSegs.at(PLSeg-1) - accIPL * WLResistancePerCell;
      }

    }

    if ( iNLCells.at(0) != iPLCells.back() ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("somthing worng with selected cell current.");
      throw exceptionMsgThrown;
    }
    auto zeroAmp = 0. * rrs::nanoamperes;
    auto SCCurrent = iNLCells.at(0);
    auto SPCurrent = accumulate(iPLCells.begin(), iPLCells.end()-1, zeroAmp);
    SPCurrent += accumulate(iNLCells.begin()+1, iNLCells.end(), zeroAmp);

    if ( op == set_op ) {
      setSCCurrent = SCCurrent;
      setSPCurrent = SPCurrent;
    }
    else if ( op == reset_op ) {
      resetSCCurrent = SCCurrent;
      resetSPCurrent = SPCurrent;
    }
    else if ( op == read_hrs_op ) {
      readHRSSCCurrent = SCCurrent;
      readHRSSPCurrent = SPCurrent;
    }
    else if ( op == read_lrs_op ) {
      readLRSSCCurrent = SCCurrent;
      readLRSSPCurrent = SPCurrent;
    }

    return vSC.at(0);

  } catch(rramOperations op) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("unable to recognize array operation");
    exceptionMsgThrown.append(" for selected cell voltage calculation.\n");
    exceptionMsgThrown.append(" Operation should be either \'set_op\' (");
    exceptionMsgThrown.append(to_string(set_op));
    exceptionMsgThrown.append(") or \'reset_op\' (");
    exceptionMsgThrown.append(to_string(reset_op));
    exceptionMsgThrown.append(") or \'read_hrs_op\' (");
    exceptionMsgThrown.append(to_string(read_hrs_op));
    exceptionMsgThrown.append(") or \'read_lrs_op\' (");
    exceptionMsgThrown.append(to_string(read_lrs_op));
    exceptionMsgThrown.append(") or \'calib_wr_all_hrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_wr_all_hrs_op));
    exceptionMsgThrown.append(") or \'calib_wr_all_lrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_wr_all_lrs_op));
    exceptionMsgThrown.append(") or \'calib_rd_all_hrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_rd_all_hrs_op));
    exceptionMsgThrown.append(") or \'calib_rd_all_lrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_rd_all_lrs_op));
    exceptionMsgThrown.append(") but was ");
    exceptionMsgThrown.append(to_string(op));
    exceptionMsgThrown.append(".\n");
    throw exceptionMsgThrown;
  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

void
XPointArray::initializeIterativeVariables(rramOperations op)
{
  try {
    if ( !areValid(
           nRows, nCols,
           WLResistancePerCell, BLResistancePerCell,
           WLWriteDriverResistance, BLWriteDriverResistance,
           WLReadDriverResistance, BLReadDriverResistance,
           halfBiasDriverResistance
          )
    ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("Tried initialize varibles for");
      exceptionMsgThrown.append(" iterative methods");
      exceptionMsgThrown.append(", but at least one of the following");
      exceptionMsgThrown.append(" parameters was unknown:");
      exceptionMsgThrown.append("\n  nRows");
      exceptionMsgThrown.append("\n  nCols");
      exceptionMsgThrown.append("\n  WLResistancePerCell");
      exceptionMsgThrown.append("\n  BLResistancePerCell");
      exceptionMsgThrown.append("\n  WLWriteDriverResistance");
      exceptionMsgThrown.append("\n  BLWriteDriverResistance");
      exceptionMsgThrown.append("\n  WLReadDriverResistance");
      exceptionMsgThrown.append("\n  BLReadDriverResistance");
      exceptionMsgThrown.append("\n  halfBiasDriverResistance");
      exceptionMsgThrown.append("\n");
      throw exceptionMsgThrown;
    }

    // Invalidation for future check
    nPLSegs = INVALID_DOUBLE;
    nNLSegs = INVALID_DOUBLE;

    PLResistancePerCell = INVALID_DOUBLE * rrs::ohms;
    NLResistancePerCell = INVALID_DOUBLE * rrs::ohms;

    PAMUXResistance = INVALID_DOUBLE * rrs::ohms;
    NAMUXResistance = INVALID_DOUBLE * rrs::ohms;

    vPLSegs.clear();
    vPLSegs.push_back( INVALID_DOUBLE * rrs::volts );
    iPLCells.clear();
    iPLCells.push_back( INVALID_DOUBLE * rrs::nanoamperes );
    vNLSegs.clear();
    vNLSegs.push_back( INVALID_DOUBLE * rrs::volts );
    iNLCells.clear();
    iNLCells.push_back( INVALID_DOUBLE * rrs::nanoamperes );

    auto totalSeriesResistance = INVALID_DOUBLE * rrs::ohms;

    accRPL.clear();
    accRPL.push_back( INVALID_DOUBLE * rrs::ohms );
    accRNL.clear();
    accRNL.push_back( INVALID_DOUBLE * rrs::ohms );

    if ( op == set_op || op == read_hrs_op || op == read_lrs_op ||
         op == calib_wr_all_hrs_op || op == calib_wr_all_lrs_op ||
         op == calib_rd_all_hrs_op || op == calib_rd_all_lrs_op ) {
      // PL is WL and NL is BL
      nPLSegs = nCols;
      nNLSegs = nRows;
      PLResistancePerCell = WLResistancePerCell;
      NLResistancePerCell = BLResistancePerCell;
      if ( op == set_op  ||
           op == calib_wr_all_hrs_op || op == calib_wr_all_lrs_op ) {
        PAMUXResistance = WLWriteDriverResistance;
        NAMUXResistance = BLWriteDriverResistance;
      }
      else if ( op == read_hrs_op || op == read_lrs_op ||
                op == calib_rd_all_hrs_op || op == calib_rd_all_lrs_op ) {
        PAMUXResistance = WLReadDriverResistance;
        NAMUXResistance = BLReadDriverResistance;
      }
      else {
        throw op;
      }
    }
    else if ( op == reset_op ) {
      // PL is BL and NL is WL
      nPLSegs = nRows;
      nNLSegs = nCols;
      PLResistancePerCell = BLResistancePerCell;
      NLResistancePerCell = WLResistancePerCell;
      PAMUXResistance = BLWriteDriverResistance;
      NAMUXResistance = WLWriteDriverResistance;
    }
    else {
      throw op;
    }

    vPLSegs.clear();
    vPLSegs.resize(nPLSegs, 0. * rrs::volts);
    iPLCells.clear();
    iPLCells.resize(nPLSegs, 0. * rrs::nanoamperes);
    vNLSegs.clear();
    vNLSegs.resize(nNLSegs, 0. * rrs::volts);
    iNLCells.clear();
    iNLCells.resize(nNLSegs, 0. * rrs::nanoamperes);

    // Total resistance in series with selector of the half selected cells
    // Memory device res. + line driver res. + complete line res.
    totalSeriesResistance = selectedCell.getMemDevLRSResistance();
    totalSeriesResistance += halfBiasDriverResistance;
    totalSeriesResistance += nNLSegs * NLResistancePerCell;
    HSCellPL.setMemDevLRSResistance(totalSeriesResistance);

    totalSeriesResistance = selectedCell.getMemDevHRSResistance();
    totalSeriesResistance += halfBiasDriverResistance;
    totalSeriesResistance += nNLSegs * NLResistancePerCell;
    HSCellPL.setMemDevHRSResistance(totalSeriesResistance);

    totalSeriesResistance = selectedCell.getMemDevLRSResistance();
    totalSeriesResistance += halfBiasDriverResistance;
    totalSeriesResistance += nPLSegs * PLResistancePerCell;
    HSCellNL.setMemDevLRSResistance(totalSeriesResistance);

    totalSeriesResistance = selectedCell.getMemDevHRSResistance();
    totalSeriesResistance += halfBiasDriverResistance;
    totalSeriesResistance += nPLSegs * PLResistancePerCell;
    HSCellNL.setMemDevHRSResistance(totalSeriesResistance);

    HSCellPL.buildCellIxV();
    HSCellNL.buildCellIxV();

    if ( op == set_op || op == reset_op || op == read_lrs_op ||
         op == calib_wr_all_lrs_op || op == calib_rd_all_lrs_op ) {
      HSCellPL.setMemDevResistanceState(true);
      HSCellNL.setMemDevResistanceState(true);
      if ( op == set_op || op == read_hrs_op ) {
        // Selected cell will be set, so it's in HRS (0)
        selectedCell.setMemDevResistanceState(false);
      }
      else if ( op == reset_op || op == read_lrs_op ||
                op == calib_wr_all_lrs_op || op == calib_rd_all_lrs_op ) {
        // Selected cell will be reset, so it's in LRS (1)
        selectedCell.setMemDevResistanceState(true);
      }
      else {
        throw op;
      }
    }
    else if ( op == read_hrs_op ||
              op == calib_wr_all_hrs_op  || op == calib_rd_all_hrs_op ) {
      HSCellPL.setMemDevResistanceState(false);
      HSCellNL.setMemDevResistanceState(false);
      selectedCell.setMemDevResistanceState(false);
    }
    else {
      throw op;
    }

    // Create vector containing total resistance seen
    //  from PL segment to PL AMUX
    // It is the accumulated resistance from the begining
    //  of the line (AMUX) until the PL segment
    // nPLSegs+1 to avoid seg. fault during VSC calculation
    accRPL.clear();
    accRPL.resize(nPLSegs+1, 0. * rrs::ohms);
    accRPL.at(0) = PAMUXResistance + PLResistancePerCell;
    for (size_t PLSeg = 1; PLSeg < nPLSegs+1; PLSeg++) {
      accRPL.at(PLSeg) = accRPL.at(PLSeg - 1) + PLResistancePerCell;
    }

    // Create vector containing total resistance seen
    //  from NL segment to NL AMUX
    // It is the accumulated resistance from the begining
    //  of the line (AMUX) until the NL segment
    accRNL.clear();
    accRNL.resize(nNLSegs, 0. * rrs::ohms);
    accRNL.at(0) = NAMUXResistance + nNLSegs * NLResistancePerCell;
    for (size_t NLSeg = 1; NLSeg < nNLSegs; NLSeg++) {
      accRNL.at(NLSeg) = accRNL.at(NLSeg - 1) - NLResistancePerCell;
    }

    if ( !areValid(
           nPLSegs, nNLSegs,
           PLResistancePerCell, NLResistancePerCell,
           PAMUXResistance, NAMUXResistance,
           vPLSegs.back(), iPLCells.back(),
           vNLSegs.back(), iNLCells.back(),
           totalSeriesResistance,
           accRPL.back(), accRNL.back()
          )
      )
    {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("some varible(s) for iterative methods");
      exceptionMsgThrown.append(" where not correctly initialized.\n");
      throw exceptionMsgThrown;
    }

  } catch(rramOperations op) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("unable to recognize array operation");
    exceptionMsgThrown.append(" for initialization of");
    exceptionMsgThrown.append(" iterative methods variables.\n");
    exceptionMsgThrown.append(" Operation should be either \'set_op\' (");
    exceptionMsgThrown.append(to_string(set_op));
    exceptionMsgThrown.append(") or \'reset_op\' (");
    exceptionMsgThrown.append(to_string(reset_op));
    exceptionMsgThrown.append(") or \'read_hrs_op\' (");
    exceptionMsgThrown.append(to_string(read_hrs_op));
    exceptionMsgThrown.append(") or \'read_lrs_op\' (");
    exceptionMsgThrown.append(to_string(read_lrs_op));
    exceptionMsgThrown.append(") or \'calib_wr_all_hrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_wr_all_hrs_op));
    exceptionMsgThrown.append(") or \'calib_wr_all_lrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_wr_all_lrs_op));
    exceptionMsgThrown.append(") or \'calib_rd_all_hrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_rd_all_hrs_op));
    exceptionMsgThrown.append(") or \'calib_rd_all_lrs_op\' (");
    exceptionMsgThrown.append(to_string(calib_rd_all_lrs_op));
    exceptionMsgThrown.append(") but was ");
    exceptionMsgThrown.append(to_string(op));
    exceptionMsgThrown.append(".\n");
    throw exceptionMsgThrown;
  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }


}



void
XPointArray::updateXPointArray()
{
  try {
    if ( isInvalid(nRows) || isInvalid(nCols) ) {
      string exceptionMsgThrown("[ERROR] ");
      exceptionMsgThrown.append("Unexpected behaviour - ");
      exceptionMsgThrown.append("number of rows or columns is undefined.");
      throw exceptionMsgThrown;
    }

    /*
    // Derive all not expecified variable
    // First test if all possible information was given by the user
    //  if so, no need to derive anything
    //  esle, test if enough information was given
    //   if so, update/derive the missing info
    //   else, throw error

    // NOTE: The order of groups of variables to be tested is important
    // The more "fanout" a variable has, the earlier it should be tested

    // No class internal dependencies - other than already set in this function
    */ // This comments may be outdated
    if ( isInvalid(WLMetalWidth) ) {
      updateWLMetalWidth();
    }
    if ( isInvalid(BLMetalWidth) ) {
      updateBLMetalWidth();
    }

    if ( isInvalid(heightwiseCellPitch) ) {
      updateHeightwiseCellPitch();
    }
    if ( isInvalid(widthwiseCellPitch) ) {
      updateWidthwiseCellPitch();
    }

    updateLinesElectricalParameters();

    updateArea();
    updateCapacity();

    // Update AMUX resistance
    updateWLWriteDriverResistance();
    updateBLWriteDriverResistance();
    updateWLReadDriverResistance();
    updateBLReadDriverResistance();
    updateHalfBiasDriverResistance();


    // Use the maximum voltage "supported" by the thicker oxide transistors
    writeVoltage = 0.9*tech.getBreakdownVoltage();

    auto vReset = calcVSelectedCell(writeVoltage, reset_op);
    selectedCell.setCellResetVoltage(vReset);

    auto vSet = calcVSelectedCell(writeVoltage, set_op);
    selectedCell.setCellSetVoltage(vSet);

    readVoltage = findBestVRead();

    updateAdjLineDelays();
    updateLineDelays();
    updateCalibrationDelay();

    updatePrechargeTime();
    updateWriteTime();
    updateReadTime();

    cout << endl;

    updatePrechargeCurrent();
    updateWriteCurrent();
    updateReadCurrent();

    updatePrechargeEnergy();
    updateWriteEnergy();
    updateReadEnergy();

//    PRINT_VAR(getNRows());
//    PRINT_VAR(getNCols());
//    PRINT_VAR(getAreaEfficiency());
//    PRINT_VAR(getWLWriteDriverResistance());
//    PRINT_VAR(getSetTime());
//    PRINT_VAR(getSetCurrent());
//    PRINT_VAR(getResetTime());
//    PRINT_VAR(getResetCurrent());
//    PRINT_VAR(getReadTime());
//    PRINT_VAR(getWriteTime());
//    PRINT_VAR(getWriteEnergy());
//    PRINT_VAR(getReadEnergy());

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}



XPointArray::XPointArray()
{
  initialize();
}

XPointArray::XPointArray(const Config& config)
{
  try {
    initialize();

    // Configuration file names as C-like strings
    cellFileName = config.cellFileName.c_str();
    techFileName = config.techFileName.c_str();
    archFileName = config.archFileName.c_str();

    buildFromConfigFiles();

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

XPointArray::~XPointArray()
{

}







