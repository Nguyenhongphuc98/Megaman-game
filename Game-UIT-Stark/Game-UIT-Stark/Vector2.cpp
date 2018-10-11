#include"Vector2.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2 &vector)
{
	this->x = vector.x;
	this->y = vector.y;
}

Vector2::~Vector2()
{

}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}


//Overloading
Vector2& Vector2::operator+(const Vector2 &b)
{
	Vector2 result;
	result.x = this->x + b.x;
	result.y = this->y + b.y;
	return result;
}
Vector2& Vector2:: operator-(const Vector2 &b)
{
	Vector2 result;
	result.x = this->x - b.x;
	result.y = this->y - b.y;
	return result;
}

Vector2&  Vector2::operator=(const Vector2 &b)
{
	this->x = b.x;
	this->y = b.y;
	return *this;
}

bool Vector2::operator==(const Vector2 &b)
{
	return (this->x == b.x) && (this->y == b.y);
}

bool Vector2::operator!=(const Vector2 &b)
{
	return (this->x != b.x) || (this->y != b.y);
}