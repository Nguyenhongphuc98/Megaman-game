#pragma once
#ifndef Virtual_Object_H_
#define Virtual_Object_H_
#include "Object.h"

//virtual object co location Top-Left
class VirtualObject:public Object
{
public:
	VirtualObject(float top,float left,float w,float h);
	~VirtualObject();

	void Render() {};
	BoundingBox GetBoundingBox();
};


#endif // !Virtual_Object_H_
