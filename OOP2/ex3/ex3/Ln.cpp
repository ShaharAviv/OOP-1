#include "Ln.h"

#define _USE_MATH_DEFINES 
#include <math.h>
#include <iostream>
#include <iomanip>

//---------------------------------------------------------------------------//
/*
* onstructor of ln (log e) expression
* Gets a pointer to function used as inner function
*/
Ln::Ln(std::shared_ptr<Function> p)
	:Log(p, double(M_E)) {}

//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a number as optional argument, if so print ln(f(9)) (e.g num = 9)
* otherwise print ln(f) , f as inner function
*/
void Ln::print(double num) const
{
	check_value(num); // check if the value is in Range(ln)
	UnaryExp::print("ln" ,num);
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
std::shared_ptr<Function> Ln::clone() const
{
	return std::make_shared<Ln>(*this);
}
