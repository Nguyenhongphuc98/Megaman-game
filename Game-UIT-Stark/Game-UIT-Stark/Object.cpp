#include"Object.h"


Object::Object()
{
	locationX = locationY = 0;
	velocityX = velocityY = 0;

	animation = new Animation();
}

Object::~Object()
{
}

Object::Object(Global::IdObject id, int x, int y, int vx, int vy, int w, int h)
{
	this->idObject = id;
	this->locationX = x;
	this->locationY = y;
	this->velocityX = vx;
	this->velocityY = vy;
	this->width = w;
	this->height = h;
}


ResultColision Object::ProcessCollision(Object * object)
{
	ResultColision result;
	result = Collision::Instance()->ProcessCollisionSweptAABB(
		this->GetBound(),
		object->GetBound());

	return result;
}



void Object::Update(DWORD dt)
{
	this->dt = dt;
	dx = velocityX * dt;
	dy = velocityY * dt;
}

Global::IdObject Object::GetIdObject()
{
	return this->idObject;
}

int Object::GetWidth()
{
	return this->width;
}

int Object::GetHeight()
{
	return this->height;
}

int Object::GetLocationX()
{
	return locationX;
}

int Object::GetLocationY()
{
	return this->locationY;
}

int Object::GetVelocityX()
{
	return velocityX;
}

int Object::GetVelocityY()
{
	return this->velocityY;
}

Global::Team Object::GetTeam()
{
	return this->team;
}

void Object::SetVelocityX(int vx)
{
	this->velocityX = vx;
}

void Object::SetVelocityY(int vy)
{
	this->velocityY = vy;
}
