#pragma once
#ifndef DieBox_H_
#define DieBox_H_
#include "Object.h"

//Elevator co location buttom-Left in world
class DieBox :public Object
{

public:
	DieBox(float bottom, float left, float w, float h);
	~DieBox();

	void Render() {};
	BoundingBox GetBoundingBox();

};


#endif // !DieBox_H_
