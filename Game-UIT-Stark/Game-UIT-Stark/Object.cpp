#include"Object.h"


Object::Object()
{
	timeToCollision = 1;
}

Object::~Object()
{
}

Object::Object(Global::IdObject id, int x, int y, int vx, int vy, int w, int h)
{
	this->idObject = id;
	this->centerX = x;
	this->centerY = y;
	this->velocityX = vx;
	this->velocityY = vy;
	this->width = w;
	this->height = h;
	timeToCollision = 1;
}

CollisionRect Object::GetBound()
{
	int left = this->centerX - this->width / 2;
	int top = this->centerY - this->height / 2;
	CollisionRect bound(top, left, width, height, velocityX, velocityY);
	return bound;
}

ResultColision Object::ProcessCollision(Object * object)
{
	ResultColision result;
	result = Collision::Instance()->ProcessCollisionSweptAABB(
		this->GetBound(),
		object->GetBound());

	return result;
}

void Object::UpdateVelocity(ResultColision result)
{
	timeToCollision = result.timeToColision;
	this->velocityX *= result.velocityX;
	this->velocityY *= result.velocityY;
}

void Object::Update()
{
	//this->centerX = this->centerX+ velocityX*timeToCollision;
	//this->centerY = this->centerY+ velocityY *timeToCollision;
	//timeToCollision = 1;

	//xai tam cai nay vi xu li va cham dang bi loi
	if (this->centerX > 760 || this->centerX < 40)
		velocityX *= -1;
	if (this->centerY > 560 || this->centerY < 40)
		velocityY *= -1;

	this->centerX = this->centerX + velocityX;
	this->centerY = this->centerY + velocityY;
}
