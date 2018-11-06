#include"VirtualObject.h"

VirtualObject::VirtualObject(float top, float left, float w, float h)
{
	this->x = left;
	this->y = top;
	this->width = w;
	this->height = h;
}

VirtualObject::~VirtualObject()
{
}

BoundingBox VirtualObject::GetBoundingBox()
{
	BoundingBox r;
	r.vx = r.vy = 0;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	return r;
}
