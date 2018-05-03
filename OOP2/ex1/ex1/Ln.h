#pragma once

#include "Log.h"

class Ln : public Log
{
public:
	Ln(std::shared_ptr<Function> p = std::make_shared<VarX>());
//	virtual void evaluate(double num) const override;
	virtual void print(double num = INT_MAX) const override;
	virtual void setVar(std::shared_ptr<Function>);
	virtual std::shared_ptr<Function> clone() const override;

};
//
//std::ostream& operator<<(std::ostream& output, const std::shared_ptr<Ln> Func)
//{
//	Func->print();
//	return output;
//}

