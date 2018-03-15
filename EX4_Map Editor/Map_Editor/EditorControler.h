#pragma once
#include "Menu.h"
#include "Editor.h"
class EditorControler
{
public:
	EditorControler();

	void run();
	void openAsk(sf::RenderWindow& window);
	void openWin1(sf::RenderWindow& , int []);
	void openWin2(int numbers[2]);
	int file_size(std::string filename); // path to file
	~EditorControler();

private:
	Editor m_gameEditor;
};