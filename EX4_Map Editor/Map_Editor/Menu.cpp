#pragma once
#include "Menu.h"
const float M_SIZE = 45;
Menu::Menu()
{
	m_currAct.setState(10);
	for (int i = 0; i < 10; i++)
		m_buttons[i].setPosition((float)20, (float)50*i+40);

	for (int i = 0; i < 10; i++)
		m_buttons[i].setState(i);
}


void Menu::draw(sf::RenderWindow& window)
{
	sf::Texture ttt[10];
	
	sf::RectangleShape selctedI(sf::Vector2f(M_SIZE, M_SIZE));
	 selctedI.setFillColor(sf::Color::Transparent);
	selctedI.setOutlineColor(sf::Color::White);
	selctedI.setOutlineThickness(5);
	sf::RectangleShape selcted2(sf::Vector2f(M_SIZE, M_SIZE));
	selcted2.setFillColor(sf::Color::Transparent);
	selcted2.setOutlineColor(sf::Color(100,150,150));
	
	selcted2.setOutlineThickness(4);
	std::string src = "Images\\";
	for (int i = 0; i < 10; i++)
	{
		std::string name;
		std::ostringstream ss;     // string buffer to convert numbers to string
		ss << i; 	      		   // put float into string buffer
		name = src + ss.str() + ".png";  // converts the string buffer into a regular string

		ttt[i].loadFromFile(name);
	}

	for (int i = 0; i < 10; i++)
	{
		m_buttons[i].draw(window, ttt[i]);
		if (i == m_currColor.getState())
		{
			selctedI.setPosition((m_buttons[i]).getPos());
			window.draw(selctedI);
		}

		else if (m_currAct.getState()!=8 && m_currAct.getState() != 9
			         && i == m_currAct.getState())
		{
			selcted2.setPosition((m_buttons[i]).getPos());
			window.draw(selcted2);
		}			
	}
}

Button Menu::getclickedButton(sf::Vector2f currPos)
{
	int code;
	int cl = 1, currState = 1;
	for (code = 0; code <= 9; code++)
	{
		if (isClickedOnButton(m_buttons[code], currPos))
		{	
			if ( code>=0 && code <= 2)
				m_currColor = m_buttons[code];
			else
				m_currAct = m_buttons[code];
			break;
		}
	}

	return m_buttons[code];
}

bool Menu::isClickedOnButton(Button _b, sf::Vector2f _pos)
{
	sf::Vector2f topV = _b.getPos();
	sf::Vector2f downV = topV + sf::Vector2f(60, 60);

	bool t = inRange(_pos, topV, downV);

	return t;
}

bool Menu::inRange(sf::Vector2f my, sf::Vector2f p1, sf::Vector2f p2)
{
	return (my.x >= p1.x && my.y >= p1.y) &&
		(my.x <= p2.x && my.y <= p2.y);
}


Menu::~Menu()
{
}
