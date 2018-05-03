#include "Player.h"
#include <iostream>
#include "util.h"


/*
 * Constructor that build a Pacman, set his life and pos according to the data.
 */
Player::Player(VectorInt PlayerPos)
	:m_life(LIFE), m_pos(PlayerPos)
{
}

//---------------------------------------------------------------------------//
/*
 * Method that draws the pacman onto a game board.
 */
void Player::draw(Board &_board) const
{
	_board.draw(PACMAN, m_pos);
}

//---------------------------------------------------------------------------//
/*
 * Method that kiils the pacman, decrease his life by 1.
 */
void Player::kill()
{
	m_life--;
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the pacman's position from 2 coordinates.
 */
void Player::setPos(int _x, int _y)
{
	setPos({ _x,_y });
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the pacman's position from 2-size vector.
 */
void Player::setPos(VectorInt pos)
{
	m_pos = pos;
}

//---------------------------------------------------------------------------//
/*
 * Method that return the pacman's postion vector.
 */
VectorInt Player::getPos() const
{
	return m_pos;
}

//---------------------------------------------------------------------------//
/*
 * Method that moves the pacman according to x and y values .
 */
void Player::move(int x, int y)
{
	VectorInt newPos;
	newPos = { m_pos.m_x + x, m_pos.m_y + y };

	if (isValid(newPos))
		m_pos = newPos;

}

//---------------------------------------------------------------------------//
/*
 * Method that checks and returns if the pacman is dead.
 */
bool Player::isDead() const
{
	return (m_life == 0);
}

//---------------------------------------------------------------------------//
/*
 * Method that returns how lives the pacman has now.
 */
int Player::getLife() const
{
	return m_life;
}

//---------------------------------------------------------------------------//
/*
 * Method that adds 1 life for the pacman.
 */
void Player::IncreaseLife()
{
	m_life++;
}
