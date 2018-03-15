#pragma once
#include <iostream>
#include <fstream>

const float M_SIZE = 30;
const char m_colors[3][4] = { { '@','#','$','%' },
{ 'w','e','r','t' } ,
{ 's','d','f','g' } };

enum ObjectType_t
{
	PACMAN_T = 1,
	WALL_T,
	COOKIE_T,
	GHOST_T
};
enum Color_t
{
	RED=1,
	GREEN,
	BLUE
};
enum ActionType_t
{
	DRAW_MODE_T= 4,
	ERASE_MODE_T,
	SAVE_MODE_T,
	RESET_MODE_T
};
