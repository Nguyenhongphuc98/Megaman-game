#pragma once
#ifndef _Ball_H_
#define _Ball_H_
#include"Object.h"

#define BALL_SPEED -0.13f
#define BALL_WIDTH 57
#define BALL_HEIGHT 57

class Ball:public Object
{
private:
	LPDIRECT3DSURFACE9 boundingbox;
public:
	Ball();
	~Ball();

	virtual CollisionRect	GetBound();
	virtual void Render();
	virtual void Update(float deltaTime, vector<Object*> List_Object_Can_Collision);
	virtual void RenderBoundingBox();
};


#endif // !_Ball_H_
