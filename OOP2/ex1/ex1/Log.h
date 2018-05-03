#pragma once
#include "UnaryExp.h"

class Log : public UnaryExp
{ 
public:
	Log() {}
	Log(std::shared_ptr<Function> p, double base);
//	virtual void evaluate(double num) const override;
	virtual void print(double num = INT_MAX) const override;
///	virtual double sum(double value) const override;
	virtual void setVar(std::shared_ptr<Function>)override;
	virtual std::shared_ptr<Function> clone() const;


	double valueAt(double value) const override;

protected:
	double m_base;
};

