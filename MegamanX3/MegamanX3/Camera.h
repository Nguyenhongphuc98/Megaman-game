#pragma once
#ifndef Camera_H_
#define Camera_H_
#include"Global.h"
#include"Box.h"

class Camera
{
private:
	static Camera *instance;
	float x, y; //position of camera in world Port | position viewport
	bool auto_moving_x;
	bool locked;
public:
	Camera();
	~Camera();

	static Camera* Instance();
	void Update(float x, float y);
	void Reset();

	D3DXVECTOR2 GetPositionInViewPort(float x,float y);
	void GetCameraPosition(float &x, float&y);
	Box GetBound();

	void SetAutoMovingX(bool moving) { this->auto_moving_x = moving; }
	//lock when meet boss
	void SetLocked(bool lock) { this->locked = lock; }
	//when shurikein die, make to avoid loop lock camera
	void SetBonousX(float x) { this->x += x; } 
};


#endif // !Camera_H_
