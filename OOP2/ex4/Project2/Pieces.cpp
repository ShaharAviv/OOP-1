#include "Pieces.h"
#include "Board.h"

//////////////////////////////////////////////////////////////////////////
I::I(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{
	m_rotatations.push_back({ { { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 } } });
	m_rotatations.push_back({ { { -1,1 },{ 0,1 },{ 1,1 },{ 2,1 } } });
	m_rotatations.push_back({ { { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 } } });
	m_rotatations.push_back({ { { -1,1 },{ 0,1 },{ 1,1 },{ 2,1 } } });
	
	init(*texture, pos);

}


J::J(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{
	m_rotatations.push_back({ { { 1,0 },{ 1,1 },{ 1,2 },{ 0,2 } } });
	m_rotatations.push_back({ { { 2,1 },{ 1,1 },{ 0,1 },{ 0,0 } } });
	m_rotatations.push_back({ { { 1,2 },{ 1,1 },{ 1,0 },{ 2,0 } } });
	m_rotatations.push_back({ { { 0,1 },{ 1,1 },{ 2,1 },{ 2,2 } } });

	init(*texture, pos);

}

O::O(const sf::Texture *texture, const sf::Vector2i &pos)
	:PieceNSize<4>(pos)
{
	for (int i =1 ; i<= 4 ; i++)
		m_rotatations.push_back({ { { 0,0 },{ 1,0 },{ 0,1 },{ 1,1 } } });

	init(*texture, pos);
}

L::L(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{

	m_rotatations.push_back({ { { 0,0 },{ 0,1 },{ 0,2 },{ 1,2 } } });
	m_rotatations.push_back({ { { -1,1 },{ 0,1 },{ 1,1 },{ -1,2 } } });
	m_rotatations.push_back({ { { 0,0 },{ 0,1 },{ 0,2 },{ -1,0 } } });
	m_rotatations.push_back({ { { -1,1 },{ 0,1 },{ 1,1 },{ 1,0 } } });

	init(*texture, pos);

}

Z::Z(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{
	m_rotatations.push_back({ { { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } } });
	m_rotatations.push_back({ { { 1,-1 },{ 1,0 },{ 0,0 },{ 0,1 } } });
	m_rotatations.push_back({ { { 0,-1 },{ 1,-1 },{ 1,0 },{ 2,0 } } });
	m_rotatations.push_back({ { { 1,1 },{ 1,0 },{ 2,0 },{ 2,-1 } } });

	init(*texture, pos);

}


S::S(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{
	m_rotatations.push_back({ { { 2,0 },{ 1,0 },{ 1,1 },{ 0,1 } } });
	m_rotatations.push_back({ { { 1,1 },{ 1,0 },{ 0,0 },{ 0,-1 } } });
	m_rotatations.push_back({ { { 2,-1 },{ 1,-1 },{ 1,0 },{ 0,0 } } });
	m_rotatations.push_back({ { { 2,1 },{ 2,0 },{ 1,0 },{ 1,-1 } } });

	init(*texture, pos);
}

T::T(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod)
	:PieceNSize<4>(pos, rotationMod)
{

	m_rotatations.push_back({ { { 0,0 },{ 1,0 },{ 2,0 },{ 1,1 } } });
	m_rotatations.push_back({ { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,0 } } });
	m_rotatations.push_back({ { { 0,0 },{ 1,0 },{ 2,0 },{ 1,-1 } } });
	m_rotatations.push_back({ { { 1,1 },{ 1,0 },{ 1,-1 },{ 2,0 } } });

	init(*texture, pos);

}
