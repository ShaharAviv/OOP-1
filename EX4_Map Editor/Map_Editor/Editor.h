#pragma once
#include <vector>
#include <windows.h>
#include "Menu.h"
#include "settings.h"
#include "Map.h"

class Editor
{
public:
	bool loadFromFile(const char* fileName) {
		std::ifstream file;
		file.open(fileName, std::ios_base::binary);

		if (file_size(fileName) == -1)
		{
			return false;
			file.close();
		}

		m_gameMap = Map(file);
		file.close();
		return true;
	}

	Editor(const char* file_name);
	Editor(int row = 1, int col = 1);
	void drawE(sf::RenderWindow &_window);
	bool reset();
	sf::Vector2i getPlace(sf::Vector2f src);
	void setSize(int row, int col);
	void ShowButton(sf::Vector2f currPos, sf::RenderWindow & app);
	void PlayButton(sf::Vector2f currPos);

private:
	std::ofstream file;

	Map m_gameMap;
	Menu m_Bmenu;

	enum Color_t m_currColor;
	enum ActionType_t m_CurrState;

	void copy2File();
	int file_size(std::string filename);
};


