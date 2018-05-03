#include "VarX.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
 * Method of printing the function
 * Gets a number as optional argument, id so print the num
 * otherwise print x
 */
void VarX::print(double num) const
{
	(num == INT_MAX) ? std::cout << "x" : std::cout << num;	
}

//---------------------------------------------------------------------------//
/*
* Method thats create new (copied) pointer to the current object 
* Return the new copy pointer
*/
std::shared_ptr<Function> VarX::clone() const
{
	return std::make_shared<VarX>(*this);
}

//---------------------------------------------------------------------------//
/*
* Method thats calcs the function's value at certain x
* Get a double number and return the the funtion value at this point
*/
double VarX::valueAt(double value) const
{
	return value;
}
