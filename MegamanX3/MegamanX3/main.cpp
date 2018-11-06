#include<Windows.h>
#include"MyGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MyGame *game = new MyGame(nCmdShow);
	game->InitGame();
	game->GameRun();

	return 0;
}