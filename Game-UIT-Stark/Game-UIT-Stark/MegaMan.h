#pragma once
#ifndef _MegaMan_H_
#define _MegaMan_H_
#include "Object.h"
#include "Collision.h"
#include "Global.h"
#include"Camera.h"

#define MEGAMAN_WALKING_SPEED 0.5f
#define MEGAMAN_JUMP_SPEED 2.0f
#define MEGAMAN_WIDTH 60
#define MEGAMAN_HEIGHT 70

class MegaMan:public Object
{
private:
	Global::Status status;
	Global::Direction direction;
	static MegaMan* instance;

	int tempAllowRender = 0;
public:
	virtual void LoadResource();
	virtual void Update(float deltaTime, vector<Object*> List_Object_Can_Collision);
	virtual void Render();
	void RenderBoundingBox();
	//virtual ResultColision ProcessCollision();

	static MegaMan* Instance();
	CollisionRect	GetBound() ;

	MegaMan();
	void SetStatus(Global::Status);
	void SetDirection(Global::Direction);
};
#endif
