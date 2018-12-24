#pragma once
#ifndef Honey_H_
#define Honey_H_
#include"ActionObject.h"
#include"WeaponSystem.h"
#include"Megaman.h"
#define HONEY_WIDTH 16*2.5
#define HONEY_HEIGHT 18*2.5
#define HONEY_VY 0.2f

#define BLASTHORNET_TOP 15317
#define BLASTHORNET_LEFT 7700*G_Scale.x
#define BLASTHORNET_RIGHT 7925*G_Scale.x
#define GROUND (107+G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y

class Honey :public ActionObject
{
private:
	int center_region_y;
	float time_start_active;

	bool touchedMegaman;

public:
	Honey();
	Honey(int x, int y, int w, int h, Direction d);
	~Honey();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void ResetHoney(int x, int y);

	bool IsTouchedMegaman() { return this->touchedMegaman; }
};


#endif // !Honey_H_
