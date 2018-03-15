#pragma once
#include "Button.h"
#include <sstream>
#include <iostream>

class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow&);
	Button getclickedButton(sf::Vector2f currPos);
	bool isClickedOnButton(Button _b, sf::Vector2f _pos);
	bool inRange(sf::Vector2f my, sf::Vector2f p1, sf::Vector2f p2);
	~Menu();
	
private:
	Button m_buttons[10];
	Button m_currColor;
	Button m_currAct;
};

