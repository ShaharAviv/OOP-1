#include "States.h"
#include <iostream>
float States::m_timeElapsed = 0;


//---------------------------------------------------------------------------//
/*
*
*/
States::States(const sf::Font& font, const sf::Vector2i& position)
	:m_scoreValue(0), m_rowsValue(10), m_currlevel(1),
	m_scoreText("Score: \n 0", font, 30),
	m_text2("Left for\nnext level : \n 0", font, 30),
	m_nextShapeText("Next Shape:", font, 30),
	m_levelText("Curr Level:", font, 30),
	m_levelNumText("1", font, 40)
{
	m_scoreText.setPosition((sf::Vector2f)position);
	m_text2.setPosition((float)position.x, position.y + 150.f);
	m_nextShapeText.setPosition(20, 70);
	m_levelText.setPosition(20, 280);
	m_levelNumText.setPosition(90, 320);
}

//---------------------------------------------------------------------------//
/*
*
*/
int States::scoreValue() const
{
	return m_scoreValue;
}

//---------------------------------------------------------------------------//
/*
*
*/
void States::addTime(int val)
{
	m_timeElapsed -= val;
}

//---------------------------------------------------------------------------//
/*
*
*/
void States::setScore(int value)
{
	m_scoreValue = value;
}


//---------------------------------------------------------------------------//
/*
*
*/
void States::update(const sf::Time& delta)
{
	m_timeElapsed += delta.asSeconds();
	
	if (m_timeElapsed >= TIME_OF_LEVEL)
	{
		m_timeElapsed = 0;
		m_text2.setFillColor(sf::Color::White);
		m_currlevel++;
		m_levelNumText.setString(std::to_string(m_currlevel));
	}

	if (m_timeElapsed <= 5)
		m_levelNumText.setFillColor(sf::Color(255,255, 0, 255 * (int(m_timeElapsed) % 2)));
	
	else
		m_levelNumText.setFillColor(sf::Color::White);

	m_scoreText.setString("Score: \n" + std::to_string(m_scoreValue));
	m_text2.setString("passed level in: \n" +
		std::to_string((int)(TIME_OF_LEVEL+1 - m_timeElapsed)) + " seconds ");

	if (m_timeElapsed >= 20) 
	{
		sf::Uint8 gradiant = (int)(255 * ((TIME_OF_LEVEL - m_timeElapsed) / 10.f));
		m_text2.setFillColor({ 255, gradiant, gradiant , 255});
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void States::reset()
{
	m_timeElapsed = 0;
	m_scoreValue = 0;
	m_currlevel = 1;
}

//---------------------------------------------------------------------------//
/*
*
*/
void States::draw(sf::RenderWindow &target) const
{
	target.draw(m_scoreText);
	target.draw(m_text2);
	target.draw(m_nextShapeText);
	target.draw(m_levelText);
	target.draw(m_levelNumText);
}

//---------------------------------------------------------------------------//
/*
*
*/
float States::getSpeed() const
{
	return PIECE_MOVE_DELAY / m_currlevel;
}
