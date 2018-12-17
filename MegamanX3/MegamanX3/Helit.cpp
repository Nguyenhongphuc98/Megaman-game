#include"Helit.h"
Helit::Helit()
{
	x = 400;
	y = 7050 * G_Scale.y;

	center_region_y = x;
	this->nameObject = HELIT;

	this->vx = 0;
	this->vy = HELIT_VY;
	this->hitpoints = HELIT_MAX_HP;
	this->destroyed = false;
	this->nameObject = HELIT;
	this->time_last_bulet = GetTickCount();
	LoadResource();
}

Helit::Helit(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	center_region_y = y;
	this->nameObject = HELIT;

	this->vx = 0;
	this->vy = HELIT_VY;
	this->hitpoints = HELIT_MAX_HP;
	this->destroyed = false;
	this->nameObject = HELIT;
	this->time_last_bulet = GetTickCount();
	LoadResource();
}

Helit::~Helit()
{
}

void Helit::Update(DWORD dt, vector<Object*>* List_object_can_col)
{

	float megaman_x, megaman_y;
	Megaman::Instance()->GetPosition(megaman_x, megaman_y);


	//==========reset if distance so far=================

	if (abs(this->x - megaman_x) > 300 && this->destroyed)
	{
		this->destroyed = false;
		this->hitpoints = HELIT_MAX_HP;
		this->SetState(RUN);
		return;
	}

	if (destroyed)
		return;
	//=============CHECK LIFE===============================
	if (this->hitpoints <= 0)
	{
		this->destroyed = true;
		Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
		tempBullet->SetState(DESTROYBULLET);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
		return;
	}

	//===================alive===================================
	Object::Update(dt, List_object_can_col);
	x += dx;
	y += dy;

	if (this->y < center_region_y - 100)
		SetDirection(RIGHT); //UP

	if (this->y > center_region_y + 100)
		SetDirection(LEFT); //DOWN


	//======================shooting==============================
	if (GetTickCount() - this->time_last_bulet > 1000)
	{
		this->time_last_bulet = GetTickCount();
		Bullet* bullet = new HelitBulet(this->x, this->y-15,this->direction /*(this->direction==LEFT)?RIGHT:LEFT*/);
		WeaponSystem::Instance()->AddBulletEnemy(bullet);
	}
}

void Helit::Render()
{
	if (destroyed)
		return;
	ActionObject::Render();
}

void Helit::LoadResource()
{
	//vector<RECT*> list_source_rect_helit = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\helit.txt");
	//MyTexture* texture_helit = new MyTexture((char*)"SourceImage\\helit.png", D3DCOLOR_XRGB(255, 255, 255));

	vector<RECT*> list_source_rect_helit = TXT::Instance()->GetListSourceRect(SHELITSTAND);
	MyTexture* texture_helit = TXT::Instance()->GetTexture(THELIT);
	animation->listSprite[State::RUN] = new Sprite(texture_helit, list_source_rect_helit, 1);
}

BoundingBox Helit::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - HELIT_WIDTH / 2;
	bound.y = y - HELIT_HEIGHT / 2;
	bound.w = HELIT_WIDTH;
	bound.h = HELIT_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Helit::SetState(State s)
{
	this->state = s;
}

void Helit::SetDirection(Direction d)
{
	this->direction = d;
	switch (d)
	{
	case LEFT:
		vy = -HELIT_VY;
		break;
	case RIGHT:
		vy = HELIT_VY;
		break;
	default:
		vx = 0;
		break;
	}
}
