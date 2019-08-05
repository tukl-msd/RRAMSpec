///*
// * Copyright (c) 2019, University of Kaiserslautern
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without
// * modification, are permitted provided that the following conditions are
// * met:
// *
// * 1. Redistributions of source code must retain the above copyright notice,
// *    this list of conditions and the following disclaimer.
// *
// * 2. Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the distribution.
// *
// * 3. Neither the name of the copyright holder nor the names of its
// *    contributors may be used to endorse or promote products derived from
// *    this software without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// * Authors: Andr'e L. Chinazzo, Deepak M. Mathew, Christian Weis
// */


// // TODO: move implementatin of functions to .cpp file. Need to explicitly
// //   specify all possible units U.
// // template class Param<rrs::volt_unit>
// // template class Param<rrs::millivolt_unit>
// // ... for all units (and scaled units) at the end of this .cpp file.
// // Probably better to have a thrid file included at the end of this,
// // possibly with the implementation of the auto scaling for pretty print out
// // Whenever doing this, ignore the commented following code
// // and rather get the definitions (implementation) from the .h file.


//#include "Param.h"

//// Constructor used in explicit declaration of parameter
//template<class U>
//Param<U>::Param(const string& pName)
//{
//  if ( isInvalid(pName) ) { generateErrorMsg("Construtor by name"); }
//  _name = pName;
//  invalidate(&_q);
//  _isInvalid = true;

//  // As it was given a proper name, is must be a declared variable
//  _isDeclaredVariable = true;
//  _isOperationResult = false;

//  _isUserInput = false;
//}

//// Constructor used for automatic assessment of the quantity's unit
//template<class U>
//Param<U>::Param(const Param& p)
//{
//  invalidate(&_name);
//  invalidate(&_q);
//  _isInvalid = true;

//  _isDeclaredVariable = true;
//  _isOperationResult = false;

//  _isUserInput = false;
//}

//// Private constructor used in operator overloads
//template<class U>
//Param<U>::Param(const bu::quantity<U>& qi)
//{
//  invalidate(&_name);
//  _q = qi;
//  _isInvalid = isInvalid(qi);

//  // Being a private constructor, it can only be called from operation overload
//  // and therefore the constructed parameter is the result of an operation
//  // and should NOT be directly assigned to a declared variable
//  _isDeclaredVariable = false;
//  _isOperationResult = true;

//  _isUserInput = false;
//}

//template<class U>
//const string&
//Param<U>::getName() const
//{
//  return this->_name;
//}

//template<class U>
//const bu::quantity<U>&
//Param<U>::getQuantity() const
//{
//  return this->_q;
//}

//template<class U>
//bool
//Param<U>::isInvalid() const
//{
//  return this->_isInvalid;
//}

//template<class U>
//bool
//Param<U>::isDeclaredVariable() const
//{
//  return this->_isDeclaredVariable;
//}

//template<class U>
//bool
//Param<U>::isOperationResult() const
//{
//  return this->_isOperationResult;
//}

//template<class U>
//bool
//Param<U>::isUserInput() const
//{
//  return this->_isUserInput;
//}


//template<class U>
//void
//Param<U>::setAsSameParam(const Param& pi)
//{
//  _name = pi._name;
//  _q = pi._q;
//  // Source param must be valid
//  if ( !_isInvalid ) { throw generateErrorMsg("setAsSameParam", pi); }
//  _isInvalid = false;

//  // Source param must be a declared variable, with a proper name
//  if ( !_isDeclaredVariable ) { throw generateErrorMsg("setAsSameParam", pi); }
//  _isDeclaredVariable = true;

//  // Source param must not be the direct result of an math. operation
//  if ( !_isOperationResult ) { throw generateErrorMsg("setAsSameParam", pi); }
//  _isOperationResult = false;

//  _isUserInput = pi._isUserInput;
//}

//template<class U>
//Param<U>
//Param<U>::operator+(const Param<U>& pi) const
//{
//  if ( this->_isInvalid ) { throw generateErrorMsg("+", pi); }
//  if ( pi._isInvalid ) { throw generateErrorMsg("+", pi); }

//  bu::quantity<U> sum = this->_q + pi._q;
//  if ( isInvalid(sum) ) { throw generateErrorMsg("+", pi); }

//  return Param<U>(sum);
//}

