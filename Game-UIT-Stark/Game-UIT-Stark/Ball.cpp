#include"Ball.h"
Ball::Ball()
{
	locationX = 200;
	locationY = 200;

	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 119;
	r1->left = 43;
	r1->right = 75;
	r1->bottom = 151;

	listSourceRectStand.push_back(r1);
	animation->ListSprite[Global::STAND] = new Sprite("ball.png", listSourceRectStand, D3DCOLOR_XRGB(12, 19, 19));
}

Ball::~Ball()
{
}

CollisionRect Ball::GetBound()
{
	return CollisionRect();
}

void Ball::Render()
{
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0));
	animation->NextFrame(Global::STAND);
}
