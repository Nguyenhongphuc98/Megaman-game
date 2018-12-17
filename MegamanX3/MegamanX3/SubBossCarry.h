#pragma once
#ifndef SubBossCarry_H_
#define SubBossCarry_H_
#include"ActionObject.h"
#include"WeaponSystem.h"
#include"CarryBox.h"
#include"CarryArm.h"
#include"MetaCapsule.h"

#define SUBBOSSCARRY_VY -0.08f
#define SUBBOSSCARRY_BOX_SUM 6


class SubBossCarry :public ActionObject
{
private:
	float start_location_y;
	float location_leg_x, location_leg_y;// leg
	float time_body_start_runing;
	float time_start_create_box;

	bool leg_runing;
	bool can_create_box;
	bool cleared_box;

	int count_box;
	int box_colli;

	Animation* animation_leg;

	CarryBox* carryBox1;
	CarryBox* carryBox2;

	CarryArm* carryArm1;
	CarryArm* carryArm2;

	MetaCapsule* metaSapsule;

	static SubBossCarry* instance;
public:
	SubBossCarry();
	SubBossCarry(int x, int y, int w, int h, Direction d);
	~SubBossCarry();

	static SubBossCarry* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetActived(bool active);
	void SetBeingAttacked(int damage);
};


#endif // !SubBossCarry_H_
