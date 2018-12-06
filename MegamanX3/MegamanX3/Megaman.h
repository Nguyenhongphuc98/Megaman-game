#pragma once
#ifndef Megaman_H_
#define Megaman_H_
#include"ActionObject.h"
#include<d3dx9.h>




#define MEGAMAN_HEIGHT 84
#define MEGAMAN_WIDTH 75
#define MEGAMAN_GRAVITY -0.008f
#define MEGAMAN_WALK_SPEED 0.2f
#define MEGAMAN_STAND_JUMP_SPEED 1.5f
#define MEGAMAN_RUN_JUMP_SPEED 1.8f
#define MEGAMAN_JUMP_WALL_SPEED 0.8f
#define MEGAMAN_DASH_SPEED 0.4f

class Megaman:public ActionObject
{
private:
	int yPre;
	bool isGround;
	bool isAllowClimbWall;
	bool charging;

	float time_start_press_A;
	static Megaman* instance;

	
	Animation * animation_charging;
public:
	Megaman();
	~Megaman();

	static Megaman* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	bool SetTimeStartPressA();
	void ResetTimeStartPressA();

	State GetState();
	//State GetShootOldState() { return shoot_state_old; }
	State GetNewState(State currentState, EControler controler);
	Direction GetDirection();
	float GetTimePressA();


	bool IsCanJump() { return (isGround||isAllowClimbWall); }
	bool IsGround() { return isGround; }
	bool IsFinishUpGun();
	bool IsFinshAction();
	bool IsCharging() { return charging; }
	void SetGround(bool ground) { this->isGround = ground; }
	void ResetAnimation() { this->animation->listSprite[state]->Reset(); }
};

#endif // !Megaman_H_
