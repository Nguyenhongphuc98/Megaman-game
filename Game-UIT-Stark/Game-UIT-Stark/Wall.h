#pragma once
#ifndef _Wall_H_
#define _Wall_H_

#include"Object.h"
#include"Global.h"

#define WALL_WIDTH 800
#define WALL_HEIGHT 20

class  Wall :public Object
{
private:
	Global::Status status;

public:
	Wall();
	~Wall();
	

	virtual CollisionRect	GetBound();
	virtual void			Render();
	void SetStatus(Global::Status);
};

#endif // !_Wall_H_