#pragma once
#include <memory>

class Function
{
public:
	virtual void print(double num = INT_MAX) const = 0; 
	virtual double valueAt(double value) const  = 0;
	virtual std::shared_ptr<Function> clone() const = 0;
	virtual void setVar(std::shared_ptr<Function>) {};

	virtual void check_value(double value) const;
};
