#pragma once

#include "VarX.h"
#include <string>

class UnaryExp : public Function
{
public:
	UnaryExp(std::shared_ptr<Function> p = std::make_shared<VarX>());
	virtual void print(double num = INT_MAX) const = 0; // ?? ===> { }


//	virtual void print() const = 0;
///	virtual double sum(double value) const  = 0;
	virtual void setVar(std::shared_ptr<Function>) = 0;

	virtual double valueAt(double value) const = 0;

protected:
	std::shared_ptr<Function> m_expression;
	double fixTo2Digits(double x) const;	
	
	virtual void print(std::string funcName,double num = INT_MAX) const;
};

