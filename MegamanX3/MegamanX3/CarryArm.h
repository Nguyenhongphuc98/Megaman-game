#pragma once
#ifndef CarryArm_H_
#define CarryArm_H_
#include"ActionObject.h"
#include"TXT.h"

#define CARRYARM_STRAIGHT_HEIGHT 60*2.5
#define CARRYARM_STRAIGHT_WIDTH 29*2.5

#define CARRYARM_BREAK_HEIGHT 42*2.5
#define CARRYARM_BREAK_WIDTH 29*2.5

class CarryArm:public ActionObject
{
private:
	int count_time_change_animation;
public:
	CarryArm();
	~CarryArm();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	State GetState();
	Direction GetDirection();
};


#endif