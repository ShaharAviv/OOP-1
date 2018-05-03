#pragma once
#include "Function.h"
class BinaryExp : public Function
{
public:
	BinaryExp(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2);

	virtual void setVar(std::shared_ptr<Function>) = 0;
	virtual double valueAt(double value) const  = 0;

protected:
	std::shared_ptr<Function> m_func1;
	std::shared_ptr<Function> m_func2;

	// private function
	virtual void print(char op, double num = INT_MAX) const;
};

