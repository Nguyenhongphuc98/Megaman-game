#include"Wall.h"

Wall::Wall()
{
	//vector<RECT*> listSourceRect1;
	//RECT *r1 = new RECT;
	//r1->top = 1;
	//r1->left = 2;
	//r1->right = 37;
	//r1->bottom = 60;
	//listSourceRect1.push_back(r1);

	vector<RECT*> listSourceRect2;
	RECT *r2 = new RECT;
	r2->top = 0;
	r2->left = 0;
	r2->right = 22;
	r2->bottom = 419;
	listSourceRect2.push_back(r2);

//	animation->ListSprite[Global::HORIZONTAL]=new Sprite("wall.png", listSourceRect1, D3DCOLOR_XRGB(255, 255, 255));
	animation->ListSprite[Global::VERTICAL] = new Sprite("wall.png", listSourceRect2, D3DCOLOR_XRGB(255, 255, 255));
}

Wall::~Wall()
{
}

CollisionRect Wall::GetBound()
{
	if (status == Global::VERTICAL) {
		return CollisionRect(locationY, locationX, 20, 600, 0.0f, 0.0f);
	}
	else
	{
		return CollisionRect(locationY, locationX, WALL_WIDTH, WALL_HEIGHT, 0.0f, 0.0f);
	}
	
}

void Wall::Render()
{
	if (status == Global::VERTICAL) {
		animation->Render(Global::RIGHT, Global::VERTICAL, D3DXVECTOR3(locationX, locationY, 0), D3DXVECTOR3(1, 1.5, 0));
	}
	else
	{
		Object::RenderBoundingBox();
	}

}

void Wall::SetStatus(Global::Status s)
{
	this->status = s;
}
