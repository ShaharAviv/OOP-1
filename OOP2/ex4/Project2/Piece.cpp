#include "Piece.h"

//---------------------------------------------------------------------------//
/*
*
*/
Piece::Piece(const sf::Vector2i &offsetPosition, short rotationMod, bool f)
	:m_currRotation(rotationMod), m_offset(offsetPosition), m_isStopped(false)
{
}

//---------------------------------------------------------------------------//
/*
*
*/
size_t Piece::size() const 
{
	return m_blocks.size();
}

//---------------------------------------------------------------------------//
/*
*
*/
Block Piece::operator[](size_t blockNum) const  
{
	try {
		return m_blocks[blockNum];
	}
	catch (std::exception&)
	{
		std::cout << m_blocks.size();
		return m_blocks[0];
	}
}
