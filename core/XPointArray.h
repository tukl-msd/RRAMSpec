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


#ifndef XPOINTARRAY_H
#define XPOINTARRAY_H

#include "../utils/constants.h"
#include "../utils/functions.h"

#include "../parser/ArgumentsParser.h"
#include "../parser/JsonAssist.h"

#include "../core/Cell.h"
#include "../core/Technology.h"

#include "../expandedBoostUnits/Units/rramSpec_units.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

class XPointArray
{

private:
  // Configuration files
  const char* cellFileName;
  const char* techFileName;
  const char* archFileName;

  // Mechanical parameters
  // This is one expection where width is in the direction of the bitline
  bu::quantity<rrs::nanometer_unit> WLMetalWidth;
  bu::quantity<rrs::nanometer_unit> BLMetalWidth;

  bu::quantity<rrs::nanometer_unit> heightwiseCellPitch;
  bu::quantity<rrs::nanometer_unit> widthwiseCellPitch;
  bu::quantity<rrs::square_nanometer_unit> area4F2;

  bu::quantity<rrs::square_nanometer_unit> area;
  bu::quantity<rrs::nanometer_unit> height;
  bu::quantity<rrs::nanometer_unit> width;
  bu::quantity<rrs::dimensionless> areaEfficiency;

  // Numerical parameters
  bu::quantity<rrs::dimensionless> nCols;
  bu::quantity<rrs::dimensionless> nRows;

  bu::quantity<rrs::bit_unit> capacity;

  // Electrical parameters
  bu::quantity<rrs::ohm_unit> WLResistancePerCell;
  bu::quantity<rrs::ohm_unit> BLResistancePerCell;
  bu::quantity<rrs::attofarad_unit> WLCapacitancePerCell;
  bu::quantity<rrs::attofarad_unit> BLCapacitancePerCell;

  bu::quantity<rrs::ohm_per_nanometer_unit> WLResistancePerLength;
  bu::quantity<rrs::ohm_per_nanometer_unit> BLResistancePerLength;
  bu::quantity<rrs::nanofarad_per_meter_unit> WLCapacitancePerLength;
  bu::quantity<rrs::nanofarad_per_meter_unit> BLCapacitancePerLength;

  bu::quantity<rrs::ohm_unit> WLWriteDriverResistance;
  bu::quantity<rrs::ohm_unit> BLWriteDriverResistance;

  bu::quantity<rrs::ohm_unit> WLReadDriverResistance;
  bu::quantity<rrs::ohm_unit> BLReadDriverResistance;

  bu::quantity<rrs::ohm_unit> halfBiasDriverResistance;

  bu::quantity<rrs::volt_unit> writeVoltage;
  bu::quantity<rrs::volt_unit> readVoltage;


  // Variables used by iterative methods
  // PL is the selected line where the positive voltage is applied
  // while NL is the selected line that is grounded (or lower voltage)
  bu::quantity<rrs::volt_unit> VP;
  bu::quantity<rrs::volt_unit> VN;

  bu::quantity<rrs::dimensionless> nPLSegs;
  bu::quantity<rrs::dimensionless> nNLSegs;

  vector<bu::quantity<rrs::volt_unit>> vPLSegs;
  vector<bu::quantity<rrs::nanoampere_unit>> iPLCells;
  vector<bu::quantity<rrs::volt_unit>> vNLSegs;
  vector<bu::quantity<rrs::nanoampere_unit>> iNLCells;

  ebool selectedCellState;
  ebool PHSCState; // Half Selected Cell in PL state
  ebool NHSCState; // Half Selected Cell in NL state

  bu::quantity<rrs::ohm_unit> PAMUXResistance;
  bu::quantity<rrs::ohm_unit> NAMUXResistance;
  bu::quantity<rrs::ohm_unit> PLResistancePerCell;
  bu::quantity<rrs::ohm_unit> NLResistancePerCell;
  vector<bu::quantity<rrs::ohm_unit>> accRPL;
  vector<bu::quantity<rrs::ohm_unit>> accRNL;

  // Timing results
  bu::quantity<rrs::nanosecond_unit> adjWLDelay;
  bu::quantity<rrs::nanosecond_unit> adjBLDelay;
  bu::quantity<rrs::nanosecond_unit> adjLineMaxDelay;

  bu::quantity<rrs::nanosecond_unit> WLDelay;
  bu::quantity<rrs::nanosecond_unit> BLDelay;
  bu::quantity<rrs::nanosecond_unit> lineMaxDelay;

  bu::quantity<rrs::nanosecond_unit> prechargeTime;
  bu::quantity<rrs::nanosecond_unit> calibrationDelay;
  bu::quantity<rrs::nanosecond_unit> setTime;
  bu::quantity<rrs::nanosecond_unit> resetTime;
  bu::quantity<rrs::nanosecond_unit> writeTime;
  bu::quantity<rrs::nanosecond_unit> readTime;


  // Current results
  bu::quantity<rrs::nanoampere_unit> prechargeCurrent;

  bu::quantity<rrs::nanoampere_unit> setSCCurrent;
  bu::quantity<rrs::nanoampere_unit> setSPCurrent;
  bu::quantity<rrs::nanoampere_unit> setCurrent;
  bu::quantity<rrs::nanoampere_unit> resetSCCurrent;
  bu::quantity<rrs::nanoampere_unit> resetSPCurrent;
  bu::quantity<rrs::nanoampere_unit> resetCurrent;
  bu::quantity<rrs::nanoampere_unit> writeCurrent;

  bu::quantity<rrs::nanoampere_unit> readHRSSPCurrent;
  bu::quantity<rrs::nanoampere_unit> readHRSSCCurrent;
  bu::quantity<rrs::nanoampere_unit> readLRSSPCurrent;
  bu::quantity<rrs::nanoampere_unit> readLRSSCCurrent;
  bu::quantity<rrs::nanoampere_unit> readCurrent;

  // Energy results
  bu::quantity<rrs::picojoule_unit> prechargeEnergy;
  bu::quantity<rrs::picojoule_unit> writeEnergy;
  bu::quantity<rrs::picojoule_unit> readEnergy;

  // Best values for different opt modes
  bu::quantity<rrs::picojoule_unit> bestWriteEnergy;
  bu::quantity<rrs::nanosecond_unit> bestWriteTime;

  // Private methods
  void initialize();
  void buildFromConfigFiles();

  void updateWLResistancePerLength();
  void updateBLResistancePerLength();
  void updateWLCapacitancePerLength();
  void updateBLCapacitancePerLength();

  void updateWLResistancePerCell();
  void updateBLResistancePerCell();
  void updateWLCapacitancePerCell();
  void updateBLCapacitancePerCell();

  // Calcutate the needed driver supply voltage
  //  given the write voltage at the selected cell
  // vHalf is half of vP
  bu::quantity<rrs::volt_unit> calcVEdge(bu::quantity<rrs::volt_unit>,
                                         rramOperations);
  // vHalf is fixed
  bu::quantity<rrs::volt_unit> calcVEdge(bu::quantity<rrs::volt_unit>,
                                         bu::quantity<rrs::volt_unit>,
                                         rramOperations);

  // Calculate the resulting voltage at selected cell
  //  given the driver supply voltage
  // vHalf is half of vP
  bu::quantity<rrs::volt_unit> calcVSelectedCell(bu::quantity<rrs::volt_unit>,
                                         rramOperations);
  // vHalf is fixed
  bu::quantity<rrs::volt_unit> calcVSelectedCell(bu::quantity<rrs::volt_unit>,
                                                 bu::quantity<rrs::volt_unit>,
                                                 rramOperations);

  bu::quantity<rrs::ohm_unit> calcDriverResistance(rramOperations op = any_op);

  void initializeIterativeVariables(rramOperations op);

  bu::quantity<rrs::volt_unit> findBestVRead();

  // TODO: Temporary variables that could be estimated
  bu::quantity<rrs::ohm_unit> LDOResistance = 100 * rrs::ohms;
  bu::quantity<rrs::nanosecond_unit> currentSensingDelay = 4 * rrs::nanoseconds;

public:
  XPointArray();
  XPointArray(const Config& config);
  ~XPointArray();

  // Cell objects
  // Three cells are considered, based on its positions in the array
  //  They are modeled with (possibly)
  //    different resistances in series with the selector:
  //  1. Selected cell: uses exact numbers provided in cell file (pure cell)
  //  2. Half select cell on WL: has the BL complete resistance, as well as
  //    its (BL) driver resistance, added to original memory device resistance
  //  2. Half select cell on BL: has the WL complete resistance, as well as
  //    its (WL) driver resistance, added to original memory device resistance
  Cell selectedCell;
  Cell HSCellPL;
  Cell HSCellNL;

  // Technology object
  //  Used to derive higher level parameters, such as drivers resistances
  Technology tech;


  // Update XPointArray values
  void updateXPointArray();

  // Set/Get number of word- and bitlines (array size)
  // Number of columns translates to the number of cells per wordline
  // Number of rows translates to the number of cells per bitline
  void setNCols(bu::quantity<rrs::dimensionless>,
                settingOptions setOpt = normal_opt);
  void updateNCols();
  bu::quantity<rrs::dimensionless> const &getNCols() const;
  void setNRows(bu::quantity<rrs::dimensionless>,
                settingOptions setOpt = normal_opt);
  void updateNRows();
  bu::quantity<rrs::dimensionless> const &getNRows() const;
  void updateNRowsAndNCols();

  void updateCapacity();
  bu::quantity<rrs::bit_unit> const &getCapacity() const;

  // Widths of the lines
  void setWLMetalWidth(bu::quantity<rrs::nanometer_unit>,
                       settingOptions setOpt = normal_opt);
  void updateWLMetalWidth();
  bu::quantity<rrs::nanometer_unit> const &getWLMetalWidth() const;
  void setBLMetalWidth(bu::quantity<rrs::nanometer_unit>,
                       settingOptions setOpt = normal_opt);
  void updateBLMetalWidth();
  bu::quantity<rrs::nanometer_unit> const &getBLMetalWidth() const;

  // Mechanical parameters
  void updateHeightwiseCellPitch();
  bu::quantity<rrs::nanometer_unit> const &getHeightwiseCellPitch() const;
  void updateWidthwiseCellPitch();
  bu::quantity<rrs::nanometer_unit> const &getWidthwiseCellPitch() const;
  void updateArea4F2();
  bu::quantity<rrs::square_nanometer_unit> const &getArea4F2() const;

  void setArea(bu::quantity<rrs::square_nanometer_unit>,
                         settingOptions setOpt = normal_opt);
  void updateArea();
  bu::quantity<rrs::square_nanometer_unit> const &getArea() const;
  bu::quantity<rrs::nanometer_unit> const &getHeight() const;
  bu::quantity<rrs::nanometer_unit> const &getWidth() const;
  bu::quantity<rrs::dimensionless> const &getAreaEfficiency() const;

  void updateLinesElectricalParameters();
  // Line resistance and capacitance per segment, i.e., per length
  bu::quantity<rrs::ohm_per_nanometer_unit>
    const &getWLResistancePerLength() const;
  bu::quantity<rrs::ohm_per_nanometer_unit>
    const &getBLResistancePerLength() const;
  bu::quantity<rrs::nanofarad_per_meter_unit>
    const &getWLCapacitancePerLength() const;
  bu::quantity<rrs::nanofarad_per_meter_unit>
    const &getBLCapacitancePerLength() const;

  // Line resistance and capacitance per segment, i.e., per cell
  bu::quantity<rrs::ohm_unit> const &getWLResistancePerCell() const;
  bu::quantity<rrs::ohm_unit> const &getBLResistancePerCell() const;
  bu::quantity<rrs::attofarad_unit> const &getWLCapacitancePerCell() const;
  bu::quantity<rrs::attofarad_unit> const &getBLCapacitancePerCell() const;

  // Driver resistances
  void updateWLWriteDriverResistance();
  bu::quantity<rrs::ohm_unit> const &getWLWriteDriverResistance() const;
  void updateBLWriteDriverResistance();
  bu::quantity<rrs::ohm_unit> const &getBLWriteDriverResistance() const;

  void updateWLReadDriverResistance();
  bu::quantity<rrs::ohm_unit> const &getWLReadDriverResistance() const;
  void updateBLReadDriverResistance();
  bu::quantity<rrs::ohm_unit> const &getBLReadDriverResistance() const;

  void updateHalfBiasDriverResistance();
  bu::quantity<rrs::ohm_unit> const &getHalfBiasDriverResistance() const;

  // Voltages
  bu::quantity<rrs::volt_unit> const &getReadVoltage() const;
  bu::quantity<rrs::volt_unit> const &getWriteVoltage() const;

  // Intermidiate steps timing results
  void updateAdjLineDelays();
  bu::quantity<rrs::nanosecond_unit> const &getAdjLineMaxDelay() const;
  bu::quantity<rrs::nanosecond_unit> const &getAdjWLDelay() const;
  bu::quantity<rrs::nanosecond_unit> const &getAdjBLDelay() const;
  void updateLineDelays();
  bu::quantity<rrs::nanosecond_unit> const &getLineMaxDelay() const;
  bu::quantity<rrs::nanosecond_unit> const &getWLDelay() const;
  bu::quantity<rrs::nanosecond_unit> const &getBLDelay() const;
  void updateCalibrationDelay();
  bu::quantity<rrs::nanosecond_unit> const &getCalibrationDelay() const;

  // Complete internal timing results
  void updatePrechargeTime();
  bu::quantity<rrs::nanosecond_unit> const &getPrechargeTime() const;
  void updateWriteTime();
  bu::quantity<rrs::nanosecond_unit> const &getWriteTime() const;
  bu::quantity<rrs::nanosecond_unit> const &getSetTime() const;
  bu::quantity<rrs::nanosecond_unit> const &getResetTime() const;
  void updateReadTime();
  bu::quantity<rrs::nanosecond_unit> const &getReadTime() const;

  // Intermediate power results
  bu::quantity<rrs::nanoampere_unit> const &getSetSCCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getSetSPCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getSetCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getResetSCCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getResetSPCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getResetCurrent() const;

  bu::quantity<rrs::nanoampere_unit> const &getReadHRSSCCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getReadHRSSPCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getReadLRSSCCurrent() const;
  bu::quantity<rrs::nanoampere_unit> const &getReadLRSSPCurrent() const;

  // Complete internal current results
  void updatePrechargeCurrent();
  bu::quantity<rrs::nanoampere_unit> const &getPrechargeCurrent() const;
  void updateWriteCurrent();
  bu::quantity<rrs::nanoampere_unit> const &getWriteCurrent() const;
  void updateReadCurrent();
  bu::quantity<rrs::nanoampere_unit> const &getReadCurrent() const;

  // Complete internal energy results
  void updatePrechargeEnergy();
  bu::quantity<rrs::picojoule_unit> const &getPrechargeEnergy() const;
  void updateWriteEnergy();
  bu::quantity<rrs::picojoule_unit> const &getWriteEnergy() const;
  void updateReadEnergy();
  bu::quantity<rrs::picojoule_unit> const &getReadEnergy() const;

};
#endif //XPOINTARRAY_H
