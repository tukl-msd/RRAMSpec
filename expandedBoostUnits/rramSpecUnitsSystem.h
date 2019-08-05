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



#ifndef RERAMSPEC_UNITS_SYSTEM_H
#define RERAMSPEC_UNITS_SYSTEM_H

#include <boost/units/static_constant.hpp>
#include <boost/units/unit.hpp>
#include "expanded_make_system.hpp"

#include <boost/units/base_units/si/meter.hpp>
#include <boost/units/base_units/si/kilogram.hpp>
#include <boost/units/base_units/si/second.hpp>
#include <boost/units/base_units/si/ampere.hpp>
#include <boost/units/base_units/temperature/celsius.hpp>
#include <boost/units/base_units/information/bit.hpp>
#include <boost/units/base_units/information/byte.hpp>

namespace boost {

namespace units {

namespace rramspec {

/// placeholder class defining rramspec unit system
///  with information base unit being bit
typedef make_system<si::meter_base_unit,
                    si::kilogram_base_unit,
                    si::second_base_unit,
                    si::ampere_base_unit,
                    temperature::celsius_base_unit,
                    information::bit_base_unit>::type system_bit;

/// placeholder class defining rramspec unit system
///  with information base unit being Byte
typedef make_system<si::meter_base_unit,
                    si::kilogram_base_unit,
                    si::second_base_unit,
                    si::ampere_base_unit,
                    temperature::celsius_base_unit,
                    information::byte_base_unit>::type system_byte;

/// dimensionless rramspec unit
typedef unit<dimensionless_type,system_bit>         dimensionless;

} // namespace rramspec

} // namespace units

} // namespace boost

#endif // RERAMSPEC_UNITS_SYSTEM_H
