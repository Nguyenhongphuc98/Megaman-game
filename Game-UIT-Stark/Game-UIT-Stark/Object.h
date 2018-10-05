#pragma once
#ifndef _Object_H_
#define _Object_H_
#include"Global.h"
#include<vector>
#include "Animation.h"
using namespace std;

class Object
{
protected:
	Global::IdObject	idObject;
	Global::Team		team;
	Animation *animation;

	int locationX; //left
	int locationY; //top

	int dx; //quang duong thuc su se di / frame -> dx=v*dt	
	int dy;

	float velocityX;
	float velocityY;

	int width;
	int height;

	DWORD dt;

public:
	Object();
	~Object();

	Object(Global::IdObject idObject, int x, int y, float vx, float vy, int w, int h);
	virtual CollisionRect	GetBound() = 0;
	Global::IdObject GetIdObject();
	ResultColision			ProcessCollision(Object *object);
	virtual void			Update(DWORD dt);
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
