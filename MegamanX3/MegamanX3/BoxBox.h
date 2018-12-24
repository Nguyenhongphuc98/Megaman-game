#pragma once
#ifndef BoxBox_H_
#define BoxBox_H_
#include"ActionObject.h"
#include"Megaman.h"

#define BOX_WIDTH 100
#define BOX_HEIGHT 100
#define BOXBOX_WIDTH 100
#define BOXBOX_HEIGHT 600

#define BOXBOX_MAX_HP 5
#define BOXBOX_DAMAGE 0
#define BOX_POSITINON1_DAMAGE 16
#define BOX_POSITINON2_DAMAGE 2

//virtual object co location button-Left in world
class BoxBox :public ActionObject
{
private:
	int damage;

public:
	BoxBox(float top, float left, float w, float h);
	~BoxBox() {};


	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	BoundingBox GetBoundingBox();

	void SetState(State s) { this->state = s; }
	int GetDamage() { return this->damage; }
};


#endif // !BoxBox_H_
