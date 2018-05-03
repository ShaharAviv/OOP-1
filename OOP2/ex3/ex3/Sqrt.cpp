#include "Sqrt.h"
#include <iostream>
#include <iomanip>
#include "MyException.h"

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
	check_value(num);
	UnaryExp::print("sqrt", num);
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
	check_value(value);				// check if the value is in Range(f)
	return UnaryExp::fixTo2Digits( sqrt(m_expression->valueAt(value)) );
}

//---------------------------------------------------------------------------//
/*
* Method that checks if a value is in the Range of sqrt Function
* Get a double number and if so, throws exception
*/
void Sqrt::check_value(double value) const
{
	if (value < 0)
		throw MinException(0);
}
