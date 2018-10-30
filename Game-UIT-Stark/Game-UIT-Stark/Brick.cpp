#include"Brick.h"

Brick::Brick()
{
	width = BRICK_WIDTH;
	height = BRICK_HEIGHT;
	vector<RECT*> listSourceRect2;
	RECT *r2 = new RECT;
	r2->top = 0;
	r2->left = 0;
	r2->right = 32;
	r2->bottom = 32;
	listSourceRect2.push_back(r2);

	animation->ListSprite[Global::STAND] = new Sprite("brick.png", listSourceRect2, D3DCOLOR_XRGB(255, 255, 255));
}

Brick::~Brick()
{
}

CollisionRect Brick::GetBound()
{
	//get in worldport
	return CollisionRect(locationY-BRICK_HEIGHT,locationX,BRICK_WIDTH,BRICK_HEIGHT,0,0);
}

void Brick::Update(DWORD dt)
{
}

void Brick::Render()
{
	Camera *camera = Camera::Instance();
	D3DXVECTOR3 inPosition = camera->GetPositionInCamera(locationX, locationY);

	animation->Render(Global::RIGHT, Global::STAND, inPosition, D3DXVECTOR3(2, 2, 0));
	//RenderBoundingBox();	
}

void Brick::RenderBoundingBox()
{
	RECT r;
	//get location in viewport
	Camera *camera = Camera::Instance();
	D3DXVECTOR3 inPosition = camera->GetPositionInCamera(locationX,locationY);
	r.left = inPosition.x;	
	r.right = r.left + BRICK_WIDTH;
	r.top = inPosition.y;
	r.bottom = r.top + BRICK_HEIGHT;
	Graphic::Instance()->DrawSurface(boundingbox, NULL, &r);
}
