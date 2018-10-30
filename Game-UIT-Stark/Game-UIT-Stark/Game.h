#pragma once
#ifndef _Game_H_
#define _Game_H_
#include"FGraphics.h"
#include "FKeyBoard.h"
#include"FMouse.h"

//cai nay la test
#include "MegaMan.h"
#include"Map.h"
#include"Brick.h"

class Game
{
private:
	MegaMan *megaMan;
	Map* map;
	Brick *br1,*br2,*br3,*br4,*br5,*br6,*br7,*br8;

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
