#pragma once
#include "BinaryExp.h"
class Composite : public BinaryExp
{
public:
	Composite(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2);

	virtual void setVar(std::shared_ptr<Function>)override {}
	virtual void print(double num = INT_MAX) const override;
	virtual double valueAt(double value) const override;

	virtual std::shared_ptr<Function> clone() const {
		return std::make_shared<Composite>(m_func1->clone(), m_func2->clone());
	}
};

