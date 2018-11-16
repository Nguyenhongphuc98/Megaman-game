#pragma once
#ifndef Bee_H_
#define Bee_H_
#include"ActionObject.h"
#define BEE_WIDTH 16*2.5
#define BEE_HEIGHT 18*2.5

class Bee:public ActionObject
{
private:

public:
	Bee();
	~Bee();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !Bee_H_
