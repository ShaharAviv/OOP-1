#pragma once
#include "macros.h"
#include "Rectangle.h"
#include "Board.h"

class Window
{
public:

	//-------------- Constructors Area --------------------------------------//
	
	Window(const Vertex& bottomLeft, const Vertex& topRight, 
		int verticalThickness, int horizontalThickness); 

	Window(const Rectangle& outerRect, const Rectangle& inerRect);	
	//-----------------------------------------------------------------------//

	// returns the Vertical Thickness
	int getVerticalThickness() const;
	// returns the Horizontal Thickness
	int getHorizontalThickness() const;
	// draw the shape on a board
	void draw(Board& board) const; 
	// returns the rectangle thats bound the shape
	Rectangle getBoundingRectangle() const;
	// return the shape's area
	double getArea() const;
	// return the shape's perimeter
	double getPerimeter() const;
	// return the shape's center vertex
	Vertex getCenter() const;
	// try to scale the shape
	bool scale(double factor);

private:
	
	Vertex m_bottomLeft,
		m_topRight;
	int m_verticalThickness,
		m_horizontalThickness;
	
	// returns the insider rectangle
	Rectangle getInnerRect() const; 
	// returns the outer rectangle
	Rectangle getOuterRect() const; 
	
	// sets new vertexes and thickness
	bool Window::set(const Vertex & bottomLeft, const Vertex & topRight,
		int verticalThickness, int horizontalThickness);
};