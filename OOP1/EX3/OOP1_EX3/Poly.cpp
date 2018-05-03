#include "Poly.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

//---------------------------------------------------------------------------//
/*
 * Constructor that build a Polynomial, using by vector of coef-factors
 */
Poly::Poly(const std::vector<double> coeffs)
{
	int maxDeg = coeffs.size() - 1;		// max degree of the built polynimal
	for (size_t i = 0; i < coeffs.size(); i++)
	{
		int currDeg = maxDeg - i;
		if (coeffs[i] != 0)			// we dont keep meaningless monoms
			append(currDeg, coeffs[i]);
	}
}

//---------------------------------------------------------------------------//
/*
 * Constructor that build a single-Polynomial, using a scalar
 */
Poly::Poly(double _scalar)
	:Poly(0,_scalar) {}

//---------------------------------------------------------------------------//
/*
 *  Constructor that build a Polynomial, which is a single monom
 *  built using a scalar and of coef-factor
 */
Poly::Poly(int _coeff, double _scalar)
{
	m_poly = new Monom[1]; 
	m_size = 1;
	m_poly[0] = Monom(_scalar,_coeff);
}

//---------------------------------------------------------------------------//
/*
 *  Copy Constructor of Poly
 */
Poly::Poly(const Poly& other)
{
	m_size = other.m_size;

	m_poly = new Monom[m_size];        // Full and smart copy
	for (int i = 0; i < m_size; i++)
		m_poly[i] = other.at(i);
}

//---------------------------------------------------------------------------//
/*
 *  Assaign operator
 */
Poly& Poly::operator=(const Poly& other)
{
	if (this == &other)	 // Testing that we do not copy the same variable
		return *this;

	// alloc Full-New copy
	delete m_poly;

	m_size = other.m_size;

	//Full and smart (new) copy
	m_poly = new Monom[m_size];
	for (int i = 0; i < m_size; i++)
		m_poly[i] = other.at(i);

	return *this;
}

//---------------------------------------------------------------------------//
/*
 *  Destructor of Poly
 */
Poly::~Poly()
{
	delete m_poly;
}

//---------------------------------------------------------------------------//
/*
 * Method that return the size of the data structer (array of monoms)
 */
int Poly::getSize() const
{
	return m_size;
}

//---------------------------------------------------------------------------//
/*
 *	Method that returns the greatest degree of the polynomal
 *	if this is the zero-polynomal - return -1.
 */
int Poly::deg() const
{
	if (*this == Poly(0))
		return -1;
	return m_poly[0].getCoeff();
}


//---------------------------------------------------------------------------//
/*
 * Multiplier-Operator
 * Multiply 2 polynomals 
 */
Poly Poly::operator*(const Poly& rightPoly) const
{
	Poly newPoly;
	for (int i = 0; i < rightPoly.getSize(); i++)
		newPoly += (*this).multiMonom(rightPoly.at(i));

	return newPoly;
}

//---------------------------------------------------------------------------//
/*
 *	Method that multiply a polynomal by a monom
 */
Poly Poly::multiMonom(const Monom & monom) const
{
	Poly newPoly = *this;
	for (int i = 0; i < m_size; i++)
		newPoly.setAt(i, m_poly[i] * monom);

	return newPoly;
}

//---------------------------------------------------------------------------//
/*
 *	Help function that Converts a monom into polynom-struct 
 */
Poly Poly::Monom2Poly(const Monom & monom) const
{
	return Poly(monom.getCoeff(), monom.getScalar());
}


//---------------------------------------------------------------------------//
/*
 *	Add operator
 *	adding 2 polinomals
 */
Poly Poly::operator+(const Poly& p2) const
{
	Poly p3;			// keep the sum of 2 polinomals	
	int i = 0,			// index for running on first
		j = 0;			// index for running on second
	int n1 = m_size;			// size of first polynomal
	int n2 = p2.getSize();      // size of second polynomal

	//-- Traverse both Polynomals --
	while (i < n1 && j < n2)	{
		// case(s) there is no scalar
		if ((*this).at(i).getScalar() == 0){
			i++;
			continue;
		}
		if (p2.at(j).getScalar() == 0){
			j++;
			continue;
		}
		// Check if current element of first Polynomal is smaller than current
		// element of second Polynomal.
		// If yes, store first Polynom monom and increment first Polynom index. 
		// Otherwise do same with second Polynom
		if ((*this).at(i).getCoeff() > p2.at(j).getCoeff()) {
			p3.append((*this).at(i));
			i++;
		}
		else if ((*this).at(i).getCoeff() < p2.at(j).getCoeff()){
			p3.append(p2.at(j));
			j++;
		}
		else {
			double scalarsSum = at(i).getScalar() + p2.at(j).getScalar();
			if (scalarsSum != 0){		// if monom have to be non-exist
				Monom tmp(scalarsSum, (*this).at(i).getCoeff());
				p3.append(tmp);
			}
			i++;
			j++;
		}
	}

	//-- Store remaining elements of first Polynom --
	while (i < n1){
		p3.append((*this).at(i));
		i++;
	}
	//-- Store remaining elements of second Polynom --
	while (j < n2){
		p3.append(p2.at(j));
		j++;
	}

	return p3;
}

//---------------------------------------------------------------------------//
/*
 *	Sub operator
 *	sub 2 polinomalss
 */
Poly operator-(const Poly& leftPoly, const Poly& rightPoly)
{
	return leftPoly + -rightPoly;
}

//---------------------------------------------------------------------------//
/*
 *	Multiply operator
 *	Multiplies a polinomal by scalar 
 */
Poly operator*(int scalar, const Poly& _Poly)
{
	return _Poly * scalar;
}

//---------------------------------------------------------------------------//
/*
 *	Help function that get a polynomial,
 *	returns the highest common factor (hcf) of the polinomal.
 */
Poly hcf(const Poly p)
{
	double factor;						// keep the hcf
	factor = p.at(0).getScalar();		// assume that we have at least 1
	
	for (int i = 1; i < p.getSize(); i++)
		factor = gcd(factor, (p.at(i).getScalar()));

	return factor;
}

//---------------------------------------------------------------------------//
/*
 *	Help function that divides 2 polynomials, 
 *	keep the reminder polynomial and return the quotity polinom.
 */
Poly Poly::divide(const Poly& otherPoly, Poly& rem) const
{
	Poly quot = 0;			// Polynomal that keep the division result
	rem = *this;

	while (rem != 0 && rem.deg() >= otherPoly.deg() )  {
		Monom t = rem.at(0) / otherPoly.at(0);    //# Divide the leading terms
		quot = quot + Monom2Poly(t);
		rem = rem - otherPoly * Monom2Poly(t);
	}

	return quot;
}
//---------------------------------------------------------------------------//
/*
 *	Divide operator
 *	divides 2 polinomals
 */
Poly Poly::operator/(const Poly& rightPoly) const
{
	Poly rem;
	return divide(rightPoly, rem);
}

//---------------------------------------------------------------------------//
/*
 * Reminder operator
 * return the reminder polinomal after division of 2 polinomals
 */
Poly Poly::operator%(const Poly& rightPoly) const
{
	Poly rem;
	divide(rightPoly, rem);
	return rem;
}

//---------------------------------------------------------------------------//
/*
 * Add and assign operator
 * Add a second polynomal into the first one
 */
Poly& Poly::operator+=(const Poly& rightPoly)
{
	*this = *this + rightPoly;
	return (*this);
}

//---------------------------------------------------------------------------//
/*
 * Sub and assign operator
 * Sub a second polynomal into the first one
 */
Poly& Poly::operator-=(const Poly& rightPoly)
{
	*this = *this - rightPoly;
	return (*this);
}

//---------------------------------------------------------------------------//
/*
 * Add and assign operator
 * Add a second polynomal into the first one
 */
Poly& Poly::operator*=(const Poly& rightPoly)
{
	(*this) = (*this) * rightPoly;
	return (*this);
}

//---------------------------------------------------------------------------//
/*
 * Multiply and assign operator
 * multiply a second polynomal into the first one
 */
Poly & Poly::operator*=(int scalar)
{
	(*this) = (*this) * scalar;
	return (*this);
}

//---------------------------------------------------------------------------//
/*
 * Divide and assign operator
 * Divide a second polynomal into the first one
 */
Poly& Poly::operator/=(const Poly& rightPoly)
{
	(*this) = (*this) / rightPoly;
	return (*this);
}
//---------------------------------------------------------------------------//
/*
 * Remainder and assign operator
 * assaign the reminder to second polynomal into the first one
 */
Poly & Poly::operator%=(const Poly& rightPoly)
{
	(*this) = (*this) % rightPoly;
	return (*this);
}

//---------------------------------------------------------------------------//
/*
 *	return the compliment polynomal (= -1 * curr-polynomal)
 */
Poly Poly::operator-() const
{
	Poly unPoly = *this;			// copy to a new copy
	for (int i = 0; i < m_size; i++)
		unPoly.setAt(i, -m_poly[i]);		// multiply each monom by (-1)

	return unPoly;
}

//---------------------------------------------------------------------------//
/*
 *	Operator that get a double and return the value of the polynomal in 
 *	this point
 */
double Poly::operator()(double value) const
{
	double sum = 0;		// the (sum) value of the polymomal when x = value
	for (int i = 0; i < m_size; i++)
		sum += m_poly[i].getScalar() * pow(value, m_poly[i].getCoeff());
	
	return sum;
}

//---------------------------------------------------------------------------//
/*
 * Operator that get a number and return the factor of this degree of the
 * polynomal.
 */
double Poly::operator[](int degree) const
{
	if (degree > deg())		// parameter is highest than the deg of polynomal 
		return 0;

	for (int i = 0; i < m_size; i++)
		if (m_poly[i].getCoeff() == degree)
			return m_poly[i].getScalar();

	return 0;

}

//---------------------------------------------------------------------------//
/*
 *	Method to compare if 2 polynomals are Equal
 */
bool operator==(const Poly& p1, const Poly& p2)
{
	if (p1.getSize() != p2.getSize())		// have diffrent number of monoms
		return false;
	
	// checking if each monom is equal 
	for (int i = 0; i < p1.getSize(); ++i)
		if (!(p1.at(i) == p2.at(i)))
			return false;

	return true;
}

//---------------------------------------------------------------------------//
/*
 *	Method to compare if 2 polynomials are not Equal
 */
bool operator!=(const Poly& p1, const Poly& p2)
{
	return !(p1 == p2);
}

//---------------------------------------------------------------------------//
/*
 *	Method That get an index(n)
 *	Returns the polinomal's n-th' monom 
 */
Monom Poly::at(int index) const
{
	if (index >= m_size) {			// highest degree is in first place
		std::cerr << "out of subscript\n";
		exit(EXIT_FAILURE);
	}

	return m_poly[index];
}

//---------------------------------------------------------------------------//
/*
 *	adding a new monom to the polynomal
 */
void Poly::append(int coeff, double scalar)
{
	if (*this == Poly(0))
		m_poly[0] = Monom(scalar, coeff);
	

	else {
		Monom* newPoly = new Monom[m_size + 1];  // created resized
		// copy old
		for (int i = 0; i < m_size; i++)
			newPoly[i] = this->m_poly[i];
		newPoly[m_size] = Monom(scalar, coeff);

		delete this->m_poly;		// delete old
		m_poly = newPoly;			// re-assign new
		m_size++;					// update to new size
	}

}

//---------------------------------------------------------------------------//
/*
 * adding a new monom to the polynomal
 */
void Poly::append(const Monom& monom)
{
	append(monom.getCoeff(), monom.getScalar());
}

//---------------------------------------------------------------------------//
/*
 * Sets the monom in the place index (on the array of Poly)
 */
void Poly::setAt(int index, Monom m)
{
	m_poly[index] = m;
}

//---------------------------------------------------------------------------//
/*
 *	Insertion operator
 *	Prints the polinomal into the stream file output
 */
std::ostream& operator<<(std::ostream& output, const Poly& _poly)
{
	int index;
	output << _poly.at(0);			// we always have one monom!
	for (index = 1; index < _poly.getSize(); ++index){
		// if scalar is positive or 0
		 if (_poly.at(index).getScalar() >= 0) 
			 output << "+";

		output << _poly.at(index);	
	}
	return output;
}

//---------------------------------------------------------------------------//
/*
 *	Method that Calculate and return the gcd polinomal of 2 polinoms
 */
Poly gcd(const Poly & a, const Poly & b)
{
	if (b == Poly(0))
		return a / hcf(a);

	return gcd(b, (a%b));
}

//---------------------------------------------------------------------------//
/*
 *	Help function that get 2 numbers and return their gcd.
 */
double gcd(double a, double b)
{
	if (b == 0)
		return a;
	return gcd(b, fmod(a,b));
}
