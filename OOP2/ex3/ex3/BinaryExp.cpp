#include "BinaryExp.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
* Constructor of a Binary exprssion
* Gets 2 pointers to function used as 2 inner functions
*/
BinaryExp::BinaryExp(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2)
	:m_func1(p1), m_func2(p2) { }


//---------------------------------------------------------------------------//
/*
* Method of printing the function
* Gets a char as the operator between the 2 function sand a number as 
* optional argument,
* if so print with the number as instead of the varaiable.
*/
void BinaryExp::print(char op, double num) const
{
	m_func1->check_value(num);
	m_func2->check_value(num);
	std::cout << "(";
	(num == INT_MAX) ? m_func1->print() : m_func1->print(num);
	std::cout << ") " << op << " (";
	(num == INT_MAX) ? m_func2->print() : m_func2->print(num);
	std::cout << ")";
}

