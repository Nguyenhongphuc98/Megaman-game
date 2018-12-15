#pragma once
#ifndef DoorRightShurikein_H_
#define DoorRightShurikein_H_
#include"ActionObject.h"
#include"Megaman.h"

#define DOORRIGHTSHURIKEIN_WIDTH 15*2.5
#define DOORRIGHTSHURIKEIN_HEIGHT 48*2.5

//virtual object co location button-Left in world
class DoorRightShurikein :public ActionObject
{
private:
	bool locked;
	bool moving_megaman;
	bool allow_open; //default false, when shuri die, we can allow open
	float x_start_megaman;

	static DoorRightShurikein* instance;

public:
	DoorRightShurikein(float top, float left, float w, float h);
	~DoorRightShurikein() {};

	static DoorRightShurikein* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	BoundingBox GetBoundingBox();

	void SetState(State s) { this->state = s; }
	void SetActived(bool active);
	void SetAllowOpen(bool allow) {
		this->allow_open = allow; 
	}
};


#endif // !DoorRightShurikein_H_
