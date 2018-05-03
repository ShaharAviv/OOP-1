//=============================== Include ===================================//
#include "Game.h"
#include "messeges.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>      // for system()
#include <conio.h>      // for _getch()

using std::cout;
//================================ Consts ===================================//
const int NUM_OF_LVLS = 5;

//============================== Prototypes =================================//
void ShowConsoleCursor(bool showFlag);

//================================= Main ====================================//
int main(void)
{

	ShowConsoleCursor(false);  
	
	Game theGame;			// The game's aperacnce
	int currentLevel = 1;   // the current level of the game

	cout << WelcomePageSticker;
	Sleep(2000);
	
	// -- wait for the start of the game --
	do
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,8 });
		cout << WelcomePlayerMsg;
	} while (_getch() != KB_ENTER);

	// -- main loop of the game, run on levels --
	while (currentLevel <= NUM_OF_LVLS)
	{
		theGame.setLevel(currentLevel);
		system("cls");

		bool isAlive = theGame.run();
	
		if (!isAlive)		// Pacman is now dead
			break;

		currentLevel++;
		system("cls");
		
		if (currentLevel > NUM_OF_LVLS)
			break;
		cout << PassedLevelMsg;
		Sleep(2000);

	}

	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool blink = true;
	int echoTime = 1;

	// CASE the user lost the game
	if (currentLevel <= NUM_OF_LVLS)
	{
		system("cls");
		
		cout << "/n                            U DIED !!!\n\n"
		     << "                      Do your best next time! \n\n\n\n\n"
			 << PlayerLostSticker;
		Sleep(5000);
	}

	// CASE the user won the game
	else{
		do
		{
			system("cls");
			cout << "\n\n";
			if (blink)
				SetConsoleTextAttribute(hconsole, 0);
			else
				SetConsoleTextAttribute(hconsole, 15);

			cout << PlayerWonSticker;

			SetConsoleTextAttribute(hconsole, 15);
			cout << "\n\n			 Congratulations !!!";
			blink = !blink;

			Sleep(400);
			echoTime++;
		} while (echoTime < 11);
	}

	// show final result and exit
		do{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,16 });
			cout << "\n\n			 Final results: "
				 << theGame.getScore() << "\n\n\n\n\n"
			     << "			Press ENTER to EXIT\n";
		} while (_getch() != KB_ENTER);

	return EXIT_SUCCESS;
}

//---------------------------------------------------------------------------//
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}