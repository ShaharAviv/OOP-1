#pragma once
#include "EquilateralTriangle.h"

//-------------- Constructors Area --------------------------------------//

/*
 *	Constructor that build a triangle from an array of 3 vertexes.
 */

EquilateralTriangle::EquilateralTriangle(const Vertex vertices[3])
	:m_vertices{ {5,sqrt(75) },{ 0,0 },{ 10,0 } }
{
	set(vertices[0], vertices[1], vertices[2]);
}

//---------------------------------------------------------------------------//
/*
 *	Method that get an index number as parameter.
 *  Returns the triangle's vertex in place index, if exist. 
 */
Vertex EquilateralTriangle::getVertex(int index) const
{
	if (index < 0 || index > 2)
	{
		std::cerr << "\n Error: Index " << index << "is Out of range \n";
		exit(EXIT_FAILURE);	 // terminate program because index is out of range
	}
	return m_vertices[index];
}

//---------------------------------------------------------------------------//
/*
 *  Method get a board as parameter.
 *  Draws the rectangle's Shape on this board.
 */
void EquilateralTriangle::draw(Board & board) const
{
	board.drawLine(m_vertices[0], m_vertices[1]);
	board.drawLine(m_vertices[0], m_vertices[2]);
	board.drawLine(m_vertices[1], m_vertices[2]);
}

//---------------------------------------------------------------------------//
/*
 *  Method that return the rectangle that Bound the triangle.
 */
Rectangle EquilateralTriangle::getBoundingRectangle() const
{
	Vertex bottomRight,			// The rectangle's bottom-right vertex
		   topLeft;
	if (isUp()) {
		bottomRight = m_vertices[1];
		topLeft = { m_vertices[2].m_x, m_vertices[0].m_y };
	}
	
	else {       // assuming its down
		bottomRight = { m_vertices[1].m_x, m_vertices[0].m_y };
		topLeft = m_vertices[2];
	}
	return Rectangle(bottomRight, topLeft);
}

//---------------------------------------------------------------------------//
/*
 *  Method that return the triangle's area.
 */
double EquilateralTriangle::getArea() const
{
	double edge = getLength();
	return sqrt(3) / 4 * pow(edge, 2);
}

//---------------------------------------------------------------------------//
/*
 *  Method that return the triangle's perimeter.
 */
double EquilateralTriangle::getPerimeter() const
{
	return 3 * getLength();
}
//---------------------------------------------------------------------------//
/*
 *  Method that return the vertex of triangle's center.
 */
Vertex EquilateralTriangle::getCenter() const
{
	double sum_x = 0,     // keeps the summary of the vertexes x coordinates
		   sum_y = 0;     // keeps the summary of the vertexes y coordinates

	for (int index = 0; index < 3; index++)
	{
		sum_x += m_vertices[index].m_x;
		sum_y += m_vertices[index].m_y;
	}

	return Vertex{sum_x / 3, sum_y / 3};
}

//---------------------------------------------------------------------------//
/*
 *  Method that returns the length of triangle's edge.
 */
double EquilateralTriangle::getLength() const
{
	return distance(m_vertices[0], m_vertices[1]);
}

//---------------------------------------------------------------------------//
/*
 *  Method that get a number to try scale the triangle.
 *  Return true if it succeed to scale, otherwise returns false.
 *  If the scale failed the shape is unchanged.
*/
bool EquilateralTriangle::scale(double factor)
{
	Vertex newMiddleTop,				// keeps the new middle-top vertex 
		   newBottomLeft,				// keeps the new bottom-left vertex
		   newBottomRight;				// keeps the new bottom-right vertex
	double more = (getLength() * (factor - 1)) / 2;
	double ditFromCenter = distance(m_vertices[0], getCenter());
	newBottomLeft = Vertex{m_vertices[1].m_x - more,m_vertices[1].m_y - more};
	newBottomRight = Vertex{m_vertices[2].m_x + more,m_vertices[2].m_y - more};
	newMiddleTop.m_x = m_vertices[0].m_x;
	newMiddleTop.m_y = newBottomRight.m_y + 0.5* sqrt(3)* getLength() * factor;

	return set(newMiddleTop, newBottomLeft, newBottomRight);
}

//---------------------------------------------------------------------------//
/*
 *  Method that gets 3 vertexes that resembles as triangle's vertexes.
 *  Return if it can set, tries to set the new vertexes.
 *  If so return true, else returns false.
 */
bool EquilateralTriangle::set(const Vertex & v1, const Vertex & v2, 
							  const Vertex & v3)
{
	if (isShapeValid(v1, v2, v3)){
		m_vertices[0] = v1;
		m_vertices[1] = v2;
		m_vertices[2] = v3;
		return true;
	}
	return false; 
}

//---------------------------------------------------------------------------//
/*
 *	Method that gets 3 vertexes that resembles as triangle's vertexes.
 *	checks if the triangle is a valid one, means it equilateral-triangle and
 *  thats all his vertexes have valid values.
 *	If so return true, else returns false.
*/
bool EquilateralTriangle::isShapeValid(const Vertex & v1, const Vertex & v2, 
									  const Vertex & v3)
{
	bool all_point_valid,     // check if all vertexes are on valid value
		all_egde_equal,       // check if all edges are equal
		parall_2_x;           // check if shape it parall to the x axis

	double edge1 = distance(v1, v3);
	double edge2 = distance(v1, v2);
	double edge3 = distance(v2, v3);

	all_point_valid = (v1.isValid() && v2.isValid() && v3.isValid());
	all_egde_equal = isEqual(edge1, edge2) && isEqual(edge1, edge3) &&
		             isEqual(edge2, edge3);
	parall_2_x = (v2.m_y == v3.m_y);

	return (all_point_valid && all_egde_equal && parall_2_x);
}

//---------------------------------------------------------------------------//
/*
 *	Method that gets length of 2 edegs.
 *	Returns true if they equal, otherwise returns false.
 */
bool EquilateralTriangle::isEqual(double edgeA, double edgeB) const
{
	return (abs(edgeA - edgeB)) < 1.0;
}
//---------------------------------------------------------------------------//
/*
*	Method that check the side of the triangle.
*	Returns true if the upward, otherwise returns false.
*/
bool EquilateralTriangle::isUp() const
{
	return (getVertex(0).m_y > getVertex(1).m_y);
}
