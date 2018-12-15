#pragma once
#ifndef Shurikein_H_
#define Shurikein_H_
#include"ActionObject.h"
#include"WeaponSystem.h"
#include"DoorRightShurikein.h"
#include<random>

#define SHURIKEIN_WIDTH 42*2.5
#define SHURIKEIN_HEIGHT 42*2.5

#define SHURIKEIN_RUN_VX 0.3f
#define SHURIKEIN_JUMP_WALL_VY 0.3f
#define SHURIKEIN_JUMP_VX 0.1f
#define SHURIKEIN_JUMP_VY 0.4f
#define SHURIKEIN_MAX_HP 100

enum ActionShurikein
{
	RunHorizontal,
	JumpWall,
	StandRotate,
	RunAround
};

class Shurikein:public ActionObject
{
private:
	int animation_loop_rotate;
	float time_start_stand;
	float start_x, start_y;
	float time_create_fire_start;
	int count_run_horizontal;

	bool actived;

	ActionShurikein current_action;

	static Shurikein* instance;

public:
	Shurikein();
	Shurikein(int x, int y, int w, int h, Direction d);
	~Shurikein();

	static Shurikein* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetActived(bool allow) { this->actived = allow; }
};


#endif // !Shurikein_H_
