#include"CollisionRect.h"

CollisionRect::CollisionRect()
{
}

CollisionRect::CollisionRect(float top, float left, float width, float height, float vx, float vy)
{
	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;
	this->velocityX = vx;
	this->velocityY = vy;
}

CollisionRect::~CollisionRect()
{}

bool CollisionRect::IsIntersect(CollisionRect CRect)
{
	return !(this->left > (CRect.left + CRect.width)
		|| this->top > (CRect.top + CRect.height)
		|| (this->left + this->width) < CRect.left
		|| (this->top + this->height) < CRect.top);
}

bool CollisionRect::IsContain(CollisionRect CRect)
{
	return (this->top >= CRect.GetTop()
		&& this->left <= CRect.GetLeft()
		&& (this->GetLeft() + this->GetWidth()) >= (CRect.GetLeft() + CRect.GetWidth())
		&& (this->GetTop()-this->GetHeight())<= (CRect.GetTop() - CRect.GetHeight()));
}

void CollisionRect::SetVelocityX(float v)
{
	this->velocityX = v;
}

float CollisionRect::GetVelocityX()
{
	return this->velocityX;
}

void CollisionRect::SetVelocityY(float v)
{
	this->velocityY = v;
}

float CollisionRect::GetVelocityY()
{
	return this->velocityY;
}

float CollisionRect::GetTop()
{
	return this->top;
}

float CollisionRect::GetLeft()
{
	return this->left;
}

float CollisionRect::GetWidth()
{
	return this->width;
}

float CollisionRect::GetHeight()
{
	return this->height;
}
