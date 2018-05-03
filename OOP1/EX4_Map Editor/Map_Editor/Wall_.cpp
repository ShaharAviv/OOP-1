#include "Wall_.h"

Wall_::Wall_(const sf::Color & cl, const sf::Vector2i & pos)
{
	m_color = cl;
	m_pos = pos;
}

void Wall_::draw(sf::RenderWindow & app)
{
	sf::Texture wall_tx;
	wall_tx.loadFromFile("Images\\wall.png");
	sf::Sprite s1;
	s1.setTexture(wall_tx);
	s1.setColor(this->m_color);
	s1.setPosition((sf::Vector2f) this->m_pos);
	app.draw(s1);

}