#pragma once

#include "UnaryExp.h"
#include <vector>

class Poly : public UnaryExp
{
public:
	Poly(std::vector <double> vec, std::shared_ptr<Function> p);
	
	virtual void print(double num = INT_MAX) const override;
	std::shared_ptr<Poly> reverse();
	virtual std::shared_ptr<Function> clone() const;
	double valueAt(double value) const override;
	
private:
	std::vector <double> m_coeffs;	
};

