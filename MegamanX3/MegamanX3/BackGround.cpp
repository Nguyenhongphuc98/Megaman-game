#include"Background.h"

BackGround::BackGround(MyTexture *texture, float x, float y)
{
	vector<RECT*> l;
	RECT* r=new RECT();
	r->top = 0;
	r->left = 0;
	r->right = 585;
	r->bottom = 257;
	l.push_back(r);
	this->animation->listSprite[STAND] = new Sprite(texture, l,1);

	this->x = x;
	this->y = y;
}

BackGround::~BackGround()
{
}

void BackGround::Render()
{
	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(x, y);
	animation->Render(STAND, RIGHT, position);
}
