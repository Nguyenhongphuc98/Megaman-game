#pragma once
#include "GameObject.h"
class Camera : public GameObject
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
};