#pragma once

#include <vector>
#include "ValidatorGen.h"
#include <iostream>

class FieldGen
{
public:
	FieldGen(const std::string&);

	virtual void addValidator(ValidatorGen* toAdd) = 0;
	virtual void readData() = 0;
	virtual bool isValid() const = 0;
	virtual void checkIfValid() = 0;
	virtual std::string getQuest() const = 0;
	virtual std::string getData() const = 0;
	virtual std::string getErrorMsg() const = 0;
	
	virtual void setValid(bool val) = 0;
	virtual void print(std::ostream& = std::cout) const = 0;

	virtual bool operator<=(int value) const = 0;
	virtual bool operator>=(int value) const = 0;

protected:
	std::string m_data;
	std::vector<ValidatorGen*> m_validators;
	std::vector<bool> m_areValids;
	bool m_valid;

};

std::ostream& operator<<(std::ostream& output, const FieldGen& fieldGen);
