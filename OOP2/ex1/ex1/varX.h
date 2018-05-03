#pragma once

#include "Function.h"

class VarX : public Function
{
public:
	VarX() {}
//	virtual void evaluate(double num) const override;
//	virtual void print() const override;
//	virtual double sum(double value) const override;
	virtual std::shared_ptr<Function> clone() const;

	virtual void print(double num = INT_MAX) const;
	virtual double valueAt(double value) const;
};

