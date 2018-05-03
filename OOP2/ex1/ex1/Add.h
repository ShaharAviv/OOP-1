#pragma once

#include "BinaryExp.h"

class Add : public BinaryExp
{
public:
	Add(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2);
//	virtual void evaluate(double num) const override;
	virtual void print(double num = INT_MAX) const override;
	virtual void setVar(std::shared_ptr<Function>);
	virtual std::shared_ptr<Function> clone() const;
	double valueAt(double value) const override;
};

