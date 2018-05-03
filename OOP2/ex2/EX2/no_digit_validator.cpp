#include "no_digit_validator.h"

//---------------------------------------------------------------------------//
/*
* Constructor of no-digit validator
*/
NoDigitValidator::NoDigitValidator()
	:Validator<std::string>("Can't contain digits") { }

//---------------------------------------------------------------------------//
/*
 * Method that checks if a value suit correctly (have no digits).
 * Gets string as the value to check.
 */
bool NoDigitValidator::check(const std::string& data)
{
	int i;
	for (i=0 ; i<data.size(); i++)
		if (isdigit(data[i]))
			break;
		
	return (i == data.size());;
}


