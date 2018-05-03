#include "faculty_value.h"

// vector to save the different faulties names according their presenting number
std::vector<std::string> FacultyValue::m_names = 
{"", "Computer Science" ,"Medicine" ,"Literature" };

//---------------------------------------------------------------------------//
/*
 * Constructor of The Faculty-Value, defined by a integer 
 */

FacultyValue::FacultyValue(int value)
	:m_facultyName(value) { }

//---------------------------------------------------------------------------//
/*
 * Method that sets The faculty name (as number)
 * @param integer
 */
void FacultyValue::setName(int value)
{
	m_facultyName = value;
}

//---------------------------------------------------------------------------//
/*
 * Method to return The faculty name (as number)
 */
std::string FacultyValue::getName() const 
{
	if (m_facultyName >= 1 && m_facultyName <= 3)
		return m_names[m_facultyName];
	else
		return std::to_string(m_facultyName);
}

//---------------------------------------------------------------------------//
/*
 *  Cast operator from FacultyValue to int
 */
FacultyValue::operator int() const
{
	return m_facultyName;
}

///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------//
/*
 * Insertion operator for FacultyValue 
 */
std::istream& operator>>(std::istream& input, FacultyValue& facultyVal)
{
	int num;
	input >> num;
	facultyVal.setName(num);
	return input;
}

//---------------------------------------------------------------------------//
/*
 * Extraction operator for FacultyValue
 */
std::ostream& operator<<(std::ostream& output, const FacultyValue& facultyVal)
{
	output << facultyVal.getName();
	return output;
}
