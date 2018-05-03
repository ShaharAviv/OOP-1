#include "id_validator.h"

const int ID_SIZE = 9;			// length of a valid id

//---------------------------------------------------------------------------//
/*
 * Constructor of Id Validator
 */
IDValidator::IDValidator()
	:Validator<uint32_t>("Wrong control digit") { }

//---------------------------------------------------------------------------//
/*
 * Method that checks if a value suit correctly (as id number).
 * Gets uint32_t as the value to check.
 * Executes the algorithm of checking validality of an id.
 */
bool IDValidator::check(const uint32_t& data)
{
	std::string idNum = std::to_string(data);
	int sum = 0;

	if (idNum.size() != ID_SIZE)		// id is length is incorrect
		return false;

	int incNum;				// sums the digit after multiply by 1 or 2
	for (int i = 0; i < ID_SIZE; i++)
	{
		incNum = int(idNum[i] - '0') * ((i % 2) + 1);
		sum += (incNum > 9) ? incNum - 9 : incNum;
	}

	return (sum % 10 == 0);
}
