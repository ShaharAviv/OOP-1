#pragma once
#include <SFML/Graphics.hpp>

// game settings
const float PIECE_MOVE_DELAY = 1.0f;      // delay of piece drop/sec
const unsigned TIME_OF_LEVEL = 40u;      // time (in seconds) of each level


class States
{

public:
	States(const sf::Font& font, const sf::Vector2i& position);
	int scoreValue() const;
	void setScore(int value);

	void update(const sf::Time& delta);
	void reset();
	void draw(sf::RenderWindow &target) const;
	float getSpeed() const;

	void addTime(int val);

private:
	int m_scoreValue;
	int m_rowsValue;
	short m_currlevel;

	static float m_timeElapsed;
	sf::Text m_text2;

	sf::Text m_scoreText;
	sf::Text m_nextShapeText;
	sf::Text m_levelText;
	sf::Text m_levelNumText;
};



