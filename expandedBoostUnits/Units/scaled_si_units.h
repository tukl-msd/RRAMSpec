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


#ifndef RERAMSPEC_SCALED_SI_UNITS
#define RERAMSPEC_SCALED_SI_UNITS

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/cmath.hpp>

namespace boost {

namespace units {

namespace rramspec {

// Length dimension
typedef make_scaled_unit<si::length,scale<10, static_rational<15>>>::type petameter_unit;
BOOST_UNITS_STATIC_CONSTANT(petameter, petameter_unit);
BOOST_UNITS_STATIC_CONSTANT(petameters, petameter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<12>>>::type terameter_unit;
BOOST_UNITS_STATIC_CONSTANT(terameter, terameter_unit);
BOOST_UNITS_STATIC_CONSTANT(terameters, terameter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<9>>>::type gigameter_unit;
BOOST_UNITS_STATIC_CONSTANT(gigameter, gigameter_unit);
BOOST_UNITS_STATIC_CONSTANT(gigameters, gigameter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<6>>>::type megameter_unit;
BOOST_UNITS_STATIC_CONSTANT(megameter, megameter_unit);
BOOST_UNITS_STATIC_CONSTANT(megameters, megameter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<3>>>::type kilometer_unit;
BOOST_UNITS_STATIC_CONSTANT(kilometer, kilometer_unit);
BOOST_UNITS_STATIC_CONSTANT(kilometers, kilometer_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<0>>>::type meter_unit;
BOOST_UNITS_STATIC_CONSTANT(meter, meter_unit);
BOOST_UNITS_STATIC_CONSTANT(meters, meter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-3>>>::type millimeter_unit;
BOOST_UNITS_STATIC_CONSTANT(millimeter, millimeter_unit);
BOOST_UNITS_STATIC_CONSTANT(millimeters, millimeter_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-6>>>::type micrometer_unit;
BOOST_UNITS_STATIC_CONSTANT(micrometer, micrometer_unit);
BOOST_UNITS_STATIC_CONSTANT(micrometers, micrometer_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-9>>>::type nanometer_unit;
BOOST_UNITS_STATIC_CONSTANT(nanometer, nanometer_unit);
BOOST_UNITS_STATIC_CONSTANT(nanometers, nanometer_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-12>>>::type picometer_unit;
BOOST_UNITS_STATIC_CONSTANT(picometer, picometer_unit);
BOOST_UNITS_STATIC_CONSTANT(picometers, picometer_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-15>>>::type femtometer_unit;
BOOST_UNITS_STATIC_CONSTANT(femtometer, femtometer_unit);
BOOST_UNITS_STATIC_CONSTANT(femtometers, femtometer_unit);
typedef make_scaled_unit<si::length,scale<10, static_rational<-18>>>::type attometer_unit;
BOOST_UNITS_STATIC_CONSTANT(attometer, attometer_unit);
BOOST_UNITS_STATIC_CONSTANT(attometers, attometer_unit);
// Length dimension

// Area dimension
typedef make_scaled_unit<si::area,scale<10, static_rational<6>>>::type square_kilometer_unit;
BOOST_UNITS_STATIC_CONSTANT(square_kilometer, square_kilometer_unit);
BOOST_UNITS_STATIC_CONSTANT(square_kilometers, square_kilometer_unit);
typedef make_scaled_unit<si::area,scale<10, static_rational<0>>>::type square_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(square_meter, square_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(square_meters, square_meter_unit);
typedef make_scaled_unit<si::area,scale<10, static_rational<-6>>>::type square_millimeter_unit;
BOOST_UNITS_STATIC_CONSTANT(square_millimeter, square_millimeter_unit);
BOOST_UNITS_STATIC_CONSTANT(square_millimeters, square_millimeter_unit);
typedef make_scaled_unit<si::area,scale<10, static_rational<-12>>>::type square_micrometer_unit;
BOOST_UNITS_STATIC_CONSTANT(square_micrometer, square_micrometer_unit);
BOOST_UNITS_STATIC_CONSTANT(square_micrometers, square_micrometer_unit);
typedef make_scaled_unit<si::area,scale<10, static_rational<-18>>>::type square_nanometer_unit;
BOOST_UNITS_STATIC_CONSTANT(square_nanometer, square_nanometer_unit);
BOOST_UNITS_STATIC_CONSTANT(square_nanometers, square_nanometer_unit);
// Area dimension

// Volt dimension
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<15>>>::type petavolt_unit;
BOOST_UNITS_STATIC_CONSTANT(petavolt, petavolt_unit);
BOOST_UNITS_STATIC_CONSTANT(petavolts, petavolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<12>>>::type teravolt_unit;
BOOST_UNITS_STATIC_CONSTANT(teravolt, teravolt_unit);
BOOST_UNITS_STATIC_CONSTANT(teravolts, teravolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<9>>>::type gigavolt_unit;
BOOST_UNITS_STATIC_CONSTANT(gigavolt, gigavolt_unit);
BOOST_UNITS_STATIC_CONSTANT(gigavolts, gigavolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<6>>>::type megavolt_unit;
BOOST_UNITS_STATIC_CONSTANT(megavolt, megavolt_unit);
BOOST_UNITS_STATIC_CONSTANT(megavolts, megavolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<3>>>::type kilovolt_unit;
BOOST_UNITS_STATIC_CONSTANT(kilovolt, kilovolt_unit);
BOOST_UNITS_STATIC_CONSTANT(kilovolts, kilovolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<0>>>::type volt_unit;
BOOST_UNITS_STATIC_CONSTANT(volt, volt_unit);
BOOST_UNITS_STATIC_CONSTANT(volts, volt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-3>>>::type millivolt_unit;
BOOST_UNITS_STATIC_CONSTANT(millivolt, millivolt_unit);
BOOST_UNITS_STATIC_CONSTANT(millivolts, millivolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-6>>>::type microvolt_unit;
BOOST_UNITS_STATIC_CONSTANT(microvolt, microvolt_unit);
BOOST_UNITS_STATIC_CONSTANT(microvolts, microvolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-9>>>::type nanovolt_unit;
BOOST_UNITS_STATIC_CONSTANT(nanovolt, nanovolt_unit);
BOOST_UNITS_STATIC_CONSTANT(nanovolts, nanovolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-12>>>::type picovolt_unit;
BOOST_UNITS_STATIC_CONSTANT(picovolt, picovolt_unit);
BOOST_UNITS_STATIC_CONSTANT(picovolts, picovolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-15>>>::type femtovolt_unit;
BOOST_UNITS_STATIC_CONSTANT(femtovolt, femtovolt_unit);
BOOST_UNITS_STATIC_CONSTANT(femtovolts, femtovolt_unit);
typedef make_scaled_unit<si::electric_potential,scale<10, static_rational<-18>>>::type attovolt_unit;
BOOST_UNITS_STATIC_CONSTANT(attovolt, attovolt_unit);
BOOST_UNITS_STATIC_CONSTANT(attovolts, attovolt_unit);
// Volt dimension

// Current dimension
typedef make_scaled_unit<si::current,scale<10, static_rational<15>>>::type petaampere_unit;
BOOST_UNITS_STATIC_CONSTANT(petaampere, petaampere_unit);
BOOST_UNITS_STATIC_CONSTANT(petaamperes, petaampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<12>>>::type teraampere_unit;
BOOST_UNITS_STATIC_CONSTANT(teraampere, teraampere_unit);
BOOST_UNITS_STATIC_CONSTANT(teraamperes, teraampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<9>>>::type gigaampere_unit;
BOOST_UNITS_STATIC_CONSTANT(gigaampere, gigaampere_unit);
BOOST_UNITS_STATIC_CONSTANT(gigaamperes, gigaampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<6>>>::type megaampere_unit;
BOOST_UNITS_STATIC_CONSTANT(megaampere, megaampere_unit);
BOOST_UNITS_STATIC_CONSTANT(megaamperes, megaampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<3>>>::type kiloampere_unit;
BOOST_UNITS_STATIC_CONSTANT(kiloampere, kiloampere_unit);
BOOST_UNITS_STATIC_CONSTANT(kiloamperes, kiloampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<0>>>::type ampere_unit;
BOOST_UNITS_STATIC_CONSTANT(ampere, ampere_unit);
BOOST_UNITS_STATIC_CONSTANT(amperes, ampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-3>>>::type milliampere_unit;
BOOST_UNITS_STATIC_CONSTANT(milliampere, milliampere_unit);
BOOST_UNITS_STATIC_CONSTANT(milliamperes, milliampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-6>>>::type microampere_unit;
BOOST_UNITS_STATIC_CONSTANT(microampere, microampere_unit);
BOOST_UNITS_STATIC_CONSTANT(microamperes, microampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-9>>>::type nanoampere_unit;
BOOST_UNITS_STATIC_CONSTANT(nanoampere, nanoampere_unit);
BOOST_UNITS_STATIC_CONSTANT(nanoamperes, nanoampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-12>>>::type picoampere_unit;
BOOST_UNITS_STATIC_CONSTANT(picoampere, picoampere_unit);
BOOST_UNITS_STATIC_CONSTANT(picoamperes, picoampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-15>>>::type femtoampere_unit;
BOOST_UNITS_STATIC_CONSTANT(femtoampere, femtoampere_unit);
BOOST_UNITS_STATIC_CONSTANT(femtoamperes, femtoampere_unit);
typedef make_scaled_unit<si::current,scale<10, static_rational<-18>>>::type attoampere_unit;
BOOST_UNITS_STATIC_CONSTANT(attoampere, attoampere_unit);
BOOST_UNITS_STATIC_CONSTANT(attoamperes, attoampere_unit);
// Current dimension

// Time dimension
typedef make_scaled_unit<si::time,scale<10, static_rational<15>>>::type petasecond_unit;
BOOST_UNITS_STATIC_CONSTANT(petasecond, petasecond_unit);
BOOST_UNITS_STATIC_CONSTANT(petaseconds, petasecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<12>>>::type terasecond_unit;
BOOST_UNITS_STATIC_CONSTANT(terasecond, terasecond_unit);
BOOST_UNITS_STATIC_CONSTANT(teraseconds, terasecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<9>>>::type gigasecond_unit;
BOOST_UNITS_STATIC_CONSTANT(gigasecond, gigasecond_unit);
BOOST_UNITS_STATIC_CONSTANT(gigaseconds, gigasecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<6>>>::type megasecond_unit;
BOOST_UNITS_STATIC_CONSTANT(megasecond, megasecond_unit);
BOOST_UNITS_STATIC_CONSTANT(megaseconds, megasecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<3>>>::type kilosecond_unit;
BOOST_UNITS_STATIC_CONSTANT(kilosecond, kilosecond_unit);
BOOST_UNITS_STATIC_CONSTANT(kiloseconds, kilosecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<0>>>::type second_unit;
BOOST_UNITS_STATIC_CONSTANT(second, second_unit);
BOOST_UNITS_STATIC_CONSTANT(seconds, second_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-3>>>::type millisecond_unit;
BOOST_UNITS_STATIC_CONSTANT(millisecond, millisecond_unit);
BOOST_UNITS_STATIC_CONSTANT(milliseconds, millisecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-6>>>::type microsecond_unit;
BOOST_UNITS_STATIC_CONSTANT(microsecond, microsecond_unit);
BOOST_UNITS_STATIC_CONSTANT(microseconds, microsecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-9>>>::type nanosecond_unit;
BOOST_UNITS_STATIC_CONSTANT(nanosecond, nanosecond_unit);
BOOST_UNITS_STATIC_CONSTANT(nanoseconds, nanosecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-12>>>::type picosecond_unit;
BOOST_UNITS_STATIC_CONSTANT(picosecond, picosecond_unit);
BOOST_UNITS_STATIC_CONSTANT(picoseconds, picosecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-15>>>::type femtosecond_unit;
BOOST_UNITS_STATIC_CONSTANT(femtosecond, femtosecond_unit);
BOOST_UNITS_STATIC_CONSTANT(femtoseconds, femtosecond_unit);
typedef make_scaled_unit<si::time,scale<10, static_rational<-18>>>::type attosecond_unit;
BOOST_UNITS_STATIC_CONSTANT(attosecond, attosecond_unit);
BOOST_UNITS_STATIC_CONSTANT(attoseconds, attosecond_unit);
// Time dimension

// Frequency dimension
typedef make_scaled_unit<si::frequency,scale<10, static_rational<15>>>::type petahertz_unit;
BOOST_UNITS_STATIC_CONSTANT(petahertz, petahertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<12>>>::type terahertz_unit;
BOOST_UNITS_STATIC_CONSTANT(terahertz, terahertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<9>>>::type gigahertz_unit;
BOOST_UNITS_STATIC_CONSTANT(gigahertz, gigahertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<6>>>::type megahertz_unit;
BOOST_UNITS_STATIC_CONSTANT(megahertz, megahertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<3>>>::type kilohertz_unit;
BOOST_UNITS_STATIC_CONSTANT(kilohertz, kilohertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<0>>>::type hertz_unit;
BOOST_UNITS_STATIC_CONSTANT(hertz, hertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-3>>>::type millihertz_unit;
BOOST_UNITS_STATIC_CONSTANT(millihertz, millihertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-6>>>::type microhertz_unit;
BOOST_UNITS_STATIC_CONSTANT(microhertz, microhertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-9>>>::type nanohertz_unit;
BOOST_UNITS_STATIC_CONSTANT(nanohertz, nanohertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-12>>>::type picohertz_unit;
BOOST_UNITS_STATIC_CONSTANT(picohertz, picohertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-15>>>::type femtohertz_unit;
BOOST_UNITS_STATIC_CONSTANT(femtohertz, femtohertz_unit);
typedef make_scaled_unit<si::frequency,scale<10, static_rational<-18>>>::type attohertz_unit;
BOOST_UNITS_STATIC_CONSTANT(attohertz, attohertz_unit);
// Frequency dimension

// Resistance dimension
typedef make_scaled_unit<si::resistance,scale<10, static_rational<15>>>::type petaohm_unit;
BOOST_UNITS_STATIC_CONSTANT(petaohm, petaohm_unit);
BOOST_UNITS_STATIC_CONSTANT(petaohms, petaohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<12>>>::type teraohm_unit;
BOOST_UNITS_STATIC_CONSTANT(teraohm, teraohm_unit);
BOOST_UNITS_STATIC_CONSTANT(teraohms, teraohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<9>>>::type gigaohm_unit;
BOOST_UNITS_STATIC_CONSTANT(gigaohm, gigaohm_unit);
BOOST_UNITS_STATIC_CONSTANT(gigaohms, gigaohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<6>>>::type megaohm_unit;
BOOST_UNITS_STATIC_CONSTANT(megaohm, megaohm_unit);
BOOST_UNITS_STATIC_CONSTANT(megaohms, megaohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<3>>>::type kiloohm_unit;
BOOST_UNITS_STATIC_CONSTANT(kiloohm, kiloohm_unit);
BOOST_UNITS_STATIC_CONSTANT(kiloohms, kiloohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<0>>>::type ohm_unit;
BOOST_UNITS_STATIC_CONSTANT(ohm, ohm_unit);
BOOST_UNITS_STATIC_CONSTANT(ohms, ohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-3>>>::type milliohm_unit;
BOOST_UNITS_STATIC_CONSTANT(milliohm, milliohm_unit);
BOOST_UNITS_STATIC_CONSTANT(milliohms, milliohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-6>>>::type microohm_unit;
BOOST_UNITS_STATIC_CONSTANT(microohm, microohm_unit);
BOOST_UNITS_STATIC_CONSTANT(microohms, microohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-9>>>::type nanoohm_unit;
BOOST_UNITS_STATIC_CONSTANT(nanoohm, nanoohm_unit);
BOOST_UNITS_STATIC_CONSTANT(nanoohms, nanoohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-12>>>::type picoohm_unit;
BOOST_UNITS_STATIC_CONSTANT(picoohm, picoohm_unit);
BOOST_UNITS_STATIC_CONSTANT(picoohms, picoohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-15>>>::type femtoohm_unit;
BOOST_UNITS_STATIC_CONSTANT(femtoohm, femtoohm_unit);
BOOST_UNITS_STATIC_CONSTANT(femtoohms, femtoohm_unit);
typedef make_scaled_unit<si::resistance,scale<10, static_rational<-18>>>::type attoohm_unit;
BOOST_UNITS_STATIC_CONSTANT(attoohm, attoohm_unit);
BOOST_UNITS_STATIC_CONSTANT(attoohms, attoohm_unit);
// Resistance dimension

// Capacitance dimension
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<15>>>::type petafarad_unit;
BOOST_UNITS_STATIC_CONSTANT(petafarad, petafarad_unit);
BOOST_UNITS_STATIC_CONSTANT(petafarads, petafarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<12>>>::type terafarad_unit;
BOOST_UNITS_STATIC_CONSTANT(terafarad, terafarad_unit);
BOOST_UNITS_STATIC_CONSTANT(terafarads, terafarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<9>>>::type gigafarad_unit;
BOOST_UNITS_STATIC_CONSTANT(gigafarad, gigafarad_unit);
BOOST_UNITS_STATIC_CONSTANT(gigafarads, gigafarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<6>>>::type megafarad_unit;
BOOST_UNITS_STATIC_CONSTANT(megafarad, megafarad_unit);
BOOST_UNITS_STATIC_CONSTANT(megafarads, megafarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<3>>>::type kilofarad_unit;
BOOST_UNITS_STATIC_CONSTANT(kilofarad, kilofarad_unit);
BOOST_UNITS_STATIC_CONSTANT(kilofarads, kilofarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<0>>>::type farad_unit;
BOOST_UNITS_STATIC_CONSTANT(farad, farad_unit);
BOOST_UNITS_STATIC_CONSTANT(farads, farad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-3>>>::type millifarad_unit;
BOOST_UNITS_STATIC_CONSTANT(millifarad, millifarad_unit);
BOOST_UNITS_STATIC_CONSTANT(millifarads, millifarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-6>>>::type microfarad_unit;
BOOST_UNITS_STATIC_CONSTANT(microfarad, microfarad_unit);
BOOST_UNITS_STATIC_CONSTANT(microfarads, microfarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-9>>>::type nanofarad_unit;
BOOST_UNITS_STATIC_CONSTANT(nanofarad, nanofarad_unit);
BOOST_UNITS_STATIC_CONSTANT(nanofarads, nanofarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-12>>>::type picofarad_unit;
BOOST_UNITS_STATIC_CONSTANT(picofarad, picofarad_unit);
BOOST_UNITS_STATIC_CONSTANT(picofarads, picofarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-15>>>::type femtofarad_unit;
BOOST_UNITS_STATIC_CONSTANT(femtofarad, femtofarad_unit);
BOOST_UNITS_STATIC_CONSTANT(femtofarads, femtofarad_unit);
typedef make_scaled_unit<si::capacitance,scale<10, static_rational<-18>>>::type attofarad_unit;
BOOST_UNITS_STATIC_CONSTANT(attofarad, attofarad_unit);
BOOST_UNITS_STATIC_CONSTANT(attofarads, attofarad_unit);
// Capacitance dimension

// Electric charge dimension
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<15>>>::type petacoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(petacoulomb, petacoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(petacoulombs, petacoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<12>>>::type teracoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(teracoulomb, teracoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(teracoulombs, teracoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<9>>>::type gigacoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(gigacoulomb, gigacoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(gigacoulombs, gigacoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<6>>>::type megacoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(megacoulomb, megacoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(megacoulombs, megacoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<3>>>::type kilocoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(kilocoulomb, kilocoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(kilocoulombs, kilocoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<0>>>::type coulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(coulomb, coulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(coulombs, coulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-3>>>::type millicoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(millicoulomb, millicoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(millicoulombs, millicoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-6>>>::type microcoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(microcoulomb, microcoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(microcoulombs, microcoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-9>>>::type nanocoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(nanocoulomb, nanocoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(nanocoulombs, nanocoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-12>>>::type picocoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(picocoulomb, picocoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(picocoulombs, picocoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-15>>>::type femtocoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(femtocoulomb, femtocoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(femtocoulombs, femtocoulomb_unit);
typedef make_scaled_unit<si::electric_charge,scale<10, static_rational<-18>>>::type attocoulomb_unit;
BOOST_UNITS_STATIC_CONSTANT(attocoulomb, attocoulomb_unit);
BOOST_UNITS_STATIC_CONSTANT(attocoulombs, attocoulomb_unit);
// Electric charge dimension

// Resistivity dimension
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<15>>>::type petaohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(petaohm_meter, petaohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(petaohm_meters, petaohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<12>>>::type teraohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(teraohm_meter, teraohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(teraohm_meters, teraohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<9>>>::type gigaohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(gigaohm_meter, gigaohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(gigaohm_meters, gigaohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<6>>>::type megaohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(megaohm_meter, megaohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(megaohm_meters, megaohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<3>>>::type kiloohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(kiloohm_meter, kiloohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(kiloohm_meters, kiloohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<0>>>::type ohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(ohm_meter, ohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(ohm_meters, ohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-3>>>::type milliohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(milliohm_meter, milliohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(milliohm_meters, milliohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-6>>>::type microohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(microohm_meter, microohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(microohm_meters, microohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-9>>>::type nanoohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(nanoohm_meter, nanoohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(nanoohm_meters, nanoohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-12>>>::type picoohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(picoohm_meter, picoohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(picoohm_meters, picoohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-15>>>::type femtoohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(femtoohm_meter, femtoohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(femtoohm_meters, femtoohm_meter_unit);
typedef make_scaled_unit<si::resistivity,scale<10, static_rational<-18>>>::type attoohm_meter_unit;
BOOST_UNITS_STATIC_CONSTANT(attoohm_meter, attoohm_meter_unit);
BOOST_UNITS_STATIC_CONSTANT(attoohm_meters, attoohm_meter_unit);
// Resistivity dimension

// Energy dimension
typedef make_scaled_unit<si::energy,scale<10, static_rational<15>>>::type petajoule_unit;
BOOST_UNITS_STATIC_CONSTANT(petajoule, petajoule_unit);
BOOST_UNITS_STATIC_CONSTANT(petajoules, petajoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<12>>>::type terajoule_unit;
BOOST_UNITS_STATIC_CONSTANT(terajoule, terajoule_unit);
BOOST_UNITS_STATIC_CONSTANT(terajoules, terajoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<9>>>::type gigajoule_unit;
BOOST_UNITS_STATIC_CONSTANT(gigajoule, gigajoule_unit);
BOOST_UNITS_STATIC_CONSTANT(gigajoules, gigajoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<6>>>::type megajoule_unit;
BOOST_UNITS_STATIC_CONSTANT(megajoule, megajoule_unit);
BOOST_UNITS_STATIC_CONSTANT(megajoules, megajoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<3>>>::type kilojoule_unit;
BOOST_UNITS_STATIC_CONSTANT(kilojoule, kilojoule_unit);
BOOST_UNITS_STATIC_CONSTANT(kilojoules, kilojoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<0>>>::type joule_unit;
BOOST_UNITS_STATIC_CONSTANT(joule, joule_unit);
BOOST_UNITS_STATIC_CONSTANT(joules, joule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-3>>>::type millijoule_unit;
BOOST_UNITS_STATIC_CONSTANT(millijoule, millijoule_unit);
BOOST_UNITS_STATIC_CONSTANT(millijoules, millijoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-6>>>::type microjoule_unit;
BOOST_UNITS_STATIC_CONSTANT(microjoule, microjoule_unit);
BOOST_UNITS_STATIC_CONSTANT(microjoules, microjoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-9>>>::type nanojoule_unit;
BOOST_UNITS_STATIC_CONSTANT(nanojoule, nanojoule_unit);
BOOST_UNITS_STATIC_CONSTANT(nanojoules, nanojoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-12>>>::type picojoule_unit;
BOOST_UNITS_STATIC_CONSTANT(picojoule, picojoule_unit);
BOOST_UNITS_STATIC_CONSTANT(picojoules, picojoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-15>>>::type femtojoule_unit;
BOOST_UNITS_STATIC_CONSTANT(femtojoule, femtojoule_unit);
BOOST_UNITS_STATIC_CONSTANT(femtojoules, femtojoule_unit);
typedef make_scaled_unit<si::energy,scale<10, static_rational<-18>>>::type attojoule_unit;
BOOST_UNITS_STATIC_CONSTANT(attojoule, attojoule_unit);
BOOST_UNITS_STATIC_CONSTANT(attojoules, attojoule_unit);
// Energy dimension

// Power dimension
typedef make_scaled_unit<si::power,scale<10, static_rational<15>>>::type petawatt_unit;
BOOST_UNITS_STATIC_CONSTANT(petawatt, petawatt_unit);
BOOST_UNITS_STATIC_CONSTANT(petawatts, petawatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<12>>>::type terawatt_unit;
BOOST_UNITS_STATIC_CONSTANT(terawatt, terawatt_unit);
BOOST_UNITS_STATIC_CONSTANT(terawatts, terawatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<9>>>::type gigawatt_unit;
BOOST_UNITS_STATIC_CONSTANT(gigawatt, gigawatt_unit);
BOOST_UNITS_STATIC_CONSTANT(gigawatts, gigawatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<6>>>::type megawatt_unit;
BOOST_UNITS_STATIC_CONSTANT(megawatt, megawatt_unit);
BOOST_UNITS_STATIC_CONSTANT(megawatts, megawatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<3>>>::type kilowatt_unit;
BOOST_UNITS_STATIC_CONSTANT(kilowatt, kilowatt_unit);
BOOST_UNITS_STATIC_CONSTANT(kilowatts, kilowatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<0>>>::type watt_unit;
BOOST_UNITS_STATIC_CONSTANT(watt, watt_unit);
BOOST_UNITS_STATIC_CONSTANT(watts, watt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-3>>>::type milliwatt_unit;
BOOST_UNITS_STATIC_CONSTANT(milliwatt, milliwatt_unit);
BOOST_UNITS_STATIC_CONSTANT(milliwatts, milliwatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-6>>>::type microwatt_unit;
BOOST_UNITS_STATIC_CONSTANT(microwatt, microwatt_unit);
BOOST_UNITS_STATIC_CONSTANT(microwatts, microwatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-9>>>::type nanowatt_unit;
BOOST_UNITS_STATIC_CONSTANT(nanowatt, nanowatt_unit);
BOOST_UNITS_STATIC_CONSTANT(nanowatts, nanowatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-12>>>::type picowatt_unit;
BOOST_UNITS_STATIC_CONSTANT(picowatt, picowatt_unit);
BOOST_UNITS_STATIC_CONSTANT(picowatts, picowatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-15>>>::type femtowatt_unit;
BOOST_UNITS_STATIC_CONSTANT(femtowatt, femtowatt_unit);
BOOST_UNITS_STATIC_CONSTANT(femtowatts, femtowatt_unit);
typedef make_scaled_unit<si::power,scale<10, static_rational<-18>>>::type attowatt_unit;
BOOST_UNITS_STATIC_CONSTANT(attowatt, attowatt_unit);
BOOST_UNITS_STATIC_CONSTANT(attowatts, attowatt_unit);
// Power dimension



} // namespace rramspec

inline std::string name_string(const reduce_unit<rramspec::ohm_meter_unit>::type&)   { return "Ohm m"; }
inline std::string symbol_string(const reduce_unit<rramspec::ohm_meter_unit>::type&) { return "Ohm m"; }

inline std::string name_string(const reduce_unit<rramspec::square_kilometer_unit>::type&)    { return "km^2"; }
inline std::string symbol_string(const reduce_unit<rramspec::square_kilometer_unit>::type&)  { return "km^2"; }
inline std::string name_string(const reduce_unit<rramspec::square_meter_unit>::type&)        { return "m^2"; }
inline std::string symbol_string(const reduce_unit<rramspec::square_meter_unit>::type&)      { return "m^2"; }
inline std::string name_string(const reduce_unit<rramspec::square_millimeter_unit>::type&)   { return "mm^2"; }
inline std::string symbol_string(const reduce_unit<rramspec::square_millimeter_unit>::type&) { return "mm^2"; }
inline std::string name_string(const reduce_unit<rramspec::square_micrometer_unit>::type&)   { return "um^2"; }
inline std::string symbol_string(const reduce_unit<rramspec::square_micrometer_unit>::type&) { return "um^2"; }
inline std::string name_string(const reduce_unit<rramspec::square_nanometer_unit>::type&)    { return "nm^2"; }
inline std::string symbol_string(const reduce_unit<rramspec::square_nanometer_unit>::type&)  { return "nm^2"; }

} // namespace units

} // namespace boost

#endif // RERAMSPEC_SCALED_SI_UNITS
