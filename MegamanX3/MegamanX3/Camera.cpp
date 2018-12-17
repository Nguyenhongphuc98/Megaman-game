#include"Camera.h"
Camera* Camera::instance;

Camera::Camera()
{
	this->auto_moving_x = false;
	this->locked = false;
}

Camera::~Camera()
{
}

Camera * Camera::Instance()
{
	if (!instance)
		instance = new Camera();
	return instance;
}

void Camera::Update(float x, float y)
{
	//========don't allow update x,y when meet boss===================
	if (this->locked)
		return;

	//=======if open the door, can auto moving camera and megaman to meet boss
	if (this->auto_moving_x)
	{
		this->x += 3;

		//=========boss shurikein die / open door==============================
		if (this->x > 2553 * G_Scale.x&&this->x < 2556 * G_Scale.x)
		{
			this->auto_moving_x = false;
			//this->locked = true;
		}
		else
		//=========meet boss shurikein==============================
		if (this->x > 2313 * G_Scale.x&&this->x < 2317 * G_Scale.x&&!locked)
		{
			this->auto_moving_x = false;
			this->locked = true;
		}
		else
			//===============meet subboss carry=======================
		if (this->x > 4900 * G_Scale.x&&this->x < 4902 * G_Scale.x)
		{
			this->auto_moving_x = false;
			this->locked = true;
		}
		return;
	}



	this->x = x - G_ScreenWidth / 2;
	this->y = y + 3*G_ScreenHeight / 4-40;

	if (this->x < 0)
		this->x = 0;
	if (this->y < G_ScreenHeight)
		this->y = G_ScreenHeight;

	//d=========uong ong ngang dau tien================
	if (this->x < (700)*G_Scale.x && this->y>((1285+G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y))
		this->y = (1285 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	//==============duong ong doc===============
	if (this->x > 772 * G_Scale.x&&this->x<1520*G_Scale.x&&this->y<(1765+G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y)
		this->x = 772 * G_Scale.x;

	//============duong ong ngang tiep theo===============
	if (this->x > 770 * G_Scale.x&&this->y > (1799 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y)
		this->y = (1799 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;

	//==========open door shurikein boss==============
	if (this->x > 2060 * G_Scale.x&&this->x < 2260 * G_Scale.x)
		this->x = 2060 * G_Scale.x;

	//=========khi di qua door right boss shurikein k cho camera quay lai
	if (this->x > 2313 * G_Scale.x&&this->x < 2553 * G_Scale.x)
		this->x = 2553 * G_Scale.x;

	//============when subboss box die - not allow camera quay lai===============
	if (this->x > 4800 * G_Scale.x&&this->x < 4902 * G_Scale.x)
		this->x = 4902 * G_Scale.x;
}

void Camera::Reset()
{
	x = 0;
	y = G_ScreenHeight;
}

D3DXVECTOR2 Camera::GetPositionInViewPort(float x, float y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -this->x;
	matrix._42 =  this->y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}

void Camera::GetCameraPosition(float & x, float & y)
{
	x = this->x;
	y = this->y;
}

Box Camera::GetBound()
{
	return Box(this->x / G_Scale.x,this->y / G_Scale.y,G_ScreenWidth/G_Scale.x,G_ScreenHeight / G_Scale.y);
}
