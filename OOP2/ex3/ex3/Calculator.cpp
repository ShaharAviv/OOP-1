#include "Calculator.h"
#include "Ln.h"
#include "Sqrt.h"
#include "Poly.h"
#include "Mul.h"
#include "Add.h"
#include "MyException.h" //

#include <iomanip>   
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

static const int MAX_COMMAND_SIZE = 5;
//---------------------------------------------------------------------------//
/*
 * Constructor of Calculator Object, defines a new Calculator board with
 * sqrt(x) an ln(x) functions as base list
 */
Calculator::Calculator()
	:m_onHelp(false), m_cell_used(2)
{
	// add pre-made functions
	m_funcList.push_back(std::make_shared<Ln>());
	m_funcList.push_back(std::make_shared<Sqrt>());

	// add all known commands
	m_knownCommands.emplace_back("exit");
	m_knownCommands.emplace_back("help");
	m_knownCommands.emplace_back("eval");
	m_knownCommands.emplace_back("add");
	m_knownCommands.emplace_back("rev");
	m_knownCommands.emplace_back("poly");
	m_knownCommands.emplace_back("del");
	m_knownCommands.emplace_back("mul");
	m_knownCommands.emplace_back("log");
	m_knownCommands.emplace_back("comp");

	m_knownCommands.emplace_back("read");   // NEW
	m_knownCommands.emplace_back("resize"); // NEW

}


//---------------------------------------------------------------------------//
void Calculator::askSize()		
{
	int listSize;
	do {
		std::cout << "Choose the limit of the function the calculator can hold:\n";
		std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		try
		{
			std::cin >> listSize;
			if (listSize <= 2)
				throw MinException(2, false);

			break;
		}
		catch (const std::ios_base::failure&)
		{
			std::cout << "Error: input can be only numeric \n";
			// reapir and clean broken std::cin stream
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		catch (std::out_of_range&)
		{
			throw MinException(2, false);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << "\n";
		}

	} while (true);
	m_funcList.resize(listSize);

}
//---------------------------------------------------------------------------//

void Calculator::run2()			
{
	std::string commandLine;
	
	askSize();
	do
	{
		if (!m_onHelp)
			print();
		else
			m_onHelp = false;

		do
		{
			std::getline(std::cin, commandLine);
		} while (commandLine.empty());

		try
		{
			if (!HandleCommand(commandLine))
				break;
		}
		catch (std::out_of_range& )
		{
			std::cout << "Error : No space left on list \n";// "Invalid argument(s) : out of list index\n";
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << "\n";
		}
	} while (true);
}

//---------------------------------------------------------------------------//

void Calculator::HandleFile()         
{
	std::string fileName,
		        commandLine;
	std::ifstream inp_fd;
	char ans;

	std::cout << "Please Enter the full path of the file to read: \n";
	std::cin >> fileName;
	inp_fd.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		inp_fd.open(fileName);
		while (!inp_fd.eof())
		{
			getline(inp_fd, commandLine);
			try {
				HandleCommand(commandLine);
			}
			catch (std::out_of_range& e)
			{
				std::cout << commandLine <<"\n";
				std::cout << "Error : No space left on list \n"
					<< "Do you want to continue reading? (y\\n) \n";

				std::cin >> ans;
				if (ans == 'n')
					break;
			}
			
			catch (std::exception& e)
			{
				std::cout << e.what() << "\n"
					<< "do you want to continue reading?  (y\\n)\n";

				std::cin >> ans;
				if (ans == 'n')
					break;
			}
		}
		inp_fd.close();
	}
	catch (const std::ifstream::failure&)
	{
		std::cout << "Error: cannot open\\ read file \n";
	}

	std::cin.ignore(256, '\n');			//ignore "read" command in buffer
}

//---------------------------------------------------------------------------//
bool Calculator::HandleCommand(std::string command)    
{
	std::string commandName,
		        commandArgs;
	std::stringstream oss;

	oss << command;
	oss >> commandName;
	size_t commandLen = commandName.size();

	commandArgs = command.substr(commandLen);

	int i;
	for (i = 0; i < m_knownCommands.size(); i++)
		if (commandName == m_knownCommands[i])
			break;

	if (i != m_knownCommands.size())		// found a known command
	{
		if ((!commandArgs.empty()) &&
			(std::all_of(commandArgs.begin(), commandArgs.end(), ::isalpha)))
			throw NoDigitException();
	}

	// now executes the requested command
	switch (COMMAND_T(i))
	{
		case EVALUATE_OP:	 eval(commandArgs);           break;
		case ADD_OP:		 addFuncs(commandArgs);       break;
		case REVERSE_OP:	 reversePoly(commandArgs);    break;
		case POLY_OP:		 addPoly(commandArgs);        break;
		case DELETE_OP:		 deleteFunc(commandArgs);     break;
		case MULTIPLY_OP:	 multiplyFuncs(commandArgs);  break;
		case LOG_OP:		 log(commandArgs);			  break;
		case COMPOSTION_OP:	 composite(commandArgs);      break;
							 							 
		case READ_FILE_OP:   HandleFile();				  break;
		case RESIZE_OP:      resize(commandArgs);         break;
							 							 
		case EXIT_OP:		 puts("Goodbye.");			  return false;
		case HELP_OP:		 help(commandArgs); 		  break;
														 
		default:			puts("Unknown command");      break;
	}

	return true;
}


//---------------------------------------------------------------------------//
/*
* This Method calculates a function at certain point
* shows to the user the value of the function
*/
void Calculator::eval(string args) const
{
	int funcNum;
	double value = NO_DATA;
	std::stringstream iss;
	iss << args;
	iss >> funcNum >> value;

	catch_2_much_n(args);

	if (value == NO_DATA)
		throw MissedArgsException(2);

	catch_index(funcNum);

	m_funcList[funcNum]->print(value);
	std::cout << " = " << m_funcList[funcNum]->valueAt(value) << "\n";
}

//---------------------------------------------------------------------------//
/*
* This Method adds 2 existing functions into new one function
* inserts the result into the calculator's function list
*/
void Calculator::addFuncs(string args)
{
	int funcNum1 = NO_DATA,
		funcNum2 = NO_DATA;

	catch_invalid_args(args, funcNum1, funcNum2);

	std::shared_ptr<Function> f1 = m_funcList.at(funcNum1);
	std::shared_ptr<Function> f2 = m_funcList.at(funcNum2);
	auto funcsSum = std::make_shared<Add>(f1, f2);

	m_funcList.at(m_cell_used) = std::move(funcsSum);
	
	m_cell_used++;


}
//---------------------------------------------------------------------------//
/*
* This Method multiplies 2 existing functions into new one function
* inserts the result into the calculator's function list
*/
void Calculator::multiplyFuncs(string args)
{
	int funcNum1 = NO_DATA,
		funcNum2 = NO_DATA;

	catch_invalid_args(args, funcNum1, funcNum2);

	std::shared_ptr<Function> f1 = m_funcList.at(funcNum1);
	std::shared_ptr<Function> f2 = m_funcList.at(funcNum2);

	auto funcsMult = std::make_shared<Mul>(f1, f2);
	m_funcList.at(m_cell_used) = std::move(funcsMult);
	m_cell_used++;
}

//---------------------------------------------------------------------------//
/*
* This Method composite 2 existing functions into new one function
* inserts the result into the calculator's function list
*/
void Calculator::composite(string args)
{
	int funcNum1 = NO_DATA,
		funcNum2 = NO_DATA;

	catch_invalid_args(args, funcNum1, funcNum2);

	std::shared_ptr<Function> funcCopy1 = m_funcList[funcNum1]->clone();
	std::shared_ptr<Function> funcCopy2 = m_funcList[funcNum2]->clone();
	
	funcCopy1->setVar(funcCopy2);	// composition of 1st func on 2nd func
	m_funcList.at(m_cell_used) = std::move(funcCopy1);
	++m_cell_used;
}

//---------------------------------------------------------------------------//
/*
* This Method reverse A function (only if it's a polynomal)
* inserts the result into the calculator's function list
*/
void Calculator::reversePoly(string args)
{
	int funcNum = NO_DATA;
	std::stringstream iss;
	iss << args;
	iss >> funcNum;

	catch_2_much_n(args, 1);

	if (funcNum == NO_DATA)
		throw MissedArgsException(1);
	catch_index(funcNum);

	std::shared_ptr<Function> funcCopy = m_funcList.at(funcNum);
	std::shared_ptr<Poly> revPoly = std::dynamic_pointer_cast<Poly>(funcCopy);
	if (!revPoly)
		throw RevException();
	
	m_funcList.at(m_cell_used) = std::move(revPoly->reverse());
	++m_cell_used;


}

//---------------------------------------------------------------------------//
/*
* This Method execute log in base N on existing functions into new one function
* inserts the result into the calculator's function list
*/
void Calculator::log(string args)
{
	double base = NO_DATA;
	int funcNum = NO_DATA;

	catch_valid_log_args(args, base, funcNum);

	std::shared_ptr<Function> func = m_funcList[funcNum];
	auto logFunc = std::make_shared<Log>(func, base);

	m_funcList.at(m_cell_used) = std::move(logFunc);
	++m_cell_used;

}

//---------------------------------------------------------------------------//
/*
* This Method remove a function in a certain position
*/
void Calculator::deleteFunc(string args)
{
	int funcNum = NO_DATA;

	catch_invalid_args(args, funcNum);
	m_funcList.erase(m_funcList.begin() + funcNum);
	--m_cell_used;
}

//---------------------------------------------------------------------------//
/*
* This Method is makes a new polynomial
* adds it to the calculator's functions list
*/
void Calculator::addPoly(string args)
{
	int polySize = NO_DATA;
	std::vector <double> v;
	std::stringstream iss;

	iss << args;
	iss >> polySize;

	if (polySize == NO_DATA)
		throw MissedArgsException();
	if (polySize < 0)
		throw MinException();

	else if (polySize != 0)
	{
		for (int i = 0; i < polySize; ++i)
		{
			int element = NO_DATA;
			iss >> element;
			v.insert(v.begin() + i, element);
		}

		catch_2_much_n(args, polySize + 1);

		if (v.at(polySize - 1) == NO_DATA)
			throw MissedArgsException(polySize + 1);

	}
	std::shared_ptr<Poly> newPoly(std::make_shared<Poly>(v, std::make_shared<VarX>()));
	m_funcList[m_cell_used] = std::move(newPoly);
	m_cell_used++;
}

//---------------------------------------------------------------------------//
/*
 * This method enables user to set a new size to the Calculator's list size
 */
void Calculator::resize(string args)	
{
	int newSize = NO_DATA;

	std::stringstream iss;
	iss << args;
	iss >> newSize;

	char ans;
	do {
		if (newSize < m_cell_used)
		{
			std::cout << "Warning: Entered a smaller size than the current used functions size\n" 
				      << "Do you want to pick a new size ? (y\\n)";

			std::cin >> ans;
			if (ans == 'y')
			{
				std::cout << "Please enter the new size of the function list: \n";
				std::cin >> newSize;
				continue;
			}
			else
				break;
		}
		else	// first was good
			break;
	} while (true);

	// we got here if user confirm to resize
	try {
		m_funcList.resize(newSize);
	}
	catch (std::exception&){
		throw MinException(0);
	}

	if (m_cell_used > newSize)
		m_cell_used = newSize;
}

//---------------------------------------------------------------------------//
/*
* This method shows the information about each of the available commands that
* user can enter
*/
void Calculator::help(std::string args)
{
	if (!args.empty())
		throw TooManyException();

	std::string msg =
		"eval(uate) num x - Evaluates function #num on x\n"
		"poly(nomial) N c0 c1 ... cN - 1 - Creates a polynomial with N coefficients\n"
		"rev(erse) num - Creates a polynomial with N coefficients in reversee order\n"
		"mul(tiply) num1 num2 - Creates a function that is the multiplication of function #num1 and function #num2\n"
		"add num1 num2 - Creates a function that is the sum of function #num1 and function #num2\n"
		"comp(osite) num1 num2 - Creates a function that is the composition of function #num1 and function #num2\n"
		"log N num - Log N of function #num\n"
		"del(ete) num - Deletes function #num from function list\n"
		"help - Prints this help screen\n"
		"exit - Exits the program\n";

	std::cout << msg;
	m_onHelp = true;	/*@1*/
}

//---------------------------------------------------------------------------//
/*
* This method shows all the available function in the current state of the
* calculator
*/
void Calculator::print() const
{
	std::cout <<"\n" << std::string(42, '=') << "\n"
		<< "This is the function list: "
		<< "[used " << m_cell_used << " of " << m_funcList.size() << "]\n";

	int index = 0;
	for (auto func = m_funcList.begin(); func < m_funcList.begin() + m_cell_used;
		                                            ++func, ++index)
	{
		std::cout << index << ": ";
		(*func)->print();
		std::cout << "\n";
	}

	std::cout << std::string(42, '=') << "\n"
			  << "Please enter a command (\"help\" for command list) \n";
}


void Calculator::catch_2_much_n(string args, int argsCount) const
{
	std::stringstream iss;
	iss << args;
	int tmp;
	for (int i = 1; i <= argsCount + 1; i++)
	{
		tmp = NO_DATA;
		iss >> tmp;
	}

	if (tmp != NO_DATA)
		throw TooManyException();
}

void Calculator::catch_index(int funcNum) const
{
//	m_funcList.at(funcNum);
	if (funcNum >= m_cell_used || funcNum < 0)
		throw IndexException();

}


void Calculator::catch_invalid_args(string args, int& funcNum1, int& funcNum2) const
{

	std::stringstream iss;
	iss << args;
	iss >> funcNum1 >> funcNum2;

	catch_2_much_n(args);
	if (funcNum2 == NO_DATA)
		throw MissedArgsException(2);
	catch_index(funcNum1);
	catch_index(funcNum2);
}

void Calculator::catch_invalid_args(string args, int& funcNum) const
{
	std::stringstream iss;
	iss << args;
	iss >> funcNum;

	catch_2_much_n(args, 1);
	if (funcNum == NO_DATA)
		throw MissedArgsException(1);
	catch_index(funcNum);

}

void Calculator::catch_valid_log_args(string args, double& base,
	                                                 int& funcNum) const
{
	std::stringstream iss;
	iss << args;
	iss >> base >> funcNum;

	catch_2_much_n(args, 1);
	if (funcNum == NO_DATA)
		throw MissedArgsException(1);
	catch_index(funcNum);
	if (base <= 0 || base == 1.f)
		throw BaseException();

}