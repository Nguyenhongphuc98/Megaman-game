#pragma once
#ifndef Helit_H_
#define Helit_H_
#include"ActionObject.h"

#define HELIT_VX 0.2f

class Helit:public ActionObject	
{
private:
	int center_region_x;

public:
	Helit();
	~Helit();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !Helit_H_
