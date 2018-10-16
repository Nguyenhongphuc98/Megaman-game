#pragma once
#ifndef _Bar_H_
#define _Bar_H_
#include"Object.h"
#include"Global.h"

#define BAR_RUN_SPEED 2.0f
#define BAR_WIDTH 24
#define BAR_HEIGHT 192
#define BAR_A 2

class Bar:public Object
{
private:
	Global::Status status;
	Global::Direction direction;

	LPDIRECT3DSURFACE9 boundingbox;
public:
	Bar();
	~Bar();

	virtual void LoadResource();
	virtual void Update(float deltaTime, vector<Object*> List_Object_Can_Collision);
	virtual void Render();
	//virtual ResultColision ProcessCollision();
	virtual void RenderBoundingBox();

	CollisionRect	GetBound();
	void SetStatus(Global::Status);
	void SetDirection(Global::Direction);

};


#endif // !_Bar_H_
