#include "Sqrt.h"
#include <iostream>
#include <iomanip>

//---------------------------------------------------------------------------//
/*
* Constructor of square root expression
* Gets a pointer to function used as inner function
*/
Sqrt::Sqrt(std::shared_ptr<Function> p)
	:UnaryExp(p) {}

//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a number as optional argument, if so print sqrt(f(9)) (e.g num = 9)
* otherwise print sqrt(f) , f as inner function
*/
void Sqrt::print(double num) const
{
	UnaryExp::print("sqrt", num);
}


//---------------------------------------------------------------------------//
/*
* Method thats set new function as inner function
* Gets a pointer to change
*/
void Sqrt::setVar(std::shared_ptr<Function> p)
{

		if (std::dynamic_pointer_cast<VarX>(m_expression))
			m_expression = p;

	
		else
			m_expression->setVar(p->clone());

}


//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
std::shared_ptr<Function> Sqrt::clone() const
{
	return std::make_shared<Sqrt>(*this);
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the Squre root value of a function at certain x
* Get a double number and return the the funtion value at this point
*/
double Sqrt::valueAt(double value) const
{
	return UnaryExp::fixTo2Digits(sqrt(m_expression->valueAt(value)));
}
