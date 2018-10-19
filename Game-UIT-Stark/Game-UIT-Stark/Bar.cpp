#include"Ball.h"
#include "Bar.h"

Bar::Bar()
{
	idObject = Global::BAR;
	locationX = 30;
	locationY = 80;
	LoadResource();	
}

Bar::~Bar()
{
}

void Bar::LoadResource()
{
	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 384;
	r1->left = 430;
	r1->right = 478;
	r1->bottom = 576;

	boundingbox = Graphic::Instance()->CreateSurface(D3DCOLOR_XRGB(0, 122, 204));
	listSourceRectStand.push_back(r1);
	animation->ListSprite[Global::STAND] = new Sprite("bar.png", listSourceRectStand, D3DCOLOR_XRGB(0, 102, 102));
	
}

void Bar::Update(float deltaTime, vector<Object*> List_Object_Can_Collision)
{
	//update location
	Object::Update(deltaTime);

	//update collision
	//get list collision

	//if listCollision.size=0 => 0 va cham
	locationX += dx;
	locationY += dy;

	if (locationY >= 388)
		locationY = 387;
	if (locationY <= 20)
		locationY = 21;
}

void Bar::Render()
{
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0), D3DXVECTOR3(0.5, 1, 0));
	//RenderBoundingBox();
}

void Bar::RenderBoundingBox()
{
	Graphic *g = Graphic::Instance();
	/*RECT *r = new RECT();
	r->top = this->locationY-2;
	r->left = this->locationX-2;
	r->right = r->left + BAR_WIDTH+3;
	r->bottom = r->top + BAR_HEIGHT+3;*/

	RECT r;
	r=Global::ConvertCollisionRectToRECT(this->GetBound());

	g->DrawSurface(boundingbox, NULL, &r);
}

CollisionRect Bar::GetBound()
{
	return CollisionRect(locationY,locationX,BAR_WIDTH,BAR_HEIGHT,velocityX,velocityY);
}

void Bar::SetStatus(Global::Status status)
{
	this->status = status;
	switch (status)
	{
	case Global::STAND:
		//set x,y lai vi trang thi khac nhau thi boundingbox khac nhau
		velocityX = 0;
		velocityY = 0;
		//Trace::Log("stand bar");
		break;
	case Global::RUN:
		if (this->direction == Global::UP)
			velocityY = -BAR_RUN_SPEED;
		if (this->direction == Global::DOWN)
			velocityY = BAR_RUN_SPEED;
		break;
	}
}

void Bar::SetDirection(Global::Direction d)
{
	this->direction = d;
}
