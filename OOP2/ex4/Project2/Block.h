#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <map>
#include <ostream>

#include "Board.h"


class Block
{
public:
	
	Block(const sf::Texture &texture,const sf::Vector2i &pixelPosition ,
		const sf::Vector2i &coords);

	void moveAbsolute(const sf::Vector2i &newPos, const sf::Vector2i& offset);
	void moveDown();
	const sf::Vector2f& getPosition() const;
	const sf::Vector2i& coordinates() const;
	
	void draw(sf::RenderWindow &target) const;

private:
	sf::Sprite m_sprite;
	sf::Vector2i m_cords;		// coordinates of the block
};

