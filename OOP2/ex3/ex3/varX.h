#pragma once

#include "Function.h"

class VarX : public Function
{
public:
	virtual void print(double num = INT_MAX) const;
	virtual double valueAt(double value) const;
	virtual std::shared_ptr<Function> clone() const;
};

