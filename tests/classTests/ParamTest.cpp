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



#ifndef PARAMTEST_CPP
#define PARAMTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../utils/Param.h"

namespace bu=boost::units;
namespace rrs=boost::units::rramspec;

using namespace std;

BOOST_AUTO_TEST_SUITE( testParam )

BOOST_AUTO_TEST_CASE( checkParam_StringConstructor )
{

  string myVoltageName("A voltage quantity");
  Param<rrs::volt_unit> myVoltage(myVoltageName);

  BOOST_CHECK_MESSAGE( !isInvalid(myVoltage.getName()),
                      "The name of the parameter"
                       << " was not correctly initialized."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !myVoltage.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( myVoltage.getName() == myVoltageName,
                      "The name of the parameter"
                       << " was not correctly assigned by contructor."
                       << "\nExpected: " << myVoltageName
                       << "\nGot: " << myVoltage.getName());

  BOOST_CHECK_MESSAGE( isInvalid(myVoltage.getQuantity()),
                      "The quantity of the parameter"
                       << " was not correctly initialized."
                       << " Should be invalid.");

  BOOST_CHECK_MESSAGE( myVoltage.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( myVoltage.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( myVoltage.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !myVoltage.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !myVoltage.isUserInput(),
                      "The user input flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

}

BOOST_AUTO_TEST_CASE( checkParam_makeSameParam )
{

  string myVoltageName("A voltage quantity");
  Param<rrs::volt_unit> myVoltage(myVoltageName);
  myVoltage = 2. * rrs::volts;

  auto sameVoltageInOtherObject = myVoltage.makeSameParam();

  BOOST_CHECK_MESSAGE( myVoltage.getName()
                       == sameVoltageInOtherObject.getName(),
                      "The name of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.getName()
                       << "\nGot: " << sameVoltageInOtherObject.getName());

  BOOST_CHECK_MESSAGE( myVoltage.hasInvalidName()
                       == sameVoltageInOtherObject.hasInvalidName(),
                       "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.hasInvalidName()
                       << "\nGot: "
                       << sameVoltageInOtherObject.hasInvalidName());

  BOOST_CHECK_MESSAGE( myVoltage.getQuantity()
                       == sameVoltageInOtherObject.getQuantity(),
                       "The quantity of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.getQuantity()
                       << "\nGot: " << sameVoltageInOtherObject.getQuantity());

  BOOST_CHECK_MESSAGE( myVoltage.hasInvalidQuantity()
                       == sameVoltageInOtherObject.hasInvalidQuantity(),
                       "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.hasInvalidQuantity()
                       << "\nGot: "
                       << sameVoltageInOtherObject.hasInvalidQuantity());

  BOOST_CHECK_MESSAGE( myVoltage.isInvalid()
                       == sameVoltageInOtherObject.isInvalid(),
                       "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.isInvalid()
                       << "\nGot: " << sameVoltageInOtherObject.isInvalid());

  BOOST_CHECK_MESSAGE( myVoltage.isDeclaredVariable()
                       == sameVoltageInOtherObject.isDeclaredVariable(),
                       "The declarared variable flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.isDeclaredVariable()
                       << "\nGot: "
                       << sameVoltageInOtherObject.isDeclaredVariable());

  BOOST_CHECK_MESSAGE( myVoltage.isOperationResult()
                       == sameVoltageInOtherObject.isOperationResult(),
                       "The result of operation flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.isOperationResult()
                       << "\nGot: "
                       << sameVoltageInOtherObject.isOperationResult());

  BOOST_CHECK_MESSAGE( myVoltage.isUserInput()
                       == sameVoltageInOtherObject.isUserInput(),
                       "The user input flag of the parameter"
                       << " was not correctly modified."
                       << "\nExpected: " << myVoltage.isUserInput()
                       << "\nGot: " << sameVoltageInOtherObject.isUserInput());
}

BOOST_AUTO_TEST_CASE( checkParam_makeOtherParam )
{


  Param<rrs::volt_unit> myVoltage("A voltage quantity");
  myVoltage = 2. * rrs::volts;

  string myOtherVoltageName("Another voltage quantity");
  // Deduce param type to create a new param
  auto myOtherVoltage = myVoltage.makeAnotherParam(myOtherVoltageName);

  BOOST_CHECK_MESSAGE( !isInvalid(myOtherVoltage.getName()),
                      "The name of the parameter"
                       << " was not correctly initialized."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !myOtherVoltage.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( myOtherVoltage.getName() == myOtherVoltageName,
                      "The name of the parameter"
                       << " was not correctly assigned by contructor."
                       << "\nExpected: " << myOtherVoltageName
                       << "\nGot: " << myOtherVoltage.getName());

  BOOST_CHECK_MESSAGE( isInvalid(myOtherVoltage.getQuantity()),
                      "The quantity of the parameter"
                       << " was not correctly initialized."
                       << " Should be invalid.");

  BOOST_CHECK_MESSAGE( myOtherVoltage.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( myOtherVoltage.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( myOtherVoltage.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !myOtherVoltage.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !myOtherVoltage.isUserInput(),
                      "The user input flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

}

BOOST_AUTO_TEST_CASE( checkParam_BasicAssignmentOperatorDouble )
{

  bu::quantity<rrs::volt_unit> expVoltage = 2.0 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;

  string myVoltageName("A voltage quantity");
  Param<rrs::volt_unit> myVoltage(myVoltageName);
  myVoltage = expVoltage;

  // Should have been modified
  gotVoltage = myVoltage.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !myVoltage.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !myVoltage.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = myVoltageName;
  gotStr = myVoltage.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !myVoltage.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( myVoltage.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !myVoltage.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !myVoltage.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

}

BOOST_AUTO_TEST_CASE( checkParam_BasicAssignmentOperatorParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 2.0 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;

  string myVoltageName("A voltage quantity");
  Param<rrs::volt_unit> myVoltage(myVoltageName);

  string mySecondVoltageName("Another voltage quantity");
  Param<rrs::volt_unit> mySecondVoltage(mySecondVoltageName);

  myVoltage = expVoltage;
  mySecondVoltage = myVoltage;

  // Should have been modified
  gotVoltage = mySecondVoltage.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = myVoltageName;
  gotStr = myVoltage.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !mySecondVoltage.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( mySecondVoltage.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");
}

BOOST_AUTO_TEST_CASE( checkParam_QuantityConstructor )
{

  bu::quantity<rrs::volt_unit> expVoltage = 12321 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  Param<rrs::volt_unit> myVoltage("A voltage quantity");

  auto mySecondVoltage = myVoltage.funcForTest();

  BOOST_CHECK_MESSAGE( isInvalid(mySecondVoltage.getName()),
                      "The name of the parameter"
                       << " was not correctly initialized."
                       << " Should be invalid.");

  BOOST_CHECK_MESSAGE( mySecondVoltage.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  gotVoltage = mySecondVoltage.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly initialized."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( mySecondVoltage.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( mySecondVoltage.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !mySecondVoltage.isUserInput(),
                      "The user input flag of the parameter"
                       << " was not correctly initialized."
                       << " Should be false.");
}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorParamParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 3 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage sum of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  Param<rrs::volt_unit> vB("Voltage at node B");
  Param<rrs::volt_unit> vC(vCName);

  vA = 1. * rrs::volts;
  vB = 2. * rrs::volts;
  vC = vA + vB;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorParamQuantity )
{

  bu::quantity<rrs::volt_unit> expVoltage = 6 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage sum of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  bu::quantity<rrs::volt_unit> vB;
  Param<rrs::volt_unit> vC(vCName);

  vA = 2. * rrs::volts;
  vB = 4. * rrs::volts;
  vC = vA + vB;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorQuantityParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 12 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage sum of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  bu::quantity<rrs::volt_unit> vB;
  Param<rrs::volt_unit> vC(vCName);

  vA = 4. * rrs::volts;
  vB = 8. * rrs::volts;
  vC = vB + vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorParamDimensionlessDouble )
{

  double expNumber = 48;
  double gotNumber;

  string expStr, gotStr;
  string nCName("The sum of two numbers");

  Param<rrs::dimensionless> nA("A number");
  double nB;
  Param<rrs::dimensionless> nC(nCName);

  nA = 32.;
  nB = 16.;
  nC = nA + nB;

  // Should have been modified
  gotNumber = nC.getQuantity();
  BOOST_CHECK_MESSAGE( gotNumber == expNumber,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expNumber
                       << "\nGot: " << gotNumber);

  BOOST_CHECK_MESSAGE( !isInvalid(gotNumber),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !nC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = nCName;
  gotStr = nC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !nC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( nC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !nC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorDoubleParamDimensionless )
{

  double expNumber = 96;
  double gotNumber;

  string expStr, gotStr;
  string nCName("The sum of two numbers");

  Param<rrs::dimensionless> nA("A number");
  double nB;
  Param<rrs::dimensionless> nC(nCName);

  nA = 64.;
  nB = 32.;
  nC = nB + nA;

  // Should have been modified
  gotNumber = nC.getQuantity();
  BOOST_CHECK_MESSAGE( gotNumber == expNumber,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expNumber
                       << "\nGot: " << gotNumber);

  BOOST_CHECK_MESSAGE( !isInvalid(gotNumber),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !nC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = nCName;
  gotStr = nC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !nC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( nC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !nC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionOperatorNullParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 64 * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("The same voltage");

  Param<rrs::volt_unit> vA("A voltage");
  Param<rrs::volt_unit> vC(vCName);

  vA = 64. * rrs::volts;
  vC = +vA;

  // Should have been modified - Actually not in this case
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorParamParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = -4. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage difference of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  Param<rrs::volt_unit> vB("Voltage at node B");
  Param<rrs::volt_unit> vC(vCName);

  vA = 4. * rrs::volts;
  vB = 8. * rrs::volts;
  vC = vA - vB;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorParamQuantity )
{

  bu::quantity<rrs::volt_unit> expVoltage = 4. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage difference of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  bu::quantity<rrs::volt_unit> vB;
  Param<rrs::volt_unit> vC(vCName);

  vA = 8. * rrs::volts;
  vB = 4. * rrs::volts;
  vC = vA - vB;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorQuantityParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = -8. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Voltage difference of nodes A and B");

  Param<rrs::volt_unit> vA("Voltage at node A");
  bu::quantity<rrs::volt_unit> vB;
  Param<rrs::volt_unit> vC(vCName);

  vA = 16. * rrs::volts;
  vB = 8. * rrs::volts;
  vC = vB - vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorParamDimensionlessDouble )
{

  double expNumber = 16;
  double gotNumber;

  string expStr, gotStr;
  string nCName("The difference between two numbers");

  Param<rrs::dimensionless> nA("A number");
  double nB;
  Param<rrs::dimensionless> nC(nCName);

  nA = 32.;
  nB = 16.;
  nC = nA - nB;

  // Should have been modified
  gotNumber = nC.getQuantity();
  BOOST_CHECK_MESSAGE( gotNumber == expNumber,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expNumber
                       << "\nGot: " << gotNumber);

  BOOST_CHECK_MESSAGE( !isInvalid(gotNumber),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !nC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = nCName;
  gotStr = nC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !nC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( nC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !nC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorDoubleParamDimensionless )
{

  double expNumber = -32.;
  double gotNumber;

  string expStr, gotStr;
  string nCName("The difference of two numbers");

  Param<rrs::dimensionless> nA("A number");
  double nB;
  Param<rrs::dimensionless> nC(nCName);

  nA = 64.;
  nB = 32.;
  nC = nB - nA;

  // Should have been modified
  gotNumber = nC.getQuantity();
  BOOST_CHECK_MESSAGE( gotNumber == expNumber,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expNumber
                       << "\nGot: " << gotNumber);

  BOOST_CHECK_MESSAGE( !isInvalid(gotNumber),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !nC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = nCName;
  gotStr = nC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !nC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( nC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !nC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !nC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionOperatorNullParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = -64. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("The same voltage but negative");

  Param<rrs::volt_unit> vA("A voltage");
  Param<rrs::volt_unit> vC(vCName);

  vA = 64. * rrs::volts;
  vC = -vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationOperatorParamParam )
{

  bu::quantity<rrs::watt_unit> expPower = 3 * 5 * rrs::watts;
  bu::quantity<rrs::watt_unit> gotPower;

  string expStr, gotStr;
  string pRName("Resulting power quantity");

  Param<rrs::volt_unit> vR("A voltage");
  Param<rrs::ampere_unit> iR("A current");
  Param<rrs::watt_unit> pR(pRName);

  vR = 3. * rrs::volts;
  iR = 5. * rrs::amperes;
  pR = vR * iR;

  // Should have been modified
  gotPower = pR.getQuantity();
  BOOST_CHECK_MESSAGE( gotPower == expPower,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expPower
                       << "\nGot: " << gotPower);

  BOOST_CHECK_MESSAGE( !isInvalid(gotPower),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !pR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = pRName;
  gotStr = pR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !pR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( pR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !pR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationOperatorParamQuantity )
{

  bu::quantity<rrs::watt_unit> expPower = 3 * 7 * rrs::watts;
  bu::quantity<rrs::watt_unit> gotPower;

  string expStr, gotStr;
  string pRName("Resulting power quantity");

  Param<rrs::volt_unit> vR("A voltage");
  bu::quantity<rrs::ampere_unit> iR;
  Param<rrs::watt_unit> pR(pRName);

  vR = 3. * rrs::volts;
  iR = 7. * rrs::amperes;
  pR = vR * iR;

  // Should have been modified
  gotPower = pR.getQuantity();
  BOOST_CHECK_MESSAGE( gotPower == expPower,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expPower
                       << "\nGot: " << gotPower);

  BOOST_CHECK_MESSAGE( !isInvalid(gotPower),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !pR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = pRName;
  gotStr = pR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !pR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( pR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !pR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationOperatorQuantityParam )
{

  bu::quantity<rrs::watt_unit> expPower = 3 * 11 * rrs::watts;
  bu::quantity<rrs::watt_unit> gotPower;

  string expStr, gotStr;
  string pRName("Resulting power quantity");

  Param<rrs::volt_unit> vR("A voltage");
  bu::quantity<rrs::ampere_unit> iR;
  Param<rrs::watt_unit> pR(pRName);

  vR = 3 * rrs::volts;
  iR = 11 * rrs::amperes;
  pR = iR * vR;

  // Should have been modified
  gotPower = pR.getQuantity();
  BOOST_CHECK_MESSAGE( gotPower == expPower,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expPower
                       << "\nGot: " << gotPower);

  BOOST_CHECK_MESSAGE( !isInvalid(gotPower),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !pR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = pRName;
  gotStr = pR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !pR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( pR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !pR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationOperatorParamDouble )
{

  bu::quantity<rrs::watt_unit> expPower = 3 * 13 * rrs::watts;
  bu::quantity<rrs::watt_unit> gotPower;

  string expStr, gotStr;
  string pRName("Resulting power quantity");

  double aDouble = 2.0;
  Param<rrs::watt_unit> pR(pRName);

  aDouble = 3;
  pR = 13 * rrs::watts;
  pR = pR * aDouble;

  // Should have been modified
  gotPower = pR.getQuantity();
  BOOST_CHECK_MESSAGE( gotPower == expPower,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expPower
                       << "\nGot: " << gotPower);

  BOOST_CHECK_MESSAGE( !isInvalid(gotPower),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !pR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = pRName;
  gotStr = pR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !pR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( pR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !pR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationOperatorDoubleParam )
{

  bu::quantity<rrs::watt_unit> expPower = 3 * 17 * rrs::watts;
  bu::quantity<rrs::watt_unit> gotPower;

  string expStr, gotStr;
  string pRName("Resulting power quantity");

  double aDouble = 2.0;
  Param<rrs::watt_unit> pR(pRName);

  aDouble = 3;
  pR = 17 * rrs::watts;
  pR = aDouble * pR;

  // Should have been modified
  gotPower = pR.getQuantity();
  BOOST_CHECK_MESSAGE( gotPower == expPower,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expPower
                       << "\nGot: " << gotPower);

  BOOST_CHECK_MESSAGE( !isInvalid(gotPower),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !pR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = pRName;
  gotStr = pR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !pR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( pR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !pR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !pR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionOperatorParamParam )
{

  bu::quantity<rrs::ampere_unit> expCurrent = 3. / 5. * rrs::amperes;
  bu::quantity<rrs::ampere_unit> gotCurrent;

  string expStr, gotStr;
  string iRName("Resulting current quantity");

  Param<rrs::volt_unit> vR("A voltage");
  Param<rrs::ohm_unit> rR("A resistance");
  Param<rrs::ampere_unit> iR(iRName);

  vR = 3 * rrs::volts;
  rR = 5 * rrs::ohms;
  iR = vR / rR;

  // Should have been modified
  gotCurrent = iR.getQuantity();
  BOOST_CHECK_MESSAGE( gotCurrent == expCurrent,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << gotCurrent);

  BOOST_CHECK_MESSAGE( !isInvalid(gotCurrent),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !iR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = iRName;
  gotStr = iR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !iR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( iR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !iR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionOperatorParamQuantity )
{

  bu::quantity<rrs::ampere_unit> expCurrent = 3. / 7. * rrs::amperes;
  bu::quantity<rrs::ampere_unit> gotCurrent;

  string expStr, gotStr;
  string iRName("Resulting current quantity");

  Param<rrs::volt_unit> vR("A voltage");
  bu::quantity<rrs::ohm_unit> rR;
  Param<rrs::ampere_unit> iR(iRName);

  vR = 3 * rrs::volts;
  rR = 7 * rrs::ohms;
  iR = vR / rR;

  // Should have been modified
  gotCurrent = iR.getQuantity();
  BOOST_CHECK_MESSAGE( gotCurrent == expCurrent,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << gotCurrent);

  BOOST_CHECK_MESSAGE( !isInvalid(gotCurrent),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !iR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = iRName;
  gotStr = iR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !iR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( iR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !iR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionOperatorQuantityParam )
{

  bu::quantity<rrs::ampere_unit> expCurrent = 3. / 11. * rrs::amperes;
  bu::quantity<rrs::ampere_unit> gotCurrent;

  string expStr, gotStr;
  string iRName("Resulting current quantity");

  bu::quantity<rrs::volt_unit> vR;
  Param<rrs::ohm_unit> rR("A resistance");
  Param<rrs::ampere_unit> iR(iRName);

  vR = 3 * rrs::volts;
  rR = 11 * rrs::ohms;
  iR = vR / rR;

  // Should have been modified
  gotCurrent = iR.getQuantity();
  BOOST_CHECK_MESSAGE( gotCurrent == expCurrent,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << gotCurrent);

  BOOST_CHECK_MESSAGE( !isInvalid(gotCurrent),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !iR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = iRName;
  gotStr = iR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !iR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( iR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !iR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionOperatorParamDouble )
{

  bu::quantity<rrs::ampere_unit> expCurrent = 3. / 13. * rrs::amperes;
  bu::quantity<rrs::ampere_unit> gotCurrent;

  string expStr, gotStr;
  string iRName("Resulting current quantity");

  double aDouble;
  Param<rrs::ampere_unit> iR(iRName);

  iR = 3 * rrs::ampere;
  aDouble = 13;
  iR = iR / aDouble;

  // Should have been modified
  gotCurrent = iR.getQuantity();
  BOOST_CHECK_MESSAGE( gotCurrent == expCurrent,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << gotCurrent);

  BOOST_CHECK_MESSAGE( !isInvalid(gotCurrent),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !iR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = iRName;
  gotStr = iR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !iR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( iR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !iR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionOperatorDoubleParam )
{

  bu::quantity<rrs::hertz_unit> expFrequency = 3. / 17. * rrs::hertz;
  bu::quantity<rrs::hertz_unit> gotFrequency;

  string expStr, gotStr;
  string fName("Resulting frequency quantity");

  double aDouble;
  Param<rrs::second_unit> t("Three periods");
  Param<rrs::hertz_unit> f(fName);

  aDouble = 3;
  t = 17 * rrs::seconds;
  f = aDouble / t;

  // Should have been modified
  gotFrequency = f.getQuantity();
  BOOST_CHECK_MESSAGE( gotFrequency == expFrequency,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expFrequency
                       << "\nGot: " << gotFrequency);

  BOOST_CHECK_MESSAGE( !isInvalid(gotFrequency),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !f.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !f.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = fName;
  gotStr = f.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !f.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( f.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !f.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !f.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MixOfOperators )
{

  bu::quantity<rrs::ampere_unit> expCurrent = -256. / 85. * rrs::amperes;
  bu::quantity<rrs::ampere_unit> gotCurrent;

  string expStr, gotStr;
  string iRName("A current");

  Param<rrs::volt_unit> vR("A voltage");
  Param<rrs::ohm_unit> rR("A resistance");
  bu::quantity<rrs::dimensionless> dless(2.);
  Param<rrs::ampere_unit> iR(iRName);

  vR = 3. * rrs::volts;
  rR = 5. * rrs::ohms;
  iR = ( +vR + (vR+vR) + (vR+(2.*rrs::volt)) + (vR/vR+2)*vR + (2+vR/vR)*vR ) *
       ( -vR + (vR-vR) + (vR-(2.*rrs::volt)) + (vR/vR-2)*vR + (2-vR/vR)*vR ) /
       (       (vR*vR) + (vR*(2.*rrs::volt)) + (vR*2)*vR    + (2*vR)*vR    ) *
       (       (vR/vR) + (vR/(dless)/vR)     + (vR/2)/vR    + (2/vR)*vR    ) *
       vR / rR;

  // Should have been modified
  gotCurrent = iR.getQuantity();
  BOOST_CHECK_MESSAGE( gotCurrent == expCurrent,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expCurrent
                       << "\nGot: " << gotCurrent);

  BOOST_CHECK_MESSAGE( !isInvalid(gotCurrent),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !iR.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = iRName;
  gotStr = iR.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !iR.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( iR.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !iR.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !iR.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionAssignmentOperatorParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 384. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  Param<rrs::volt_unit> vA("Voltage at node A");
  Param<rrs::volt_unit> vC(vCName);

  vA = 128. * rrs::volts;
  vC = 256. * rrs::volts;
  vC += vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionAssignmentOperatorQuantity )
{

  bu::quantity<rrs::volt_unit> expVoltage = 1536. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  bu::quantity<rrs::volt_unit> vA;
  Param<rrs::volt_unit> vC(vCName);

  vA = 512. * rrs::volts;
  vC = 1024. * rrs::volts;
  vC += vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_AdditionAssignmentOperatorDouble )
{

  bu::quantity<rrs::dimensionless> expVoltage = 6144.;
  bu::quantity<rrs::dimensionless> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting number");

  double vA;
  Param<rrs::dimensionless> vC(vCName);

  vA = 2048.;
  vC = 4096.;
  vC += vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_IncrementOperatorParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 4. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  Param<rrs::volt_unit> vC(vCName);

  vC = 2. * rrs::volts;
  vC++;
  ++vC;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionAssignmentOperatorParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = -128. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  Param<rrs::volt_unit> vA("Voltage at node A");
  Param<rrs::volt_unit> vC(vCName);

  vA = 256. * rrs::volts;
  vC = 128. * rrs::volts;
  vC -= vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionAssignmentOperatorQuantity )
{

  bu::quantity<rrs::volt_unit> expVoltage = -512. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  bu::quantity<rrs::volt_unit> vA;
  Param<rrs::volt_unit> vC(vCName);

  vA = 1024. * rrs::volts;
  vC = 512. * rrs::volts;
  vC -= vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_SubtractionAssignmentOperatorDouble )
{

  bu::quantity<rrs::dimensionless> expVoltage = -2048.;
  bu::quantity<rrs::dimensionless> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting number");

  double vA;
  Param<rrs::dimensionless> vC(vCName);

  vA = 4096.;
  vC = 2048.;
  vC -= vA;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DecrementOperatorParam )
{

  bu::quantity<rrs::volt_unit> expVoltage = 8. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  Param<rrs::volt_unit> vC(vCName);

  vC = 10. * rrs::volts;
  vC--;
  --vC;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_MultiplicationAssignmentOperatorDouble )
{

  bu::quantity<rrs::volt_unit> expVoltage = 3. * 5. * 7. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  double aDouble;
  bu::quantity<rrs::dimensionless> aDimensionless;
  Param<rrs::volt_unit> vC(vCName);

  aDouble = 3.;
  aDimensionless = 5.;
  vC = 7. * rrs::volts;
  vC *= aDouble;
  vC *= aDimensionless;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( gotVoltage == expVoltage,
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}

BOOST_AUTO_TEST_CASE( checkParam_DivisionAssignmentOperatorDouble )
{

  bu::quantity<rrs::volt_unit> expVoltage = 7. / 5. / 3. * rrs::volts;
  bu::quantity<rrs::volt_unit> gotVoltage;

  string expStr, gotStr;
  string vCName("Resulting voltage");

  double aDouble;
  bu::quantity<rrs::dimensionless> aDimensionless;
  Param<rrs::volt_unit> vC(vCName);

  aDouble = 3.;
  aDimensionless = 5.;
  vC = 7. * rrs::volts;
  vC /= aDouble;
  vC /= aDimensionless;

  // Should have been modified
  gotVoltage = vC.getQuantity();
  BOOST_CHECK_MESSAGE( areEqual(gotVoltage, expVoltage),
                      "The quantity of the parameter"
                       << " was not correctly assigned."
                       << "\nExpected: " << expVoltage
                       << "\nGot: " << gotVoltage);

  BOOST_CHECK_MESSAGE( !isInvalid(gotVoltage),
                      "The quantity of the parameter"
                       << " was not correctly modified."
                       << " Should be valid.");

  BOOST_CHECK_MESSAGE( !vC.hasInvalidQuantity(),
                      "The invalid quantity flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isInvalid(),
                      "The invalidation flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");


  // Should not have been modified
  expStr = vCName;
  gotStr = vC.getName();
  BOOST_CHECK_MESSAGE( gotStr == expStr,
                      "The name of the parameter"
                       << " should not have been modified."
                       << "\nExpected: " << expStr
                       << "\nGot: " << gotStr);

  BOOST_CHECK_MESSAGE( !vC.hasInvalidName(),
                      "The invalid name flag of the parameter"
                       << " was not correctly modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( vC.isDeclaredVariable(),
                      "The declarared variable flag of the parameter"
                       << " should not have been modified."
                       << " Should be true.");

  BOOST_CHECK_MESSAGE( !vC.isOperationResult(),
                      "The result of operation flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");

  BOOST_CHECK_MESSAGE( !vC.isUserInput(),
                      "The user input flag of the parameter"
                       << " should not have been modified."
                       << " Should be false.");


}


BOOST_AUTO_TEST_SUITE_END()

#endif // PARAMTEST_CPP
