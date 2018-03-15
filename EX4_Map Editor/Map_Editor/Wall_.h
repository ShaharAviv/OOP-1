#pragma once
#include "Object_.h"
class Wall_ : public Object
{
public:
	Wall_(const sf::Color& cl, const sf::Vector2i &pos);
	void draw(sf::RenderWindow &app);
};

