#include "UI.h"
#include "game.h"
#include <windows.h>
int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { 131, 37 };
	SMALL_RECT rc = { 0, 0, 130, 36 };
	SetConsoleScreenBufferSize(hOut, size);
	SetConsoleWindowInfo(hOut, TRUE, &rc);
	srand((unsigned)time(NULL));
	Game * pGame = CreatGame();
	StartGame(pGame);
	DestroyGame(pGame);
	system("pause");
	return 0;
}