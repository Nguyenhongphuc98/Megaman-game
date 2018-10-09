#include"CollisionRect.h"

CollisionRect::CollisionRect()
{
}

CollisionRect::CollisionRect(int top, int left, int width, int height, float vx, float vy)
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
	return !(this->left>(CRect.left+CRect.width)
		||this->top<(CRect.top-CRect.height)
		||(this->left+width)<CRect.left
		||(this->top-height)>CRect.top);
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

int CollisionRect::GetTop()
{
	return this->top;
}

int CollisionRect::GetLeft()
{
	return this->left;
}

int CollisionRect::GetWidth()
{
	return this->width;
}

int CollisionRect::GetHeight()
{
	return this->height;
}
