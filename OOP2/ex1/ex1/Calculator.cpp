#include "Calculator.h"
#include "Ln.h"
#include "Sqrt.h"
#include "Mul.h"
#include "Add.h"
#include "Composite.h"

#include <iomanip>   
#include <iostream>
#include <fstream>
#include <string>

//---------------------------------------------------------------------------//
/*
 * Constructor of Board Object, defines a new Empty board with no cookies
 */
Calculator::Calculator()
{
	m_funcList.push_back(std::make_shared<Ln>());
	m_funcList.push_back(std::make_shared<Sqrt>());
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Calculator::add()
{
	int funcNum1, funcNum2;
	std::cin >> funcNum1 >> funcNum2;
	std::shared_ptr<Function> f1 = m_funcList[funcNum1];
	std::shared_ptr<Function> f2 = m_funcList[funcNum2];

	m_funcList.push_back(std::make_shared<Add>(f1, f2));
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Calculator::multiply()
{
	int funcNum1, funcNum2;
	std::cin >> funcNum1 >> funcNum2;
	std::shared_ptr<Function> f1 = m_funcList[funcNum1];
	std::shared_ptr<Function> f2 = m_funcList[funcNum2];

	m_funcList.push_back(std::make_shared<Mul>(f1, f2));
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::composite()
{
	int funcNum1, funcNum2;
	std::cin >> funcNum1 >> funcNum2;
	std::shared_ptr<Function> funcCopy1 = m_funcList[funcNum1]->clone();
	std::shared_ptr<Function> funcCopy2 = m_funcList[funcNum2]->clone();

	funcCopy1->print(); std::cout << " ® "; funcCopy2->print(); puts("");

	funcCopy1->setVar(funcCopy2);
	m_funcList.push_back(funcCopy1);

	/// tried to use comp-Class, bad idea
	//int funcNum1, funcNum2;
	//std::cin >> funcNum1 >> funcNum2;
	//std::shared_ptr<Function> f1 = m_funcList[funcNum1];
	//std::shared_ptr<Function> f2 = m_funcList[funcNum2];

	//m_funcList.push_back(std::make_shared<Composite>(f1, f2));


}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::reversePoly()
{
	int funcNum;
	std::cin >> funcNum;
	std::shared_ptr<Function> funcCopy = m_funcList[funcNum];

	// checks if this function is a Polynomal
	if (std::dynamic_pointer_cast<Poly>(funcCopy))
	{
		std::shared_ptr<Poly> revPoly = std::dynamic_pointer_cast<Poly>(funcCopy);
		m_funcList.push_back(revPoly->reverse());
	}

	else
		std::cout << "Error: cannot reverse this function \n";
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::log()
{
	double base;
	int funcNum;
	std::cin >> base >> funcNum;
	std::shared_ptr<Function> func = m_funcList[funcNum];
	m_funcList.push_back(std::make_shared<Log>(func, base));
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::deleteFunc()
{
	int funcNum;
	std::cin >> funcNum;
	m_funcList.erase(m_funcList.begin() + funcNum);
}

//---------------------------------------------------------------------------//
/*
*
*/
std::shared_ptr<Poly> Calculator::makePoly()
{
	int polySize;
	std::cin >> polySize;
	std::vector <double> v(polySize);

	for (size_t i = 0; i < v.size(); i++)
		std::cin >> v[i];

	return std::make_shared<Poly>(v, std::make_shared<VarX>());
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::run()
{
	bool onHelp = false;
	std::string commandName;

	do
	{
		if (!onHelp)
			print();
		else
			onHelp = false;

		std::cin >> std::setw(5) >> commandName;

		if (commandName == "exit")
		{
			std::cout << "Goodbye.\n";
			break;
		}
		else if (commandName == "help")
		{
			help();
			onHelp = true;
			continue;
		}

		if (commandName == "eval")
		{
			int funcNum;
			double value;
			std::cin >> funcNum >> value;

			m_funcList[funcNum]->print(value);
			std::cout << " = " << m_funcList[funcNum]->valueAt(value);
			std::cout << "\n";

		}
		else if (commandName == "rev")
			reversePoly();

		else if (commandName == "poly")
			m_funcList.push_back(makePoly());

		else if (commandName == "del")
			deleteFunc();

		else if (commandName == "mul")
			multiply();

		else if (commandName == "add")
			add();

		else if (commandName == "log")
			log();

		else if (commandName == "comp")
			composite();

	} while (1);
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::help() const
{
	std::ifstream file;
	std::string line;
	file.open("msg.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file \n";
		exit(EXIT_FAILURE);
	}
	while (!file.eof())
	{
		getline(file, line);
		std::cout << line << std::endl;
	}
	file.close();

	// 		std::string msg =
	// 		"eval(uate) num x - Evaluates function #num on x\n"
	// 		"poly(nomial) N c0 c1 ... cN - 1 - Creates a polynomial with N coefficients\n"
	// 		"rev(erse) num - Creates a polynomial with N coefficients in reversee order\n"
	// 		"mul(tiply) num1 num2 - Creates a function that is the multiplication of function #num1 and function #num2\n"
	// 		"add num1 num2 - Creates a function that is the sum of function #num1 and function #num2\n"
	// 		"comp(osite) num1 num2 - Creates a function that is the composition of function #num1 and function #num2\n"
	// 		"log N num - Log N of function #num\n"
	// 		"del(ete) num - Deletes function #num from function list\n"
	// 		"help - Prints this help screen\n"
	// 		"exit - Exits the program\n";
	// 
	// 	std::cout << msg;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Calculator::print() const
{
	std::cout << "This is the function list:\n";

	for (size_t index = 0; index < m_funcList.size(); index++)
	{
		std::cout << index << ": ";///<< m_funcList[index];
		m_funcList[index]->print();
		std::cout << "\n";
	}

	std::cout << "Please enter a command (\"help\" for command list) \n";
}