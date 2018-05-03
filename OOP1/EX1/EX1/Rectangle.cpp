//#include "Utilities.h"
#include "Rectangle.h"

#include <iostream>
#include <cmath>

//-------------- Constructors Area --------------------------------------//

/*
 *	Constructor that build a rectangle from 2 vertexes.
 */
Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
	:m_bottomLeft{ 0,0 }, m_topRight{ 10,10 }
{
	set(bottomLeft, topRight);
}

//---------------------------------------------------------------------------//
/*
 *	Constructor that build a rectangle from an array of 2 vertexes.
 */
Rectangle::Rectangle(const Vertex vertices[2])
	:Rectangle(vertices[0], vertices[1])
{
}

//---------------------------------------------------------------------------//
/*
 *	Constructor that build a rectangle from 4 coordinates.
 *	each 2 coordinates resembles a vertex.
 */
Rectangle::Rectangle(double x0, double y0, double x1, double y1)
	:Rectangle(Vertex{ x0,y0 }, Vertex{ x1,y1 })
{
}

//---------------------------------------------------------------------------//
/*
 *	Constructor that build a rectangle from vertex and the lengths of the
 *  width and height from it.
 */
Rectangle::Rectangle(const Vertex& start, double width, double height)
	:m_bottomLeft{ 0,0 }, m_topRight{ 10,10 }
{
	Vertex bottomLeft, topRight;
	if (width > 0)
	{
		if (height > 0){
			bottomLeft = { start.m_x + width, start.m_y };
			topRight = { start.m_x, start.m_y + height };
		}
		else {
			bottomLeft = { start.m_x + width, start.m_y + height };
			topRight = start;
		}
	}

	else        // if (width < 0)
	{
		if (height > 0) {
			bottomLeft = start;
			topRight = { start.m_x + width, start.m_y + height };
		}
		else {
			bottomLeft = { start.m_x, start.m_y + height };
			topRight = { start.m_x + width, start.m_y};
		}
	}

	set(bottomLeft, topRight);
}
//---------------------------------------------------------------------------//
/*
 *	Method that returns the rectangle's bottom-left vertex. 
 */
Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}

//---------------------------------------------------------------------------//
/*
 *	Method that returns the rectangle's top-Right vertex.
 */
Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

//---------------------------------------------------------------------------//
/*
 *	Method that returns the rectangle's width.
 */
double Rectangle::getWidth() const
{
	return abs(m_bottomLeft.m_x - m_topRight.m_x);
}

//---------------------------------------------------------------------------//
/*
 *	Method that returns the rectangle's height.
 */
double Rectangle::getHeight() const
{
	return abs(m_bottomLeft.m_y - m_topRight.m_y);
}

//---------------------------------------------------------------------------//
/*
 *	Method get a board as parameter.
 *  Draws the rectangle's Shape on this board.
 */
void Rectangle::draw(Board & board) const
{
	Vertex bottomRight,			// The rectangle's bottom-right vertex
		   topLeft;				// The rectangle's top-left vertex
	bottomRight = { m_topRight.m_x, m_bottomLeft.m_y };
	topLeft = { m_bottomLeft.m_x, m_topRight.m_y};

	board.drawLine(m_bottomLeft, bottomRight);
	board.drawLine(m_bottomLeft, topLeft);
	board.drawLine(m_topRight, topLeft);
	board.drawLine(m_topRight, bottomRight);
}

//---------------------------------------------------------------------------//
/*
 *	Method that return the rectangle that Bound the rectangle.
 */
Rectangle Rectangle::getBoundingRectangle() const
{
	 return *this;
}
//---------------------------------------------------------------------------//
/*
 *	Method that return the rectangle's area.
 */
double Rectangle::getArea() const
{
	return  getHeight() * getWidth();
}

//---------------------------------------------------------------------------//
/*
 *	Method that return the rectangle's perimeter.
 */
double Rectangle::getPerimeter() const
{
	return 2 * (getHeight() + getWidth());
}

//---------------------------------------------------------------------------//
/*
 *	Method that return the vertex of rectangle's center.
 */
Vertex Rectangle::getCenter() const {
	Vertex center;			// keep rectangle's center
	center.m_x = (m_bottomLeft.m_x + m_topRight.m_x) / 2;
	center.m_y = (m_bottomLeft.m_y + m_topRight.m_y) / 2;

	return center;
}
//---------------------------------------------------------------------------//
/*
 *	Method that get a number to try scale the rectangle.
 *  Return true if it succeed to scale, otherwise - false.
 *	If the scale failed the shape is unchanged. 
 */
bool Rectangle::scale(double factor) {
	Vertex newTopLeft, newBottomRight;
	double more_width = (factor - 1) / 2 * getWidth();
	double more_height = (factor - 1) / 2 * getHeight();
	
	newTopLeft = { m_topRight.m_x + more_width,
				   m_topRight.m_y + more_height };
	newBottomRight = { m_bottomLeft.m_x - more_width,
					   m_bottomLeft.m_y - more_height };

	return set(newBottomRight, newTopLeft);   //try to scale
}
//---------------------------------------------------------------------------//
/*
 *	Method that gets a parameter 2 vertexes that resembles as the bottom-right
 *  and top-left of rectangle and return if it can set.
 *  Try to set the new vertexes. If so return true, else returns false. 
 */
bool Rectangle::set(const Vertex &bottomLeft, const Vertex &topRight) {
	if ( bottomLeft.isValid() && topRight.isValid() &&
		!bottomLeft.isRighterThan(topRight) &&
		topRight.isHigherThan(bottomLeft) ){
		m_bottomLeft = bottomLeft;
		m_topRight = topRight;
		return true;
	}
	
	return false;
}