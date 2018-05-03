#pragma once


#include <memory>		// for shared_ptr()
#include <vector>
#include "Function.h"
#include <string>

#define NO_DATA INT_MAX
//
#define _USE_ENUM 1
using std::string;

enum COMMAND_T
{
	EXIT_OP,
	HELP_OP,

	EVALUATE_OP,
	ADD_OP,
	REVERSE_OP,
	POLY_OP,
	DELETE_OP,
	MULTIPLY_OP,
	LOG_OP,
	COMPOSTION_OP,

	READ_FILE_OP,   // NEW
	RESIZE_OP // NEW
};

class Calculator
{
public:
	Calculator();
	void run();
	void run2();


private:
	std::vector <std::shared_ptr<Function>> m_funcList;
	bool m_onHelp;
	std::vector<std::string> m_knownCommands;
	
	/*** private functions ***/
	void help(string args) /*const*/;
	void print() const;

	void eval(string args) const;
	void addFuncs(string args);
	void multiplyFuncs(string args);
	void composite(string args);
	void reversePoly(string args);
	void log(string args);
	void deleteFunc(string args);
	void addPoly(string args);


	void catch_2_much_n(string args, int = 2) const;
	void catch_index(int) const;

	void catch_invalid_args(string args, int& funcNum1, int& funcNum2) const;
	void catch_invalid_args(string args, int& funcNum) const;
	void catch_valid_log_args(string args, double& base, int& funcNum) const;
	void HandleFile();
	bool HandleCommand(std::string command);
	void resize(std::string command);
	void askSize();

	int m_cell_used;
	//template<typename... ArgTypes>
	//bool foo(std::string args, ArgTypes... nums);

	//template<typename T, typename... ArgTypes>
	//bool foo(std::string args, T& t, ArgTypes... nums);

	//template<>
	//bool foo(std::string args);
};

