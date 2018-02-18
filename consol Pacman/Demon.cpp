#include "Demon.h"
#include "util.h"

/*
 * Constructor that build a default demon
 */
Demon::Demon()
	:m_pos({ 1,1 })
{
}

//---------------------------------------------------------------------------//
/*
 * Method that draws the demon onto a game board.
 */
void Demon::draw(Board & _board) const
{
	_board.draw(DEAMON, m_pos);
}

//---------------------------------------------------------------------------//
/*
 * Method that moves the demon according to x and y values .
 */
void Demon::move(int x, int y)
{
	VectorInt newPos;
	newPos = { m_pos.m_x + x, m_pos.m_y + y };

	if (isValid(newPos))
		m_pos = newPos;

}

//---------------------------------------------------------------------------//
/*
* Method that returns the demon's position.
*/
VectorInt Demon::getPos() const
{
	return m_pos;
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the demon's position from 2 coordinates.
 */
void Demon::setPos(int _x, int _y)
{
	m_pos = VectorInt{ _x, _y };
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the demon's position from 2-size vector.
 */
void Demon::setPos(VectorInt pos)
{
	m_pos = pos;
}
