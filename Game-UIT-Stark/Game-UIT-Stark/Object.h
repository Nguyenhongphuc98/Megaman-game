#pragma once
#ifndef _Object_H_
#define _Object_H_
#include"Global.h"
#include"Collision.h"
#include"define.h"

class Object
{
protected:
	Global::IdObject	idObject;
	Global::Team		team;

	int locationX; //left
	int locationY; //top

	int dx; //quang duong thuc su se di / frame -> dx=v*dt	
	int dy;

	int velocityX;
	int velocityY;

	int width;
	int height;

	DWORD dt;

public:
	Object();
	~Object();

	Object(Global::IdObject idObject, int x, int y, int vx, int vy, int w, int h);
	virtual CollisionRect	GetBound() = 0;
	Global::IdObject GetIdObject();
	ResultColision			ProcessCollision(Object *object);
	virtual void			Update(DWORD dt, vector<Object*> *List_Object_Can_Collision);
	virtual void			Render() {};

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
