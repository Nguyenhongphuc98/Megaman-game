#pragma once
#ifndef MegamanBullet3_H_
#define MegamanBullet3_H_
#include"Bullet.h"

#define MEGAMAN_BULLET3_VX 1.0
#define MEGAMAN_BULLET3_VY 0
#define MEGAMAN_BULLET3_WIDTH 22
#define MEGAMAN_BULLET3_HEIGHT 22
#define MEGAMAN_BULLET3_DAMAGE 5

class MegamanBullet3 :public Bullet
{
private:
	float distance_has_shot_x;

public:
	MegamanBullet3(float x, float y, Direction d);
	~MegamanBullet3();

	virtual void Update(DWORD dt, vector<Object*> *List_enemy_objects);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MegamanBullet1_H_
