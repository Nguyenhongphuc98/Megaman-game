#include"Ball.h"
#include "Bar.h"

Bar::Bar()
{
	locationX = 30;
	locationY = 100;
	LoadResource();	
}

Bar::~Bar()
{
}

void Bar::LoadResource()
{
	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 18;
	r1->left = 2;
	r1->right = 24;
	r1->bottom = 41;


	listSourceRectStand.push_back(r1);
	animation->ListSprite[Global::STAND] = new Sprite("megaman.png", listSourceRectStand, D3DCOLOR_XRGB(0, 102, 102));
	
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
}

void Bar::Render()
{
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0));
}

CollisionRect Bar::GetBound()
{
	return CollisionRect();
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
		Trace::Log("stand bar");
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
