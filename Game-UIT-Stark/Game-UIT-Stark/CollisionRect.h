#pragma once
#ifndef _CollisionRect_H_
#define _CollisionRect_H_


class CollisionRect
{
private:
	float top; //y
	float left;//x
	float width;
	float height;

	float velocityX;
	float velocityY;
public:
	CollisionRect();
	CollisionRect(float top, float left, float width, float height,float vx,float xy);
	~CollisionRect();
	
	bool IsIntersect(CollisionRect CRect);
	bool IsContain(CollisionRect CRect);

	void SetVelocityX(float v);
	float GetVelocityX();

	void SetVelocityY(float v);
	float GetVelocityY();

	float GetTop();
	float GetLeft();
	float GetWidth();
	float GetHeight();
};

#endif // !_CollisionRect_H_
