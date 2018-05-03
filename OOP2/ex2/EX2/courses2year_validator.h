#pragma once
#include "TwoFactorValidator.h"

template<class T, class U>
class Courses2YearValidator : public TwoFactorValidator<Field<short>, Field<int> >
{
public:
	Courses2YearValidator(T* first, U* second);
	bool check() const override;

//	m_factor1 - presents num of courses
//  m_factor2 - presents study-year
};
//===========================================================================//
/*
 * Constructor of The validator checks match between courses' number an the
 * students current study year
 */
template<class T, class U>
Courses2YearValidator<T, U>::Courses2YearValidator(T* first, U* second)
	:TwoFactorValidator("Course(s) and Year(s) don't match\n", first, second)
{
}

//---------------------------------------------------------------------------//
/*
 * Method for checking if the courses' number suit correctly to the  students'
 * current study year, if so return true. otherwise, the 2 fields get invalid
 */
template<class T, class U>
bool Courses2YearValidator<T, U>::check() const
{
	bool check = false;	   // keep if year suits to the faculty (number)
	switch (stoi(m_factor2->getData()))		// check faculty number
	{
	case 1:
	case 2:
		check = ((*m_factor1) >= 2 && *m_factor1 <= 6);
		break;
	case 3:
	case 4:
		check = ((*m_factor1) >= 2 && (*m_factor1) <= 10);
		break;
	case 5:
	case 6:
	case 7:
		check = ((*m_factor1) >= 2 && (*m_factor1) <= 8);
		break;
	}

	if (!check){			// reset 2 fields back to fasle
		m_factor1->setValid(false);
		m_factor2->setValid(false);
	}
	return check;
}
