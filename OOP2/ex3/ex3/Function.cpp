#include "Function.h"
#include "MyException.h"

void Function::check_value(double value) const
{
	if (value <= 0)
		throw MinException(0,true);
}
