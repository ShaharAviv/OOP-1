#include "ValidatorGen.h"

//---------------------------------------------------------------------------//
/*
 * Constructor of General validator
 * Gets a string as the error of the validator in case it's invalid
 */
ValidatorGen::ValidatorGen(std::string errorMsg)
	:m_msgError(errorMsg), m_valid(false)
{
}

//---------------------------------------------------------------------------//
/*
 *	Method that return the validator's error message
 *	return it as a string
 */
std::string ValidatorGen::getMsgError() const
{
	return m_msgError;
}

