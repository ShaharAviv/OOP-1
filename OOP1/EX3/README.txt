Object Oriented Programming ; 2018 a

ex3 : Michael Shriki , Kfir Matityahu

This program Implementing Operators for the Library/Class we created (Poly)

================================================================================================
Files:
------

Monom.cpp & Monom.h:
Handle all the operations that regards to monoms.

Poly.cpp & Poly.h:
Handle all the operations that regards to polynomals.

================================================================================================
Data Structures:
------------------
Monom* m_poly:
Vector as Array type that save the Poly's 

================================================================================================
Remarkable Algorithms:
--------------------------

in Poly: 
Poly operator+(const Poly&) const;
Poly operator/(const Poly& rightPoly) const;
Poly divide(const Poly&, Poly&) const;
Poly gcd(const Poly& a, const Poly& b);

================================================================================================
Known bugs:

None.

================================================================================================