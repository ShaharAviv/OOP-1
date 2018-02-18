#pragma once
#include "Board.h"
#include "settings.h"

class Demon
{
public:
	Demon();
	void draw(Board &_board) const;
	void move(int x, int y);
	VectorInt getPos() const;
	void setPos(int _x, int _y);
	void setPos(VectorInt pos);

private:
	VectorInt m_pos;
};

