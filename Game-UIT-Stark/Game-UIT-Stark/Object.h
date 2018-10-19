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
	LPDIRECT3DSURFACE9 boundingbox;

	float locationX; //left
	float locationY; //top

	float dx; //quang duong thuc su se di / frame -> dx=v*dt	
	float dy;

	float velocityX;
	float velocityY;

	float width;
	float height;

	DWORD dt;

public:
	Object();
	~Object();

	Object(Global::IdObject idObject, float x, float y, float vx, float vy, float w, float h);
	virtual CollisionRect	GetBound()=0;
	Global::IdObject GetIdObject();
	ResultColision			ProcessCollision(Object *object);
	virtual void			Update(DWORD dt);
	virtual void			Render() {};
	virtual void RenderBoundingBox();

	float GetWidth();
	float GetHeight();
	float GetLocationX();
	float GetLocationY();
	float GetVelocityX();
	float GetVelocityY();
	float GetDx();
	float GetDy();
	Global::Team GetTeam();

	void SetVelocityX(float vx);
	void SetVelocityY(float vy);
	void SetLocation(float x, float y);
};

#endif // !_Object_H_
