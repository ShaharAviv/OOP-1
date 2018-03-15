#include "Cookie_.h"

Cookie_::Cookie_(const sf::Color & cl, const sf::Vector2i & pos)
{
	m_color = cl;
	m_pos = pos;
}

void Cookie_::draw(sf::RenderWindow & app)
{
	sf::Texture pacman_tx;
	pacman_tx.loadFromFile("Images\\cookie.png");
	sf::Sprite s1;
	s1.setTexture(pacman_tx);
	s1.setColor(this->m_color);
	s1.setPosition((sf::Vector2f) this->m_pos);
	app.draw(s1);
}