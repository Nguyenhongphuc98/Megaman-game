#include "MegaMan.h"
MegaMan* MegaMan::instance;

MegaMan::MegaMan()
{
	locationX = 400;
	locationY = 400;
	status = Global::STAND;
	LoadResource();
}

void MegaMan::LoadResource()
{
	//-----------------------------------------------------------------------
	//Load sprite stand
	//-----------------------------------------------------------------------
	//cai nay se lay tu xml, gio test tam. set cung o day
	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 329;
	r1->left = 165;
	r1->right = 195;
	r1->bottom = 366;

	RECT *r2 = new RECT;
	r2->top = 329;
	r2->left = 195;
	r2->right = 228;
	r2->bottom = 366;

	RECT *r3 = new RECT;
	r3->top = 329;
	r3->left = 228;
	r3->right = 260;
	r3->bottom = 366;

	RECT *r4 = new RECT;
	r4->top = 329;
	r4->left = 260;
	r4->right = 292;
	r4->bottom = 366;

	RECT *r5 = new RECT;
	r5->top = 329;
	r5->left = 292;
	r5->right = 325;
	r5->bottom = 366;


	listSourceRectStand.push_back(r1);
	listSourceRectStand.push_back(r2);
	listSourceRectStand.push_back(r3);
	listSourceRectStand.push_back(r4);
	listSourceRectStand.push_back(r5);
	animation->ListSprite[Global::STAND] = new Sprite("megamansheet.png", listSourceRectStand, D3DCOLOR_XRGB(50, 96, 166));


	vector<RECT*> listSourceRectRun;
	RECT *r6 = new RECT;
	r6->top = 66;
	r6->left = 6;
	r6->right = 35;
	r6->bottom = 102;

	RECT *r7 = new RECT;
	r7->top = 66;
	r7->left = 48;
	r7->right = 72;
	r7->bottom = 102;

	RECT *r8 = new RECT;
	r8->top = 66;
	r8->left = 72;
	r8->right = 99;
	r8->bottom = 102;

	RECT *r9 = new RECT;
	r9->top = 66;
	r9->left = 103;
	r9->right = 138;
	r9->bottom = 102;

	RECT *r10 = new RECT;
	r10->top = 66;
	r10->left = 144;
	r10->right = 178;
	r10->bottom = 102;

	RECT *r11 = new RECT;
	r11->top = 66;
	r11->left = 189;
	r11->right = 216;
	r11->bottom = 102;

	RECT *r12 = new RECT;
	r12->top = 66;
	r12->left = 220;
	r12->right = 245;
	r12->bottom = 102;
	
	RECT *r13 = new RECT;
	r13->top = 66;
	r11->left = 247;
	r11->right = 273;
	r11->bottom = 102;

	RECT *r14 = new RECT;
	r14->top = 66;
	r14->left = 278;
	r14->right = 311;
	r14->bottom = 102;

	RECT *r15 = new RECT;
	r15->top = 66;
	r15->left = 318;
	r15->right = 352;
	r15->bottom = 102;

	RECT *r16 = new RECT;
	r16->top = 66;
	r16->left = 358;
	r16->right = 388;
	r16->bottom = 102;
	listSourceRectRun.push_back(r6);
	listSourceRectRun.push_back(r7);
	listSourceRectRun.push_back(r8);
	listSourceRectRun.push_back(r9);
	listSourceRectRun.push_back(r10);
	listSourceRectRun.push_back(r11);
	listSourceRectRun.push_back(r12);
	listSourceRectRun.push_back(r13);
	listSourceRectRun.push_back(r14);
	listSourceRectRun.push_back(r15);
	listSourceRectRun.push_back(r16);
	animation->ListSprite[Global::RUN] = new Sprite("megamansheet.png", listSourceRectRun, D3DCOLOR_XRGB(50, 96, 166));
	

	vector<RECT*> listSourceRectJump;
	RECT *r17 = new RECT;
	r17->top = 146;
	r17->left = 6;
	r17->right = 32;
	r17->bottom = 190;

	RECT *r18 = new RECT;
	r18->top = 146;
	r18->left = 35;
	r18->right = 54;
	r18->bottom = 190;

	RECT *r19 = new RECT;
	r19->top = 146;
	r19->left = 54;
	r19->right = 76;
	r19->bottom = 190;

	RECT *r20 = new RECT;
	r20->top = 146;
	r20->left = 105;
	r20->right = 136;
	r20->bottom = 190;

	RECT *r21 = new RECT;
	r21->top = 146;
	r21->left = 137;
	r21->right = 164;
	r21->bottom = 190;


	listSourceRectJump.push_back(r17);
	listSourceRectJump.push_back(r18);
	listSourceRectJump.push_back(r19);
	listSourceRectJump.push_back(r20);
	listSourceRectJump.push_back(r21);

	animation->ListSprite[Global::JUMP] = new Sprite("megamansheet.png", listSourceRectJump, D3DCOLOR_XRGB(50, 96, 166));
}

void MegaMan::Update(float deltaTime, vector<Object*> List_Object_Can_Collision)
{
	//update location
	Object::Update(deltaTime); 

	//gravity in worldport
	velocityY += -0.01*deltaTime;

	//update collision
	//get list collision

	vector<ResultColision> ListResultCo;
	for (int i = 0; i < List_Object_Can_Collision.size(); i++)
	{
		ResultColision r = this->ProcessCollision(List_Object_Can_Collision[i]);
		if (r.collision)
		{
			ListResultCo.push_back(r);
		}	
	}


	if (ListResultCo.size() == 0)
	{
		locationX += dx;
		locationY += dy;
	}
	else
	{
		Trace::Log("collision");
		//Global::Notify("collision", "notify");
		// block 

		//get tmin
		float min_tx = 1.0f, min_ty = 1.0f, nx = 0, ny = 0;
		for (int i = 0; i < ListResultCo.size(); i++) {
			if (ListResultCo[i].timeToColision < min_tx && ListResultCo[i].velocityX != 0) {
				min_tx = ListResultCo[i].timeToColision; nx = ListResultCo[i].velocityX;
			}

			if (ListResultCo[i].timeToColision < min_ty  && ListResultCo[i].velocityY != 0) {
				min_ty = ListResultCo[i].timeToColision; ny = ListResultCo[i].velocityY;
			}
		}
		//locationX += (r.timeToColision * dx + r.velocityX * 0.4f);		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//locationY += (r.timeToColision * dy + r.velocityY * 0.4f);

		locationX += (min_tx * dx + nx * 0.4f);		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		locationY += (min_ty * dy + ny * 0.4f);
	}
}

void MegaMan::Render()
{
	Camera *camera = Camera::Instance();
	D3DXVECTOR3 inPosition = camera->GetPositionInCamera(locationX,locationY);
	//Trace::Log("%f, %f", inPosition.x, inPosition.y);
	animation->Render(this->direction, this->status, D3DXVECTOR3(inPosition.x, inPosition.y, 0), D3DXVECTOR3(2, 2, 0));


	//if (tempAllowRender % 3 == 0)
	//{	
		animation->NextFrame(this->status);
	//}
	tempAllowRender++;
	//	RenderBoundingBox();
	}
void MegaMan::RenderBoundingBox()
{
	RECT r;
	r = Global::ConvertCollisionRectToRECT(GetBound());	
	Camera *camera = Camera::Instance();
	D3DXVECTOR3 inPosition = camera->GetPositionInCamera(locationX,locationY);
	r.left = inPosition.x;
	r.right = r.left + 70;
	r.top = inPosition.y;
	r.bottom = r.top + 120;
	Graphic::Instance()->DrawSurface(boundingbox, NULL, &r);
}
//
//ResultColision MegaMan::ProcessCollision()
//{
//	return ResultColision();
//}

MegaMan * MegaMan::Instance()
{
	if (!instance)
		instance = new MegaMan();
	return instance;
}

CollisionRect MegaMan::GetBound()
{
	//in world
	return CollisionRect(locationY-MEGAMAN_HEIGHT,locationX,MEGAMAN_WIDTH,MEGAMAN_HEIGHT,dx,dy);
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
	case Global::JUMP:
		//if (this->direction == Global::UP)
			velocityY = MEGAMAN_JUMP_SPEED;
		if (this->direction == Global::DOWN)
			velocityY = -MEGAMAN_JUMP_SPEED;
		break;
	}
}

void MegaMan::SetDirection(Global::Direction d)
{
	this->direction = d;
}
