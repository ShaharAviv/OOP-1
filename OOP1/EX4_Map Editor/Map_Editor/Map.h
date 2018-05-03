#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
#include <vector>
struct Info
{
	sf::Vector2i m_place;
	char m_sign;
};
class Map
{
public:

	Map(int row = 1, int col = 1);
	Map(std::ifstream& file);

	Map(const Map& other)
	{
		m_row = other.m_row;
		m_col = other.m_col;
		lastPacPos = other.lastPacPos;
		
		for (int i = 0; i < m_row; i++)
			delete[] map2[i];
		delete[] map2;
		
		// Full and smart cop
		map2 = new Info*[m_row];
		for (int i = 0; i < m_row; i++)
			map2[i] = new Info[m_col];

		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
			{
				(map2[i][j]).m_place = (other.map2[i][j]).m_place;
				(map2[i][j]).m_sign = (other.map2[i][j]).m_sign;
			}
	}

	Map& operator=(const Map& other)
	{
		if (this == &other)    // Testing that we dont copy the same variable
			return *this;

		for (int i = 0; i < m_row; i++)
			delete[] map2[i];
		delete[] map2;

		// alloc Full-New copy
	
		m_row = other.m_row;
		m_col = other.m_col;
		
		lastPacPos = other.lastPacPos;

		map2 = new Info*[m_row];
		for (int i = 0; i < m_row; i++)
			map2[i] = new Info[m_col];


		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
			{
				map2[i][j].m_place =  other.map2[i][j].m_place;
				map2[i][j].m_sign = other.map2[i][j].m_sign;
			}

		return *this;
	}


	~Map(){
 		for (int i = 0; i < m_row; i++)
 			delete[] map2[i];
 		delete[] map2;

	//	map2 = NULL;
		
	}
	void draw(sf::Vector2i _place, char _s)
	{
		(map2[_place.y][_place.x]).m_sign = _s;
	}
	void display(sf::RenderWindow & _window) const;
	void remove(int i, int j);
	void cleanMap();
	sf::Vector2i getPacPos() const;
	void setPacPos(sf::Vector2i);
	bool inRange(sf::Vector2f my);
	sf::Vector2i getSignPos(char ch) const;
	char getSign(int x, int y);
	sf::Vector2i getPlace(int x, int y);
	int getRowSize() const;
	int getColSize() const;
	int getCell() const;
	int setCell() const;


	
// std::vector <std::vector <char> > map1;
//  char ** map1;
private:

	// std::vector <std::vector <Info> > map1;
//	sf::Vector2i** grid;
   // std::vector<std::vector <sf::Vector2<int>> > grid;
	
	Info** map2;
	int m_row;
	int m_col;
	sf::Vector2i lastPacPos;
	void setGridPos();
	void setGridSign();
};

