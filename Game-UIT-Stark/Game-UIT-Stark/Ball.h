#pragma once
#ifndef _Ball_H_
#define _Ball_H_
#include"Object.h"

#define BALL_SPEED 1.0f
#define BALL_WIDTH 28
#define BALL_HEIGHT 28

class Ball:public Object
{
private:
public:
	Ball();
	~Ball();

	virtual CollisionRect	GetBound();
	virtual void Render();
	virtual void Update(float deltaTime, vector<Object*> List_Object_Can_Collision);
	virtual void RenderBoundingBox();
};


#endif // !_Ball_H_
