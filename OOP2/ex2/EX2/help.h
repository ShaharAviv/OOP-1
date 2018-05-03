#pragma once
#include "windows.h"
#include <string>
#include <iostream>

#define FG_WHITE 15
#define FG_YELLOW 14
#define FG_DEFAULT 7

/*
 * sets the visibility of console cursor
 */
inline void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO  cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;			// set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

//-----------------------------------------------------------------------------
/*
 * sets the console colors (using WORD flags)
 */
inline void SetOutputColor(WORD wAttributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
}

//-----------------------------------------------------------------------------
/*
 * sets the console to default colors
 */
inline void ResetOutputColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG_DEFAULT);
}