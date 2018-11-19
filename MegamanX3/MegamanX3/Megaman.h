#pragma once
#ifndef Megaman_H_
#define Megaman_H_
#include"ActionObject.h"
#include<d3dx9.h>

#define MEGAMAN_HEIGHT 84
#define MEGAMAN_WIDTH 75
#define MEGAMAN_GRAVITY -0.02f
#define MEGAMAN_WALK_SPEED 0.2f
#define MEGAMAN_JUMP_SPEED 1.0f
#define MEGAMAN_DASH_SPEED 0.4f

class Megaman:public ActionObject
{
private:
	

public:
	Megaman();
	~Megaman();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	State GetState();
	Direction GetDirection();
};

#endif // !Megaman_H_
