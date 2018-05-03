#pragma once
#include "Object_.h"

class Pacman_ : public Object
{
public:
	Pacman_(sf::Color cl, sf::Vector2i pos);
	void draw(sf::RenderWindow &app);
};
  
