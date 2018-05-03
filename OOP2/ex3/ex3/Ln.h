#pragma once

#include "Log.h"

class Ln : public Log
{
public:
	Ln(std::shared_ptr<Function> p = std::make_shared<VarX>());
	virtual void print(double num = INT_MAX) const override;
	virtual std::shared_ptr<Function> clone() const override;
};


