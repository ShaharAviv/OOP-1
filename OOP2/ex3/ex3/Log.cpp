#include "Log.h"
#include <iostream>
#include <sstream>
#include "MyException.h"
//---------------------------------------------------------------------------//
/*
* onstructor of logarithm expression
* Gets a pointer to function used as inner function and the logarithm base
*/
Log::Log(std::shared_ptr<Function> p, double base)
	:UnaryExp(p), m_base(base) { }

//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a number as optional argument, if so print log(f(4)) (e.g num = 4)
* otherwise print log(f) , f as inner function
*/
void Log::print(double num) const
{
	std::ostringstream ostreamer;
	ostreamer << m_base;
	check_value(num);
	UnaryExp::print("log" + ostreamer.str(), num);
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
std::shared_ptr<Function> Log::clone() const
{
	return std::make_shared<Log>(*this);
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the logarithm value of a function at certain x
* Get a double number and return the the funtion value at this point
*/
double Log::valueAt(double value) const
{
	Function::check_value(value);
	return UnaryExp::fixTo2Digits( log(m_expression->valueAt(value)) / log(m_base) );
}

//---------------------------------------------------------------------------//
/*
* Method that checks if a value is in the Range of sqrt Function
* Get a double number and if so, throws exception
*/
void Log::check_value(double value) const
{
	if (value <= 0)
		throw MinException(0, false);
}