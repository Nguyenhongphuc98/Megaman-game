#pragma once
#ifndef Camera_H_
#define Camera_H_
#include"Global.h"

class Camera
{
private:
	static Camera *instance;
	float x, y; //position of camera in world Port | position viewport
public:
	Camera();
	~Camera();

	static Camera* Instance();
	void Update(float x, float y);
	void Reset();

	D3DXVECTOR2 GetPositionInViewPort(float x,float y);
	void GetCameraPosition(float &x, float&y);
};


#endif // !Camera_H_
