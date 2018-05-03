#include "Add.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
* Constructor of 2 Expression consist by addition
* Gets 2 pointers to function used as 2 inner functions
*/
Add::Add(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2)
	:BinaryExp(p1, p2) {}

//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a number as optional argument, if so print (f(4) + g(4)) (e.g num = 4)
* otherwise print (f(x) + g(x))
*/
void Add::print(double num) const
{
	BinaryExp::print('+', num);
}

//---------------------------------------------------------------------------//
/*
* This method sets the inner function
* Gets a pointer to function used as inner function and replaced it
*/
void Add::setVar(std::shared_ptr<Function> p)
{
	m_func1->setVar(p);
	m_func2->setVar(p);
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object
* Return the new copy pointer
*/
std::shared_ptr<Function> Add::clone() const
{
	return std::make_shared<Add>(m_func1->clone(), m_func2->clone());
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the value of addition 2 function at certain x
* Get a double number and return the the funtion value at this point
*/
double Add::valueAt(double value) const
{
	return m_func1->valueAt(value) + m_func2->valueAt(value);
}

