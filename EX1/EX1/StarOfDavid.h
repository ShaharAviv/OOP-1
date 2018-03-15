#pragma once
#include "EquilateralTriangle.h"
#include "Rectangle.h"
#include "Utilities.h"

class StarOfDavid
{
public:

	//-------------- Constructors Area --------------------------------------//
	
	StarOfDavid(Vertex firstTriange[3], Vertex secondTriange[3]);
	StarOfDavid(const EquilateralTriangle &t1, const EquilateralTriangle &t2);
	//-----------------------------------------------------------------------//

	 // returns the total height of the Star
	double getTotalHeight() const;
	// returns the rectangle thats bound the shape
	Rectangle getBoundingRectangle() const;
	// draw the shape on a board
	void draw(Board& board) const;
	// return the shape's area
	double getArea() const;
	// return the shape's perimeter
	double getPerimeter() const;
	// return the shape's center vertex
	Vertex getCenter() const;
	// try to scale the shape
	bool scale(double factor);

private:
	
	EquilateralTriangle m_up; 
	EquilateralTriangle m_down;
	
	// function that set a default Star
	bool setUpdown(const EquilateralTriangle & t1, const EquilateralTriangle & t2);
	//check if triangle is up or down
	bool EquilateralTriangleIsUp(const EquilateralTriangle trg);
};