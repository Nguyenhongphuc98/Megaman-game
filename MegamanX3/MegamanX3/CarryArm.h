#pragma once
#ifndef CarryArm_H_
#define CarryArm_H_
#include"ActionObject.h"
#include"TXT.h"

#define CARRYARM_STRAIGHT_HEIGHT 60*2.5
#define CARRYARM_STRAIGHT_WIDTH 29*2.5

#define CARRYARM_BREAK_HEIGHT 42*2.5
#define CARRYARM_BREAK_WIDTH 29*2.5

#define CARRYARM_VY -0.15f
#define CARRYARM_VX 0.15f

class CarryArm:public ActionObject
{
private:
	int count_time_change_animation;
	float start_location_y, start_location_x;
	bool uping;

public:
	CarryArm();
	CarryArm(int x, int y, int w, int h, Direction d);
	~CarryArm();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	State GetState();
	Direction GetDirection();
	void SetActived(bool active) { this->Reset(); this->actived = active; }

	void Reset();
};


#endif