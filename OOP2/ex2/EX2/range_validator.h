#pragma once
#include "Validator.h"
#include "faculty_value.h"

template<class T>
class RangeValidator : public Validator<T>
{
public:
	RangeValidator(const T& min, const T& max);
	bool check(const T& data);

private:
	T m_min;
	T m_max;
};

//===========================================================================//
//---------------------------------------------------------------------------//
/*
* Constructor of Template range validator
* Gets 2 Template-type values as the minimum and maximum of the range
*/
template<class T>
RangeValidator<T>::RangeValidator(const T& min, const T& max)
	:Validator<T>("Out of range"), m_min(min), m_max(max) { }

//---------------------------------------------------------------------------//
/* 
 * Method that checks if a value suit correctly to the defined range
 * Gets Template-type value as the value to check.
 */
template<class T>
bool RangeValidator<T>::check(const T& data)
{
	return (data >= m_min && data <= m_max);
}
