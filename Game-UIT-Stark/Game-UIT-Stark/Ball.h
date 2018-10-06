#pragma once
#ifndef _Ball_H_
#define _Ball_H_
#include"Object.h"

class Ball:public Object
{
public:
	Ball();
	~Ball();

	virtual CollisionRect	GetBound();
	virtual void Render();
private:

};


#endif // !_Ball_H_
