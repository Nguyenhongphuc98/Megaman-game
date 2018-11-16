#include"Megaman.h"

Megaman::Megaman()
{
	x = 100;
	y = 1143*G_Scale.y;
	LoadResource();
}

Megaman::~Megaman()
{
}

void Megaman::Update(DWORD dt, vector<Object*> *List_object_can_col)
{
	vy += MEGAMAN_GRAVITY*dt;
	Object::Update(dt, List_object_can_col);
	//x += dx;
	//y += dy;

	//if (y > 410)
	//	y = 410;

	vector<ResultCollision> List_result_col;
	List_result_col.clear();

	for (int i=0; i < List_object_can_col->size(); i++) {
		ResultCollision r ;
		r=Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), List_object_can_col->at(i)->GetBoundingBox());
		if (r.isCollision)
			List_result_col.push_back(r);
	}

	if (List_result_col.size() == 0) {
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx = 1.0f, min_ty = 1.0f;
		int nx = 0, ny = 0;

		for (int i = 0; i <List_result_col.size(); i++) {
			if (List_result_col[i].t < min_tx && List_result_col[i].nx != 0) {
				min_tx = List_result_col[i].t; nx = List_result_col[i].nx;
			}

			if (List_result_col[i].t < min_ty  && List_result_col[i].ny != 0) {
				min_ty = List_result_col[i].t; ny = List_result_col[i].ny;
			}
		}

		x += (min_tx * dx + nx * 0.4f);		
		y += (min_ty * dy + ny * 0.4f);
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

}

void Megaman::Render()
{
	D3DXVECTOR2 position=Camera::Instance()->GetPositionInViewPort(x,y);
	animation->Render(state, direction, position);
	animation->Next(state);
}

void Megaman::LoadResource()
{
	//=====================Load Status Stand=============================
	/*RECT* r1 = new RECT();
	r1->top = 3;
	r1->bottom = 40;
	r1->left = 3;
	r1->right = 34;

	RECT* r2 = new RECT();
	r2->top = 3;
	r2->bottom = 40;
	r2->left = 34;
	r2->right = 66;

	RECT* r3 = new RECT();
	r3->top = 3;
	r3->bottom = 40;
	r3->left = 67;
	r3->right = 99;

	RECT* r4 = new RECT();
	r4->top = 3;
	r4->bottom = 40;
	r4->left = 99;
	r4->right = 131;

	RECT* r5 = new RECT();
	r5->top = 3;
	r5->bottom = 40;
	r5->left = 131;
	r5->right = 163;

	vector<RECT*> list_source_rect;
	list_source_rect.push_back(r1);
	list_source_rect.push_back(r2);
	list_source_rect.push_back(r3);
	list_source_rect.push_back(r4);
	list_source_rect.push_back(r5);*/

	vector<RECT*> list_source_rect = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanstand.txt");
	MyTexture* texture_stand = new MyTexture((char*)"SourceImage\\megamanstand.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::STAND] = new Sprite(texture_stand, list_source_rect, 1);

	//=====================Load Status Run=============================

	/*RECT* r11 = new RECT();
	r11->top = 0;
	r11->bottom = 35;
	r11->left = 3;
	r11->right = 32;

	RECT* r12 = new RECT();
	r12->top = 0;
	r12->bottom = 35;
	r12->left = 35;
	r12->right = 58;

	RECT* r13 = new RECT();
	r13->top = 0;
	r13->bottom = 35;
	r13->left = 61;
	r13->right = 87;

	RECT* r14 = new RECT();
	r14->top = 0;
	r14->bottom = 35;
	r14->left = 93;
	r14->right = 124;

	RECT* r15 = new RECT();
	r15->top = 0;
	r15->bottom = 35;
	r15->left = 131;
	r15->right = 166;

	RECT* r16 = new RECT();
	r16->top = 0;
	r16->bottom = 35;
	r16->left = 172;
	r16->right = 202;

	vector<RECT*> list_source_rect_run;
	list_source_rect_run.push_back(r11);
	list_source_rect_run.push_back(r12);
	list_source_rect_run.push_back(r13);
	list_source_rect_run.push_back(r14);
	list_source_rect_run.push_back(r15);
	list_source_rect_run.push_back(r16);*/

	vector<RECT*> list_source_rect_run = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanrun.txt");
	MyTexture* texture_run = new MyTexture((char*)"SourceImage\\megamanrun.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::RUN] = new Sprite(texture_run, list_source_rect_run, 1);

	//=====================Load Status Jump=============================
	/*RECT* r17 = new RECT();
	r17->top = 3;
	r17->bottom = 48;
	r17->left = 3;
	r17->right = 28;

	RECT* r18 = new RECT();
	r18->top = 3;
	r18->bottom = 48;
	r18->left = 34;
	r18->right = 50;

	RECT* r19 = new RECT();
	r19->top = 3;
	r19->bottom = 48;
	r19->left = 53;
	r19->right = 73;

	RECT* r20 = new RECT();
	r20->top = 3;
	r20->bottom = 48;
	r20->left = 77;
	r20->right = 101;


	RECT* r21 = new RECT();
	r21->top = 3;
	r21->bottom = 48;
	r21->left = 105;
	r21->right = 133;


	RECT* r22 = new RECT();
	r22->top = 3;
	r22->bottom = 48;
	r22->left = 136;
	r22->right = 161;


	RECT* r23 = new RECT();
	r23->top = 3;
	r23->bottom = 48;
	r23->left = 163;
	r23->right = 194;
	vector<RECT*> list_source_rect_jump;
	list_source_rect_jump.push_back(r17);
	list_source_rect_jump.push_back(r18);
	list_source_rect_jump.push_back(r19);
	list_source_rect_jump.push_back(r20);
	list_source_rect_jump.push_back(r21);
	list_source_rect_jump.push_back(r22);
	list_source_rect_jump.push_back(r23);*/

	vector<RECT*> list_source_rect_jump = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanjump.txt");
	MyTexture* texture_jump = new MyTexture((char*)"SourceImage\\megamanjump.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::JUMP] = new Sprite(texture_jump, list_source_rect_jump, 1);

	//=====================Load Status Shoot=============================
	/*RECT* r31 = new RECT();
	r31->top = 0;
	r31->bottom = 35;
	r31->left = 9;
	r31->right = 39;

	RECT* r41 = new RECT();
	r41->top = 0;
	r41->bottom = 35;
	r41->left = 44;
	r41->right = 77;

	RECT* r51 = new RECT();
	r51->top = 0;
	r51->bottom = 35;
	r51->left = 83;
	r51->right = 119;

	RECT* r61 = new RECT();
	r61->top = 0;
	r61->bottom = 35;
	r61->left = 127;
	r61->right = 166;

	RECT* r71 = new RECT();
	r71->top = 0;
	r71->bottom = 35;
	r71->left = 173;
	r71->right = 206;

	vector<RECT*> list_source_rect_runshoot;
	list_source_rect_runshoot.push_back(r31);
	list_source_rect_runshoot.push_back(r41);
	list_source_rect_runshoot.push_back(r51);
	list_source_rect_runshoot.push_back(r61);
	list_source_rect_runshoot.push_back(r71);*/

	vector<RECT*> list_source_rect_runshoot = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanrunshoot.txt");
	MyTexture* texture_runshoot = new MyTexture((char*)"SourceImage\\megamanrunshoot.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::SHOOT] = new Sprite(texture_runshoot, list_source_rect_runshoot, 1);

	//=====================Load Status Climb=============================
	vector<RECT*> list_source_rect_climb = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanClimb.txt");
	MyTexture* texture_climb = new MyTexture((char*)"SourceImage\\megamanClimb.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::CLIMB] = new Sprite(texture_climb, list_source_rect_climb, 1);
}

BoundingBox Megaman::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x- MEGAMAN_WIDTH/2;
	bound.y = y- MEGAMAN_HEIGHT/2;
	bound.w = MEGAMAN_WIDTH;
	bound.h = MEGAMAN_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Megaman::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case RUN:
		if(direction==RIGHT)
		vx = MEGAMAN_WALK_SPEED;
		else
		{
			vx = -MEGAMAN_WALK_SPEED;
		}
		break;

	case JUMP:
		vy = MEGAMAN_JUMP_SPEED;
		break;
	case STAND:
		vx = 0;
		vy = 0;
		break;
	case SHOOT:
		vx = 0;
		vy = 0;
		break;
	default:
		vx = 0;
		vy = 0;
		break;
	}
}

void Megaman::SetDirection(Direction d)
{
	this->direction = d;
}

State Megaman::GetState()
{
	return state;
}

Direction Megaman::GetDirection()
{
	return direction;
}
