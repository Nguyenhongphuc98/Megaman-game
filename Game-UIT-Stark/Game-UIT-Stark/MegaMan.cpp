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
	r1->left = 1;
	r1->right = 25;
	r1->bottom = 41;

	RECT *r2 = new RECT;
	r2->top = 18;
	r2->left = 26;
	r2->right = 50;
	r2->bottom = 41;

	RECT *r3 = new RECT;
	r3->top = 18;
	r3->left = 51;
	r3->right = 75;
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
	animation->ListSprite[status]->Render();
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
