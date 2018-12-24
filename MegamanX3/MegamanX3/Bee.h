#pragma once
#ifndef Bee_H_
#define Bee_H_
#include"ActionObject.h"
#include"WeaponSystem.h"
#include"Megaman.h"
#define BEE_WIDTH 16*2.5
#define BEE_HEIGHT 18*2.5
#define BEE_VY 0.2f
#define BEE_TIME_DESTROY 8000
#define BEE_MAX_HP 3

#define BLASTHORNET_TOP 15317
#define BLASTHORNET_LEFT 7700*G_Scale.x
#define BLASTHORNET_RIGHT 7925*G_Scale.x
#define GROUND (107+G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y

class Bee:public ActionObject
{
private:
	int center_region_y;
	float time_start_active;
	bool folowBlasthornet;
	bool folowMegaman;

public:
	Bee();
	Bee(int x, int y, int w, int h, Direction d);
	~Bee();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetFollowBlastHornet(bool allow) { this->folowBlasthornet = allow; }
	void SetFollowMegaman(bool allow) { this -> folowMegaman = allow; }
	void ResetBee(int x, int y, Direction d,float vx,float vy);
};


#endif // !Bee_H_
