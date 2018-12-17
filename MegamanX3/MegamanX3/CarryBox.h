#pragma once
#ifndef CarryBox_H_
#define CarryBox_H_
#include"ActionObject.h"
#include"WeaponSystem.h"

#define CARRYBOX_VY -0.15f
#define CARRYBOX_VX 0.15f
#define CARRYBOX_WIDTH 100
#define CARRYBOX_HEIGHT 100

#define CARRYBOX_MAX_HP 3


class CarryBox :public ActionObject
{
private:
	float start_location_y, start_location_x;
	bool arrived;

public:
	CarryBox();
	CarryBox(int x, int y, int w, int h, Direction d);
	~CarryBox();


	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetActived(bool active) { this->Reset(); this->actived = active; }

	void Reset();

	bool IsArrived() { return this->arrived&&!this->destroyed; }
};


#endif // !CarryBox_H_
