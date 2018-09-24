#pragma once
#ifndef _Collision_H_
#define _Collision_H_

#include"CollisionRect.h"
#include <limits> 

struct ResultColision
{
	bool collision; //flag if collision it =true
	float timeToColision; //thời gian để xảy ra va chạm tiếp theo
	int velocityX; //hướng của vector theo x sau khi va chạm
	int velocityY; //hướng của vector theo y sau khi va chạm
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

	float timeToCollision;
	float timeToEndCollision;

	static Collision *instance;

public:
	 Collision();
	~ Collision();

	static Collision* Instance();

	ResultColision ProcessCollisionSweptAABB(CollisionRect oject1, CollisionRect object2);
};


#endif // !_Collision_H_
