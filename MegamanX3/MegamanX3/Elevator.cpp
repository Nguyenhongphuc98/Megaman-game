#include"Elevator.h"

Elevator::Elevator(float bottom, float left, float w, float h, Direction d)
{
	this->x = left;
	this->y = bottom;
	this->width = w;
	this->height = h;
	this->dir = d;
	this->nameObject = ELEVATOR;
}

Elevator::~Elevator()
{
}

BoundingBox Elevator::GetBoundingBox()
{
	BoundingBox r;
	r.vx = r.vy = 0;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	return r;
}
