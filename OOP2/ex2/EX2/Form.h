#pragma once
#include "Field.h"
#include "ValidatorForm.h"
#include <vector>

class Form
{
public:
	Form() { ShowConsoleCursor(false); }
	void addField(FieldGen* toAdd);
	void addValidator(ValidatorForm* toAdd);
	void fillForm();						
	bool validateForm() const;	

	void print(std::ostream& output = std::cout) const;

private:
	std::vector<FieldGen*> m_fields;
	std::vector<ValidatorForm*> m_validators;
	std::vector<bool> m_areValids;
	bool m_valid;
};

//---------------------------------------------------------------------------//

std::ostream& operator<<(std::ostream& output, const Form& aForm);


