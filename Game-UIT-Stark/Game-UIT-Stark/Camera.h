#pragma once
#include "Object.h"
#include"define.h"
#include"MegaMan.h"

class Camera : public Object
{
private:
	static Camera * instance;
	/*POINT _Position;
	POINT _Size;*/
	Camera();
public:
	bool followPlayerX;
	bool followPlayerY;
	bool canFollowLeft;
	bool canFollowRight;
	bool canFollowUp;
	bool canFollowDown;
	~Camera();
	/*POINT getPosition() const;
	POINT getSize() const;
	void setPosition(const POINT& p);
	void setSize(const POINT &p);*/
	static Camera* Instance();
	CollisionRect	GetBound();
	void Update(float x,float y);
	void Refresh();
	void SetPosition(float x, float y);
	D3DXVECTOR3 GetPositionInCamera(float x, float y);
};