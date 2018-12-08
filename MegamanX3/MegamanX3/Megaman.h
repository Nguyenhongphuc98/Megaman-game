#pragma once
#ifndef Megaman_H_
#define Megaman_H_
#include"ActionObject.h"
#include<d3dx9.h>
#include"Bullet.h"
#include<list>


#define MEGAMAN_HEIGHT 84
#define MEGAMAN_WIDTH 75
#define MEGAMAN_GRAVITY -0.008f
#define MEGAMAN_WALK_SPEED 0.2f
#define MEGAMAN_STAND_JUMP_SPEED 1.5f
#define MEGAMAN_RUN_JUMP_SPEED 1.8f
#define MEGAMAN_JUMP_WALL_SPEED 0.8f
#define MEGAMAN_DASH_SPEED 0.4f
#define MEGAMAN_DISTANCE_DASH 250

class Megaman:public ActionObject
{
private:
	int yPre;
	int xStartDash;

	bool isAllowDash;
	bool isGround;
	bool isAllowClimbWall;
	bool charging;
	bool hurting;

	float time_start_press_A;
	static Megaman* instance;

	
	Animation * animation_charging;
	Animation * animation_lifebar;
public:
	Megaman();
	~Megaman();

	static Megaman* Instance();

	void Update(DWORD dt, vector<Object*> *List__virtual_object_can_col);
	void ProcessCollisionBullet(list<Bullet*> List__bullet_enemy);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	bool SetTimeStartPressA();
	void SetAllowDash(bool allow) { this->isAllowDash = allow; }
	void ResetTimeStartPressA();

	State GetState();
	//State GetShootOldState() { return shoot_state_old; }
	State GetNewState(State currentState, EControler controler);
	Direction GetDirection();
	float GetTimePressA();
	int GetDistanceDash() { return abs(this->x - xStartDash); }


	bool IsCanJump() { return (isGround||isAllowClimbWall); }
	bool IsGround() { return isGround; }
	bool IsFinishUpGun();
	bool IsFinshAction();
	bool IsCharging() { return charging; }
	bool IsCanDash() { return isAllowDash; }

	void SetGround(bool ground) { this->isGround = ground; }
	void ResetAnimation() { this->animation->listSprite[state]->Reset(); }
};

#endif // !Megaman_H_
