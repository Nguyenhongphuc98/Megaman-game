#pragma once
#ifndef _Object_H_
#define _Object_H_
#include"Global.h"
#include"Collision.h"

class Object
{
private:
	Global::IdObject idObject;

	int centerX; //location
	int centerY; //location

	int velocityX;
	int velocityY;

	int width;
	int height;

	float timeToCollision;

public:
	Object();
	~Object();

	Object(Global::IdObject idObject,int x,int y, int vx,int vy,int w,int h);
	CollisionRect GetBound();
	ResultColision ProcessCollision(Object *object);
	void UpdateVelocity(ResultColision result);
	void Update();
};

#endif // !_Object_H_
