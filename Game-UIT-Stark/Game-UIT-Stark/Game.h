#pragma once
#ifndef _Game_H_
#define _Game_H_
#include"FGraphics.h"
#include "FKeyBoard.h"
#include"FMouse.h"

//cai nay la test
#include "MegaMan.h"
#include"Ball.h"
#include"Bar.h"

class Game
{
private:
	MegaMan *megaMan;
	Ball *ball;
	Bar *bar;
	Bar *barRight;
	//temp;
	LPDIRECT3DSURFACE9 t;
public:
	Game();
	~Game();

	void Init();
	void LoadResource();

	void ProcessInput();
	void Update(float deta);
	void Render();

	void RunGame(float delta); //go to the main loop
	FKeyBoard *keyboard;
};


#endif // !_Game_H_
