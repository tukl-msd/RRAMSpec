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

#ifndef PARAM_H
#define PARAM_H

/* This class implements a parameter class that represent physical quantities.
 * The main attribute of the class is the quantity itself, consisting of a
 * value - or magnitude - and a unit.
 * Each parameter must have a name, which briefly describes what is represents.
 * The name is mandatory and is intended for easy debug
 * and reverse engineering of the code.
 * Helper attributes (flags) may be added as needed.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <string>
#include <type_traits>

#include "../utils/functions.h"

using namespace std;

// Default parameter assumed to be a quantity of a certain unit U
template<class U>
class Param
{
public:
  Param(const string&);

  Param<U> makeSameParam();
  Param<U> makeAnotherParam(const string& pName);

  // Invalid constructors
  Param();
  Param(const Param<U>&);

  // Getters
  const string& getName() const;
  bool hasInvalidName() const;
  const bu::quantity<U>& getQuantity() const;
  bool hasInvalidQuantity() const;
  bool isInvalid() const;
  bool isDeclaredVariable() const;
  bool isOperationResult() const;
  bool isUserInput() const;

  void operator=(const Param<U>&);
  void operator=(const bu::quantity<U>&);

  Param<U> operator+(const Param<U>&) const;
  Param<U> operator+(const bu::quantity<U>&) const;
  template<class U1>
  friend Param<U1> operator+(const bu::quantity<U1>&, const Param<U1>&);
  template<class U1>
  friend Param<U1> operator+(double, const Param<U1>&);
  template<class U1>
  friend Param<U1> operator+(const Param<U1>&);

  Param<U> operator-(const bu::quantity<U>&) const;
  Param<U> operator-(const Param<U>&) const;
  template<class U1>
  friend Param<U1> operator-(const bu::quantity<U1>&, const Param<U1>&);
  template<class U1>
  friend Param<U1> operator-(double, const Param<U1>&);
  template<class U1>
  friend Param<U1> operator-(const Param<U1>&);

  Param<U> operator*(double) const;
  template<class U2>
  Param<typename bu::multiply_typeof_helper<U, U2>::type>
  operator*(const Param<U2>&) const;
  template<class U2>
  Param<typename bu::multiply_typeof_helper<U, U2>::type>
  operator*(const bu::quantity<U2>&) const;
  template<class U1, class U2>
  friend Param<typename bu::multiply_typeof_helper<U1, U2>::type>
  operator*(const bu::quantity<U1>&, const Param<U2>&);
  template<class U1>
  friend Param<U1> operator*(double, const Param<U1>&);
  template<class U1, class U2>
  friend Param<typename bu::multiply_typeof_helper<U1, U2>::type>
  multiplication_helper(const bu::quantity<U1>&, const Param<U2>&);

  template<class U2>
  Param<typename bu::divide_typeof_helper<U, U2>::type>
  operator/(const Param<U2>&) const;
  template<class U2>
  Param<typename bu::divide_typeof_helper<U, U2>::type>
  operator/(const bu::quantity<U2>&) const;
  Param<U> operator/(double) const;
  template<class U1, class U2>
  friend Param<typename bu::divide_typeof_helper<U1, U2>::type>
  operator/(const bu::quantity<U1>&, const Param<U2>&);
  template<class U1>
  friend
  Param<typename bu::power_typeof_helper<U1, bu::static_rational<-1>>::type>
  operator/(double, const Param<U1>&);
  template<class U1, class U2>
  friend Param<typename bu::divide_typeof_helper<U1, U2>::type>
  division_helper(const bu::quantity<U1>&, const Param<U2>&);
  template<class U1, class U2>
  friend Param<typename bu::divide_typeof_helper<U1, U2>::type>
  division_helper(const Param<U1>&, const bu::quantity<U2>&);


  void operator+=(const Param<U>&);
  void operator+=(const bu::quantity<U>&);
  void operator++();
  void operator++(int);
  void operator-=(const Param<U>&);
  void operator-=(const bu::quantity<U>&);
  void operator--();
  void operator--(int);
  void operator*=(double);
  void operator/=(double);


  // Function used for testing private constructor !! DONT USE !!
  Param<U> funcForTest();

private:
  // Private constructor used in operator overloads
  Param(const bu::quantity<U>& qi);

  string generateErrorMsg(const string&, const Param<U>&) const;

  string _name;
  bool _hasInvalidName;
  bu::quantity<U> _q;
  bool _hasInvalidQuantity;
  bool _isInvalid;

  bool _isOperationResult;
  bool _isDeclaredVariable;

  bool _isUserInput;



};

// Constructor used in explicit declaration of parameter
template<class U>
Param<U>::Param(const string& pName)
{
  if ( ::isInvalid(pName) ) { generateErrorMsg("Construtor by name", *this); }
  _name = pName;
  _hasInvalidName = false;
  invalidate(&_q);
  _hasInvalidQuantity = true;
  _isInvalid = _hasInvalidName || _hasInvalidQuantity;

  // As it was given a proper name, is must be a declared variable
  _isDeclaredVariable = true;
  _isOperationResult = false;

  _isUserInput = false;
}

template<class U>
Param<U>
Param<U>::makeSameParam()
{
  Param<U> newParam(this->_name);
  newParam._q = this->_q;
  newParam._hasInvalidQuantity = this->_hasInvalidQuantity;
  newParam._isInvalid = this->_isInvalid;

  newParam._isDeclaredVariable = this->_isDeclaredVariable;
  newParam._isOperationResult = this->_isOperationResult;

  newParam._isUserInput = this->_isUserInput;

  return newParam;
  // TODO: maybe keep track of which parameters are the same using
  //       a list of addresses or something else
}

// Used to deduce quanitity's unit using "auto" declaration. Example:
// Param<a_unit> aParam("A physical parameter");
// auto anotherParam = aParam.makeAnotherParam("Another physical parameter");
// @anotherParam has the same type, i.e. same unit (a_unit), as @aParam
template<class U>
Param<U>
Param<U>::makeAnotherParam(const string& pName)
{
  return Param<U>(pName);
}

// Private constructor used in operator overloads
template<class U>
Param<U>::Param(const bu::quantity<U>& qi)
{
  invalidate(&_name);
  _hasInvalidName = true;
  _q = qi;
  _hasInvalidQuantity = ::isInvalid(qi);
  _isInvalid = _hasInvalidName || _hasInvalidQuantity;

  // Being a private constructor, it can only be called from operation overload
  // and therefore the constructed parameter is the result of an operation
  // and should NOT be directly assigned to a declared variable
  _isDeclaredVariable = false;
  _isOperationResult = true;

  _isUserInput = false;
}

template<class U>
Param<U>
Param<U>::funcForTest()
{
  // !! DONT USE !!
  return Param<U>( bu::quantity<U>::from_value(12321.) );
}

template<class U>
const string&
Param<U>::getName() const
{
  return this->_name;
}

template<class U>
bool
Param<U>::hasInvalidName() const
{
  return this->_hasInvalidName;
}

template<class U>
const bu::quantity<U>&
Param<U>::getQuantity() const
{
  return this->_q;
}

template<class U>
bool
Param<U>::hasInvalidQuantity() const
{
  return this->_hasInvalidQuantity;
}

template<class U>
bool
Param<U>::isInvalid() const
{
  return this->_isInvalid;
}

template<class U>
bool
Param<U>::isDeclaredVariable() const
{
  return this->_isDeclaredVariable;
}

template<class U>
bool
Param<U>::isOperationResult() const
{
  return this->_isOperationResult;
}

template<class U>
bool
Param<U>::isUserInput() const
{
  return this->_isUserInput;
}


template<class U>
void
Param<U>::operator=(const bu::quantity<U>& qi)
{
  if ( ::isInvalid(qi) ) { throw generateErrorMsg("=", *this); }
  if ( _hasInvalidName ) { throw generateErrorMsg("=", *this); }

  _q = qi;
  _hasInvalidQuantity = false;
  _isInvalid = false;

}

template<class U>
void
Param<U>::operator=(const Param<U>& pi)
{
  if ( pi._hasInvalidQuantity ) { throw generateErrorMsg("=", pi); }
  if ( _hasInvalidName ) { throw generateErrorMsg("=", *this); }

  _q = pi._q;
  _hasInvalidQuantity = false;
  _isInvalid = false;

}

template<class U>
Param<U>
Param<U>::operator+(const Param<U>& pi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("+", pi); }
  if ( pi.hasInvalidQuantity() ) { throw generateErrorMsg("+", pi); }

  bu::quantity<U> sum = this->_q + pi._q;
  if ( ::isInvalid(sum) ) { throw generateErrorMsg("+", pi); }
  Param<U> temp("temp");
  temp = sum;
  return temp;
}

template<class U>
Param<U>
Param<U>::operator+(const bu::quantity<U>& qi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("+", *this); }
  if ( ::isInvalid(qi) ) { throw generateErrorMsg("+", *this); }

  bu::quantity<U> sum = this->_q + qi;
  if ( ::isInvalid(sum) ) { throw generateErrorMsg("+", *this); }

  return Param<U>(sum);
}

template<class U1>
Param<U1>
operator+(const bu::quantity<U1>& qi, const Param<U1>& pi)
{
  return pi + qi;
}

template<class U1>
Param<U1>
operator+(double di, const Param<U1>& pi)
{
  return pi + di;
}

template<class U1>
Param<U1>
operator+(const Param<U1>& pi)
{
  if ( pi.hasInvalidQuantity() ) { throw pi.generateErrorMsg("+", pi); }
  return Param<U1>(pi._q);
}

template<class U>
Param<U>
Param<U>::operator-(const Param<U>& pi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("-", pi); }
  if ( pi.hasInvalidQuantity() ) { throw generateErrorMsg("-", pi); }

  bu::quantity<U> diff = this->_q - pi._q;
  if ( ::isInvalid(diff) ) { throw generateErrorMsg("-", pi); }

  return Param<U>(diff);
}

template<class U>
Param<U>
Param<U>::operator-(const bu::quantity<U>& qi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("-", *this); }
  if ( ::isInvalid(qi) ) { throw generateErrorMsg("-", *this); }

  bu::quantity<U> diff = this->_q - qi;
  if ( ::isInvalid(diff) ) { throw generateErrorMsg("-", *this); }

  return Param<U>(diff);
}

template<class U1>
Param<U1>
operator-(const bu::quantity<U1>& qi, const Param<U1>& pi)
{
  return -pi + qi;
}

template<class U1>
Param<U1>
operator-(double di, const Param<U1>& pi)
{
  return -pi + di;
}

template<class U1>
Param<U1>
operator-(const Param<U1>& pi)
{
  if ( pi.hasInvalidQuantity() ) { throw pi.generateErrorMsg("-", pi); }
  return Param<U1>(-pi._q);
}


template<class U>
Param<U>
Param<U>::operator*(double di) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }
  if ( ::isInvalid(di) ) { throw generateErrorMsg("*", *this); }

  auto newParam = Param<U>(this->_q * di);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  return newParam;
}

template<class U1>
Param<U1>
operator*(double di, const Param<U1>& pi)
{
  return pi * di;
}

template<class U>
template<class U2>
Param<typename bu::multiply_typeof_helper<U, U2>::type>
Param<U>::operator*(const Param<U2>& pi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }
  if ( pi.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  auto newParam = multiplication_helper(this->_q, pi);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  return newParam;
}

template<class U>
template<class U2>
Param<typename bu::multiply_typeof_helper<U, U2>::type>
Param<U>::operator*(const bu::quantity<U2>& qi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }
  if ( ::isInvalid(qi) ) { throw generateErrorMsg("*", *this); }

  auto newParam = multiplication_helper(qi, *this);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  return newParam;
}

template<class U1, class U2>
Param<typename bu::multiply_typeof_helper<U1, U2>::type>
operator*(const bu::quantity<U1>& qi, const Param<U2>& pi)
{
  if ( ::isInvalid(qi) ) { throw pi.generateErrorMsg("*", pi); }
  if ( pi.hasInvalidQuantity() ) { throw pi.generateErrorMsg("*", pi); }

  auto newParam = multiplication_helper(qi, pi);
  if ( newParam.hasInvalidQuantity() ) { throw pi.generateErrorMsg("*", pi); }

  return newParam;
}

template<class U1, class U2>
Param<typename bu::multiply_typeof_helper<U1, U2>::type>
multiplication_helper(const bu::quantity<U1>& qi, const Param<U2>& pi)
{
  typedef typename bu::multiply_typeof_helper<U1, U2>::type U1xU2;
  bu::quantity<U1xU2> prod = qi * pi._q;
  return Param<U1xU2>(prod);
}

template<class U>
template<class U2>
Param<typename bu::divide_typeof_helper<U, U2>::type>
Param<U>::operator/(const Param<U2>& pi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }
  if ( pi.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  auto newParam = division_helper(this->_q, pi);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("*", *this); }

  return newParam;
}

template<class U>
template<class U2>
Param<typename bu::divide_typeof_helper<U, U2>::type>
Param<U>::operator/(const bu::quantity<U2>& qi) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("/", *this); }
  if ( ::isInvalid(qi) ) { throw generateErrorMsg("/", *this); }

  auto newParam = division_helper(*this, qi);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("/", *this); }

  return newParam;
}

template<class U>
Param<U>
Param<U>::operator/(double di) const
{
  if ( this->hasInvalidQuantity() ) { throw generateErrorMsg("/", *this); }
  if ( ::isInvalid(di) ) { throw generateErrorMsg("/", *this); }

  bu::quantity<rrs::dimensionless> q = di;
  auto newParam = division_helper(*this, q);
  if ( newParam.hasInvalidQuantity() ) { throw generateErrorMsg("/", *this); }

  return newParam;
}

template<class U1, class U2>
Param<typename bu::divide_typeof_helper<U1, U2>::type>
operator/(const bu::quantity<U1>& qi, const Param<U2>& pi)
{
  if ( ::isInvalid(qi) ) { throw pi.generateErrorMsg("/", pi); }
  if ( pi.hasInvalidQuantity() ) { throw pi.generateErrorMsg("/", pi); }

  auto newParam = division_helper(qi, pi);
  if ( newParam.hasInvalidQuantity() ) { throw pi.generateErrorMsg("/", pi); }

  return newParam;
}

template<class U1>
Param<typename bu::power_typeof_helper<U1, bu::static_rational<-1>>::type>
operator/(double di, const Param<U1>& pi)
{
  if ( ::isInvalid(di) ) { throw pi.generateErrorMsg("/", pi); }
  if ( pi.hasInvalidQuantity() ) { throw pi.generateErrorMsg("/", pi); }

  bu::quantity<rrs::dimensionless> q = di;
  auto newParam = division_helper(q, pi);
  if ( newParam.hasInvalidQuantity() ) { throw pi.generateErrorMsg("/", pi); }

  return newParam;
}

template<class U1, class U2>
Param<typename bu::divide_typeof_helper<U1, U2>::type>
division_helper(const bu::quantity<U1>& qi, const Param<U2>& pi)
{
  typedef typename bu::divide_typeof_helper<U1, U2>::type U1overU2;
  bu::quantity<U1overU2> quot = qi / pi._q;
  return Param<U1overU2>(quot);
}

template<class U1, class U2>
Param<typename bu::divide_typeof_helper<U1, U2>::type>
division_helper(const Param<U1>& pi, const bu::quantity<U2>& qi)
{
  typedef typename bu::divide_typeof_helper<U1, U2>::type U1overU2;
  bu::quantity<U1overU2> quot = pi._q / qi;
  return Param<U1overU2>(quot);
}

template<class U>
void
Param<U>::operator+=(const Param<U>& pi)
{
  *this = *this + pi;
}

template<class U>
void
Param<U>::operator+=(const bu::quantity<U>& qi)
{
  *this = *this + qi;
}

template<class U>
void
Param<U>::operator++()
{
  *this = *this + bu::quantity<U>::from_value(1.);
}

template<class U>
void
Param<U>::operator++(int)
{
  *this = *this + bu::quantity<U>::from_value(1.);
}

template<class U>
void
Param<U>::operator-=(const Param<U>& pi)
{
  *this = *this - pi;
}

template<class U>
void
Param<U>::operator-=(const bu::quantity<U>& qi)
{
  *this = *this - qi;
}

template<class U>
void
Param<U>::operator--()
{
  *this = *this - bu::quantity<U>::from_value(1.);
}

template<class U>
void
Param<U>::operator--(int)
{
  *this = *this - bu::quantity<U>::from_value(1.);
}

template<class U>
void
Param<U>::operator*=(double qi)
{
  *this = *this * qi;
}

template<class U>
void
Param<U>::operator/=(double qi)
{
  *this = *this / qi;
}



template<class U>
string
Param<U>::generateErrorMsg(const string& opStr, const Param<U>& pi) const
{
  // TODO:
  return opStr;
}

#endif //PARAM_H
