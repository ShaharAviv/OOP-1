#include "util.h"
#include "windows.h"
#include <iostream>
#include "time.h"

int manhattenDistance(const VectorInt v1, const VectorInt v2)
{
	return abs(v1.m_x - v2.m_x) + abs(v1.m_y - v2.m_y);
}

VectorInt shotestDist(VectorInt pac_v, VectorInt deam_v, Board _b)
{
	VectorInt directions[4] = { { 0,1 },{ 1,0 },{ -1,0 },{ 0,-1 } };
	VectorInt x = deam_v;
	VectorInt newPlace;
	int minDist = manhattenDistance(pac_v, deam_v);

	for (auto & direction : directions)
	{
		newPlace = { deam_v.m_x + direction.m_x,
							   deam_v.m_y + direction.m_y };
		if (_b.inPos(newPlace) == WALL || manhattenDistance(pac_v, newPlace) == 1)
			continue;
		if (manhattenDistance(pac_v, newPlace) <= minDist)
		{
			minDist = manhattenDistance(pac_v, newPlace);
			x = newPlace;
			break;
		}
	}
	return x;
}
VectorInt shotestNeib(VectorInt v1, Board _b)
{
	VectorInt directions[8] =
	{ { 0,1 },{ 1,1 },{ 1,0 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };

	if (_b.inPos(v1) != WALL)
		return v1;

	VectorInt mybe;
	while (1)
	{
		for (auto & direction : directions)
		{
			mybe = { v1.m_x + direction.m_x, v1.m_y + direction.m_y };

			if (isValid(mybe) && _b.inPos(mybe) != WALL)
				return mybe;
		}
		if (manhattenDistance(v1, mybe) > SCREEN_HEIGHT / 2)
			break;
	}
	return mybe;
}

VectorInt randomClosePath(VectorInt v1, Board _b)
{
	VectorInt directions[4] = { { 0,1 },{ 1,0 },{ -1,0 },{ 0,-1 } };
	VectorInt mybe;
	for (auto & direction : directions)
	{
		mybe = { v1.m_x + direction.m_x, v1.m_y + direction.m_y };

		if (isValid(mybe) && _b.inPos(mybe) != WALL)
			return mybe;
	}
	return v1;

}

bool isValid(VectorInt pos)
{
	return (pos.m_x > 0 && pos.m_x < SCREEN_HEIGHT)
		&& (pos.m_y > 0 && pos.m_y < SCREEN_WIDTH);
}

bool samePlace(const VectorInt pos1, const VectorInt pos2)
{
	return (pos1.m_x == pos2.m_x &&  pos1.m_y == pos2.m_y);
}

VectorInt copyPlayer(VectorInt v1, VectorInt v2, VectorInt v3, Board _b)
{
	VectorInt mybe;

	mybe = { v3.m_x - (v1.m_x - v2.m_x), v3.m_y - (v1.m_y - v2.m_y) };
	if (_b.inPos(mybe) == DEAMON)
		return v3;

	if (isValid(mybe) && _b.inPos(mybe) != WALL)
		return mybe;

	return v3;
}