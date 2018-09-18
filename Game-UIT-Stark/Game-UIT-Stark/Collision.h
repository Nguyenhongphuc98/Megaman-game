#pragma once
#ifndef _Collision_H_
#define _Collision_H_

#include"CollisionRect.h"
#include <limits> 

struct ResultColision
{
	float timeToColision; //thời gian để xảy ra va chạm tiếp theo
	int velocityX; //hướng của vector theo x saukhi va chạm
	int velocityY; //hướng của vector theo y saukhi va chạm
};

class  Collision
{
private:
	float sXToCollision;
	float sYToCollision;

	float sXToEndCollision;
	float sYToEndCollision;

	float tXToCollision;
	float tYToCollision;

	float tXToEndCollision;
	float tYToEndCollision;

public:
	 Collision();
	~ Collision();

	ResultColision ProcessCollisionSweptAABB(CollisionRect oject1, CollisionRect object2);
};


#endif // !_Collision_H_
