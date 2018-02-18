#include "Board.h"
#include <iostream>

#include <string>
#include <windows.h>
#include <iomanip>

using std::cout;

/*
 * Default C-ctor that build an emtpy Board
 */
Board::Board()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
		m_gameBoard.push_back("                    ");

}

//---------------------------------------------------------------------------//
/*
 * Method that prints the current board state into the screen.
 */
void Board::print() const
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 20; i++) 
	{
		cout << std::setw(13) << " ";
		for (int j = 0; j < 20; j++) {
			char currCell = m_gameBoard[i][j];
			
			switch (currCell) // polish the right color
			{
				case COOKIE:
					SetConsoleTextAttribute(hconsole, YELLOW_TEXT);
					break;
				case WALL:
					SetConsoleTextAttribute(hconsole, DARK_GREY_TEXT);
					break;
				case DEAMON:
					SetConsoleTextAttribute(hconsole, MAGENTA_TEXT);
					break;
				default:
					SetConsoleTextAttribute(hconsole, WHITE_TEXT);
				break;
			}
			cout << " " << currCell;
			SetConsoleTextAttribute(hconsole, WHITE_TEXT);
		}
		cout << "\n";
	}
}

//---------------------------------------------------------------------------//
/*
 * Method that load the desired level of the game according to the number
 * it got, from the level-defined file (*.txt)
 */
void Board::loadLevel(int _num)
{
	std::ifstream inp_fd;
	std::string currLine;
	int boardDim;
	m_cookies = 0;

	m_gameBoard.clear();
	
	// open the games's File of where level maps defined
	inp_fd.open("Board.txt");
	checkOpendFile(inp_fd);

	// seeking the right starting place of the current level
	inp_fd.seekg((_num - 1)*(444), (std::ios::beg));
	if ((int)inp_fd.tellg() != 0) {
		inp_fd.seekg(3 + (_num - 2), std::ios::_Seekcur);
	}

	//reads size of board
	inp_fd >> boardDim;
	inp_fd.get();

	// reads file's data into the game's Board
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		getline(inp_fd, currLine);
		countCookies(currLine);
		m_gameBoard.push_back(currLine);
	}

	// close the input file, as not needed anymore
	inp_fd.close();
}

//---------------------------------------------------------------------------//
/*
 * Method that update the number of cookies, decrease one.
 */
void Board::ateCookie()
{
	m_cookies--;
}

//---------------------------------------------------------------------------//
/*
 * Method that returns how much cookies left on the screen.
 */
int Board::leftCookies() const
{
	return m_cookies;
}

//---------------------------------------------------------------------------//
/*
 * Method that sets a character into a desired place on the board
 * (using 2 coordinates).
 */
void Board::draw(const char _sign, int _posX, int _posY)
{
	m_gameBoard[_posX][_posY] = _sign;
}

//---------------------------------------------------------------------------//
/*
 * Method that sets a character into a desired place on the board 
 * (using 2-size vector).
 */
void Board::draw(const char _sign, VectorInt _pos)
{
	draw(_sign, _pos.m_x, _pos.m_y);
}

//---------------------------------------------------------------------------//
/*
 * Method that clears the character that appears in the position it got.
 */
void Board::clear(VectorInt _pos)
{
	draw(' ', _pos);
}

//---------------------------------------------------------------------------//
/*
 * Method that returns the character that appears in the position it got.
 */
char Board::inPos(VectorInt _pos) const
{
	return m_gameBoard[_pos.m_x][_pos.m_y];
}

//---------------------------------------------------------------------------//
/*
 * Method that counts the number of cookies on a board's row.
 */
void Board::countCookies(std::string line)
{
	for (int j = 0; j < 20; j++)
		if (line[j] == COOKIE)
			m_cookies++;
}

//---------------------------------------------------------------------------//
/*
 * Method that checks if a file open succesfully.
 */
void Board::checkOpendFile(ifstream &fd)
{
	if (!fd.is_open()) {
		std::cerr << "Cannot open File\n";
		exit(EXIT_FAILURE);
	}
}