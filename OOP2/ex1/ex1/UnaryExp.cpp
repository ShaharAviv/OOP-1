#include "UnaryExp.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
* Constructor of unary Expression
* Gets a pointer to function used as inner function
*/
UnaryExp::UnaryExp(std::shared_ptr<Function> p)
	:m_expression(p) { }


//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a string as function name and a number as optional argument,
* if so print f(3) (e.g num = 3) otherwise print f(x), where f is the
* function name
*/
void UnaryExp::print(std::string funcName, double num) const
{
	std::cout << funcName << "(";
	/*(num = INT_MAX) ?*/ m_expression->print(num) /*: m_expression->print()*/;
	std::cout << ")";
}

//---------------------------------------------------------------------------//
/*
* Help-function thats cuts the results at 2 digits after point
* gets a double value to fix, and return the fixed number
*/
double UnaryExp::fixTo2Digits(double x) const
{
	double temp1 = double(x * 100);
	double temp2 = double(temp1) / 100;
	return temp2;
}
