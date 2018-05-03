#pragma once
#include "UnaryExp.h"

class Log : public UnaryExp
{ 
public:
	Log() {}
	Log(std::shared_ptr<Function> p, double base);

	virtual void print(double num = INT_MAX) const override;
	virtual std::shared_ptr<Function> clone() const;
// 	double valueAt(double value) const override;
// 
// 	void check_value(double value) const;
protected:
	double m_base;
	double valueAt(double value) const override;

	void check_value(double value) const;
};

