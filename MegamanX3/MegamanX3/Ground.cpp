#include"Ground.h"

Ground::Ground()
{
	x = 518;
	y = 94;
	vx = vy = 0;
	LoadResource();
}

Ground::~Ground()
{
}

BoundingBox Ground::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x- GROUNG_WIDTH/2;
	bound.y = y- GROUND_HEIGHT/2;
	bound.w = GROUNG_WIDTH;
	bound.h = GROUND_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Ground::Render()
{
	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(x, y);
	animation->Render(STAND, RIGHT,position);
}

void Ground::LoadResource()
{
	vector<RECT*> List;
	RECT* r = new RECT();
	r->top = 0;
	r->left = 0;
	r->bottom = 73;
	r->right = 414;
	List.push_back(r);
	MyTexture* texture = new MyTexture((char*)"SourceImage\\ground1.png",D3DCOLOR_XRGB(0,0,0));
	animation->listSprite[STAND] = new Sprite(texture,List , 1);
}
