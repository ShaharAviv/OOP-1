#pragma once
#include <fstream>
#include "settings.h"
#include "VectorInt.h"
#include <iosfwd>
#include <vector>

using std::ifstream;

class Board
{
public:
	Board();
	
	void clear(VectorInt _pos);
	
	void loadLevel(int _num);
	void draw(const char _sign, int _posX, int _posY);
	void draw(const char _sign, VectorInt _pos);
	void print() const;
	char inPos(VectorInt _pos) const;
	void ateCookie();
	int leftCookies() const;

private:
	std::vector <std::string> m_gameBoard;
	int m_cookies;

	void checkOpendFile(ifstream &fd);
	void countCookies(std::string line);
};

