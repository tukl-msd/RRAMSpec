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


#ifndef BANK_H
#define BANK_H

#include "../utils/constants.h"
#include "../utils/functions.h"

#include "../parser/ArgumentsParser.h"
#include "../parser/JsonAssist.h"

#include "../core/XPointArray.h"

#include "../expandedBoostUnits/Units/rramSpec_units.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

class Bank
{

private:

  enum optimizationModes { fixed, density, performance, energy,
                           INVALID_OPT_MODE };
  optimizationModes optMode;

  bu::quantity<rrs::gibibit_unit> capacity;
  bu::quantity<rrs::dimensionless> nDataBusBits;
  bu::quantity<rrs::dimensionless> prefetch;

  bu::quantity<rrs::dimensionless> nSubarrays;
  bu::quantity<rrs::dimensionless> nActiveSubarraysPerAccess;
  bu::quantity<rrs::dimensionless> nSubarraysPerRow;
  bu::quantity<rrs::dimensionless> nSubarraysPerCol;

  bu::quantity<rrs::bit_unit> minAddressableBlock;
  bu::quantity<rrs::bit_unit> pageSize;
  bu::quantity<rrs::dimensionless> nRowAddressLines;
  bu::quantity<rrs::dimensionless> nColAddressLines;


  // Mechanical parameters
  bu::quantity<rrs::nanometer_unit> rowDecoderWidth;
  bu::quantity<rrs::nanometer_unit> rowDecoderHeight;
  bu::quantity<rrs::square_nanometer_unit> rowDecoderArea;
  bu::quantity<rrs::nanometer_unit> colDecoderWidth;
  bu::quantity<rrs::nanometer_unit> colDecoderHeight;
  bu::quantity<rrs::square_nanometer_unit> colDecoderArea;

  bu::quantity<rrs::square_nanometer_unit> area;
  bu::quantity<rrs::nanometer_unit> height;
  bu::quantity<rrs::nanometer_unit> width;
  bu::quantity<rrs::dimensionless> areaEfficiency;


  // Timing results
  bu::quantity<rrs::nanosecond_unit> rowDecoderDelay;
  bu::quantity<rrs::nanosecond_unit> colDecoderDelay;

  bu::quantity<rrs::nanosecond_unit> globalBusDelay;

  bu::quantity<rrs::nanosecond_unit> prechargeTime;
  bu::quantity<rrs::nanosecond_unit> writeTime;
  bu::quantity<rrs::nanosecond_unit> readTime;

  bu::quantity<rrs::nanosecond_unit> tpd;
  bu::quantity<rrs::nanosecond_unit> tccdr;
  bu::quantity<rrs::nanosecond_unit> tccdw;
  bu::quantity<rrs::nanosecond_unit> trl;
  bu::quantity<rrs::nanosecond_unit> twl;

  // Power results
  bu::quantity<rrs::nanowatt_unit> leakagePower;

  // Energy results
  bu::quantity<rrs::picojoule_unit> interfaceBusEnergy;
  bu::quantity<rrs::picojoule_unit> prechargeEnergy;
  bu::quantity<rrs::picojoule_unit> writeEnergy;
  bu::quantity<rrs::picojoule_unit> readEnergy;

  // Best values for different opt modes
  bu::quantity<rrs::picojoule_unit> bestWriteEnergy;
  bu::quantity<rrs::nanosecond_unit> bestWriteTime;

  // Configuration files
  const char* cellFileName;
  const char* techFileName;
  const char* archFileName;

  // Private methods
  void initialize();
  void buildFromConfigFiles(const Config&);

  // Optimization functions
  void runFixedMode();
  void runOptimizationMode();

  // Evaluates if the current solution is a better solution
  ebool isBetterSolution();

  // Constants
  bu::quantity<rrs::dimensionless> nCommandLines = 2;

  bu::quantity<rrs::dimensionless> nVppDecodedLvls = 4;

  // TODO: Temporary variables that could be estimated
  bu::quantity<rrs::nanoampere_unit> leakagePerVoltageTranslator
                                      = 50 * rrs::nanoamperes;

  bu::quantity<rrs::dimensionless> nF2PerDecodedAddress = 100;

  bu::quantity<rrs::dimensionless> nF2LevelTranslator = 1000;

  bu::quantity<rrs::dimensionless> globalWireResistanceMultiplier = 0.1;
  bu::quantity<rrs::dimensionless> globalWireCapacitanceMultiplier = 2;

  bu::quantity<rrs::nanosecond_unit> decodingDelay = 5 * rrs::nanoseconds;


public:
  Bank();
  Bank(const Config& config);
  ~Bank();

  XPointArray subarray;

  Technology tech;

  void setOptMode( string );
  string getOptMode();


  void setCapacity(bu::quantity<rrs::gibibit_unit>);
  bu::quantity<rrs::gibibit_unit> const &getCapacity() const;
  void setNDataBusBits(bu::quantity<rrs::dimensionless>);
  bu::quantity<rrs::dimensionless> const &getNDataBusBits() const;
  void setPrefetch(bu::quantity<rrs::dimensionless>);
  bu::quantity<rrs::dimensionless> const &getPrefetch() const;

  void updateNSubarrays();
  bu::quantity<rrs::dimensionless> const &getNSubarrays() const;
  bu::quantity<rrs::dimensionless> const &getNActiveSubarraysPerAccess() const;
  bu::quantity<rrs::dimensionless> const &getNSubarraysPerRow() const;
  bu::quantity<rrs::dimensionless> const &getNSubarraysPerCol() const;

  void setMinAddressableBlock( bu::quantity<rrs::bit_unit>);
  bu::quantity<rrs::bit_unit> const &getMinAddressableBlock() const;
  void updatePageSize();
  bu::quantity<rrs::bit_unit> const &getPageSize() const;
  void updateNRowAddressLines();
  bu::quantity<rrs::dimensionless> const &getNRowAddressLines() const;
  void updateNColAddressLines();
  bu::quantity<rrs::dimensionless> const &getNColAddressLines() const;


  void updateRowDecoderArea();
  bu::quantity<rrs::square_nanometer_unit> const &getRowDecoderArea() const;
  bu::quantity<rrs::nanometer_unit> const &getRowDecoderWidth() const;
  bu::quantity<rrs::nanometer_unit> const &getRowDecoderHeight() const;

  void updateColDecoderArea();
  bu::quantity<rrs::square_nanometer_unit> const &getColDecoderArea() const;
  bu::quantity<rrs::nanometer_unit> const &getColDecoderWidth() const;
  bu::quantity<rrs::nanometer_unit> const &getColDecoderHeight() const;

  void updateArea();
  bu::quantity<rrs::square_nanometer_unit> const &getArea() const;
  bu::quantity<rrs::nanometer_unit> const &getHeight() const;
  bu::quantity<rrs::nanometer_unit> const &getWidth() const;
  bu::quantity<rrs::dimensionless> const &getAreaEfficiency() const;


  void updateRowDecoderDelay();
  bu::quantity<rrs::nanosecond_unit> const &getRowDecoderDelay() const;
  void updateColDecoderDelay();
  bu::quantity<rrs::nanosecond_unit> const &getColDecoderDelay() const;
  void updateGlobalBusDelay();
  bu::quantity<rrs::nanosecond_unit> const &getGlobalBusDelay() const;

  void updatePrechargeTime();
  bu::quantity<rrs::nanosecond_unit> const &getPrechargeTime() const;
  void updateWriteTime();
  bu::quantity<rrs::nanosecond_unit> const &getWriteTime() const;
  void updateReadTime();
  bu::quantity<rrs::nanosecond_unit> const &getReadTime() const;

  void updateTpd();
  bu::quantity<rrs::nanosecond_unit> const &getTpd() const;
  void updateTccdr();
  bu::quantity<rrs::nanosecond_unit> const &getTccdr() const;
  void updateTccdw();
  bu::quantity<rrs::nanosecond_unit> const &getTccdw() const;
  void updateTrl();
  bu::quantity<rrs::nanosecond_unit> const &getTrl() const;
  void updateTwl();
  bu::quantity<rrs::nanosecond_unit> const &getTwl() const;


  void updateLeakagePower();
  bu::quantity<rrs::nanowatt_unit> const &getLeakagePower() const;


  void updateInterfaceBusEnergy();
  bu::quantity<rrs::picojoule_unit> const &getInterfaceBusEnergy() const;

  void updatePrechargeEnergy();
  bu::quantity<rrs::picojoule_unit> const &getPrechargeEnergy() const;
  void updateWriteEnergy();
  bu::quantity<rrs::picojoule_unit> const &getWriteEnergy() const;
  void updateReadEnergy();
  bu::quantity<rrs::picojoule_unit> const &getReadEnergy() const;

  void updateAll();

  // Best values for different opt modes
  bu::quantity<rrs::picojoule_unit> const &getBestWriteEnergy() const;
  bu::quantity<rrs::nanosecond_unit> const &getBestWriteTime() const;


};
#endif //BANK_H
