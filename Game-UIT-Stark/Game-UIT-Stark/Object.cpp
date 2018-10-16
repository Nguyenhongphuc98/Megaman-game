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

Object::Object(Global::IdObject id, int x, int y, float vx, float vy, int w, int h)
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
	/*dx = velocityX * dt;
	dy = velocityY * dt;*/
	dx = velocityX;
	dy = velocityY;
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

void Object::SetLocation(int x, int y)
{
	locationX = x;
	locationY = y;
}
