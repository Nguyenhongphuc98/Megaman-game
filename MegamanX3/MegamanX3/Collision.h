#pragma once
#ifndef Collision_H_
#define	Collision_H_
#include<limits>
#include<float.h>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

struct BoundingBox {
	float x, y;
	float w, h;
	float vx, vy; //quang duong di duoc thuc su
};

struct ResultCollision
{
	bool isCollision;
	float nx, ny;
	float t;
}; 

//in worldPort
class Collision
{
private:
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	float xEntry, yEntry;
	float xExit, yExit;

	float entryTime;
	float exitTime;

	//van toc tuong doi cua 2 vat
	float vx, vy;

	static Collision *instance;
public:
	Collision();
	~Collision();

	static Collision* Instance();
	bool CollisionAABB(BoundingBox b1, BoundingBox b2);
	ResultCollision CollisionSweptAABB(BoundingBox b1, BoundingBox b2);
};
#endif // !Collision_H
