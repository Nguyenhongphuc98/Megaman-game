#include"DieBox.h"

DieBox::DieBox(float bottom, float left, float w, float h)
{
	this->x = left;
	this->y = bottom;
	this->width = w;
	this->height = h;

	this->nameObject = DIEBOX;
}

DieBox::~DieBox()
{
}

BoundingBox DieBox::GetBoundingBox()
{
	BoundingBox r;
	r.vx = r.vy = 0;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	return r;
}
