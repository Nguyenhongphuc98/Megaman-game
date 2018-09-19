#pragma once
#ifndef _CollisionRect_H_
#define _CollisionRect_H_


class CollisionRect
{
private:
	int top; //y
	int left;//x
	int width;
	int height;

	float velocityX;
	float velocityY;
public:
	CollisionRect();
	CollisionRect(int top,int left,int width,int height,int vx,int xy);
	~CollisionRect();
	
	bool IsIntersect(CollisionRect CRect);
	bool IsContain(CollisionRect CRect);

	void SetVelocityX(float v);
	float GetVelocityX();

	void SetVelocityY(float v);
	float GetVelocityY();

	int GetTop();
	int GetLeft();
	int GetWidth();
	int GetHeight();
};

#endif // !_CollisionRect_H_
