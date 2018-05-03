#pragma once
#include "Validator.h"

class NoDigitValidator : public Validator<std::string>
{
public:
	NoDigitValidator();
	bool check(const std::string& data) override;
};
