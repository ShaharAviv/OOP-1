#pragma once
#include "Vertex.h"
#include "Board.h"
#include "Utilities.h"
#include "macros.h"
#include "Rectangle.h"

class EquilateralTriangle
{
public:

	//-------------- Constructors Area --------------------------------------//

	EquilateralTriangle(const Vertex vertices[3]);
	//-----------------------------------------------------------------------//

	// returns vertex in place index 
	Vertex getVertex(int index) const;
	// draw the shape on a board
	void draw(Board& board) const;
	// returns the rectangle thats bounds the shape
	Rectangle getBoundingRectangle() const;
	// return the shape's area
	double getArea() const;												
	// return the shape's perimeter
	double getPerimeter() const;										
	// return the shape's center vertex
	Vertex getCenter() const;											
	// return the shape's edge
	double getLength() const;
	// try the scale the shape
	bool scale(double factor);

private:
	Vertex m_vertices[3];

	// sets new vertexes to the shape
	bool set(const Vertex & v1, const Vertex & v2, const Vertex & v3);
	// returns if the shape is valid and compile the conditions
	bool isShapeValid(const Vertex & v1, const Vertex & v2, const Vertex & v3);
	// returns if 2 edges are equal
	bool isEqual(double edgeA, double edgeB) const;
	// return if the shape is upwards
	bool isUp() const;
};