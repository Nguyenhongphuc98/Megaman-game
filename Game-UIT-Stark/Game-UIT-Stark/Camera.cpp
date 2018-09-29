#include "Camera.h"

Camera::Camera() : Object()
{
	locationX = 0;
	locationY = 0;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
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

CollisionRect Camera::GetBound()
{
	return CollisionRect();
}
