#include "MegaMan.h"
MegaMan* MegaMan::instance;

void MegaMan::LoadResource()
{
	//-----------------------------------------------------------------------
	//Load sprite stand
	//-----------------------------------------------------------------------
	//cai nay se lay tu xml, gio test tam. set cung o day
	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 18;
	r1->left = 2;
	r1->right = 24;
	r1->bottom = 41;

	RECT *r2 = new RECT;
	r2->top = 18;
	r2->left = 27;
	r2->right = 49;
	r2->bottom = 41;

	RECT *r3 = new RECT;
	r3->top = 18;
	r3->left = 52;
	r3->right = 74;
	r3->bottom = 41;

	listSourceRectStand.push_back(r1);
	listSourceRectStand.push_back(r2);
	listSourceRectStand.push_back(r3);
	animation->ListSprite[Global::STAND] = new Sprite("megaman.png", listSourceRectStand);
}

void MegaMan::Update(float deltaTime, vector<Object*> List_Object_Can_Collision)
{
	//update location
	Object::Update(deltaTime); 

	//update collision
	//get list collision

	//if listCollision.size=0 => 0 va cham
	locationX += dx;
	locationY += dy;


	//else
	//xu li va cham
	//nho xet th co nhieu cai cothe va cham thi pha lay cai time it nhat
	//nho su dung ky thuat block de k bi overlap nextframe-> xem sample thay dung


}

void MegaMan::Render()
{
	//animation->ListSprite[status]->Render();
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0));
	animation->NextFrame(Global::STAND);
}

ResultColision MegaMan::ProcessCollision()
{
	return ResultColision();
}

MegaMan * MegaMan::Instance()
{
	if (!instance)
		instance = new MegaMan();
	return instance;
}

CollisionRect MegaMan::GetBound()
{
	return CollisionRect();
}

MegaMan::MegaMan()
{
	status = Global::STAND;
	LoadResource();
}

void MegaMan::SetStatus(Global::Status status)
{
	this->status = status;
	switch (status)
	{
	case Global::STAND:
		//set x,y lai vi trang thi khac nhau thi boundingbox khac nhau
		velocityX = 0;
		velocityY = 0;
		break;
	case Global::RUN:
		if(this->direction==Global::LEFT)
			velocityX = -MEGAMAN_WALKING_SPEED;
		if (this->direction == Global::RIGHT)
			velocityX = MEGAMAN_WALKING_SPEED;
		break;
	}
}

void MegaMan::SetDirection(Global::Direction d)
{
	this->direction = d;
}
