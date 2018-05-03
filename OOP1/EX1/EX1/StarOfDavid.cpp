#pragma once
#include "StarOfDavid.h"

Vertex verticesUP[] = { { 5, sqrt(75) + 2 },{ 10,2 },{ 0,2 } };
Vertex verticesDown[] = { { 5,0 },{ 0,sqrt(75) },{ 10,sqrt(75) } };

//-------------- Constructors Area ------------------------------------------//

/*
*	Constructor that build a star from array of Vertexes.
*/
StarOfDavid::StarOfDavid(Vertex first[3], Vertex second[3])
	:m_up(verticesUP), m_down(verticesDown)
{
	setUpdown(m_up, m_down);
}

//-----------------------------------------------------------------------//

/*
*	Constructor that build a star from 2 triangles.
*/

StarOfDavid::StarOfDavid(const EquilateralTriangle & t1,
	const EquilateralTriangle & t2)
	: m_up(verticesUP), m_down(verticesDown)
{
	setUpdown(m_up, m_down);
}


//-----------------------------------------------------------------------//

/*
*	Method that return the total height of the star.
*/

double StarOfDavid::getTotalHeight() const
{
	return distance(m_up.getVertex(0), m_down.getVertex(0));
}

//-----------------------------------------------------------------------//

/*
*	Method that return the rectangle that Bound the star.
*/

Rectangle StarOfDavid::getBoundingRectangle() const
{
	Vertex bottomLeft, topRight;
	// the new points
	topRight = m_up.getBoundingRectangle().getTopRight();
	bottomLeft = m_down.getBoundingRectangle().getBottomLeft();
	
	return Rectangle(bottomLeft, topRight);
}

//-----------------------------------------------------------------------//

/*
*	Method get a board as parameter.
*   Draws the star Shape on this board.
*/

void StarOfDavid::draw(Board & board) const
{
	m_up.draw(board);
	m_down.draw(board);
}

//-----------------------------------------------------------------------//

/*
*	Method that return the star's Area.
*/

double StarOfDavid::getArea() const
{
	return m_up.getArea() + m_down.getArea();
}

//-----------------------------------------------------------------------//

/*
*	Method that return the star's Perimeter.
*/

double StarOfDavid::getPerimeter() const
{
	return m_up.getPerimeter() + m_down.getPerimeter();
}

//-----------------------------------------------------------------------//

/*
*	Method that return the Vertex of star's Center.
*/

Vertex StarOfDavid::getCenter() const
{
	//average of both EquilateralTriangles' center
	//@EQUAL: return (m_up.getCenter() + m_down.getCenter()) / 2;
	Vertex center;
	// the new tow points
	center.m_x = (m_up.getCenter().m_x + m_down.getCenter().m_x) / 2;
	center.m_y = (m_up.getCenter().m_y + m_down.getCenter().m_y) / 2;
	return center;
}

//-----------------------------------------------------------------------//

/*
*	Method that get a number to try scale the star.
*	Return true if it succeed to scale, otherwise - false.
*	If the scale failed the shape is unchanged.
*/

bool StarOfDavid::scale(double factor)
{
	EquilateralTriangle old_up = m_up;
	if (m_up.scale(factor)) {
		if (!m_down.scale(factor)) {
			m_up = old_up;
			return false;
		}
		else return true;
	}
	return false;
}

//-----------------------------------------------------------------------//

/*
*	Method that return if one of the triangle is up and the other is down
*	and replace them if it's doesn't
*/

bool StarOfDavid::setUpdown(const EquilateralTriangle & t1,
	const EquilateralTriangle & t2)
{
	// check if the first up and the second down and replace
	if (EquilateralTriangleIsUp(t1) && !EquilateralTriangleIsUp(t2))
	{
		m_up = t1;
		m_down = t2;
		return true;
	}
	// check if the first down and the second up and leave it that way
	if (!EquilateralTriangleIsUp(t1) && EquilateralTriangleIsUp(t2))
		return setUpdown(t2, t1);
	
	return false;
}

//-----------------------------------------------------------------------//

/*
*	Method that return if the triangle is up.
*/

bool StarOfDavid::EquilateralTriangleIsUp(const EquilateralTriangle trg)
{
	return (trg.getVertex(0).m_y > trg.getVertex(1).m_y);
}
