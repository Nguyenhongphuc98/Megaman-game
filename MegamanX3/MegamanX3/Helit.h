#pragma once
#ifndef Helit_H_
#define Helit_H_
#include"ActionObject.h"
#include"WeaponSystem.h"
#include"Megaman.h"

#define HELIT_VY 0.1f
#define HELIT_MAX_HP 1

#define HELIT_WIDTH 20
#define HELIT_HEIGHT 20

class Helit:public ActionObject	
{
private:
	int center_region_y;
	float time_last_bulet; //cacula time for next bullet

public:
	Helit();
	Helit( int x, int y, int w, int h, Direction d);
	~Helit();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !Helit_H_
