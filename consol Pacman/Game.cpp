#include "Game.h"
#include "windows.h"
#include "util.h"
#include "messeges.h"

#include <iostream>
#include <cstdlib>      // for system()
#include <conio.h>      // for _getch()
#include <iomanip>
#include <time.h>


using std::cout;
using std::setw;
//--------------------------places
const VectorInt MIDDLE_SCREEN = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 };

// keep 4 corners values of the screen's corners
// (clockwise, from the top left corner)
const VectorInt CORNERS[4] = { {0 ,0},
							   {0 ,SCREEN_HEIGHT - 1} ,
							   {SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1},
							   { SCREEN_HEIGHT - 1,0 } };

bool resetFlag = false;		//"global" used to keep knowing if to reset a level
//---------------------------------------------------------------------------//
/*
 * Constructor that build a Game, set the current level into 1
 */
Game::Game()
	:m_pac(MIDDLE_SCREEN), m_map(), m_score(0)
{
	setLevel(1);
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the game to a certain level, according the number it got. 
 */
void Game::setLevel(int num)
{
	srand((unsigned)time(nullptr));
	m_startFirst = rand() % 2;
	m_currLvl = num;
	m_map.loadLevel(num);
}

//---------------------------------------------------------------------------//
/*
 * Method that sets the character(s) into their start position(s)
 */
void Game::setCharcters()
{
	m_pac.setPos(shotestNeib(MIDDLE_SCREEN, m_map));

	if (m_map.inPos(m_pac.getPos()) == COOKIE)
		m_map.ateCookie();

	for (int index = 0; index < m_currLvl - 1; ++index)
		(m_enemies[index]).setPos(shotestNeib(CORNERS[index], m_map));

}

//---------------------------------------------------------------------------//
/*
 * Method that draws the character(s) onto the board
 */
void Game::drawCharcters()
{
	m_pac.draw(m_map);

	for (int index = 0; index < m_currLvl - 1; ++index)
		(m_enemies[index]).draw(m_map);

}

//---------------------------------------------------------------------------//
/*
 * Method that run the game, as long as player lives or not passed the level
 */
bool Game::run()
{
	Board copy = m_map;
	setCharcters();
	int start = m_score;
	bool firstIteration = true;

	while (!m_pac.isDead()){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		drawCharcters(); // draw all objects

		cout << "=========================   LEVEL : " << m_currLvl
			<< "    =========================\n";

		m_map.print();
		printStates();
		
		VectorInt lastDPos[4];
		for (int pos = 0; pos < 4; pos++)
			lastDPos[pos] = m_enemies[pos].getPos();

		m_map.clear(m_pac.getPos());
		copy.draw(m_map.inPos(m_pac.getPos()), m_pac.getPos());

		VectorInt lastPacPos = m_pac.getPos();

		// play according the order of turn decided at the start of the level
		if (m_startFirst)
		{
			if (firstIteration){
				playDemon(lastPacPos);
				firstIteration = false;
			}
			else
			{
				playPac();
				playDemon(lastPacPos);
			}
		}
		else
		{
			playPac();
			playDemon(lastPacPos);
		}

		CheckCollision();

		if (resetFlag){		// user decided to reset his game (current level) 
			m_score = start;
			m_map.loadLevel(m_currLvl);
			setCharcters();
			drawCharcters();
			resetFlag = false;
			continue;
		}

		char currentPos;
		currentPos = m_map.inPos(m_pac.getPos());
		UpdateGame(currentPos);

		VectorInt currDPos[4];
		for (int pos = 0; pos < 4; pos++)
			currDPos[pos] = m_enemies[pos].getPos();

		for (int d1 = 0; d1 < 5; d1++) {
			if (!samePlace(lastDPos[d1], currDPos[d1]))
				m_map.draw(copy.inPos(lastDPos[d1]), lastDPos[d1]);
		}

		// we end successfully the current level!
		if (m_map.leftCookies() == 0) {
			m_score += 50 * m_currLvl;
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------//
/*
 * Method that checks if there are collisions between player and demons.
 */
void Game::CheckCollision()
{
	int currDemons = m_currLvl - 1;
	for (int i = 0; i < currDemons; i++)
		if (samePlace(m_enemies[i].getPos(), m_pac.getPos()))
		{
			resetAfterKill();
			break;
		}
}

//---------------------------------------------------------------------------//
/*
 * Method that skips into the next level.
 */
void Game::skipLevel()
{
	while (m_map.leftCookies() != 0)
		m_map.ateCookie();
}

//---------------------------------------------------------------------------//
/*
 * Method that adds one life to the player.
 */
void Game::addLife()
{
	m_pac.IncreaseLife();
}

//---------------------------------------------------------------------------//
/*
 * Method that control on the player's turn
 */
void Game::playPac()
{
	int c = 0;
	c = _getch();
	switch (c)
	{
	case KB_L:		// case adding a life
		addLife();
		break;
	case KB_S:	   // case asking to skip level
		skipLevel();
		break;
	case KB_R:		// reset the level - cookies get back
		resetFlag = true;
		break;
	case SPECIAL_KEY:		// user input is arrows, means he moved the pacman
		handleArrowsKey();
		break;
	case KB_SPACE:		// the user choice to skip his turn
		break;
	case KB_ESCAPE:		// case user ask to exit
		system("cls");
		cout << QuitGameMsg;
		char ans = _getch();
		if (ans == KB_Y)			// user confirm he wants to quit
			exit(EXIT_FAILURE);
		
		system("cls");
		break;
	}
}

//---------------------------------------------------------------------------//
/*
 * Method that control on the demons' turn
 */
void Game::playDemon(VectorInt lastPos)
{
	switch (m_currLvl)
	{
	case 2:
		moveAILevel2(m_enemies[0]);
		break;
	case 3:
		moveAILevel1(m_enemies[0], lastPos);
		moveAILevel2(m_enemies[1]);
		break;
	case 4:
		moveAILevel1(m_enemies[0], lastPos);
		moveAILevel1(m_enemies[1], lastPos);
		moveAILevel2(m_enemies[2]);
		break;
	case 5:
		moveAILevel1(m_enemies[0], lastPos);
		moveAILevel2(m_enemies[1]);
		moveAILevel1(m_enemies[2], lastPos);
		moveAILevel2(m_enemies[3]);
		break;
	}
}

//---------------------------------------------------------------------------//
/*
 * Method that moves a demon according to pacman move (Level 1)
 */
void Game::moveAILevel1(Demon &d, VectorInt lastPos) {

	VectorInt playerCurrPos = m_pac.getPos();
	VectorInt newPos = copyPlayer(playerCurrPos, lastPos, d.getPos(), m_map);
	char inMap = m_map.inPos(newPos);

	if (inMap != WALL)
		d.setPos(newPos);

}

//---------------------------------------------------------------------------//
/*
 * Method that moves a demon according to pacman place (Level 2)
 */
void Game::moveAILevel2(Demon &d)
{
	VectorInt newPos;

	newPos = shotestDist(m_pac.getPos(), d.getPos(), m_map);
	char inMap = m_map.inPos(newPos);

	if (inMap != WALL)
		d.setPos(newPos);
}

//---------------------------------------------------------------------------//
/*
 * Method that handles movment of the Pacman character itself.
 */
void Game::handleArrowsKey()
{
	char currentPos;
	VectorInt lastPos;
	do {
		int c = _getch();

		lastPos = m_pac.getPos();
		switch (c)
		{
		case KB_UP:            // Arrow Up pressed
			m_pac.move(-1, 0);
			break;
		case KB_DOWN:          // Arrow Down pressed
			m_pac.move(1, 0);
			break;
		case KB_LEFT:		   // Arrow Left pressed
			m_pac.move(0, -1);
			break;
		case KB_RIGHT:         // Arrow Right pressed
			m_pac.move(0, 1);
			break;
		default:			// invalid button pressed, still player's turn
			return handleArrowsKey();

		}
		// case player is blocked
		currentPos = m_map.inPos(m_pac.getPos());
		if (currentPos == WALL) {
			m_pac.setPos(lastPos);
			_getch();
		}
		else
			break;
	} while (1);
}

//---------------------------------------------------------------------------//
/*
 * Method that returns the current score.
 */
int Game::getScore()
{
	return m_score;
}

//---------------------------------------------------------------------------//
/*
 * Method that Updates the player movement on board according to his move
 */
void Game::UpdateGame(char playerCurrPos)
{
	// the move *is* legal //

	switch (playerCurrPos) {
	case COOKIE:
		m_map.ateCookie();
		m_score += 2 * m_currLvl;   // from level 2 we have 1 more daemon 
		break;

	case DEAMON:
		resetAfterKill();
		break;

	default:; break;
	}
}

//---------------------------------------------------------------------------//
/*
 * Method that prints all the states about the game:
 * current score, current life and number of cookies that left on scren.
 */
void Game::printStates()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,21 });
	cout << setw(40) << "Player's Score : "<< m_score << "  \n";
	cout << setw(39) << "Player's Life : " << m_pac.getLife() << "  \n";
	cout << setw(38) << "Cookies left : " << m_map.leftCookies() << "  \n";

	cout << "===================================="
		<< "===============================\n";
	
}
//---------------------------------------------------------------------------//
/*
 * Method that resets the current level state (except cookies).
 */
void Game::resetAfterKill()
{
	system("cls");
	cout << DemonAteMsg;
	Sleep(2000);

	m_pac.kill();
	// set to middle of screen
	m_pac.setPos(shotestNeib(MIDDLE_SCREEN, m_map));
	setCharcters();
}