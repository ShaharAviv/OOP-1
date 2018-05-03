#pragma once
#include "Validator.h"

template<class T>
class MinValidator : public Validator<T>
{
public:
	MinValidator(const T&  minimum);
	bool check(const T& data);

private:
	T m_min;
};

//===========================================================================//
//---------------------------------------------------------------------------//
/*
 * Constructor of Template minimum validator
 * Gets Template-type values as the minimum
 */
template<class T>
MinValidator<T>::MinValidator(const T&  minimum)
	:Validator<T>("Too few chosen"), m_min(minimum) { }

//---------------------------------------------------------------------------//
/*
 * Method that checks if a value suit correctly to the defined minimum
 * Gets Template-type value as the value to check.
 */
template<class T>
bool MinValidator<T>::check(const T & data) 
{
	return (data >= m_min);
}

