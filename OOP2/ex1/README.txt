Object Oriented Programming ; 2018 b

ex3 : Michael Shriki, Kfir Matityahu

This program is a Calculator that can be programmed 

================================================================================================
Files: 
--------------------------------
(^ X : inheritance from X)

Function.h:
ab abstract class for the functions.

BinaryExp.cpp & BinaryExp.h:
Handle all the binary operators. (^ Function)

UnaryExp.cpp & UnaryExp.h:
Handle all the unary operators. (^ Function)

varX.cpp & varX.h:
Handle all "x" expressions. (^ Function)

Add.cpp & Add.h:
add 2 expressions. (^ BinaryExp)

Mul.cpp & Mul.h:
multiplication 2 expressions. (^ BinaryExp)

Sqrt.cpp & Sqrt.h:
function to calculate basic square root. (^ UnaryExp)

Log.cpp & Log.h:
function to calculate "log function" with any base. (^ UnaryExp)

Poly.cpp & Poly.h:
polynomial expressions. (^ UnaryExp)

Ln.cpp & Ln.h:
function to calculate basic log with "e" base. (^ Log)

Calculator.cpp & Calculator.h:
Handle all the calculator programming. (containing a Function Vector)

================================================================================================
Data Structures:
-------------------------------
std::vector <std::shared_ptr<Function>> m_funcList:
Vector of smart pointer (Shared Pointer) to Function 

================================================================================================
Remarkable Algorithms:
--------------------------------


================================================================================================
Known bugs:

None.

================================================================================================
Other Notes:

Class Diagram png was sent in the zip

================================================================================================