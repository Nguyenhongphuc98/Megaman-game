#include"Object.h"


Object::Object()
{
	locationX = 200;
	locationY = 440;
	velocityX = 0.0f;
	velocityY = 0.0f;

	animation = new Animation();
	boundingbox = Graphic::Instance()->CreateSurface(D3DCOLOR_XRGB(0, 122, 204));
}

Object::~Object()
{
}

Object::Object(Global::IdObject id, float x, float y, float vx, float vy, float w, float h)
{
	this->idObject = id;
	this->locationX = x;
	this->locationY = y;
	this->velocityX = vx;
	this->velocityY = vy;
	this->width = w;
	this->height = h;
	boundingbox = Graphic::Instance()->CreateSurface(D3DCOLOR_XRGB(0, 122, 204));
}
//
//CollisionRect Object::GetBound()
//{
//	return CollisionRect(locationX,locationY,width,height,0,0);
//}


ResultColision Object::ProcessCollision(Object * object)
{
	ResultColision result;
	CollisionRect object1= this->GetBound();
	CollisionRect object2= object->GetBound();
	result = Collision::Instance()->ProcessCollisionSweptAABB(
		object1,
		object2);

	return result;
}



void Object::Update(DWORD dt)
{
	this->dt = dt;
	dx = velocityX * dt;
	dy = velocityY * dt;
	//dx = velocityX;
	//dy = velocityY;
}

void Object::RenderBoundingBox()
{
	RECT r;
	r = Global::ConvertCollisionRectToRECT(GetBound());

	Graphic::Instance()->DrawSurface(boundingbox, NULL, &r);
}

Global::IdObject Object::GetIdObject()
{
	return this->idObject;
}

float Object::GetWidth()
{
	return this->width;
}

float Object::GetHeight()
{
	return this->height;
}

float Object::GetLocationX()
{
	return locationX;
}

float Object::GetLocationY()
{
	return this->locationY;
}

float Object::GetVelocityX()
{
	return velocityX;
}

float Object::GetVelocityY()
{
	return this->velocityY;
}

float Object::GetDx()
{
	return dx;
}

float Object::GetDy()
{
	return dy;
}

Global::Team Object::GetTeam()
{
	return this->team;
}

void Object::SetVelocityX(float vx)
{
	this->velocityX = vx;
}

void Object::SetVelocityY(float vy)
{
	this->velocityY = vy;
}

void Object::SetLocation(float x, float y)
{
	locationX = x;
	locationY = y;
}
