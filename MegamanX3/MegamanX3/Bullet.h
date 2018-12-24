#pragma once
#ifndef Bullet_H_
#define Bullet_H_
#include"Camera.h"
#include"ActionObject.h"

class Bullet :public Object
{
protected:
	float max_distance;
	float damage;
	float angle;
	bool destroyed;
	bool destroying;

	State state;
	Direction direction;

public:
	Bullet();
	~Bullet();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col) {};
	virtual void Render();
	virtual BoundingBox GetBoundingBox() = 0;

	virtual void SetState(State s)=0;
	virtual void SetDirection(Direction d)=0;

	virtual bool IsDestroyed();
	virtual bool IsDestroying() { return this->destroying; }
	virtual void SetDestroying(bool destroying) { this->destroying = destroying; }

	int GetDamege();
};


#endif // !Bullet_H_
