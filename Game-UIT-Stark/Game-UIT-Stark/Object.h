#pragma once
#ifndef _Object_H_
#define _Object_H_
#include"Global.h"
#include"Collision.h"
#include"define.h"

class Object
{
private:
	Global::IdObject idObject;
	Global::Team team;

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
	void Update();

	Global::IdObject GetIdObject();
	int GetWidth();
	int GetHeight();
	int GetLocationX();
	int GetLocationY();
	int GetVelocityX();
	int GetVelocityY();
	Global::Team GetTeam();

	void SetVelocityX(int vx);
	void SetVelocityY(int vy);
};

#endif // !_Object_H_
