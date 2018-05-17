#include "Block.h"

//---------------------------------------------------------------------------//
/*
 *
 */
Block::Block(const sf::Texture &texture, const sf::Vector2i &pixelPosition,
	const sf::Vector2i &coords)
	: m_sprite(texture), m_cords(coords)
{
	m_sprite.setPosition(sf::Vector2f(pixelPosition));
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Block::moveAbsolute(const sf::Vector2i& newPos, const sf::Vector2i& offset)
{
	//newPos is in block coordinates, while offset uses pixel measurements

	sf::Vector2i texSize(m_sprite.getTextureRect().width,
		m_sprite.getTextureRect().height);

	sf::Vector2i relativePos(newPos.x * texSize.x, newPos.y * texSize.y);
	m_sprite.setPosition(sf::Vector2f(relativePos + offset));
	m_cords = newPos;
}

//---------------------------------------------------------------------------//
/*
 *
 */

void Block::moveDown()
{
	m_cords.y++;
	const sf::Vector2f& currentPos = std::move(m_sprite.getPosition());
	m_sprite.setPosition(currentPos.x, currentPos.y + m_sprite.getTextureRect().height);

}

//---------------------------------------------------------------------------//
/*
 *
 */
void Block::draw(sf::RenderWindow &target) const
{
	target.draw(m_sprite);
}

//---------------------------------------------------------------------------//
/*
 *
 */
const sf::Vector2f& Block::getPosition() const
{
	return m_sprite.getPosition();
}

//---------------------------------------------------------------------------//
/*
 *
 */
const sf::Vector2i & Block::coordinates() const
{
	return m_cords;
}

