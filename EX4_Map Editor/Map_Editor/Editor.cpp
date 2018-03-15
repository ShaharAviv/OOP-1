#pragma once
#include "Editor.h"

Editor::Editor(const char * file_name)
{
	std::ifstream file;
	file.open(file_name, std::ios_base::binary);
	m_gameMap = Map(file);

}
Editor::Editor(int row,int col)
{
	m_gameMap = Map(row, col);
}

int Editor::file_size(std::string filename) // path to file
{
	std::ifstream mySource;

	mySource.open(filename, std::ios_base::binary);
	mySource.seekg(0, std::ios_base::end);
	int size = (int)mySource.tellg();
	mySource.close();

	return size;
}

void Editor::copy2File()
{
	file.open("level.txt");
	// TODO :check if file failed ??
	int grid_rows = m_gameMap.getRowSize();
	int grid_cols = m_gameMap.getColSize();
	file << grid_rows <<' ' << grid_cols << '\n';
	for (int i = 0; i < grid_rows; i++)
	{
		for (int j = 0; j < grid_cols; j++)
			file << m_gameMap.getSign(i,j);

		file << "\n";
	}

	file.close();
}


void Editor::drawE(sf::RenderWindow & _window)
{
	m_Bmenu.draw(_window);
	m_gameMap.display(_window);
}

bool Editor::reset()
{
	if (m_CurrState == RESET_MODE_T)
	{
		m_CurrState = (ActionType_t)0;
		return true;
	}
	return false;
}

sf::Vector2i Editor::getPlace(sf::Vector2f src)
{
	int x0 = (int)fmod((int)((src.x - 90) / M_SIZE), 40);
	int y0 = (int)fmod((int)((src.y - 70) / M_SIZE), 40);

	return sf::Vector2i(x0, y0);
}

void Editor::setSize(int row, int col)
{
	m_gameMap = Map(row, col);
}

void Editor::ShowButton(sf::Vector2f currPos, sf::RenderWindow & app)
{
	sf::RectangleShape selctedI(sf::Vector2f(40, 40));
	sf::Sprite s1;
	sf::Texture t1;
	sf::RectangleShape tmp1 = selctedI;

	int rowA = m_gameMap.getRowSize();
	int colA = m_gameMap.getColSize();

	s1.setColor(sf::Color(255, 150, 150, 155));

	if (m_gameMap.inRange(currPos))
	{
		tmp1.setSize(sf::Vector2f(M_SIZE, M_SIZE));
		sf::Vector2i z = getPlace(currPos);
		s1.setPosition((sf::Vector2f) m_gameMap.getPlace(z.y, z.x));

		if (m_gameMap.getSign(z.y ,z.x) != ' ')
		{
			t1.loadFromFile("Images\\no.bmp");
			s1.setTexture(t1);
		}
		
		else {
			switch (m_CurrState)
			{

			case PACMAN_T:
				t1.loadFromFile("Images\\pacman.png");
				break;
			
			case WALL_T:
				t1.loadFromFile("Images\\wall.png");
				break;
			case COOKIE_T:
				t1.loadFromFile("Images\\cookie.png");
				break;
			case GHOST_T:
				t1.loadFromFile("Images\\ghost.png");
				break;
			case 5:
				t1.loadFromFile("Images\\rsz_7.png");
				s1.setColor(sf::Color::White);
				s1.setPosition((sf::Vector2f) m_gameMap.getPlace(z.y, z.x));
				break;
			}
				s1.setTexture(t1);
				tmp1.setOutlineColor(sf::Color::Red);
				tmp1.setOutlineThickness(5);
			}
	}
	app.draw(s1);
}

void Editor::PlayButton(sf::Vector2f currPos)
{
	Button b = m_Bmenu.getclickedButton(currPos);

	// pressed on color
	if (b.getState() >= 0 && b.getState() <= 2)
		m_currColor = (Color_t)b.getState();

	// pressed on action
 	if (b.getState() >= 3 && b.getState() <= 9)
		m_CurrState = (ActionType_t)(b.getState() - 2);

	if (m_CurrState == RESET_MODE_T)
	{
		m_gameMap.cleanMap();
		return;
	}
	else if (m_CurrState == SAVE_MODE_T)
	{
		m_CurrState = (ActionType_t)0;
		sf::RenderWindow msg;
		sf::Font font;
		font.loadFromFile("font.ttf");
		sf::Text saveMessage("\t Level Saved !", font, 40);
		saveMessage.setFillColor(sf::Color::White);
		msg.create(sf::VideoMode(600, 100), "", sf::Style::None);
		msg.draw(saveMessage);
		msg.display();
		
		copy2File();
		
		Sleep(2000);
	}

	if (m_gameMap.inRange(currPos))
	{
		sf::Vector2i z = getPlace(currPos);

		if (m_gameMap.getSign(z.y, z.x) == ' ')
		{
			sf::Vector2i pInfo_ = z;
			char cInfo = m_colors[m_currColor][m_CurrState-1];
			switch (m_CurrState)
			{
			case PACMAN_T:
				if (m_gameMap.getPacPos() != sf::Vector2i(-1, -1))
					m_gameMap.remove(m_gameMap.getPacPos().y, m_gameMap.getPacPos().x);
				m_gameMap.draw(pInfo_, cInfo);
				m_gameMap.setPacPos(z);
				break;
			case WALL_T:
			case COOKIE_T:
			case GHOST_T:
				m_gameMap.draw(pInfo_, cInfo);
				break;
			}
		}

		if (m_CurrState == ERASE_MODE_T)
		{
			sf::RectangleShape tmp(sf::Vector2f(40, 40));
			tmp.setFillColor(sf::Color::Black);
			tmp.setOutlineThickness(5);
			m_gameMap.remove(z.y,z.x);
		}
	}
}