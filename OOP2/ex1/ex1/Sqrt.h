#pragma once

#include "UnaryExp.h"


class Sqrt : public UnaryExp
{
public:
	Sqrt(std::shared_ptr<Function> p = std::make_shared<VarX>() );
///	virtual void evaluate(double num) const override;
	virtual void print(double num = INT_MAX)const override;
///	virtual double sum(double value) const override;
	virtual void setVar(std::shared_ptr<Function>);
	virtual std::shared_ptr<Function> clone() const;

	double valueAt(double value) const override;
	
};

//std::ostream& operator<<(std::ostream& output, const std::shared_ptr<Sqrt> Func)
//{
//	Func->print();
//	return output;
//}