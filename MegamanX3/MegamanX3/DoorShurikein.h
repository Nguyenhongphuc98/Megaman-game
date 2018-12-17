#pragma once
#ifndef DoorShurikein_H_
#define DoorShurikein_H_
#include"ActionObject.h"
#include"Megaman.h"
#include"Genjibo.h"

#define DOORSHURIKEIN_WIDTH 15*2.5
#define DOORSHURIKEIN_HEIGHT 48*2.5

//virtual object co location button-Left in world
class DoorShurikein :public ActionObject
{
private:
	bool locked;
	bool moving_megaman;
	bool allow_open; //default true, can open one time.
	float x_start_megaman;

	static DoorShurikein* instance;

public:
	DoorShurikein(float top, float left, float w, float h);
	~DoorShurikein() {};

	static  DoorShurikein* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col) ;
	void Render();
	BoundingBox GetBoundingBox();

	void SetState(State s) { this->state = s; }
	void SetActived(bool active);

};


#endif // !DoorShurikein_H_
