#pragma once
#ifndef Speedburner_H_
#define Speedburner_H_
#include"Bullet.h"


#define SPEEDBURNER_DAMAGE 10
#define SPEEDBURNER_WIDTH_NORMAL 18
#define SPEEDBURNER_HEIGHT_NORMAL 18

#define SPEEDBURNER_HEIGHT_SUPPER
#define SPEEDBURNER_WIDTH_SUPPER

#define SPEEDBURNER_VX 1.0
#define SPEEDBURNER_VY 0

class Speedburner :public Bullet
{
public:
	Speedburner(float x,float y,Direction d,State s);
	~Speedburner();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s) ;
	void SetDirection(Direction d) ;
};

#endif // !Speedburner_H_
