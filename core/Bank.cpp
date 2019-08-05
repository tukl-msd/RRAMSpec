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



#include "Bank.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

void
Bank::initialize()
{
  optMode = INVALID_OPT_MODE;

  capacity = INVALID_DOUBLE * rrs::gibibits;
  nDataBusBits = INVALID_DOUBLE;
  prefetch = INVALID_DOUBLE;

  nSubarrays = INVALID_DOUBLE;
  nActiveSubarraysPerAccess = INVALID_DOUBLE;
  nSubarraysPerRow = INVALID_DOUBLE;
  nSubarraysPerCol = INVALID_DOUBLE;

  minAddressableBlock = INVALID_DOUBLE * rrs::bits;
  pageSize = INVALID_DOUBLE * rrs::bits;
  nRowAddressLines = INVALID_DOUBLE;
  nColAddressLines = INVALID_DOUBLE;


  rowDecoderWidth = INVALID_DOUBLE * rrs::nanometers;
  rowDecoderHeight = INVALID_DOUBLE * rrs::nanometers;
  rowDecoderArea = INVALID_DOUBLE * rrs::square_nanometers;
  colDecoderWidth = INVALID_DOUBLE * rrs::nanometers;
  colDecoderHeight = INVALID_DOUBLE * rrs::nanometers;
  colDecoderArea = INVALID_DOUBLE * rrs::square_nanometers;

  area = INVALID_DOUBLE * rrs::square_nanometers;
  height = INVALID_DOUBLE * rrs::nanometers;
  width = INVALID_DOUBLE * rrs::nanometers;
  areaEfficiency = INVALID_DOUBLE;

  rowDecoderDelay = INVALID_DOUBLE * rrs::nanoseconds;
  colDecoderDelay = INVALID_DOUBLE * rrs::nanoseconds;

  globalBusDelay = INVALID_DOUBLE * rrs::nanoseconds;

  prechargeTime = INVALID_DOUBLE * rrs::nanoseconds;
  writeTime = INVALID_DOUBLE * rrs::nanoseconds;
  readTime = INVALID_DOUBLE * rrs::nanoseconds;

  leakagePower = INVALID_DOUBLE * rrs::nanowatts;

  interfaceBusEnergy = INVALID_DOUBLE * rrs::picojoules;
  prechargeEnergy = INVALID_DOUBLE * rrs::picojoules;
  writeEnergy = INVALID_DOUBLE * rrs::picojoules;
  readEnergy = INVALID_DOUBLE * rrs::picojoules;

  bestWriteEnergy = INVALID_DOUBLE * rrs::picojoules;
  bestWriteTime = INVALID_DOUBLE * rrs::nanoseconds;
}



void
Bank::setOptMode( string opt )
{
  if ( opt == "fixed" ) {
    optMode = fixed;
  }
  else if ( opt == "density" ) {
    optMode = density;
  }
  else if ( opt == "performance" ) {
    optMode = performance;
  }
  else if ( opt == "energy" ) {
    optMode = energy;
  }
  else {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Tried to set an optimization mode for");
    exceptionMsgThrown.append(" crosspoint array, \"");
    exceptionMsgThrown.append(opt);
    exceptionMsgThrown.append("\", different from the ones supported:\n");
    exceptionMsgThrown.append("  \"fixed\"\n");
    exceptionMsgThrown.append("  \"density\"\n");
    exceptionMsgThrown.append("  \"performance\"\n");
    exceptionMsgThrown.append("  \"energy\"\n");
    throw exceptionMsgThrown;
  }
}

string
Bank::getOptMode()
{
  string optModeStr;
  switch (optMode) {
    case fixed:             optModeStr = "fixed";         break;
    case density:           optModeStr = "density";       break;
    case performance:       optModeStr = "performance";   break;
    case energy:            optModeStr = "energy";        break;
    case INVALID_OPT_MODE:  optModeStr = INVALID_STRING;  break;

    default:            optModeStr = "UNLISTED";      break;
  }

  if ( optModeStr == "UNLISTED" ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to get optimization mode,");
    exceptionMsgThrown.append(" but its value is not listed.");
    throw exceptionMsgThrown;
  }

  return optModeStr;
}

void
Bank::setCapacity(bu::quantity<rrs::gibibit_unit> size)
{
  if ( !isPowerOfTwo(size.value()) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Bank capacity must be");
    exceptionMsgThrown.append(" a power of two. Tried to set it to ");
    exceptionMsgThrown.append(to_string(size));
    exceptionMsgThrown.append(".");
    invalidate(&capacity);
    throw exceptionMsgThrown;
  }
  capacity = size;
}

bu::quantity<rrs::gibibit_unit> const &
Bank::getCapacity() const
{
  return this->capacity;
}

void
Bank::setNDataBusBits(bu::quantity<rrs::dimensionless> interface)
{
  if ( !isPowerOfTwo(interface) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Data bus width must be");
    exceptionMsgThrown.append(" a power of two. Tried to set it to ");
    exceptionMsgThrown.append(to_string((double)interface));
    exceptionMsgThrown.append(".");
    invalidate(&nDataBusBits);
    throw exceptionMsgThrown;
  }
  nDataBusBits = interface;
}

bu::quantity<rrs::dimensionless> const &
Bank::getNDataBusBits() const
{
  return this->nDataBusBits;
}

void
Bank::setPrefetch(bu::quantity<rrs::dimensionless> _prefetch)
{
  prefetch = _prefetch;
}

bu::quantity<rrs::dimensionless> const &
Bank::getPrefetch() const
{
  return this->prefetch;
}



void
Bank::updateNSubarrays()
{
  nActiveSubarraysPerAccess = nDataBusBits * prefetch;
  nSubarrays = SCALE_QUANTITY(capacity, rrs::bit_unit) / subarray.getCapacity();

  nSubarraysPerRow = nSubarrays;
  nSubarraysPerCol = 1.;
  auto effWidth = nSubarraysPerRow * subarray.getWidth();
  auto effHeight = nSubarraysPerCol * subarray.getHeight();
  while ( effWidth > effHeight * 1.005 // Only 0.5% difference is ok
          && nSubarraysPerRow > nActiveSubarraysPerAccess) {
    nSubarraysPerRow /= 2.;
    nSubarraysPerCol *= 2.;
    effWidth = nSubarraysPerRow * subarray.getWidth();
    effHeight = nSubarraysPerCol * subarray.getHeight();
  }
}

bu::quantity<rrs::dimensionless> const &
Bank::getNSubarrays() const
{
  return this->nSubarrays;
}

bu::quantity<rrs::dimensionless> const &
Bank::getNActiveSubarraysPerAccess() const
{
  return this->nActiveSubarraysPerAccess;
}

bu::quantity<rrs::dimensionless> const &
Bank::getNSubarraysPerRow() const
{
  return this->nSubarraysPerRow;
}

bu::quantity<rrs::dimensionless> const &
Bank::getNSubarraysPerCol() const
{
  return this->nSubarraysPerCol;
}


void
Bank::setMinAddressableBlock( bu::quantity<rrs::bit_unit> minBlock )
{
  if ( isInvalid(minAddressableBlock) ) {
    minAddressableBlock = nDataBusBits * rrs::bits; // Default
    return;
  }
  if ( !isPowerOfTwo(minAddressableBlock.value()) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Minimum addressable block length must be");
    exceptionMsgThrown.append(" a power of two. Tried to set it to ");
    exceptionMsgThrown.append(to_string(minAddressableBlock));
    exceptionMsgThrown.append(".");
    invalidate(&nDataBusBits);
    throw exceptionMsgThrown;
  }
  minAddressableBlock = minBlock;
}

bu::quantity<rrs::bit_unit> const &
Bank::getMinAddressableBlock() const
{
  return this->minAddressableBlock;
}


void
Bank::updatePageSize()
{
  pageSize = subarray.getNCols() * nActiveSubarraysPerAccess * rrs::bits;
}

bu::quantity<rrs::bit_unit> const&
Bank::getPageSize() const
{
  return this->pageSize;
}



void
Bank::updateNRowAddressLines()
{
//  nRowAddressLines = log2( SCALE_QUANTITY(capacity, rrs::bit_unit) / pageSize );
  nRowAddressLines = log2(subarray.getNRows() * nSubarraysPerCol);
}

bu::quantity<rrs::dimensionless> const&
Bank::getNRowAddressLines() const
{
  return this->nRowAddressLines;
}

void
Bank::updateNColAddressLines()
{
//  nColAddressLines = log2( pageSize / ( nDataBusBits * rrs::bits ) );
  nColAddressLines = log2(subarray.getNCols() * nSubarraysPerRow);
}

bu::quantity<rrs::dimensionless> const&
Bank::getNColAddressLines() const
{
  return this->nColAddressLines;
}



void
Bank::updateRowDecoderArea()
{
  rowDecoderArea = 0. * rrs::square_nanometers;
  auto nVccDecodedAddress = pow( 2., nRowAddressLines - nVppDecodedLvls );
  auto F2Vcc = tech.getTechnologyNode() * tech.getTechnologyNode();
  rowDecoderArea += nF2PerDecodedAddress * F2Vcc * nVccDecodedAddress;


  auto nVppDecodedAddress = pow( 2., nRowAddressLines );
  auto F2Vpp = tech.getMinPMOSChannelLength() * tech.getMinPMOSChannelWidth();
  F2Vpp += tech.getMinNMOSChannelLength() * tech.getMinNMOSChannelWidth();
  F2Vpp /= 2.;

  rowDecoderArea += nF2LevelTranslator * F2Vpp * nVccDecodedAddress;
  rowDecoderArea += nF2PerDecodedAddress * F2Vpp * nVppDecodedAddress;

  rowDecoderHeight = nSubarraysPerCol * subarray.getHeight();
  rowDecoderWidth = rowDecoderArea / rowDecoderHeight;

}

bu::quantity<rrs::square_nanometer_unit> const &
Bank::getRowDecoderArea() const
{
  return this->rowDecoderArea;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getRowDecoderWidth() const
{
  return this->rowDecoderWidth;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getRowDecoderHeight() const
{
  return this->rowDecoderHeight;
}


void
Bank::updateColDecoderArea()
{
  colDecoderArea = 0. * rrs::square_nanometers;
  auto nVccDecodedAddress = pow( 2., nColAddressLines - nVppDecodedLvls );
  auto F2Vcc = tech.getTechnologyNode() * tech.getTechnologyNode();
  colDecoderArea += nF2PerDecodedAddress * F2Vcc * nVccDecodedAddress;


  auto nVppDecodedAddress = pow( 2., nColAddressLines );
  auto F2Vpp = tech.getMinPMOSChannelLength() * tech.getMinPMOSChannelWidth();
  F2Vpp += tech.getMinNMOSChannelLength() * tech.getMinNMOSChannelWidth();
  F2Vpp /= 2.;

  colDecoderArea += nF2LevelTranslator * F2Vpp * nVccDecodedAddress;
  colDecoderArea += nF2PerDecodedAddress * F2Vpp * nVppDecodedAddress;

  colDecoderWidth = nSubarraysPerRow * subarray.getWidth();
  colDecoderHeight = colDecoderArea / colDecoderWidth;

}

bu::quantity<rrs::square_nanometer_unit> const &
Bank::getColDecoderArea() const
{
  return this->colDecoderArea;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getColDecoderWidth() const
{
  return this->colDecoderWidth;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getColDecoderHeight() const
{
  return this->colDecoderHeight;
}


void
Bank::updateArea()
{
  auto activeWidth = nSubarraysPerRow * subarray.getWidth();
  auto activeHeight = nSubarraysPerCol * subarray.getHeight();

  width = rowDecoderWidth + activeWidth;
  height = colDecoderHeight + activeHeight;
  area = width * height;
  areaEfficiency = subarray.getArea4F2() * nSubarrays / area;
}

bu::quantity<rrs::square_nanometer_unit> const &
Bank::getArea() const
{
  return this->area;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getHeight() const
{
  return this->height;
}

bu::quantity<rrs::nanometer_unit> const &
Bank::getWidth() const
{
  return this->width;
}

bu::quantity<rrs::dimensionless> const &
Bank::getAreaEfficiency() const
{
  return this->areaEfficiency;
}



void
Bank::updateRowDecoderDelay()
{
  rowDecoderDelay = decodingDelay;

  auto totalLineRes = tech.getMetalResistancePerLength()
      * width * globalWireResistanceMultiplier;
  auto totalLineCap = tech.getMetalCapacitancePerLength()
      * width * globalWireCapacitanceMultiplier;
  rowDecoderDelay += tausToPercentLumpedRC(90) * totalLineRes
      * SCALE_QUANTITY(totalLineCap, rrs::nanofarad_unit);
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getRowDecoderDelay() const
{
  return this->rowDecoderDelay;
}

void
Bank::updateColDecoderDelay()
{
  colDecoderDelay = decodingDelay;

  auto totalLineRes = tech.getMetalResistancePerLength()
      * height * globalWireResistanceMultiplier;
  auto totalLineCap = tech.getMetalCapacitancePerLength()
      * height * globalWireCapacitanceMultiplier;
  colDecoderDelay += tausToPercentLumpedRC(90) * totalLineRes
      * SCALE_QUANTITY(totalLineCap, rrs::nanofarad_unit);
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getColDecoderDelay() const
{
  return this->colDecoderDelay;
}

void
Bank::updateGlobalBusDelay()
{
  auto totalLineRes = tech.getMetalResistancePerLength()
      * max(width, height) * globalWireResistanceMultiplier;
  auto totalLineCap = tech.getMetalCapacitancePerLength()
      * max(width, height) * globalWireCapacitanceMultiplier;

  globalBusDelay = tausToPercentLumpedRC(63) * totalLineRes
      * SCALE_QUANTITY(totalLineCap, rrs::nanofarad_unit);
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getGlobalBusDelay() const
{
  return this->globalBusDelay;
}


void
Bank::updatePrechargeTime()
{
  prechargeTime = globalBusDelay;
  prechargeTime += rowDecoderDelay;
  prechargeTime += subarray.getPrechargeTime();
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getPrechargeTime() const
{
  return this->prechargeTime;
}

void
Bank::updateWriteTime()
{
  writeTime = globalBusDelay;
  writeTime += max(rowDecoderDelay, colDecoderDelay);
  writeTime += subarray.getWriteTime();
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getWriteTime() const
{
  return this->writeTime;
}

void
Bank::updateReadTime()
{
  readTime = globalBusDelay;
  readTime += max(rowDecoderDelay, colDecoderDelay);
  readTime += subarray.getReadTime();
  readTime += globalBusDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getReadTime() const
{
  return this->readTime;
}

void
Bank::updateTpd()
{
  tpd = globalBusDelay;
  tpd += rowDecoderDelay;
  tpd += subarray.getPrechargeTime();
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getTpd() const
{
  return this->tpd;
}

void
Bank::updateTccdr()
{
  tccdr = subarray.getReadTime();
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getTccdr() const
{
  return this->tccdr;
}

void
Bank::updateTccdw()
{
  tccdw = subarray.getWriteTime();
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getTccdw() const
{
  return this->tccdw;
}

void
Bank::updateTrl()
{
  trl = globalBusDelay;
  trl += max(rowDecoderDelay, colDecoderDelay);
  trl += tccdr;
  trl += globalBusDelay;
}
bu::quantity<rrs::nanosecond_unit> const &
Bank::getTrl() const
{
  return this->trl;
}

void
Bank::updateTwl()
{
  twl = globalBusDelay;
  twl += max(rowDecoderDelay, colDecoderDelay);
  twl += globalBusDelay;
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getTwl() const
{
  return this->twl;
}

void
Bank::updateLeakagePower()
{
  auto leakagePowerPerTranslator = leakagePerVoltageTranslator
      * tech.getBreakdownVoltage();
  auto nVccDecodedAddress = pow( 2., nRowAddressLines - nVppDecodedLvls );
  nVccDecodedAddress += pow( 2., nColAddressLines - nVppDecodedLvls );
  leakagePower = leakagePowerPerTranslator * nVccDecodedAddress;
}

bu::quantity<rrs::nanowatt_unit> const &
Bank::getLeakagePower() const
{
  return this->leakagePower;
}



void
Bank::updateInterfaceBusEnergy()
{
  auto totalGlobalLineCap = tech.getMetalCapacitancePerLength()
      * (width + height)/2. * globalWireCapacitanceMultiplier;

  interfaceBusEnergy = tech.getVcc() * tech.getVcc()
      * SCALE_QUANTITY(totalGlobalLineCap, rrs::picofarad_unit);
  interfaceBusEnergy *= nCommandLines + nDataBusBits
                        + nRowAddressLines + nColAddressLines;
}

bu::quantity<rrs::picojoule_unit> const &
Bank::getInterfaceBusEnergy() const
{
  return this->interfaceBusEnergy;
}


void
Bank::updatePrechargeEnergy()
{
  prechargeEnergy = nActiveSubarraysPerAccess * subarray.getPrechargeEnergy();
  prechargeEnergy += interfaceBusEnergy;
}

bu::quantity<rrs::picojoule_unit> const &
Bank::getPrechargeEnergy() const
{
  return this->prechargeEnergy;
}

void
Bank::updateWriteEnergy()
{
  writeEnergy = nActiveSubarraysPerAccess * subarray.getWriteEnergy();
  writeEnergy += interfaceBusEnergy;
}

bu::quantity<rrs::picojoule_unit> const &
Bank::getWriteEnergy() const
{
  return this->writeEnergy;
}

void
Bank::updateReadEnergy()
{
  readEnergy = nActiveSubarraysPerAccess * subarray.getReadEnergy();
  readEnergy += interfaceBusEnergy;
}

bu::quantity<rrs::picojoule_unit> const &
Bank::getReadEnergy() const
{
  return this->readEnergy;
}


bu::quantity<rrs::picojoule_unit> const &
Bank::getBestWriteEnergy() const
{
  return this->bestWriteEnergy;
}

bu::quantity<rrs::nanosecond_unit> const &
Bank::getBestWriteTime() const
{
  return this->bestWriteTime;
}




void
Bank::updateAll()
{
try {
  updateNSubarrays();

  updatePageSize();
  updateNRowAddressLines();
  updateNColAddressLines();

  updateRowDecoderArea();
  updateColDecoderArea();
  updateArea();

  updateRowDecoderDelay();
  updateColDecoderDelay();
  updateGlobalBusDelay();
  updatePrechargeTime();
  updateWriteTime();
  updateReadTime();

  updateTpd();
  updateTccdr();
  updateTccdw();
  updateTrl();
  updateTwl();

  updateLeakagePower();

  updateInterfaceBusEnergy();
  updatePrechargeEnergy();
  updateWriteEnergy();
  updateReadEnergy();

//  cout << endl << endl << "Solution:" << endl;
//  PRINT_VAR(subarray.getNRows());
//  PRINT_VAR(subarray.getNCols());
//  PRINT_VAR(subarray.getArea());
//  PRINT_VAR(subarray.getWidth());
//  PRINT_VAR(subarray.getHeight());
//  PRINT_VAR(subarray.getAreaEfficiency());
//  PRINT_VAR(subarray.getWLWriteDriverResistance());

//  PRINT_VAR(subarray.getPrechargeTime());
//  PRINT_VAR(subarray.selectedCell.getCellSetVoltage());
//  PRINT_VAR(subarray.selectedCell.getCellResetVoltage());
//  PRINT_VAR(subarray.getWriteVoltage());
//  PRINT_VAR(subarray.getReadVoltage());
//  PRINT_VAR(subarray.getWriteTime());
//  PRINT_VAR(subarray.getReadTime());

//  PRINT_VAR(subarray.getPrechargeEnergy());
//  PRINT_VAR(subarray.getWriteEnergy());
//  PRINT_VAR(subarray.getReadEnergy());

//  cout << endl;
//  PRINT_VAR(getNSubarrays());
//  PRINT_VAR(getNActiveSubarraysPerAccess());
//  PRINT_VAR(getNSubarraysPerRow());
//  PRINT_VAR(getNSubarraysPerCol());

//  PRINT_VAR(getMinAddressableBlock());
//  PRINT_VAR(getPageSize());
//  PRINT_VAR(getNRowAddressLines());
//  PRINT_VAR(getNColAddressLines());

//  PRINT_VAR(getRowDecoderWidth());
//  PRINT_VAR(getRowDecoderHeight());
//  PRINT_VAR(getRowDecoderArea());
//  PRINT_VAR(getColDecoderWidth());
//  PRINT_VAR(getColDecoderHeight());
//  PRINT_VAR(getColDecoderArea());

//  PRINT_VAR(getArea());
//  PRINT_VAR(getWidth());
//  PRINT_VAR(getHeight());
//  PRINT_VAR(getAreaEfficiency());

//  PRINT_VAR(getRowDecoderDelay());
//  PRINT_VAR(getColDecoderDelay());
//  PRINT_VAR(getGlobalBusDelay());

//  PRINT_VAR(getPrechargeTime());
//  PRINT_VAR(getWriteTime());
//  PRINT_VAR(getReadTime());

//  PRINT_VAR(getLeakagePower());

//  PRINT_VAR(getInterfaceBusEnergy());
//  PRINT_VAR(getPrechargeEnergy());
//  PRINT_VAR(getWriteEnergy());
//  PRINT_VAR(getReadEnergy());



} catch(string exceptionMsgThrown) {
  throw exceptionMsgThrown;
}
}


void
Bank::buildFromConfigFiles(const Config& config)
{
try {

  // Build subarray
  subarray = XPointArray(config);

  // Get technology values
  tech = Technology(techFileName);

  // Get general values for the bank
  JsonAssist jsonArch(archFileName);

  double magnitude = INVALID_DOUBLE;

  // Optimization mode
  string optModeStr = jsonArch.getJSONString(
        "Optimization mode []", mandatory);
  setOptMode( optModeStr );

  magnitude = jsonArch.getJSONNumber(
        "Bank capacity [Gb]", mandatory);
  setCapacity( magnitude * rrs::gibibits );

  magnitude = jsonArch.getJSONNumber(
        "Data bus width [bits]", mandatory);
  setNDataBusBits( magnitude );

  magnitude = jsonArch.getJSONNumber(
        "Prefetch []", mandatory);
  setPrefetch( magnitude );

  magnitude = jsonArch.getJSONNumber(
        "Minimum addressable block [bits]", optional);
  setMinAddressableBlock( magnitude * rrs::bits );

  magnitude = jsonArch.getJSONNumber(
        "Crosspoint array area [nm^2]", optional);
  subarray.setArea( magnitude * rrs::square_nanometers );

  magnitude = jsonArch.getJSONNumber(
        "Number of array columns []", optional);
  subarray.setNCols( magnitude );

  magnitude = jsonArch.getJSONNumber(
        "Number of array rows []", optional);
  subarray.setNRows( magnitude );

} catch(string exceptionMsgThrown) {
  throw exceptionMsgThrown;
}


}


void
Bank::runFixedMode()
{
  subarray.updateXPointArray();
  updateAll();
}


void
Bank::runOptimizationMode()
{
  // Run optimization
  auto bestNRows = subarray.getNRows();
  auto bestNCols = subarray.getNCols();

  auto nRows = 2;
  auto nCols = 2;
  //TODO proper while
  bool tic = false;
  while ( nRows <= 8192 && nCols <= 8192 ) {
    subarray.setNRows(nRows);
    subarray.setNCols(nCols);

    subarray.updateXPointArray();
    updateAll();

    if ( isBetterSolution() ) {
      bestNCols = nCols;
      bestNRows = nRows;
    }

//   PRINT_VAR(writeEnergy);
//    PRINT_VAR(readEnergy);
//    PRINT_VAR(subarray.getReadEnergy());

    if ( tic ) {
      nCols *= 2;
      tic = !tic;
    } else {
      nRows *= 2;
      tic = !tic;
    }
  }

  // Get best size values
  cout<<"-----------------------------------" <<"\n";
  cout<<"********* Best Solution************" <<"\n";
  cout<<"-----------------------------------" <<"\n";
  subarray.setNRows(bestNRows);
  subarray.setNCols(bestNCols);
  subarray.updateXPointArray();
  updateAll();

}

ebool
Bank::isBetterSolution()
{
  ebool returnVal = INVALID_EBOOL;
  if ( !areEqual(subarray.getAreaEfficiency(), 1.) ) {
    return false;
  }
  switch (optMode) {
    case performance:
      if ( isValid(bestWriteTime)) {
        if ( tccdw < bestWriteTime ) {
          bestWriteTime = tccdw;
          returnVal = true;
        } else {
          returnVal = false;
        }
      } else {
        bestWriteTime = tccdw;
        returnVal = true;
      }
      break;
    case energy:
      if ( isValid(bestWriteEnergy) ) {
        if ( writeEnergy < bestWriteEnergy ) {
          bestWriteEnergy = writeEnergy;
          returnVal = true;
        } else {
          returnVal = false;
        }
      } else {
        bestWriteEnergy = writeEnergy;
        returnVal = true;
      }
      break;
    // Invalid optmization modes
    case fixed: break;
    case density: break;
    case INVALID_OPT_MODE: break;
  }

  if ( isInvalid(returnVal) ) {
    string exceptionMsgThrown("[ERROR] ");
    exceptionMsgThrown.append("Unexpected behaviour - ");
    exceptionMsgThrown.append("Tried to evaluate the solution");
    exceptionMsgThrown.append(" but the optmization mode was invalid.");
    throw exceptionMsgThrown;
  }

  return returnVal;
}


Bank::Bank()
{
  initialize();
}

Bank::Bank(const Config& config)
{
  try {
    initialize();

    // Configuration file names as C-like strings
    cellFileName = config.cellFileName.c_str();
    techFileName = config.techFileName.c_str();
    archFileName = config.archFileName.c_str();

    buildFromConfigFiles(config);

    switch (optMode) {
      case fixed:             runFixedMode();         break;
      case energy:            runOptimizationMode();  break;
      case performance:       runOptimizationMode();  break;
      case density:           runOptimizationMode();  break;
      case INVALID_OPT_MODE:
        string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Unexpected behaviour - ");
        exceptionMsgThrown.append("Tried to use optimization mode,");
        exceptionMsgThrown.append(" but its value is invalid.");
        throw exceptionMsgThrown;
        break;
    }

  } catch(string exceptionMsgThrown) {
    throw exceptionMsgThrown;
  }

}

Bank::~Bank()
{

}







