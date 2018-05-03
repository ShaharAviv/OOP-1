#pragma once
#include "macros.h"
#include "Vertex.h"
#include "Board.h"
#include <iostream>

class Rectangle
{
public:

	//-------------- Constructors Area --------------------------------------//

    Rectangle(const Vertex& bottomLeft, const Vertex& topRight);		
	Rectangle(const Vertex vertices[2]);								
	Rectangle(double x0, double y0, double x1, double y1);			
	Rectangle(const Vertex& start, double width, double height);	
	//-----------------------------------------------------------------------//

	// returns bottom-left vertex
	Vertex getBottomLeft() const;										
	// returns top-right vertex
	Vertex getTopRight() const;											

	// draw the shape on a board
	void draw(Board& board) const;
	// returns the rectangle thats bounds the shape
	Rectangle getBoundingRectangle() const;
	// return the shape's width
	double getWidth() const;										
	// return the shape's height
	double getHeight() const;
	// return the shape's area
	double getArea() const;												
	// return the shape's perimeter
	double getPerimeter() const;
	// return the shape's center vertex
	Vertex getCenter() const;
	// try the scale the shape
	bool scale(double factor);
	
private:
	Vertex m_bottomLeft;
	Vertex m_topRight;

	// sets new vertexes to the shape
	bool set(const Vertex &bottomLeft, const  Vertex &topRight);
};