#pragma once
#include "Board.h"
#include "settings.h"

class Player
{
public:
	Player(VectorInt PlayerPos);

	void draw(Board &_board) const;
	void move(int x, int y);
	VectorInt getPos() const;
	void setPos();
	void setPos(int _x, int _y);
	void setPos(VectorInt);

	void kill();
	bool isDead() const;
	int getLife() const;
	void IncreaseLife();

private:
	int m_life;
	VectorInt m_pos;
};

