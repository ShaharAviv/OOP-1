#pragma once
#include "ValidatorGen.h"

template<typename T>
class Validator : public ValidatorGen
{
public:
	Validator(const std::string&);
	virtual bool check(const T& data) = 0;

};

///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------//
/*
* Constructor of template-class validator
* Gets a string as the error of the validator in case it's invalid
*/
template<typename T>
Validator<T>::Validator(const std::string & errorMsg)
	:ValidatorGen(errorMsg)
{
}


