#pragma once

#include "BinaryExp.h"

class Mul : public BinaryExp
{
public:
	Mul(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2);
	virtual void print(double num = INT_MAX) const override;
	virtual void setVar(std::shared_ptr<Function>)override;
	virtual std::shared_ptr<Function> clone() const;

	double valueAt(double value) const override;
};

