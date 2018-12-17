#pragma once
#ifndef MetaCapsuleBullet_H_
#define MetaCapsuleBullet_H_
#include"WeaponSystem.h"

#define METACAPSULE_BULLET_VX -0.3
#define METACAPSULE_BULLET_VY 0
#define METACAPSULE_BULLET_WIDTH 22
#define METACAPSULE_BULLET_HEIGHT 22
#define METACAPSULE_BULLET_DAMAGE 1

class MetaCapsuleBullet :public Bullet
{
private:
	float distance_has_shot_x;
	

public:
	MetaCapsuleBullet(float x, float y, Direction d);
	~MetaCapsuleBullet();

	virtual void Update(DWORD dt, vector<Object*> *List_virtual_objects);//process col with virtaul
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MetaCapsuleBullet_H_
