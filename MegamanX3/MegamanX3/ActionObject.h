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

	int hitpoints;
	bool destroyed;

	//door shurikein==============
	bool actived;

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
	virtual void SetBeingAttacked(int damage) { this->hitpoints -= damage; }
	virtual bool IsDestroy() { return destroyed; }
	virtual bool IsActived() { return actived; }

	virtual State GetState();
	virtual Direction GetDirection();
	virtual int GetDamage() { return 1; }

	//==============door===========================
	virtual void SetActived(bool active) {this->actived = active; }

	//================blasthornet===========
	virtual BoundingBox GetBoundBee(int i) { return BoundingBox(); }
	virtual void SetBeeSBeingAttack(int indexBee, int damage) {}
};


#endif // !ActionObject_H_
