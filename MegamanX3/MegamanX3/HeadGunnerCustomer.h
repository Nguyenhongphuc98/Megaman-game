#pragma once
#ifndef HeadGunnerCustomer_H_
#define HeadGunnerCustomer_H_
#include"ActionObject.h"
#include"HeadGunnerCustomerBulletTube.h"
#include"WeaponSystem.h"
#include"Megaman.h"

#define HEADGUNNERCUSTOMER_WIDTH 36*2.5
#define HEADGUNNERCUSTOMER_HEIGHT 43*2.5
#define HEADGUNNERCUSTOMER_MAX_HP 6

class HeadGunnerCustomer:public ActionObject
{
private:
	int count_animation;
	int count_bulet_tube;
	float time_latest_shot;

public:
	HeadGunnerCustomer();
	HeadGunnerCustomer(int x, int y, int w, int h, Direction d);
	~HeadGunnerCustomer();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !HeadGunnerCustomer_H_
