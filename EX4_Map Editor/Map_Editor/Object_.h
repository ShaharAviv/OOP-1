#pragma once
#include <SFML/Graphics.hpp>
class Object
{
public:
	Object(){}
	virtual void draw(sf::RenderWindow &) = 0;

protected:
	sf::Color m_color;
	sf::Vector2i m_pos;
};

