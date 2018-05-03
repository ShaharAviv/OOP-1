#pragma once
#include "Field.h"
#include "ValidatorForm.h"

template<class T, class U>
class TwoFactorValidator : public ValidatorForm
{
public:
	TwoFactorValidator(std::string errorMsg, T* first, U* second);
	virtual bool check() const = 0 ;
	bool isValid() const;

protected:
	T* m_factor1;
	U* m_factor2;
};


//---------------------------------------------------------------------------//
/*
* Constructor of 2-factor validator
* Gets a string as the error of the validator in case it's invalid and 2
* pointers to each of factor class
*/
template<class T, class U>
TwoFactorValidator<T,U>::TwoFactorValidator(std::string errorMsg ,T* first, U* second)
	:ValidatorForm(errorMsg), m_factor1(first), m_factor2(second) {}

//---------------------------------------------------------------------------//
/*
 * Method to return if the validator is valid
 */
template<class T, class U>
inline bool TwoFactorValidator<T, U>::isValid() const
{
	return m_valid;
}
