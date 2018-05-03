#pragma once

#include "Poly.h"
#include <memory>		// for shard_ptr()
#include <vector>

class Calculator
{
public:
	Calculator();
	void run();

private:
	std::vector <std::shared_ptr<Function>> m_funcList;

	// private function
	void help() const;
	void print() const;
	void add();
	void multiply();
	void composite();
//	std::shared_ptr<Function> reversePoly(int);
	void reversePoly();
	void log();
	void deleteFunc();
	std::shared_ptr<Poly> makePoly();
};

