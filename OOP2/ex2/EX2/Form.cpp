#include "Form.h"
#include <iostream>

//---------------------------------------------------------------------------//
/*
 * Method which adds new field to the form
 * Gets a pointer to the desired field
 */
void Form::addField(FieldGen * toAdd)
{
	m_fields.push_back(toAdd);
}

//---------------------------------------------------------------------------//
/*
 * Method which adds new form-validator to the form
 * Gets a pointer to the desired validator
 */
void Form::addValidator(ValidatorForm * toAdd)
{
	m_validators.push_back(toAdd);
	m_areValids.push_back(false);
}

//---------------------------------------------------------------------------//
/*
 * Method thats print the form information (all the fields' info) to a desired
 * output stream.
 * Gets this stream as an argument (on default print to std::cout)
 */
void Form::print(std::ostream& output) const
{
	if (validateForm())   // form is fully validated
	{
		for (auto& field : m_fields)
		{
			output << std::string(60, '-') << '\n';
			output << *field;
			output << std::string(60, '-') << '\n';
		}
	}

	else                  // case not all fields are validated 
	{
		for (auto& field : m_fields)
		{
			if (!field->isValid())
			{
				output << std::string(60, '-') << '\n';
				output << *field;
				output << std::string(60, '-') << '\n';
			}
		}

		output << "\n";
		for (size_t i = 0 ; i < m_validators.size(); i++)
			if (!m_areValids[i])
			{
				SetOutputColor(FG_WHITE | BACKGROUND_RED);
				output << m_validators[i]->getMsgError() << "\n";
				ResetOutputColor();
			}
	}
}

//---------------------------------------------------------------------------//
/*
 * Method thats enable the user to fill up the forms info
 */
void Form::fillForm()
{
	for (auto field : m_fields)
		if (!field->isValid())		// (re)fill only not validated fields
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED |BACKGROUND_INTENSITY | BACKGROUND_GREEN);
			std::cout << field->getQuest() << "\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_WHITE);
			field->readData();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_DEFAULT);
			std::cout << "\n";
		}
}

//---------------------------------------------------------------------------//
/*
 * Method that checks the form's validation
 * returns true if it is.
 */
bool Form::validateForm() const
{
	bool check = true;			// determine the form's validation

    // checks if each of the form's field are validate
	for (auto& field : m_fields)
	{
		field->checkIfValid();
		if (!field->isValid())
			check = false;
	}

	// checks if all the form's validators are good
	for (auto& v : m_validators)
		if (!v->check())
			check = false;
	
	return check;
}

//---------------------------------------------------------------------------//
/*
 * Extraction operator for form
 */
std::ostream & operator<<(std::ostream & output, const Form & aForm)
{
	aForm.print(output);
	return output;
}
