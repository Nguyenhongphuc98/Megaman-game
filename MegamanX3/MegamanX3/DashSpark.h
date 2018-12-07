#pragma once
#ifndef DashSpark_H_
#define DashSpark_H_
#include"Bullet.h"


class DashSpark :public Bullet
{
private:
	

public:
	DashSpark(float x, float y, Direction d);
	~DashSpark();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox() { return BoundingBox(); };

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();

};


#endif // !MegamanBullet1_H_
