#pragma once
#include "Object_.h"
class Cookie_ : public Object
{
public:
	Cookie_(const sf::Color& cl, const sf::Vector2i &pos);
	void draw(sf::RenderWindow &app);
};

