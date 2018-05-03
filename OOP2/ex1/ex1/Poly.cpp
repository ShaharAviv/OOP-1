#include "Poly.h"
#include <iostream>
#include <algorithm>	// for std::reverse_copy()
//#include <climits>

//---------------------------------------------------------------------------//
/*
* Constructor of Polynomal Expression
* Gets a coeffecints' vector a pointer to function used as inner function
*/
Poly::Poly(std::vector <double> vec, std::shared_ptr<Function> p)
	:UnaryExp(p), m_coeffs(vec) {}

//---------------------------------------------------------------------------//
/*
*
*/
void Poly::print(double num) const
{
	if (m_coeffs.empty())			// if it's the zero-polinomal
		std::cout << 0;

	for (int i = int(m_coeffs.size()) - 1; i >= 0; i--)

		if (m_coeffs[i] != 0)
		{
			if (i != (int)m_coeffs.size() - 1)
				(m_coeffs[i] > 0) ? std::cout << " + " : std::cout << " - ";
			else if (m_coeffs[i] < 0)
				std::cout << '-';

			std::cout << ' ' << m_coeffs[i] << "*(";
			/*(num = INT_MAX) ? */m_expression->print(num)/* : m_expression->print()*/;
			std::cout << ")^" << i;
		}
}

//---------------------------------------------------------------------------//
/*
*
*/
std::shared_ptr<Poly> Poly::reverse()
{
	std::shared_ptr<Poly> newPoly = std::make_shared<Poly>(*this);
	// using STL method to reverse the coffetionts vector
	std::reverse_copy(m_coeffs.begin(), m_coeffs.end(), 
		                                              newPoly->m_coeffs.begin());
	return newPoly;
}

//---------------------------------------------------------------------------//
/*
 * Method thats create new (copied) pointer to the current object 
 * Return the new copy pointer
 */
std::shared_ptr<Function> Poly::clone() const
{
	return std::make_shared<Poly>(*this);
}

//---------------------------------------------------------------------------//
/*
 * Method thats set new functtion as inner function
 * Gets a pointer to change 
 */
void Poly::setVar(std::shared_ptr<Function> p)
{
	m_expression = p;
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the Polynomal's value at certain x
* Get a double number and return the the funtion value at this point
*/
double Poly::valueAt(double value) const
{
	double sum = 0;
	for (int i = (int)m_coeffs.size() - 1; i >= 0; i--)
		sum += (m_coeffs[i] * (pow(m_expression->valueAt(value), i)));

	return sum;
}