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
	UnaryExp::print("ln" ,num);
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
void Ln::setVar(std::shared_ptr<Function> p)
{
	//if (std::dynamic_pointer_cast<VarX>(m_expression))
	//{
		m_expression = p->clone();
	//}
	//else
//		m_expression->setVar(p->clone());

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
