#include "Mul.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
* Constructor of 2 Expression consist by multiplication
* Gets 2 pointers to function used as 2 inner functions
*/
Mul::Mul(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2)
	:BinaryExp(p1, p2) {}

//---------------------------------------------------------------------------//
/*
*
*/
void Mul::print(double num) const
{
	/*(num == INT_MAX)?*/ BinaryExp::print('*', num)/* :BinaryExp::print('*')*/;
}


//---------------------------------------------------------------------------//
/*
*
*/
void Mul::setVar(std::shared_ptr<Function> p)
{
	m_func1->setVar(p);
	m_func2->setVar(p);
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
std::shared_ptr<Function> Mul::clone() const
{
	return std::make_shared<Mul>(m_func1->clone(), m_func2->clone());
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the value of multiply 2 function at certain x
* Get a double number and return the the funtion value at this point
*/
double Mul::valueAt(double value) const
{
	return m_func1->valueAt(value) * m_func2->valueAt(value);
}