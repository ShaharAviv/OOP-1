#pragma once
#include "SrcManager.h"
#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	MainMenu(const sf::Vector2u& windowSize = { 1000,1000 });

	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);
	
	int isChoosen() const;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x);
	void unchoose();

private:
	std::shared_ptr<SrcManager> m_src;
	std::vector <sf::Text> m_texts;
	int m_choosen;

	sf::RectangleShape m_bgRect;
	
};

