#pragma once
#include <vector>
#include <string>

class FacultyValue
{
public:
	FacultyValue(int value = 0);
	void setName(int value);
	std::string getName() const;
	operator int() const;

private:
	int m_facultyName;
	static std::vector<std::string> m_names;
};

//===========================================================================//

std::istream& operator>>(std::istream& input, FacultyValue& facultyVal);
std::ostream& operator<<(std::ostream& output, const FacultyValue& facultyVal);
std::string to_string(const FacultyValue& facultyVal);


