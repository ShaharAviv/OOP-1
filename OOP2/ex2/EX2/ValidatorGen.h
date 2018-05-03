#pragma once

#include <string>

class ValidatorGen
{
public:
	ValidatorGen(std::string errorMsg);
	virtual std::string getMsgError() const;


protected:
	std::string m_msgError;
	bool m_valid;
};