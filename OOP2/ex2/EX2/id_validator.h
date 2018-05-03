#pragma once
#include "Validator.h"

class IDValidator : public Validator<uint32_t>
{
public:
	IDValidator();
	bool check(const uint32_t& data);
	bool isValid() const
	{
		return m_valid;
	}
	
};

