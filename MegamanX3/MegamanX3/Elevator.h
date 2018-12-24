#pragma once
#ifndef Elevator_H_
#define Elevator_H_
#include "Object.h"

//Elevator co location buttom-Left in world
class Elevator :public Object
{
private: Direction dir;
public:
	Elevator(float bottom, float left, float w, float h,Direction d);
	~Elevator();

	void Render() {};
	BoundingBox GetBoundingBox();

	Direction GetDirection() { return this->dir; }
};


#endif // !Elevator_H_
