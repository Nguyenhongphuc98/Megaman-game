#pragma once
#ifndef DashSmoke_H_
#define DashSmoke_H_
#include"Bullet.h"


class DashSmoke :public Bullet
{
private:
	

public:
	DashSmoke(float x, float y, Direction d);
	~DashSmoke();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox() { return BoundingBox(); };

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MegamanBullet1_H_
