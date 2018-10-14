#pragma once
#ifndef _Wall_H_
#define _Wall_H_

#include"Object.h"

#define WALL_WIDTH 800
#define WALL_HEIGHT 20

class  Wall :public Object
{
public:
	Wall();
	~Wall();

	virtual CollisionRect	GetBound();
	virtual void			Render();
private:

};

#endif // !_Wall_H_