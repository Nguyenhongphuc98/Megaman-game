#include"ActionObject.h"

ActionObject::ActionObject()
{
	this->destroyed = false;
}

ActionObject::ActionObject(int x, int y, int w, int h, Direction d):Object(x,y,w,h)
{
	this->direction = d;
}

ActionObject::~ActionObject()
{
}

void ActionObject::Render()
{
	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(x, y);
	animation->Render(state, direction, position);
	animation->Next(state);
}

BoundingBox ActionObject::GetBoundingBox()
{
	return BoundingBox();
}

State ActionObject::GetState()
{
	return state;
}

Direction ActionObject::GetDirection()
{
	return direction;
}
