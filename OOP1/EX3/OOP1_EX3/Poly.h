/************************************************************************/
/* Class of Poly
* Handle all the operations that regards to polynomals
*
/************************************************************************/
#pragma once
#include <vector>
#include "Monom.h"

class Poly
{
public:
	Poly(const std::vector<double> coeffs);
	Poly(double _scalar = 0);
	Poly(int _coeff, double _scalar);		

	Poly(const Poly& other);
	Poly& operator=(const Poly& other);
	~Poly();

	int getSize() const;
	int deg() const;

	Poly operator+(const Poly&) const;
	Poly operator*(const Poly & rightPoly) const;
	Poly operator/(const Poly& rightPoly) const;
	Poly operator%(const Poly & rightPoly) const;

	Poly& operator+=(const Poly&);
	Poly& operator-=(const Poly&);
	Poly& operator*=(const Poly&);
	Poly& operator*=(int);
	Poly& operator/=(const Poly&);
	Poly& operator%=(const Poly&);

	Poly operator-() const;
	double operator()(double value) const;
	double operator[](int degree) const;
	
	Monom at(int index) const;

private:
	Monom* m_poly;
	int m_size;

	// help functions
	void setAt(int index, Monom);
	void append(int coeff, double scalar);
	void append(const Monom& monom);

	// help functions for operators
	Poly multiMonom(const Monom & monom) const;
	Poly Monom2Poly(const Monom & monom) const;
	Poly divide(const Poly&, Poly&) const;
};


Poly operator-(const Poly&, const Poly&);
Poly operator*(int, const Poly&);			// by scalar

bool operator==(const Poly&, const Poly&);
bool operator!=(const Poly&, const Poly&);

std::ostream& operator<<(std::ostream& output, const Poly& _poly);

Poly gcd(const Poly& a, const Poly& b);
double gcd(double a, double b);
Poly hcf(const Poly p);
