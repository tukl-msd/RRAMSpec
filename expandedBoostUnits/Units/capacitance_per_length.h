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



#ifndef RERAMSPEC_CAPACITANCE_PER_LENGHT_UNIT_H
#define RERAMSPEC_CAPACITANCE_PER_LENGHT_UNIT_H

#include "../rramSpecUnitsSystem.h"
#include "../DerivedDimensions/capacitance_per_length.h"

namespace boost {

namespace units {

namespace rramspec {

typedef unit<capacitance_per_length_dimension,rramspec::system_bit>    farad_per_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(farad_per_meter,farad_per_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(farads_per_meter,farad_per_meter_unit);

// femtofarad / millimeter = picofarad / meter
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-12>>>::type femtofarad_per_millimeter_unit;
BOOST_UNITS_STATIC_CONSTANT(femtofarad_per_millimeter,femtofarad_per_millimeter_unit);
BOOST_UNITS_STATIC_CONSTANT(femtofarads_per_millimeter,femtofarad_per_millimeter_unit);
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-12>>>::type picofarad_per_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(picofarad_per_meter,picofarad_per_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(picofarads_per_meter,picofarad_per_meter_unit);

// femtofarad / micrometer = attofard / nanometer = nanofarad / meter
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-9>>>::type femtofarad_per_micrometer_unit;
BOOST_UNITS_STATIC_CONSTANT(femtofarad_per_micrometer,femtofarad_per_micrometer_unit);
BOOST_UNITS_STATIC_CONSTANT(femtofarads_per_micrometer,femtofarad_per_micrometer_unit);
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-9>>>::type attofarad_per_nanometer_unit;
BOOST_UNITS_STATIC_CONSTANT(attofarad_per_nanometer,attofarad_per_nanometer_unit);
BOOST_UNITS_STATIC_CONSTANT(attofarads_per_nanometer,attofarad_per_nanometer_unit);
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-9>>>::type nanofarad_per_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(nanofarad_per_meter,nanofarad_per_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(nanofarads_per_meter,nanofarad_per_meter_unit);

// nanofarad / millimeter = microfarad / meter
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-6>>>::type nanofarad_per_millimeter_unit;
BOOST_UNITS_STATIC_CONSTANT(nanofarad_per_millimeter,nanofarad_per_millimeter_unit);
BOOST_UNITS_STATIC_CONSTANT(nanofarads_per_millimeter,nanofarad_per_millimeter_unit);

// nanofarad / micrometer = millifarad / meter
typedef make_scaled_unit<farad_per_meter_unit,scale<10, static_rational<-3>>>::type nanofarad_per_micrometer_unit;
BOOST_UNITS_STATIC_CONSTANT(nanofarad_per_micrometer,nanofarad_per_micrometer_unit);
BOOST_UNITS_STATIC_CONSTANT(nanofarads_per_micrometer,nanofarad_per_micrometer_unit);

} // namespace rramspec

inline std::string name_string(const reduce_unit<rramspec::farad_per_meter_unit>::type&)   { return "F/m"; }
inline std::string symbol_string(const reduce_unit<rramspec::farad_per_meter_unit>::type&) { return "F/m"; }

} // namespace units

} // namespace boost

#endif // RERAMSPEC_CAPACITANCE_PER_LENGHT_UNIT_H
