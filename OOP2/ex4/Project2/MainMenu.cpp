#include "MainMenu.h"

//---------------------------------------------------------------------------//
/*
*
*/
MainMenu::MainMenu(const sf::Vector2u & windowSize)
	: m_src(SrcManager::instance()), 
	  m_choosen(-1),
	  m_bgRect({ (float)windowSize.x, (float)windowSize.y })
{
	sf::Text PlayText("Play Game", *m_src->getFont(), 50);
	sf::Text ExitText("Exit", *m_src->getFont(), 50);
	PlayText.setPosition(windowSize.x / 3.f, windowSize.y / 4.f);
	PlayText.setOutlineThickness(5);
	PlayText.setOutlineColor(sf::Color::Black);

	ExitText.setPosition(windowSize.x / 3.f, windowSize.y / 4.f + 120);
	ExitText.setOutlineThickness(5);
	ExitText.setOutlineColor(sf::Color::Black);

	m_texts.emplace_back(PlayText);
	m_texts.emplace_back(ExitText);

	m_bgRect.setTexture((m_src->getBackGround(0)));
	m_bgRect.setFillColor({ 255, 255, 255, 180 });

}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::update(sf::RenderWindow & window)
{
	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_bgRect);		// draw main menu background image

	// draws all 'buttons'
	for (const auto& t : m_texts)
		window.draw(t);
}

//---------------------------------------------------------------------------//
/*
*
*/
int MainMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int MainMenu::isOnButton(sf::RenderWindow & window) const
{
	sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition(window);
	int i = 0;
	for (auto it = m_texts.begin(); it != m_texts.end(); it++, i++)
	{
		if ((*it).getGlobalBounds().contains(currPos))
			return i;
	}

	return -1;
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_texts[x].setFillColor(sf::Color::Red);
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::unchoose()
{
	for (int i = 0; i < m_texts.size(); i++)
		if (i != m_choosen)
			m_texts[i].setFillColor(sf::Color::White);
}
