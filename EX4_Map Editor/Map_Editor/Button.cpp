#pragma once
#include "Button.h"

	Button::Button()
	{
		cl = 1;
	}

	void Button::draw(sf::RenderWindow &_window, sf::Texture &t)
	{
		sf::RectangleShape body(sf::Vector2f(45, 45));
		body.setPosition(m_pos);
		body.setTexture(&t);
		_window.draw(body);
	}

	void Button::setPosition(float x, float y)
	{
		m_pos = sf::Vector2f(x, y);
	}

	sf::Vector2f Button::getPos() const
	{
		return m_pos;
	}

	int Button::getColor() const
	{
		return cl;
	}

	void Button::setState(int x)
	{
		state = x;
	}

	int Button::getState() const
	{
		return state;
	}
