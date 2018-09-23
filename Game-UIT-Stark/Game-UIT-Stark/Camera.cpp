#include "Camera.h"

Camera::Camera() : GameObject()
{
	_Position.x = 0;
	_Position.y = 0;
	_Size.x = SCREEN_WIDTH;
	_Size.y = SCREEN_HEIGHT;
	followPlayerX = true;
	followPlayerY = false;
}

Camera::~Camera()
{
}

//POINT Camera::getPosition() const
//{
//	return _Position;
//}
//
//POINT Camera::getSize() const
//{
//	return _Size;
//}
//
//void Camera::setPosition(const POINT & p)
//{
//	_Position.x = p.x;
//	_Position.y = p.y;
//}
//
//void Camera::setSize(const POINT & p)
//{
//	_Size.x = p.x;
//	_Size.y = p.y;
//}
Camera *Camera::instance = nullptr;
Camera * Camera::Instance()
{
	if (!instance)
		instance = new Camera();
	return instance;
}
