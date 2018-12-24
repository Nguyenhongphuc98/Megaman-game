#pragma once
#ifndef NotorBanger_H_
#define NotorBanger_H_

#include"ActionObject.h"
#include"Megaman.h"
#include"WeaponSystem.h"
#include"ItemBlood.h"


#define NOTORBANGER_WIDTH 25*G_Scale.x
#define NOTORBANGER_HEIGHT 40*G_Scale.y
#define NOTORBANGER_VX 0.3f
#define NOTORBANGER_VY 0.5f

#define PII 3.141415
#define NOTORBANGER_GRAVITY 0.1f
#define NOTORBANGER_MAX_HP 5
#define NOTORBANGER_DAMAGE 1


class NotorBanger:public ActionObject
{
private:
	int center_region_x;
	float time_begin_jump;
	float jump_angle;
	//float pre_x;
	//float pre_y;

	//using when destroy
	/*float hat_x, hat_y;
	float eye_x, eye_y;
	float gun_x, gun_y;	*/

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
	int GetDamage() {return NOTORBANGER_DAMAGE;}

	void SetState(State s);
	void SetDirection(Direction d);
	
	

	void ReSet();
};


#endif // !NotorBanger_H_
