#include "Composite.h"
#include <iostream>




Composite::Composite(std::shared_ptr<Function> p1, std::shared_ptr<Function> p2)
	:BinaryExp(p1, p2) {}

void Composite::print(double num) const
{
    ///?
	// dont want to print sqrt(x)(ln (X)) 
	// correct: sqrt( ln(x) )

	std::shared_ptr<Function> funcCopy1 = m_func1->clone();
	//funcCopy1->print();
	std::shared_ptr<Function> funcCopy2 = m_func2->clone();
	funcCopy1->setVar(funcCopy2);
	funcCopy1->print();
}

double Composite::valueAt(double value) const
{
	return m_func1->valueAt(m_func2->valueAt(value));
}
