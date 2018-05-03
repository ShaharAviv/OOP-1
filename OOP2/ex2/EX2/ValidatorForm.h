#pragma once

#include "ValidatorGen.h"

class ValidatorForm : public ValidatorGen
{
public:
	ValidatorForm(std::string errorMsg);
	virtual bool check() const = 0;
	
};