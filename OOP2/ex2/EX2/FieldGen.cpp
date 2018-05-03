#include "FieldGen.h"

//---------------------------------------------------------------------------//
/*
* Constructor of The General field
* Gets a string as the question the user have to fill
*/
FieldGen::FieldGen(const std::string& data)
	:m_data(data), m_valid(false) { }

//---------------------------------------------------------------------------//
/*
 *  Extraction operator for Field
 */
std::ostream& operator<<(std::ostream& output, const FieldGen& fieldGen)
{
	fieldGen.print(output);
	return output;
}