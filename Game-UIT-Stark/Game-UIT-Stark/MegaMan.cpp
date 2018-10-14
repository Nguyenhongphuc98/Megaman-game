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
	r1->top = 1;
	r1->left = 2;
	r1->right = 37;
	r1->bottom = 60;

	RECT *r2 = new RECT;
	r2->top = 1;
	r2->left = 38;
	r2->right = 76;
	r2->bottom = 60;

	RECT *r3 = new RECT;
	r3->top = 1;
	r3->left = 78;
	r3->right = 115;
	r3->bottom = 60;

	RECT *r4 = new RECT;
	r4->top = 1;
	r4->left = 115;
	r4->right = 160;
	r4->bottom = 60;

	RECT *r5 = new RECT;
	r5->top = 1;
	r5->left = 168;
	r5->right = 209;
	r5->bottom = 60;

	RECT *r6 = new RECT;
	r6->top = 1;
	r6->left = 212;
	r6->right = 259;
	r6->bottom = 60;
	
	RECT *r7 = new RECT;
	r7->top = 1;
	r7->left = 263;
	r7->right = 328;
	r7->bottom = 60;

	RECT *r8 = new RECT;
	r8->top = 1;
	r8->left = 330;
	r8->right = 380;
	r8->bottom = 60;

	RECT *r9 = new RECT;
	r9->top = 1;
	r9->left = 389;
	r9->right = 434;
	r9->bottom = 60;

	RECT *r10 = new RECT;
	r10->top = 1;
	r10->left = 440;
	r10->right = 476;
	r10->bottom = 60;

	RECT *r11 = new RECT;
	r11->top = 1;
	r11->left = 485;
	r11->right = 519;
	r11->bottom = 60;

	listSourceRectStand.push_back(r1);
	listSourceRectStand.push_back(r2);
	listSourceRectStand.push_back(r3);
	listSourceRectStand.push_back(r4);
	listSourceRectStand.push_back(r5);
	listSourceRectStand.push_back(r6);
	listSourceRectStand.push_back(r7);
	listSourceRectStand.push_back(r8);
	listSourceRectStand.push_back(r9);
	listSourceRectStand.push_back(r10);
	listSourceRectStand.push_back(r11);
	animation->ListSprite[Global::STAND] = new Sprite("megaman.png", listSourceRectStand, D3DCOLOR_XRGB(255, 255, 255));
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
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0), D3DXVECTOR3(2, 2, 0));
	if (tempAllowRender % 3 == 0)
	{	
		animation->NextFrame(Global::STAND);
	}
	tempAllowRender++;
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
	locationX = 300;
	locationY = 480;
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
