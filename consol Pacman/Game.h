#pragma once
#include "Board.h"
#include "Player.h"
#include "Demon.h"

class Board;

class Game
{
public:
	Game();

	void setLevel(int num);
	void setCharcters();
	void drawCharcters();
	
	bool run();

	int getScore();

private:
	Player m_pac;
	Board m_map;
	int m_score;
	Demon m_enemies[4];
	int m_currLvl;
	bool m_startFirst;

	void handleArrowsKey();

	void playDemon(VectorInt lastPos);			
	void moveAILevel1(Demon & d, VectorInt lastPos);
	void moveAILevel2(Demon & d);

	void skipLevel();		
	void addLife();

	void playPac();
	void CheckCollision();

	void UpdateGame(char);
	void printStates();
	void resetAfterKill();
};

