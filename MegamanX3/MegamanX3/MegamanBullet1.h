#pragma once
#ifndef MegamanBullet1_H_
#define MegamanBullet1_H_
#include"Bullet.h"

#define MEGAMAN_BULLET1_VX 1.0
#define MEGAMAN_BULLET1_VY 0
#define MEGAMAN_BULLET1_WIDTH 22
#define MEGAMAN_BULLET1_HEIGHT 22
#define MEGAMAN_BULLET1_DAMAGE 1

class MegamanBullet1:public Bullet
{
private:
	float distance_has_shot_x;

public:
	MegamanBullet1(float x, float y, Direction d);
	~MegamanBullet1();

	virtual void Update(DWORD dt, vector<Object*> *List_enemy_objects);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MegamanBullet1_H_
