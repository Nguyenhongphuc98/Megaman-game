#pragma once
#ifndef _MegaMan_H_
#define _MegaMan_H_
#include "Object.h"
#include "Collision.h"
#include "Global.h"

class MegaMan:public Object
{
private:
	Global::Status status;
	static MegaMan* instance;
public:
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual ResultColision ProcessCollision();

	static MegaMan* Instance();
	CollisionRect	GetBound() ;
};
#endif
