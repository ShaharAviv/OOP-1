
#pragma warning(disable : 4996)


#include <iostream>
#include <stdlib.h>

#include <string>

#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#endif

class MissedArgsException : public std::exception 
{
public:
	MissedArgsException(int numofexp = 0)
	{
		m_n = numofexp;

		if (m_n == 0)
			sprintf_s(m_err_msg, 100, "Invalid size of input: missing argument(s)");
		else
			sprintf_s(m_err_msg, 100, "Invalid size of input: missing argument(s), require %d", m_n);
	}
	char const* what() const noexcept override // No-throw guarantee: this function never throws exceptions
	{									 // throw MyException{}; // This will cause a warning at compile time.
		return &m_err_msg[0];
	}

private:
	int m_n;
	char m_err_msg[100] = "";
};

class MinException : public std::exception 
{
public:
	MinException(int lowLimit = 0, bool included = true)
		:m_lowLimit(lowLimit), m_included(included)
	{
		const char* includeSign = (m_included) ? ">=" : ">";
// 		if (m_included)
// 			sprintf_s(m_err_msg, 100, "invalid argument, %s must be %s %d",subject, ">=", m_lowLimit);
// 		else
//			sprintf_s(m_err_msg, 100, "invalid argument, %s must be %s %d",subject, ">", m_lowLimit);
		sprintf_s(m_err_msg, 100, "invalid argument, %s must be %d", includeSign, m_lowLimit);
	}
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
										 // throw MyException{}; // This will cause a warning at compile time.
		return &m_err_msg[0];
	}
private:
	int m_lowLimit;
	bool m_included;
	char m_err_msg[100] = "";
};

class IndexException : public std::exception {
public:
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
												  // throw MyException{}; // This will cause a warning at compile time.
		return "Invalid argument(s) : out of list index";
	}
};


class RevException : public std::exception {
public:
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
										 // throw MyException{}; // This will cause a warning at compile time.
		return "Error: cannot reverse this function";
	}
};


class TooManyException : public std::exception {
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
										 // throw MyException{}; // This will cause a warning at compile time.
		return "Invalid arguments : too many arguments";
	}
};

class BaseException : public std::exception {
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
										 // throw MyException{}; // This will cause a warning at compile time.
		return "Invalid base argument";
	}
};

class NoDigitException : public std::exception {
	const char * what() const noexcept override { // No-throw guarantee: this function never throws exceptions
										 // throw MyException{}; // This will cause a warning at compile time.
		return "Error: input can be only numeric \n";
	}
};