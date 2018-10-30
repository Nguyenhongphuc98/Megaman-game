#include "Camera.h"

Camera::Camera() : Object()
{
	locationX = 0;
	locationY = 600;
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
	return CollisionRect(locationX,locationY,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
}

void Camera::Update(float x,float y)
{
	velocityX = 0;
	velocityY = 0;

	//in world	
	this->locationX = x - SCREEN_WIDTH / 2;
	this->locationY = y + SCREEN_HEIGHT / 2;

	Refresh();
}

void Camera::Refresh()
{
	if (locationX < 0)
		locationX = 0;
	if (locationX > (WORLD_X - SCREEN_WIDTH))
		locationX=WORLD_X - SCREEN_WIDTH;
}

void Camera::SetPosition(float x, float y)
{
	locationX = x;
	locationY = y;
}

D3DXVECTOR3 Camera::GetPositionInCamera(float x, float y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = -locationX;
	matrix._42 = locationY;
	D3DXVECTOR4 viewPort_position;

	D3DXVECTOR3 worldPosition = D3DXVECTOR3(x, y, 0);
	D3DXVec3Transform(&viewPort_position, &worldPosition, &matrix);

	D3DXVECTOR3 position = D3DXVECTOR3(viewPort_position.x, viewPort_position.y, 0);

	return position;
}
