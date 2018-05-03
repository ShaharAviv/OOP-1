#pragma once

#include "UnaryExp.h"


class Sqrt : public UnaryExp
{
public:
	Sqrt(std::shared_ptr<Function> p = std::make_shared<VarX>() );
	virtual void print(double num = INT_MAX)const override;
	virtual std::shared_ptr<Function> clone() const;
	double valueAt(double value) const override;
	
	void check_value(double value) const;

};
