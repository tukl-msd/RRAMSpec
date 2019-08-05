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



#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>

#include <iostream>
#include <iomanip>

#include "constants.h"
#include "globalStructs.h"

#include "../expandedBoostUnits/Units/rramSpec_units.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

bool isValid( const ebool& flag );
bool isValid( const double& val );
bool isValid( const char* str );
bool isValid( const std::string& str );
template<class U> inline bool
isValid( const bu::quantity<U, double>& q )
{
  return isValid(q.value());
}

template<class LastT>
bool areValid( LastT last )
{
  return isValid(last);
}

template<class FirstT, class... OtherTs>
bool areValid( FirstT first, OtherTs... others )
{
  return ( isValid(first) && areValid(others...) );
}

template<class T>
bool isInvalid( T var )
{
  return !isValid( var );
}

template<class LastT>
bool areInvalid( LastT last )
{
  return isInvalid(last);
}

template<class FirstT, class... OtherTs>
bool areInvalid( FirstT first, OtherTs... others )
{
  return ( isInvalid(first) && areInvalid(others...) );
}

void invalidate(ebool* var);
void invalidate(std::string* var);
void invalidate(double* var);
template<class U> void
invalidate( bu::quantity<U, double>* q )
{
  *q = bu::quantity<U, double>::from_value(INVALID_DOUBLE);
}

bool areEqual(const double&, const double&, const double& relTol = 1e-9);
template<class U> inline bool
areEqual( const bu::quantity<U, double>& q0,
         const bu::quantity<U, double>& q1,
         const double& relTol = 1e-9)
{
  return areEqual(q0.value(), q1.value(), relTol);
}

bool fastAreEqual(const double&, const double&, const double& relTol = 1e-9);
template<class U> inline bool
fastAreEqual( const bu::quantity<U, double>& q0,
             const bu::quantity<U, double>& q1,
             const double& relTol = 1e-9)
{
  return fastAreEqual(q0.value(), q1.value(), relTol);
}

bool isInteger( double dn );
bool isPowerOfTwo( double n );

// Finds the lowest index whose vec content is greater than val
//  Vec must be sorted in ascending order
template<class T>
std::size_t findLowestGreater(const std::vector<T>& vec, const T& val);
template<class T>
std::size_t findLowestGreater(const std::vector<T>& vec, const T& val,
                              std::size_t start, std::size_t end);
template<class T>
std::size_t findLowestGreater(const std::vector<T>& vec, const T& val)
{
  std::size_t start = 0;
  std::size_t end = vec.size();
  return findLowestGreater(vec, val, start, end);
}
template<class T>
std::size_t findLowestGreater(const std::vector<T>& vec, const T& val,
                              std::size_t start, std::size_t end)
{
  if ( start == end ) {
    return start;
  }
  const std::size_t middle = (start + end) / 2;
  if ( vec.at(middle) > val ) {
    return findLowestGreater(vec, val, start, middle);
  }
  return findLowestGreater(vec, val, middle+1, end);
}

double round(double num, size_t nSigFigs);
template<class U> inline bu::quantity<U,double>
round( const bu::quantity<U, double>& q, size_t nSigFigs )
{
  return bu::quantity<U, double>::from_value(round(q.value(), nSigFigs));
}

double tausToPercentSingleRC(double percentage);

double tausToPercentLumpedRC(double percentage);

#define PRINT_VAR(varName) \
    do{std::cout << #varName " = " << std::setprecision(60) \
       << varName << std::endl;} while(false)

#define PRINT_INFO(infoString) \
    do{ std::cout << "[INFO] " << infoString << std::endl;} while(false)

#define PRINT_WARNING(warningString) \
    do{ std::cerr << "[WARNING] " << warningString << std::endl;} while(false)

#define PRINT_ERROR(errorString) \
    do{ std::cerr << "[ERROR] " << errorString << std::endl;} while(false)

#endif // FUNCTIONS_H
