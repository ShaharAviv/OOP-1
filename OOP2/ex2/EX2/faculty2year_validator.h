#pragma once
#include "TwoFactorValidator.h"

const int MIN_YEARS = 1;		
const int MAX_CS_YEARS = 4;		// maximum year can learn computer science
const int MAX_MEDIC_YEARS = 7;	// maximum year can learn medicine
const int MAX_LIT_YEARS = 3;	// maximum year can learn literature

//===========================================================================//

template<class T, class U>
class Faculty2YearValidator : public TwoFactorValidator<Field<FacultyValue>, Field<int> >
{
public:
	Faculty2YearValidator(T* first, U* second);
	bool check() const override;

//	m_factor1 - presents faculty
//  m_factor2 - presents study-year

};

//===========================================================================//
/*
 * Constructor of The validator checks match between courses' number an the
 * students current study year
 */
template<class T, class U>
Faculty2YearValidator<T, U>::Faculty2YearValidator(T* first, U* second)
	:TwoFactorValidator("Year(s) and Faculty don't match\n", first, second)
{ }

//---------------------------------------------------------------------------//
/*
 * Method for checking if the faculty' number suit correctly to the students'
 * current study year, if so return true. otherwise, the 2 fields get invalid
 */
template<class T, class U>
bool Faculty2YearValidator<T, U>::check() const
{
	bool check = false;		  // keep if year number suits to faculty's number
	switch (stoi(m_factor1->getData()))		// check faculty number
	{
	case 1: check = ((*m_factor2) >= MIN_YEARS && (*m_factor2) <= MAX_CS_YEARS);
		break;
	case 2: check = ((*m_factor2) >= MIN_YEARS && (*m_factor2) <= MAX_MEDIC_YEARS);
		break;
	case 3: check = ((*m_factor2) >= MIN_YEARS && (*m_factor2) <= MAX_LIT_YEARS);
		break;
	}

	if (!check) {		// reset the fields
		m_factor1->setValid(false);
		m_factor2->setValid(false);
	}
	return check;
}
