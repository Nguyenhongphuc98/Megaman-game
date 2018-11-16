#pragma once
#ifndef Shurikein_H_
#define Shurikein_H_
#include"ActionObject.h"

#define SHURIKEIN_WIDTH 42*2.5
#define SHURIKEIN_HEIGHT 42*2.5

class Shurikein:public ActionObject
{
private:

public:
	Shurikein();
	~Shurikein();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !Shurikein_H_
