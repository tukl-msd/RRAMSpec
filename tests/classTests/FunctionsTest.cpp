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



#ifndef FUNCTIONSTEST_CPP
#define FUNCTIONSTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../utils/functions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE( testFunctions )

BOOST_AUTO_TEST_CASE( checkFunctions_validityChecks )
{
  BOOST_CHECK_MESSAGE(isValid((ebool)0), "isValid((ebool)0) should be true.");
  BOOST_CHECK_MESSAGE(isValid((ebool)1), "isValid((ebool)1) should be true.");
  BOOST_CHECK_MESSAGE(isValid(0.), "isValid(0.) should be true.");
  BOOST_CHECK_MESSAGE(isValid(1.), "isValid(1.) should be true.");
  BOOST_CHECK_MESSAGE(isValid(-1.), "isValid(-1.) should be true.");
  BOOST_CHECK_MESSAGE(isValid(1./0.), "isValid(infinity) should be true.");
  BOOST_CHECK_MESSAGE(isValid(-1/0.), "isValid(-infinity) should be true.");
  BOOST_CHECK_MESSAGE(isValid(NAN), "isValid(NAN) should be true.");
  BOOST_CHECK_MESSAGE(isValid((const char*)""),
                      "isValid((const char*)\"\") should be true.");
  BOOST_CHECK_MESSAGE(isValid((string)""),
                      "isValid((string)\"\") should be true.");
  BOOST_CHECK_MESSAGE(isValid((const char*)"valid"),
                      "isValid((const char*)\"valid\") should be true.");
  BOOST_CHECK_MESSAGE(isValid((string)"valid"),
                      "isValid((string)\"valid\") should be true.");
  BOOST_CHECK_MESSAGE(isValid((const char*)NULL),
                      "isValid((const char*)NULL) should be true.");
  bu::quantity<rrs::volt_unit> validQuantity(0. * rrs::volts);
  BOOST_CHECK_MESSAGE(isValid(validQuantity),
                      "isValid(quantity = 0.) should be true.");
  validQuantity = 1./0. * rrs::volts;
  BOOST_CHECK_MESSAGE(isValid(validQuantity),
                      "isValid(quantity = inf) should be true.");
  validQuantity = 0./0. * rrs::volts;
  BOOST_CHECK_MESSAGE(isValid(validQuantity),
                      "isValid(quantity = nan) should be true.");

  BOOST_CHECK_MESSAGE(areValid(
                        (ebool)0,
                        (ebool)1,
                        0.,
                        1.,
                        -1.,
                        1./0.,
                        -1./0.,
                        NAN,
                        (const char*)"",
                        (string)"",
                        (const char*)"valid",
                        (string)"valid",
                        (const char*)NULL,
                        validQuantity
                        ),
                      "areValid(arg1, ..., argn) should have the same "
                      "behavior as isValid(arg1) && ... && isValid(argn)"
                      " In this case, it should be true.");

  BOOST_CHECK_MESSAGE(!areValid(
                        INVALID_DOUBLE,
                        (ebool)0,
                        (ebool)1,
                        0.,
                        1.,
                        -1.,
                        1./0.,
                        -1./0.,
                        NAN,
                        (const char*)"",
                        (string)"",
                        (const char*)"valid",
                        (string)"valid",
                        (const char*)NULL,
                        validQuantity
                        ),
                      "areValid(arg1, ..., argn) should have the same "
                      "behavior as isValid(arg1) && ... && isValid(argn)."
                      " In this case, it should be false.");

  BOOST_CHECK_MESSAGE(!isValid((ebool)3),
                      "isValid((ebool)3) should be false.");
  BOOST_CHECK_MESSAGE(!isValid(INVALID_EBOOL),
                      "isValid(INVALID_EBOOL) should be false.");
  BOOST_CHECK_MESSAGE(!isValid(INVALID_DOUBLE),
                      "isValid(INVALID_DOUBLE) should be false.");
  BOOST_CHECK_MESSAGE(!isValid(INVALID_C_STRING),
                      "isValid(INVALID_C_STRING) should be false.");
  BOOST_CHECK_MESSAGE(!isValid(INVALID_STRING),
                      "isValid(INVALID_STRING) should be false.");
  bu::quantity<rrs::volt_unit> invalidQuantity(INVALID_DOUBLE * rrs::volts);
  BOOST_CHECK_MESSAGE(!isValid(invalidQuantity),
                      "isValid(quantity = invalid) should be false.");

  BOOST_CHECK_MESSAGE(!areValid(INVALID_EBOOL,
                                INVALID_DOUBLE,
                                INVALID_C_STRING,
                                INVALID_STRING,
                                invalidQuantity),
                      "areValid(arg1, ..., argn) should have the same "
                      "behavior as isValid(arg1) && ... && isValid(argn)."
                      " In this case, it should be false.");


}

BOOST_AUTO_TEST_CASE( checkFunctions_invalidityChecks )
{
  BOOST_CHECK_MESSAGE(!isInvalid((ebool)0),
                      "isInvalid((ebool)0) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((ebool)1),
                      "isInvalid((ebool)1) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(0.), "isInvalid(0.) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(1.), "isInvalid(1.) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(-1.), "isInvalid(-1.) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(1./0.), "isInvalid(inf) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(-1/0.), "isInvalid(-inf) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid(NAN), "isInvalid(NAN) should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((const char*)""),
                      "isInvalid((const char*)\"\") should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((string)""),
                      "isInvalid((string)\"\") should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((const char*)"valid"),
                      "isInvalid((const char*)\"valid\") should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((string)"valid"),
                      "isInvalid((string)\"valid\") should be false.");
  BOOST_CHECK_MESSAGE(!isInvalid((const char*)NULL),
                      "isInvalid((const char*)NULL) should be false.");
  bu::quantity<rrs::volt_unit> validQuantity(0. * rrs::volts);
  BOOST_CHECK_MESSAGE(!isInvalid(validQuantity),
                      "isInvalid(quantity = 0.) should be false.");
  validQuantity = 1./0. * rrs::volts;
  BOOST_CHECK_MESSAGE(!isInvalid(validQuantity),
                      "isInvalid(quantity = inf) should be false.");
  validQuantity = 0./0. * rrs::volts;
  BOOST_CHECK_MESSAGE(!isInvalid(validQuantity),
                      "isInvalid(quantity = nan) should be false.");

  BOOST_CHECK_MESSAGE(!areInvalid(
                        (ebool)0,
                        (ebool)1,
                        0.,
                        1.,
                        -1.,
                        1./0.,
                        -1./0.,
                        NAN,
                        (const char*)"",
                        (string)"",
                        (const char*)"valid",
                        (string)"valid",
                        (const char*)NULL,
                        validQuantity
                        ),
                      "areInvalid(arg1, ..., argn) should have the same "
                      "behavior as isInvalid(arg1) && ... && isInvalid(argn)"
                      " In this case, it should be false.");

  BOOST_CHECK_MESSAGE(!areInvalid(
                        INVALID_DOUBLE,
                        (ebool)0,
                        (ebool)1,
                        0.,
                        1.,
                        -1.,
                        1./0.,
                        -1./0.,
                        NAN,
                        (const char*)"",
                        (string)"",
                        (const char*)"valid",
                        (string)"valid",
                        (const char*)NULL,
                        validQuantity
                        ),
                      "areInvalid(arg1, ..., argn) should have the same "
                      "behavior as isInvalid(arg1) && ... && isInvalid(argn)."
                      " In this case, it should be false.");

  BOOST_CHECK_MESSAGE(isInvalid((ebool)3),
                      "isInvalid((ebool)3) should be true.");
  BOOST_CHECK_MESSAGE(isInvalid(INVALID_EBOOL),
                      "isInvalid(INVALID_EBOOL) should be true.");
  BOOST_CHECK_MESSAGE(isInvalid(INVALID_DOUBLE),
                      "isInvalid(INVALID_DOUBLE) should be true.");
  BOOST_CHECK_MESSAGE(isInvalid(INVALID_C_STRING),
                      "isInvalid(INVALID_C_STRING) should be true.");
  BOOST_CHECK_MESSAGE(isInvalid(INVALID_STRING),
                      "isInvalid(INVALID_STRING) should be true.");
  bu::quantity<rrs::volt_unit> invalidQuantity(INVALID_DOUBLE * rrs::volts);
  BOOST_CHECK_MESSAGE(isInvalid(invalidQuantity),
                      "isInvalid(quantity = invalid) should be true.");

  BOOST_CHECK_MESSAGE(areInvalid(INVALID_EBOOL,
                                INVALID_DOUBLE,
                                INVALID_C_STRING,
                                INVALID_STRING,
                                invalidQuantity),
                      "areInvalid(arg1, ..., argn) should have the same "
                      "behavior as isInvalid(arg1) && ... && isInvalid(argn)."
                      " In this case, it should be true.");


}

BOOST_AUTO_TEST_CASE( checkFunctions_invalidation )
{
  ebool myEbool = true;
  string myString = "this is a valid string!";
  double myDouble = 0.;
  bu::quantity<rrs::nanovolt_unit> myQuantity = 0. * rrs::nanovolts;

  BOOST_CHECK_MESSAGE(isValid(myEbool),
                      "myEbool should be valid at this point.");
  BOOST_CHECK_MESSAGE(isValid(myString),
                      "myString should be valid at this point.");
  BOOST_CHECK_MESSAGE(isValid(myDouble),
                      "myDouble should be valid at this point.");
  BOOST_CHECK_MESSAGE(isValid(myQuantity),
                      "myQuantity should be valid at this point.");

  invalidate(&myEbool);
  invalidate(&myString);
  invalidate(&myDouble);
  invalidate(&myQuantity);

  BOOST_CHECK_MESSAGE(isInvalid(myEbool),
                      "myEbool should be invalid at this point.");
  BOOST_CHECK_MESSAGE(isInvalid(myString),
                      "myString should be invalid at this point.");
  BOOST_CHECK_MESSAGE(isInvalid(myDouble),
                      "myDouble should be invalid at this point.");
  BOOST_CHECK_MESSAGE(isInvalid(myQuantity),
                      "myQuantity should be invalid at this point.");

}

BOOST_AUTO_TEST_CASE( checkFunctions_isEqual )
{
  double d1;
  double d2;

  // Evident results for relative tolerance 1e-6
  d1 = 0;
  d2 = 0;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1./0.;
  d2 = 2./0.;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = -1./0.;
  d2 = -2./0.;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1;
  d2 = 1;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1;
  d2 = 1 + 1e-15;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1 + 1e-15;
  d2 = 1;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e40;
  d2 = 1e40 + 1e20;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e40 + 1e20;
  d2 = 1e40;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-10;
  d2 = 1e-10 + 1e-20;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-10 + 1e-20;
  d2 = 1e-10;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1./0.;
  d2 = -2./0.;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1./0.;
  d2 = 2./1.;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1./1.;
  d2 = 2./0.;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 0;
  d2 = 1;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1;
  d2 = 1.001;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e27;
  d2 = 1.001e27;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e-10;
  d2 = 1.001e-10;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");



  // "Very near zero" values with respect to the relative tolerance
  // If the absolute difference between d1 and d2 is "very near zero",
  //  they are equal without regards to the relative difference
  d1 = 1e-20;
  d2 = 1e-20 + 1e-25;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-20 + 1e-25;
  d2 = 1e-20;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-25;
  d2 = 0;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 0;
  d2 = 1e-25;
  BOOST_CHECK_MESSAGE( areEqual(d1, d2),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  // "Very near zero" depends on the relative tolerance
  d1 = 1e-20;
  d2 = 1e-20 + 1e-25;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2, 1e-12),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ", " << 1e-30 << ")"
                       " should be false.");

  d1 = 1e-20 + 1e-25;
  d2 = 1e-20;
  BOOST_CHECK_MESSAGE( !areEqual(d1, d2, 1e-12),
                       setprecision(40) <<
                       "isEqual(" << d1 << ", " << d2 << ", " << 1e-30 << ")"
                       " should be false.");


}

BOOST_AUTO_TEST_CASE( checkFunctions_fastIsEqual )
{
  double d1;
  double d2;

  // Evident results for relative tolerance 1e-6
  d1 = 0.;
  d2 = 0.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1.;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1.;
  d2 = 1 + 1e-15;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1 + 1e-15;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e40;
  d2 = 1e40 + 1e20;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e40 + 1e20;
  d2 = 1e40;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-10;
  d2 = 1e-10 + 1e-20;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1e-10 + 1e-20;
  d2 = 1e-10;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1.;
  d2 = 1./0.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");
  d1 = 1.;
  d2 = -1./0.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");
  d1 = 0.;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1.;
  d2 = 1.001;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e27;
  d2 = 1.001e27;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e-10;
  d2 = 1.001e-10;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");


  // "Very near zero" are not quite 0, so are infinitly greater than 0

  d1 = 1e-20;
  d2 = 1e-20 + 1e-25;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e-20 + 1e-25;
  d2 = 1e-20;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1e-25;
  d2 = 0;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 0;
  d2 = 1e-25;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");


  // The greater the resolution,
  //  the higher the inbalance from parameter order
  d1 = 3.;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2, 1),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1.;
  d2 = 3.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2, 1),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  // DO NOT USE WITH INFINITY
  // If +inf and not_inf, returns false
  // If -inf and not_inf, returns false
  // If +inf and +inf, returns false
  // If -inf and -inf, returns false
  // If +inf and -inf, returns true
  // If -inf and +inf, returns true
  d1 = 1./0.;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");
  d1 = -1./0.;
  d2 = 1.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");
  d1 = 1./0.;
  d2 = 2./0.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = 1./0.;
  d2 = 2./0.;
  BOOST_CHECK_MESSAGE( !fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be false.");

  d1 = -2./0.;
  d2 = 1./0.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");

  d1 = 1./0.;
  d2 = -2./0.;
  BOOST_CHECK_MESSAGE( fastAreEqual(d1, d2),
                       setprecision(40) <<
                       "fastIsEqual(" << d1 << ", " << d2 << ")"
                       " should be true.");


}

BOOST_AUTO_TEST_CASE( checkFunctions_isInteger )
{

  BOOST_CHECK_MESSAGE(isInteger(0.), "isInteger(0.) should be true.");
  BOOST_CHECK_MESSAGE(isInteger(1.), "isInteger(1.) should be true.");
  BOOST_CHECK_MESSAGE(isInteger(1e308), "isInteger(1e308) should be true.");

  BOOST_CHECK_MESSAGE(!isInteger(0./0.), "isInteger(0./0.) should be false.");
  BOOST_CHECK_MESSAGE(!isInteger(0.1), "isInteger(0.1) should be false.");
  BOOST_CHECK_MESSAGE(!isInteger(5e-324),
                      "isInteger(5e-324) should be false.");


  BOOST_CHECK_MESSAGE(!isInteger(1e309),
                      "isInteger(1e309) should be false for double precison.");
  BOOST_CHECK_MESSAGE(isInteger(2e-324),
                      "isInteger(2e-324) should be true for double precison.");

//  // This test takes too long to run (several years?!)
//  //  might be enabled for very thorough testing
//  // Assuming IEEE 64-bit double
//  // Greatest integer such as all smaller integers can be
//  // exactly represented in a double (2^53)
//  double maxInt = 9007199254740992;
//  double lastVal = INVALID_DOUBLE;
//  double power = 0;
//  for ( double val = 0; val < maxInt; ++val) {
//    BOOST_CHECK_MESSAGE(isInteger(val),
//                        setprecision(60) <<
//                        "isInteger("
//                        << val
//                        << ") should be true.");

//    BOOST_CHECK_MESSAGE(!( val == lastVal ),
//                        "The number 9007199254740992 (2^53)"
//                        << " should be representable in a double variable,"
//                        << " as should all integers smaller than it."
//                        << " Last integer was "
//                        << val);

//    if ( val == lastVal ) {
//      break;
//    }

//    lastVal = val;
//  }

}

BOOST_AUTO_TEST_CASE( checkFunctions_isPowerOfTwo )
{

  BOOST_CHECK_MESSAGE(isPowerOfTwo(1.),
                      "isPowerOfTwo(1.) should be true.");
  BOOST_CHECK_MESSAGE(isPowerOfTwo(2.),
                      "isPowerOfTwo(2.) should be true.");
  BOOST_CHECK_MESSAGE(isPowerOfTwo(pow(2,1023)),
                      "isPowerOfTwo(pow(2,1023)) should be true.");
  BOOST_CHECK_MESSAGE(isPowerOfTwo(pow(2,-1)),
                      "isPowerOfTwo(pow(2,-1)) should be true.");
  BOOST_CHECK_MESSAGE(isPowerOfTwo(pow(2,-1023)),
                      "isPowerOfTwo(pow(2,-1023)) should be true.");

  BOOST_CHECK_MESSAGE(!isPowerOfTwo(0.),
                      "isPowerOfTwo(0.) should be false.");
  BOOST_CHECK_MESSAGE(!isPowerOfTwo(0.1),
                      "isPowerOfTwo(0.1) should be false.");
  BOOST_CHECK_MESSAGE(!isPowerOfTwo(3.),
                      "isPowerOfTwo(3.) should be false.");
  BOOST_CHECK_MESSAGE(!isPowerOfTwo(pow(2,52)+1),
                      "isPowerOfTwo(pow(2,52)+1) should be false.");
  BOOST_CHECK_MESSAGE(!isPowerOfTwo(0./0.),
                      "isPowerOfTwo(0./0.) should be false.");

  BOOST_CHECK_MESSAGE(isPowerOfTwo(pow(2,53)+1),
              "isPowerOfTwo(pow(2,53)+1) should be true for double precison.");
  BOOST_CHECK_MESSAGE(!isPowerOfTwo(pow(2,1024)),
              "isPowerOfTwo(pow(2,1204) should be false for double precison.");

}

BOOST_AUTO_TEST_CASE( testSingleRCTaus )
{
  vector<double> percetages = {0, 1, 1.5, 63.2, 99};
  vector<double> nTausExpecteds = {0, 0.0101, 0.0151, 1, 4.61};
  double nTausGot;

  for (auto i = 0; i < percetages.size(); ++i) {
    nTausGot = round(tausToPercentSingleRC(percetages.at(i)), 3);
    BOOST_CHECK_MESSAGE( round(nTausGot, 3) == nTausExpecteds.at(i),
                        "Number of taus needed to reach "
                        + to_string(percetages.at(i)) +
                        "\% on single RC delay"
                        " different from the expected."
                        << "\nExpected around: " << nTausExpecteds.at(i)
                        << "\nGot: " << nTausGot);
  }
}

BOOST_AUTO_TEST_CASE( testLumpedRCTaus )
{
  vector<double> percetages = {0, 1, 1.5, 63.2, 99};
  vector<double> nTausExpecteds = {0, 0.0636, 0.0696, 0.504, 1.97};
  double nTausGot;

  for (auto i = 0; i < percetages.size(); ++i) {
    nTausGot = round(tausToPercentLumpedRC(percetages.at(i)), 3);
    BOOST_CHECK_MESSAGE( round(nTausGot, 3) == nTausExpecteds.at(i),
                        "Number of taus needed to reach "
                        + to_string(percetages.at(i)) +
                        "\% on single RC delay"
                        " different from the expected."
                        << "\nExpected around: " << nTausExpecteds.at(i)
                        << "\nGot: " << nTausGot);
  }
}

BOOST_AUTO_TEST_CASE( checkFunctions_findLowestGreater )
{

  double val;
  size_t expectedValue;
  size_t gotValue;

  vector<double> testVec{-1, 0, 1, 1.5, 2, 3, 5, 10};

  val = -2;
  expectedValue = 0;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = -1;
  expectedValue = 1;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = -0.1;
  expectedValue = 1;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = -0;
  expectedValue = 2;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = 0;
  expectedValue = 2;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = 1.1;
  expectedValue = 3;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = 5;
  expectedValue = 7;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = 10;
  expectedValue = 8;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = 11;
  expectedValue = 8;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  testVec.push_back(numeric_limits<double>::infinity());

  val = 11;
  expectedValue = 8;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);

  val = numeric_limits<double>::infinity();
  expectedValue = 9;
  gotValue = findLowestGreater(testVec, val);
  BOOST_CHECK_MESSAGE( gotValue == expectedValue,
                       "findLowestGreater() returned a value"
                       << " different for the expected."
                       << "\nExpected: " << expectedValue
                       << "\nGot: " << gotValue);


}

BOOST_AUTO_TEST_CASE( checkFunctions_round )
{

  double exactDouble;
  double expectedDouble;
  double gotDouble;


  bu::quantity<rrs::kilovolt_unit> exactQuantity;
  bu::quantity<rrs::kilovolt_unit> expectedQuantity;
  bu::quantity<rrs::kilovolt_unit> gotQuantity;

  size_t nSigFigs;

  nSigFigs = 6;

  exactDouble = 0.;
  expectedDouble = 0.;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1./0.;
  expectedDouble = 1./0.;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = -1./0.;
  expectedDouble = -1./0.;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 123456789;
  expectedDouble = 123457000;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12345678.9;
  expectedDouble = 12345700;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1234567.89;
  expectedDouble = 1234570;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 123456.789;
  expectedDouble = 123457;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12345.6789;
  expectedDouble = 12345.7;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1234.56789;
  expectedDouble = 1234.57;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 123.456789;
  expectedDouble = 123.457;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12.3456789;
  expectedDouble = 12.3457;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1.23456789;
  expectedDouble = 1.23457;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = .123456789;
  expectedDouble = .123457;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);


  nSigFigs = 3;

  exactDouble = 123456789;
  expectedDouble = 123000000;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12345678.9;
  expectedDouble = 12300000;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1234567.89;
  expectedDouble = 1230000;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 123456.789;
  expectedDouble = 123000;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12345.6789;
  expectedDouble = 12300;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1234.56789;
  expectedDouble = 1230;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 123.456789;
  expectedDouble = 123;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 12.3456789;
  expectedDouble = 12.3;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = 1.23456789;
  expectedDouble = 1.23;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);

  exactDouble = .123456789;
  expectedDouble = .123;
  gotDouble = round(exactDouble, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotDouble, expectedDouble),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactDouble
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedDouble
                       << "\nGot: " << gotDouble);


  nSigFigs = 6;

  exactQuantity = 123456789 * rrs::kilovolts;
  expectedQuantity = 123457000 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12345678.9 * rrs::kilovolts;
  expectedQuantity = 12345700 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1234567.89 * rrs::kilovolts;
  expectedQuantity = 1234570 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 123456.789 * rrs::kilovolts;
  expectedQuantity = 123457 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12345.6789 * rrs::kilovolts;
  expectedQuantity = 12345.7 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1234.56789 * rrs::kilovolts;
  expectedQuantity = 1234.57 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 123.456789 * rrs::kilovolts;
  expectedQuantity = 123.457 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12.3456789 * rrs::kilovolts;
  expectedQuantity = 12.3457 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1.23456789 * rrs::kilovolts;
  expectedQuantity = 1.23457 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = .123456789 * rrs::kilovolts;
  expectedQuantity = .123457 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);




  nSigFigs = 3;

  exactQuantity = 123456789 * rrs::kilovolts;
  expectedQuantity = 123000000 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12345678.9 * rrs::kilovolts;
  expectedQuantity = 12300000 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1234567.89 * rrs::kilovolts;
  expectedQuantity = 1230000 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 123456.789 * rrs::kilovolts;
  expectedQuantity = 123000 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12345.6789 * rrs::kilovolts;
  expectedQuantity = 12300 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1234.56789 * rrs::kilovolts;
  expectedQuantity = 1230 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 123.456789 * rrs::kilovolts;
  expectedQuantity = 123 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 12.3456789 * rrs::kilovolts;
  expectedQuantity = 12.3 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = 1.23456789 * rrs::kilovolts;
  expectedQuantity = 1.23 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

  exactQuantity = .123456789 * rrs::kilovolts;
  expectedQuantity = .123 * rrs::kilovolts;
  gotQuantity = round(exactQuantity, nSigFigs);
  BOOST_CHECK_MESSAGE( areEqual(gotQuantity, expectedQuantity),
                       setprecision(10)
                       << "round(Exact, Sig. figures) returned a value"
                       << " different for the expected."
                       << "\nExact: " << exactQuantity
                       << "\nSig. figures: " << nSigFigs
                       << "\nExpected: " << expectedQuantity
                       << "\nGot: " << gotQuantity);

}

BOOST_AUTO_TEST_SUITE_END()

#endif // FUNCTIONSTEST_CPP
