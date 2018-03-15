#pragma once
#include "Map.h"
#include "Pacman_.h"
#include "Wall_.h"
#include "Cookie_.h"
#include "Ghost_.h"
#include <vector>

Map::Map(int row, int col)
	:m_row(row), m_col(col)
{
	lastPacPos = sf::Vector2i(-1, -1);

	 	map2 = new Info*[m_row];
	 	for (int i = 0; i < m_row; i++)
	 		map2[i] = new Info[m_col];
	 
	 	for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
			{
				(map2[i][j]).m_place = sf::Vector2i((int)(90 + j * M_SIZE), (int)(70 + i * M_SIZE));
				(map2[i][j]).m_sign = ' ';
			}
}


Map::Map(std::ifstream & file)
{
	lastPacPos = sf::Vector2i(-1, -1);
	file >> m_row >> m_col;
	
	map2 = new Info*[m_row];
	for (int i = 0; i < m_row; i++)
		map2[i] = new Info[m_col];

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
		{
			(map2[i][j]).m_place = sf::Vector2i((int)(90 + j * M_SIZE), (int)(70 + i * M_SIZE));
			(map2[i][j]).m_sign = ' ';
		}

	file.get();
	file.get();
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++) {
			map2[i][j].m_sign = file.get();
			if (map2[i][j].m_sign == '@' || map2[i][j].m_sign == 'w' || map2[i][j].m_sign == 's')
				lastPacPos = sf::Vector2i(j, i);
		}
		file.get();
		file.get();
		puts("");

	}
}

int Map::getRowSize() const
{
	return m_row;
}

int Map::getColSize() const
{
	return m_col;
}

void Map::setGridPos()
{
// 	grid = new sf::Vector2i*[m_row];
// 	for (int i = 0; i < m_row; i++)
// 		grid[i] = new sf::Vector2i[m_col];
// 
// 	for (int i = 0; i < m_row; i++)
// 		for (int j = 0; j < m_col; j++)
// 			grid[i][j] = sf::Vector2i((int)(90 + j * M_SIZE), (int)(70 + i * M_SIZE));

}

void Map::setGridSign()
{
	/*map1 = new char*[m_row];

	for (int i = 0; i < m_row; i++)
		map1[i] = new char[m_col]; */
}

void Map::display(sf::RenderWindow & _window) const
{
	sf::RectangleShape tmp(sf::Vector2f(M_SIZE, M_SIZE));
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++)
		{
			sf::Vector2i ddd = (map2[i][j]).m_place;
 			char sign = (map2[i][j]).m_sign;
			if (sign == ' ')
			{
				tmp.setFillColor(sf::Color::Black);
				tmp.setOutlineColor(sf::Color::Red);
				tmp.setOutlineThickness(1);
	    		tmp.setPosition((sf::Vector2f) ddd);
				_window.draw(tmp);
			}

			else {
				sf::Vector2i v = getSignPos((map2[i][j]).m_sign);
				sf::Color xl;
				switch (v.x) {		// color of objec t
				case RED: xl = sf::Color::Red; break;
				case GREEN: xl = sf::Color::Green; break;
				case BLUE: xl = sf::Color::Blue; break;
				}
				if (v.y == PACMAN_T) {
					Pacman_ p(xl, ddd);
					p.draw(_window);
				}
				else if (v.y == WALL_T) {
					Wall_ w(xl, ddd);
					w.draw(_window);
				}

				else if (v.y == COOKIE_T) {
					Cookie_ ck(xl, ddd);
					ck.draw(_window);
				}

				else if (v.y == GHOST_T) {
					Ghost_ g(xl, ddd);
					g.draw(_window);
				}
			}
		}
	}
}

void Map::remove(int i, int j)
{
	(map2[i][j]).m_sign = ' ';
}

void Map::cleanMap()
{
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			remove(i,j);
}

sf::Vector2i Map::getPacPos() const
{
	return lastPacPos;
}

void Map::setPacPos(sf::Vector2i p)
{
	lastPacPos = p;
}

bool Map::inRange(sf::Vector2f my)
{
	sf::Vector2f topCorner = (sf::Vector2f)map2[0][0].m_place;
	sf::Vector2f  bottomCorner = (sf::Vector2f)map2[m_row-1][m_col-1].m_place
		+ sf::Vector2f(30, 30);

	sf::Vector2f p1 = topCorner;
	sf::Vector2f p2 = bottomCorner;

	return (my.x >= p1.x && my.y >= p1.y) &&
		(my.x <= p2.x && my.y <= p2.y);
}

sf::Vector2i Map::getSignPos(char ch) const
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			if (m_colors[i][j] == ch)
				return sf::Vector2i(i + 1, j + 1);

	return sf::Vector2i(0, 0);
}

char Map::getSign(int x, int y)
{
	return map2[x][y].m_sign;
}

sf::Vector2i Map::getPlace(int x, int y)
{
	return map2[x][y].m_place;
}