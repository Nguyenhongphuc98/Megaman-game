#pragma once
#ifndef Object_H_
#define Object_H_
#include"Animation.h"
#include"Collision.h"
#include"TXT.h"
#include"Global.h"

class Object
{
public:
	Object();
	Object(int x,int y,int w,int h);
	~Object();

protected:
	float x, y; //vi tri o world port (TAM CUA OBJECT)
	float vx, vy; //van toc
	float dx, dy; // quang duoc thuc su =v*dt
	int width, height;
	DWORD dt;
	TypeObject nameObject;

	Animation *animation;

public:
	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);

	void GetPosition(float&x, float&y);
	void GetSpeed(float &vx, float& vy);

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);
	virtual void Render() = 0;
	virtual BoundingBox GetBoundingBox()=0;

	virtual void SetState(State s) {};
	virtual void SetDirection(Direction d) {};

	virtual State GetState() { return STAND; };
	virtual Direction GetDirection() { return RIGHT; };

	TypeObject GetNameObject();

};


#endif // !Object_H_
