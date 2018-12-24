#pragma once
#ifndef HelitBullet_H_
#define HelitBullet_H_
#include"Bullet.h"
#include"Sound.h"

#define HELIT_BULLET_VX 0.5f
#define HELIT_BULLET_VY 0
#define HELIT_BULLET_WIDTH 22
#define HELIT_BULLET_HEIGHT 22
#define HELIT_BULLET_DAMAGE 1

class HelitBulet :public Bullet
{
private:
	float distance_has_shot_x;

public:
	HelitBulet(float x, float y, Direction d);
	~HelitBulet();

	virtual void Update(DWORD dt, vector<Object*> *List_objects);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !HelitBullet_H_
