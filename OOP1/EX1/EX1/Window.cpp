#pragma once
#include "Window.h"

//-------------- Constructors Area ------------------------------------------//

/*
*	Constructor that build a window from 2 Vertexes and Thickness parameters.
*/
Window::Window(const Vertex & bottomLeft, const Vertex & topRight,
	int verticalThickness, int horizontalThickness)
	//: m_bottomLeft{ 0,0 }, m_topRight{ 10,10 },
	//m_verticalThickness(0),m_horizontalThickness( 0 )
{
	Rectangle out(bottomLeft,topRight);
	//build the window
	set(bottomLeft, topRight, verticalThickness, horizontalThickness);
}

//---------------------------------------------------------------------------//

/*
*	Constructor that build a window using 2 Rectangles 
*	and default Thickness parameters.
*/

Window::Window(const Rectangle & outerRect, const Rectangle & inerRect)
	: m_bottomLeft{ 0,0 }, m_topRight{ 0,0 },
	m_verticalThickness(0), m_horizontalThickness(0)
{
	int verticalThickness, horizontalThickness;
	if (outerRect.getCenter().m_x == inerRect.getCenter().m_x &&
		outerRect.getCenter().m_y == inerRect.getCenter().m_y)
	{
		horizontalThickness = (int)(outerRect.getHeight() -
			inerRect.getHeight())/2; // get the new horizontal thickness 
		verticalThickness = (int)(outerRect.getWidth() - 
			inerRect.getWidth()) / 2;// get the new vertical thickness
		
		//build the window
		set(outerRect.getBottomLeft(), outerRect.getTopRight(), 
			verticalThickness, horizontalThickness);
	}
}

//---------------------------------------------------------------------------//

/*
*	Method that return the window vertical thickness.
*/

int Window::getVerticalThickness() const 
{
	return m_verticalThickness;
}

//---------------------------------------------------------------------------//

/*
*	Method that return the window horizontal thickness.
*/
int Window::getHorizontalThickness() const
{
	return m_horizontalThickness;
}

//---------------------------------------------------------------------------//

/*
*	Method get a board as parameter.
*   Draws the rectangle's Shape on this board.
*/

void Window::draw(Board & board) const 
{
	getOuterRect().draw(board);
	getInnerRect().draw(board);
}

//---------------------------------------------------------------------------//

/*
*	Method that return the rectangle that Bound the window.
*/

Rectangle Window::getBoundingRectangle() const 
{
	return getOuterRect();
}

//---------------------------------------------------------------------------//

/*
*	Method that return the window's Area.
*/

double Window::getArea() const  
{
	return getOuterRect().getArea() - getInnerRect().getArea();
}

//---------------------------------------------------------------------------//

/*
*	Method that return the window Perimeter.
*/

double Window::getPerimeter() const
{
	return getOuterRect().getPerimeter() + getInnerRect().getPerimeter();

}

//---------------------------------------------------------------------------//

/*
*	Method that return the Vertex of window's Center.
*/

Vertex Window::getCenter() const 
{
	return getOuterRect().getCenter();
}

//---------------------------------------------------------------------------//

/*
*	Method that get a number to try scale the window.
*	Return true if it succeed to scale, otherwise - false.
*	If the scale failed the shape is unchanged.
*/

bool Window::scale(double factor) 
{
	Rectangle outer = getOuterRect();
	Rectangle inner = getInnerRect();
	
	if (outer.scale(factor) && inner.scale(factor)) {
		m_bottomLeft = outer.getBottomLeft();
		m_topRight = outer.getTopRight();
		m_horizontalThickness *= 2;
		m_verticalThickness *= 2;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//

/*
*	Method that return the inside rectangle.
*/

Rectangle Window::getInnerRect() const 
{
	Vertex bottomLeft,
		topRight;
	bottomLeft = { m_bottomLeft.m_x + m_verticalThickness,m_bottomLeft.m_y + 
		m_horizontalThickness };
	topRight = { m_topRight.m_x - m_verticalThickness,m_topRight.m_y - 
		m_horizontalThickness };
	return Rectangle(bottomLeft,topRight);
}

//---------------------------------------------------------------------------//

/*
*	Method that return the outside rectangle.
*/

Rectangle Window::getOuterRect() const 
{
	return Rectangle(m_bottomLeft,m_topRight);
	
}

//---------------------------------------------------------------------------//

/*
*	Method that gets a parameter 2 vertexes that resemble as the bottom-right
*	and top-left of window and return if it can set.
*	Try to set the new vertexes. If so return true, else returns false.
*/

bool Window::set(const Vertex & bottomLeft, const Vertex & topRight,
				 int verticalThickness, int horizontalThickness)
{
	if (bottomLeft.isValid() && topRight.isValid() &&// check the points
		!bottomLeft.isRighterThan(topRight) &&
		topRight.isHigherThan(bottomLeft))
	{
		m_bottomLeft = bottomLeft;
		m_topRight = topRight; 
		if (getOuterRect().getHeight() > 0.5*getInnerRect().getHeight() // check the height and width
			&& getOuterRect().getWidth() > 0.5*getInnerRect().getWidth())
		{
			m_verticalThickness = verticalThickness;
			m_horizontalThickness = horizontalThickness;
		}
		return true;
	}
	return false;
}
