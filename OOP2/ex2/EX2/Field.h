#pragma once
#include "FieldGen.h"
#include "Validator.h"
#include "faculty_value.h"
#include "help.h"
#include <iostream>
#include <iomanip>

template<typename T>
class Field : public FieldGen
{
public:
	Field(const std::string& data = "");

	void addValidator(ValidatorGen* toAdd) override;
	void readData() override;
	bool isValid() const override;
	void checkIfValid() override;
	std::string getQuest() const override;
	std::string getData() const override;
	std::string getErrorMsg() const override;
	void setValid(bool val) override;

	void print(std::ostream& = std::cout) const override;
	bool operator<=(int value) const override;
	bool operator>=(int value) const override;

private:
	T m_ans;
};

//===========================================================================//

//---------------------------------------------------------------------------//
/*
 * Constructor of The Template-Class field
 * Gets a string as the question the user have to fill
 */
template<typename T>
Field<T>::Field(const std::string& question)
	:FieldGen(question) { }

//---------------------------------------------------------------------------//
/*
 * Method which adds new validator to the field
 * Gets a pointer to the desired validator
 */
template<typename T>
void Field<T>::addValidator(ValidatorGen* toAdd)
{
	m_validators.push_back(toAdd);
	m_areValids.push_back(false);
}

//---------------------------------------------------------------------------//
/*
* Method which sets the field's data (answer)
*/
template<typename T>
void Field<T>::readData()
{
	std::cin >> m_ans;
}

//---------------------------------------------------------------------------//
/*
* Specialized Method which sets a string-field's data (answer)
*/
template<>
inline void Field<std::string>::readData()
{
	m_ans = "";
	while (m_ans.empty())
		std::getline(std::cin, m_ans);
}

//---------------------------------------------------------------------------//
/*
 * Method which returns the field question
 * returns it as a string
 */
template<typename T>
std::string Field<T>::getQuest() const
{
	return m_data;
}

//---------------------------------------------------------------------------//
/*
 * Specialized Method which returns the field's data (answer)
 * returns it as a string
 */
template<typename T>
std::string Field<T>::getData() const
{
	return std::to_string(m_ans);
}

//---------------------------------------------------------------------------//
/*
* Specialized Method which returns the field's data (answer)
* returns it as a string
*/
template<>
inline std::string Field<std::string>::getData() const
{
	return m_ans;
}

//---------------------------------------------------------------------------//
/*
* Specialized Method which returns the field's data (answer)
* returns it as a string
*/
template<>
inline std::string Field<FacultyValue>::getData() const
{
	return std::to_string(int(m_ans));
}

//---------------------------------------------------------------------------//
/*
 * Method which returns the field's errors (if exist)
 */
template<typename T>
std::string Field<T>::getErrorMsg() const
{
	std::string allMsgs;

	for (int i = 0; i < m_areValids.size(); i++)
		if (!m_areValids[i])
			allMsgs += "  (*" + m_validators[i]->getMsgError() + ")\n\t\t\t\t   ";

	return allMsgs;
}

//---------------------------------------------------------------------------//
/*
 * Operator to compares if field's data is <= from a value
 * get the value as integer
 */
template<typename T>
bool Field<T>::operator<=(int value) const
{
	return stoi(getData()) <= value;
}

//---------------------------------------------------------------------------//
/*
* Operator to compares if field's data is <= from a value
* get the value as integer
*/
template<typename T>
bool Field<T>::operator>=(int value) const
{
	return stoi(getData()) >= value;
}

//---------------------------------------------------------------------------//
/*
 * Method that return the field's validation
 * returns true if it is.
 */
template<typename T>
bool Field<T>::isValid() const
{
	return m_valid;
}

//---------------------------------------------------------------------------//
/*
 * Method that checks if the field is valid.
 * returns true if it is.
 */
template<typename T>
void Field<T>::checkIfValid()
{
	size_t i;			// index for running on array

	// pass over all validators
	for (i = 0; i < m_validators.size(); i++)
		m_areValids[i] = ((Validator<T>*)(m_validators[i]))->check(m_ans);

	// check the values got from them
	for (i = 0; i < m_areValids.size(); i++)
		if (!m_areValids[i])
			break;

	// if we ended the loop completely, the field is valid
	m_valid = (i == m_validators.size());
}

//---------------------------------------------------------------------------//
/*
* Method thats print the field information (question and answer, and in some 
* cases, errors) to a desired output stream
* get this stream as an argument (on default print to std::cout)
*/
template<typename T>
void Field<T>::print(std::ostream & output) const
{
	SetOutputColor(FG_YELLOW);
	output << getQuest();
	SetOutputColor(FG_WHITE);

	output << " = " << m_ans << "\n";
	if (!m_valid)
	{
		output << "\t\t\t\t   ";
		SetOutputColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
		output << getErrorMsg() << "\n";
	}
	ResetOutputColor();
}

//---------------------------------------------------------------------------//
/*
 * Method set the field's validation
 */
template<typename T>
void Field<T>::setValid(bool val)
{
	m_valid = val;
}

