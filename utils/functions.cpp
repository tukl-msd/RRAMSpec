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



#include "functions.h"
#include <stdio.h>
#include <iostream>

bool isValid( const ebool& flag )
{
  return ( flag == (ebool)0 || flag == (ebool)1 );
}

bool isValid( const double& val )
{
  return ( val != INVALID_DOUBLE );
}

bool isValid( const char* str )
{
  return str ? strcmp( str, INVALID_C_STRING ) : true;
}

bool isValid( const std::string& str )
{
  return isValid( str.c_str() );
}

void invalidate(ebool* var)
{
  *var = INVALID_EBOOL;
}

void invalidate(std::string* var)
{
  *var = INVALID_STRING;
}

void invalidate(double* var)
{
  *var = INVALID_DOUBLE;
}


bool areEqual(const double& a, const double& b, const double& relTol)
{
  if ( a == b ) {
    return true;
  }
  double udiff = fabs(a-b);
  if ( udiff < (relTol - std::nextafter(relTol, 0)) ) {
    return true;
  }
  return ( udiff < (fabs(a+b)/2.) * relTol );
}

bool fastAreEqual(const double& a, const double& b, const double& relTol)
{
  return fabs(a - b) <= fabs(a) * relTol;
}

bool isInteger( double dn )
{
    if ( std::isinf(dn) ) {
      return false;
    }
    double intpart;
    return ( modf(dn, &intpart) == 0 );
}

bool isPowerOfTwo( double dn )
{
  int exponent = 0;
  auto mantissa1 = frexp(dn, &exponent);
  return mantissa1 == 0.5;
}

double round(double num, size_t nSigFigs) {
  if (num == 0.) {
    return 0.;
  }
  if ( isinf(num) ) {
    return num;
  }
  int expDiff = nSigFigs - ceil(log10(fabs(num)));
  double roundedNum;
  if ( expDiff >= 0 ) {
    roundedNum = round(num * pow(10., expDiff)) / pow(10., expDiff);
  } else {
    roundedNum = round(num / pow(10., -expDiff)) * pow(10., -expDiff);
  }
  return roundedNum;
}

double tausToPercentSingleRC(double percentage)
{
    // Compute the amount of time an exponetial signal,
    //  of type V(t) = 1 - exp( - t/tau )
    //  takes to reach a given percentage of the final value.
    //  The returned amount is given in terms of number of tau's.
    return -log(1.0 - percentage/100.0);
}

double tausToPercentLumpedRC(double percentage)
{

  if ( percentage > 99 ) {
    throw "Maximum percentage for Lumped RC is 99\%.";
  }

  const double nTauss[] = {
    0.,
    0.0635953,
    0.0755382,
    0.0847084,
    0.0926021,
    0.0997503,
    0.106411,
    0.11273,
    0.118803,
    0.124691,
    0.130441,
    0.136085,
    0.141651,
    0.147158,
    0.152624,
    0.158062,
    0.163484,
    0.1689,
    0.174319,
    0.179749,
    0.185197,
    0.190668,
    0.196169,
    0.201704,
    0.207279,
    0.212899,
    0.218567,
    0.224288,
    0.230066,
    0.235905,
    0.241809,
    0.247781,
    0.253826,
    0.259947,
    0.266147,
    0.272431,
    0.278803,
    0.285266,
    0.291823,
    0.29848,
    0.305241,
    0.312109,
    0.319089,
    0.326185,
    0.333402,
    0.340746,
    0.348221,
    0.355832,
    0.363586,
    0.371487,
    0.379543,
    0.387759,
    0.396143,
    0.404703,
    0.413444,
    0.422377,
    0.43151,
    0.440851,
    0.450412,
    0.460202,
    0.470233,
    0.480518,
    0.49107,
    0.501902,
    0.513031,
    0.524474,
    0.536248,
    0.548373,
    0.560871,
    0.573766,
    0.587083,
    0.600852,
    0.615104,
    0.629875,
    0.645203,
    0.661132,
    0.677711,
    0.694996,
    0.71305,
    0.731943,
    0.751759,
    0.772591,
    0.79455,
    0.817764,
    0.842386,
    0.868598,
    0.896619,
    0.926717,
    0.959225,
    0.994564,
    1.03327,
    1.07607,
    1.1239,
    1.17814,
    1.24074,
    1.3148,
    1.40543,
    1.52228,
    1.687,
    1.96869
  };

  double nTaus;
  if ( !isInteger(percentage) ) {
    int x0 = int(percentage);
    int x1 = int(percentage) + 1;
    double y0 = nTauss[x0];
    double y1 = nTauss[x1];

    nTaus = (y1-y0)/(x1-x0) * (percentage - x0) + y0;
  }
  else {
    nTaus = nTauss[int(percentage)];
  }

  return nTaus;
}



