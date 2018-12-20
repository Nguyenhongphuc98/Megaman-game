#pragma once
#ifndef HeadGunnerCustomerBulletTube_H_
#define HeadGunnerCustomerBulletTube_H_
#include"Bullet.h"

#define HEADGUNNERCUSTOMER_BULLET_TUBE_VX 0.5
#define HEADGUNNERCUSTOMER_BULLET_TUBE_VY 0.3
#define HEADGUNNERCUSTOMER_BULLET_TUBE_WIDTH 21*G_Scale.x
#define HEADGUNNERCUSTOMER_BULLET_TUBE_HEIGHT 7*G_Scale.y

class HeadGunnerCustomerBulletTube:public Bullet
{
private:
	bool finish_smoke;
	float start_x;

public:
	HeadGunnerCustomerBulletTube(float x, float y, Direction d);
	~HeadGunnerCustomerBulletTube();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();
};


#endif // !HeadGunnerCustomerBulletTube_H_
