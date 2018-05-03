Object Oriented Programming ; 2018 b

ex3 : Michael Shriki, Kfir Matityahu

This program is a Fill out a form and check its propriety

================================================================================================
Files: 
--------------------------------
(^ X : inheritance from X)

ValidatorGen.cpp & ValidatorGen.h
an abstract class.

ValidatorForm.cpp & ValidatorForm.h: (^ ValidatorGen)

Validator.cpp & Validator.h:
Handle all the unary operators. (^ ValidatorGen)

TwoFactorValidator.cpp & TwoFactorValidator.h: (^ ValidatorForm)

courses2year_validator.cpp & courses2year_validator.h:
A class that represents a courses-vs.-year validator. (^ TwoFactorValidator)

faculty2year_validator.cpp & faculty2year_validator.h:
A class that represents a faculty-vs.-year validator. (^ TwoFactorValidator)

min_validator.cpp & min_validator.h:
A class that represents a minimal value validator. (^ TwoFactorValidator)

no_digit_validator.cpp & no_digit_validator.h:
A class that represents a no-digit-characters validator. (^ TwoFactorValidator)

range_validator.cpp & range_validator.h:
A class that represents a range validator. (^ TwoFactorValidator)

id_validator.cpp & id_validator.h:
A class that represents an ID validator. (^ TwoFactorValidator)

FieldGen.cpp & FieldGen.h:
an abstract class.

Field.cpp & Field.h:
A class that represents a form. A form has many fields. (^ FieldGen)

Form.cpp & Form.h:
A class that represents a form. A form has many fields.

FacultyValue.cpp & FacultyValue.h:
A class that represents the value use for faculty field.

================================================================================================
Data Structures:
-------------------------------

std::vector<FieldGen*> m_fields;
std::vector<ValidatorForm*> m_validators;
std::vector<bool> m_areValids;

================================================================================================
Remarkable Algorithms:
--------------------------------
None.

================================================================================================
Known bugs:

None.

================================================================================================
Other Notes:

None.

================================================================================================