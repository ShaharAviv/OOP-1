#pragma once
#include "Object_.h"
class Ghost_ : public Object
{
public:
	Ghost_(const sf::Color& cl, const sf::Vector2i &pos);
	void draw(sf::RenderWindow &app);
};

