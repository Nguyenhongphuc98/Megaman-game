#include"Object.h"

Object::Object()
{
	animation = new Animation();
}

Object::Object(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	animation = new Animation();
}

Object::~Object()
{
}

void Object::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Object::SetSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

void Object::GetPosition(float & x, float & y)
{
	x = this->x;
	y = this->y;
}

void Object::GetSpeed(float & vx, float & vy)
{
	vx = this->vx;
	vy = this->vy;
}

void Object::Update(DWORD dt ,vector<Object*> *List_object_can_col)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

TypeObject Object::GetNameObject()
{
	return this->nameObject;
}
