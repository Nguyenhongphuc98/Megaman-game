#pragma once
#ifndef NotorBanger_H_
#define NotorBanger_H_

#include"ActionObject.h"

#define NOTORBANGER_WIDTH 36*G_Scale.x
#define NOTORBANGER_HEIGHT 36*G_Scale.y
#define NOTORBANGER_VX 0.1f
#define NOTORBANGER_VY 0.1f

#define PII 3.141415
#define NOTORBANGER_GRAVITY 0.1f


class NotorBanger:public ActionObject
{
private:
	int center_region_x;
	int time_animate_shoot90;
	float time_begin_jump;
	float jump_angle;
	float pre_x;
	float pre_y;

public:
	NotorBanger();
	~NotorBanger();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !NotorBanger_H_
