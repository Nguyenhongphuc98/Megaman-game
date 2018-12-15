#pragma once
#ifndef Virtual_Object_H_
#define Virtual_Object_H_
#include "Object.h"

//virtual object co location buttom-Left in world
class VirtualObject:public Object
{
public:
	VirtualObject(float bottom,float left,float w,float h);
	~VirtualObject();

	void Render() {};
	BoundingBox GetBoundingBox();
};


#endif // !Virtual_Object_H_
