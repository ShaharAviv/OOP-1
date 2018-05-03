#include "Monom.h"


Monom::Monom(double _scalar, int _coeff)
	:m_scalar(_scalar), m_coeff(_coeff) {}

int Monom::getCoeff() const
{
	return m_coeff;
}

double Monom::getScalar() const
{
	return m_scalar;
}

Monom operator/(const Monom& monom1, const Monom& monom2)
{
	return Monom(monom1.getScalar()/monom2.getScalar(),
		         monom1.getCoeff() - monom2.getCoeff());
}

Monom operator*(const Monom& monom, int scalar)
{
	return Monom(monom.getScalar()*scalar ,monom.getCoeff());
}

Monom operator*(const Monom& monom1, const Monom& monom2)
{
	return Monom(monom1.getScalar()*monom2.getScalar(),
		         monom1.getCoeff()+ monom2.getCoeff());
}

Monom Monom::operator-() const
{
	return Monom(-getScalar(), getCoeff());
}

//---------------------------------------------------------------------------//
/*
*	Method to compare if 2 polynomals are Equal
*/
bool operator==(const Monom& leftMonom, const Monom& rightMonom)
{
	return (leftMonom.getCoeff() == rightMonom.getCoeff() &&
		    leftMonom.getScalar() == rightMonom.getScalar() );
}

//---------------------------------------------------------------------------//
/*
 *	Insertion operator
 *	Prints the monom into the stream file output
 */
std::ostream& operator<<(std::ostream& output, const Monom& _monom)
{
	int coeff = _monom.getCoeff();
	double scalar = _monom.getScalar();
	if (coeff==0)
		output << scalar;
	else if (coeff==1)
		(scalar == 1) ? output << "X" : output << scalar << "*X";
	else
		(scalar == 1) ? output << "X^" << coeff : 
		                output << scalar << "*X^" << coeff;
	return output;
}







