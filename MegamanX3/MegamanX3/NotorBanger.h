#pragma once
#ifndef NotorBanger_H_
#define NotorBanger_H_

#include"ActionObject.h"
#include"Megaman.h"

#define NOTORBANGER_WIDTH 34*G_Scale.x
#define NOTORBANGER_HEIGHT 40*G_Scale.y
#define NOTORBANGER_VX 0.3f
#define NOTORBANGER_VY 0.5f

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

	int distance_to_megaman;
	int count_number_shots;
	float time_begin_shot;
	float time_begin_stand;
	float t;
	float distance_has_jumped_x;
	float distance_has_jumped_y;
	bool shot90;
	bool shot60;
	bool uped_the_gun60;
	bool uped_the_gun90;
	bool active;
	bool jump;

public:
	NotorBanger();
	NotorBanger(int x,int y,int w,int h,Direction d);
	~NotorBanger();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	void ReSet();
};


#endif // !NotorBanger_H_
