#pragma once
#ifndef MegamanBullet2_H_
#define MegamanBullet2_H_
#include"Bullet.h"

#define MEGAMAN_BULLET2_VX 1.0
#define MEGAMAN_BULLET2_VY 0
#define MEGAMAN_BULLET2_WIDTH 22
#define MEGAMAN_BULLET2_HEIGHT 22
#define MEGAMAN_BULLET2_DAMAGE 3

class MegamanBullet2 :public Bullet
{
private:
	float distance_has_shot_x;

public:
	MegamanBullet2(float x, float y, Direction d);
	~MegamanBullet2();

	virtual void Update(DWORD dt, vector<Object*> *List_enemy_objects);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MegamanBullet1_H_
