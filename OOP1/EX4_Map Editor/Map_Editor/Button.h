#pragma once
#include <SFML\Graphics.hpp>

class Button{
public:
	Button();
	void draw(sf::RenderWindow &_window, sf::Texture &t);
	void setPosition(float x, float y);
	sf::Vector2f getPos() const;
	int getColor() const;
	void setState(int x);
	int getState() const;

private:
	sf::Vector2f m_pos;
	int cl;
	int state;
};