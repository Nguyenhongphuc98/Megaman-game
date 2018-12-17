#pragma once
#ifndef MetaCapsule_H_
#define MetaCapsule_H_
#include"ActionObject.h"
#include"WeaponSystem.h"



class MetaCapsule :public ActionObject
{
private:
	float start_location_y, start_location_x;
	float time_start_shoot;
	bool can_shoot;

public:
	MetaCapsule();
	MetaCapsule(int x, int y, int w, int h, Direction d);
	~MetaCapsule();


	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetActived(bool active) {  this->actived = active; }

};


#endif // !CarryBox_H_
