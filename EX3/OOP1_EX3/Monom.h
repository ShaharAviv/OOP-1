/************************************************************************/
/* Class of Monom
 * Handle all the operations that regards to monoms
 * 
/************************************************************************/
#pragma once
#include <iostream>
class Monom
{
public:
	Monom(double _scalar = 0, int _coeff = 0);

	int getCoeff() const;
	double getScalar() const;

	Monom operator-() const;

private:
	double m_scalar;
	int m_coeff;
};

Monom operator*(const Monom& monom, int scalar);
Monom operator*(const Monom& , const Monom& );
Monom operator/(const Monom& monom1, const Monom& monom2);
bool operator==(const Monom&, const Monom&);
std::ostream& operator<<(std::ostream& output, const Monom& _monom);
