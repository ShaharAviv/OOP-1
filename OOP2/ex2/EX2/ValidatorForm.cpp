#include "ValidatorForm.h"

//---------------------------------------------------------------------------//
/*
 * Constructor of Form validator
 * Gets a string as the error of the validator in case it's invalid
 */
ValidatorForm::ValidatorForm(std::string errorMsg)
	:ValidatorGen(errorMsg) { }
