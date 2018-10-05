#pragma once
#ifndef _MegaMan_H_
#define _MegaMan_H_
#include "Object.h"
#include "Collision.h"
#include "Global.h"

#define MEGAMAN_WALKING_SPEED 0.05f

class MegaMan:public Object
{
private:
	Global::Status status;
	Global::Direction direction;
	static MegaMan* instance;
public:
	virtual void LoadResource();
	virtual void Update(float deltaTime, vector<Object*> List_Object_Can_Collision);
	virtual void Render();
	virtual ResultColision ProcessCollision();

	static MegaMan* Instance();
	CollisionRect	GetBound() ;

	MegaMan();
	void SetStatus(Global::Status);
	void SetDirection(Global::Direction);
};
#endif
