#pragma once
#ifndef _Brick_H_
#define _Brick_H_
#include"Global.h"
#include"Object.h"
#include"Camera.h"

#define BRICK_WIDTH 64
#define BRICK_HEIGHT 64

class Brick:public Object
{
private:
public:
	Brick();
	~Brick();

	virtual CollisionRect	GetBound();
	virtual void			Update(DWORD dt);
	virtual void			Render();
	virtual void RenderBoundingBox();

};


#endif // !_Brick_H_
