#pragma once
#ifndef TextStartGame_H_
#define TextStartGame_H_
#include"ActionObject.h"

#define CARRYBOX_VY -0.08f
#define CARRYBOX_WIDTH 144
#define CARRYBOX_HEIGHT 144


class TextStartGame :public ActionObject
{
private:

public:
	TextStartGame();
	TextStartGame(int x, int y, int w, int h, Direction d);
	~TextStartGame();


	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetDestroy(bool destroy) { this->destroyed = destroy; }
};


#endif // !TextStartGame_H_
