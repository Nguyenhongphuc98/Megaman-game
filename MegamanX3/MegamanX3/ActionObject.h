#pragma once
#ifndef ActionObject_H_
#define ActionObject_H_
#include"Object.h"
#include"Camera.h"

class ActionObject:public Object
{
protected:
	State state;
	Direction direction;

public:
	ActionObject();
	ActionObject(int x,int y,int w,int h,Direction d);
	~ActionObject();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col) {};
	virtual void Render();
	virtual void LoadResource() {};

	virtual BoundingBox GetBoundingBox();

	virtual void SetState(State s) {};
	virtual void SetDirection(Direction d) {};

	virtual State GetState();
	virtual Direction GetDirection();
};


#endif // !ActionObject_H_
