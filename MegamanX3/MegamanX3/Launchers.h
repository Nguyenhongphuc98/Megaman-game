#pragma once
#ifndef Launchers_H_
#define Launchers_H_
#include"ActionObject.h"
#include"Megaman.h"

#define LAUNCHERS_WIDTH 96*G_Scale.x
#define LAUNCHERS_HEIGHT 30*G_Scale.y
#define LAUNCHERS_VX 0.0f
#define LAUNCHERS_VY 0.1f

class Launchers:public ActionObject
{
private:
	bool is_allow_runing;

public:
	Launchers();
	Launchers(int x, int y, int w, int h);
	~Launchers();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !Launchers_H_
