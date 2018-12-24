#include"Bee.h"

Bee::Bee()
{
	x = 2420;
	y = (1481+G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	center_region_y = y;
	vy = BEE_VY;
	this->hitpoints = BEE_MAX_HP;

	this->destroyed = true;
	this->folowBlasthornet = false;
	this->folowMegaman = false;

	this->nameObject = BEE;
	this->SetState(FLAPPINGANDFLYING);
	LoadResource();
}

Bee::Bee(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	center_region_y = y;
	vy = BEE_VY;

	this->nameObject = BEE;
	LoadResource();
}

Bee::~Bee()
{
}

void Bee::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->destroyed)
		return;

	if (this->hitpoints <= 0)
	{
		this->destroyed = true;
		Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
		tempBullet->SetState(DESTROYBULLET);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
	}

	if (this->state == DESTROY)
	{
		if (this->animation->listSprite[this->state]->IsFinalFrame())
		{
			this->destroyed = true;
			this->animation->Refresh(DESTROY);
		}
			
	}
	else
	if (GetTickCount() - this->time_start_active > BEE_TIME_DESTROY)
		this->state = DESTROY;



	if (this->folowMegaman)
	{
		float megaman_x, megaman_y;
		Megaman::Instance()->GetPosition(megaman_x, megaman_y);

		float a = (this->y - megaman_y) / (this->x - megaman_x);
		float b = megaman_y - a * megaman_x;

		this->y += (this->y < megaman_y) ? 1 : -1;
		this->x = (this->y - b) / a;
	}
	else
	{
		//=====================follow blast horner============
		if (this->folowBlasthornet)
		{
			dx = (rand() % 5)*(rand() % 2 == 0 ? 1 : -1);
			dy = (rand() % 5)*(rand() % 2 == 0 ? 1 : -1);
			x += dx;
			y += dy;
		}
		else

		{
			Object::Update(dt, List_object_can_col);
			x += dx;
			y += dy;
		}
	}
	
	

	if(this->state!=FLAPPING
		&&this->state != DESTROY
		&& (this->y > BLASTHORNET_TOP || this->y < GROUND-20 || this->x<BLASTHORNET_LEFT || this->x>BLASTHORNET_RIGHT))
	{
		this->vx = this->vy = 0;
		this->state = FLAPPING;
	}
}

void Bee::Render()
{
	if (this->destroyed)
		return;

	ActionObject::Render();
}

void Bee::LoadResource()
{
	//MyTexture* texture = new MyTexture((char*)"SourceImage\\bee.png", D3DCOLOR_XRGB(255, 255, 255));

	MyTexture* texture = TXT::Instance()->GetTexture(TBEE);
	//vector<RECT*> list_source_rect_flapping = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\beeflaping.txt");

	vector<RECT*> list_source_rect_flapping = TXT::Instance()->GetListSourceRect(SBEEFLAPING);
	animation->listSprite[State::FLAPPING] = new Sprite(texture, list_source_rect_flapping, 2);

	//vector<RECT*> list_source_rect_flapping_and_flying = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\beeflapingandflying.txt");

	vector<RECT*> list_source_rect_flapping_and_flying = TXT::Instance()->GetListSourceRect(SBEEFLAPINGANDFLYING);
	animation->listSprite[State::FLAPPINGANDFLYING] = new Sprite(texture, list_source_rect_flapping_and_flying, 1);

	//vector<RECT*> list_source_rect_stand = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\beestand.txt");

	vector<RECT*> list_source_rect_stand = TXT::Instance()->GetListSourceRect(SBEESTAND);
	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect_stand, 10);

	MyTexture* texture2 = TXT::Instance()->GetTexture(TBLASHORNETHONEY);
	vector<RECT*> list_source_rect_autodestroy = TXT::Instance()->GetListSourceRect(SBEEAUTODESTROY);
	animation->listSprite[State::DESTROY] = new Sprite(texture2, list_source_rect_autodestroy, 2);
}

BoundingBox Bee::GetBoundingBox()
{
	if (this->destroyed)
		return BoundingBox();

	BoundingBox bound;
	bound.x = x - BEE_WIDTH / 2;
	bound.y = y - BEE_HEIGHT / 2;
	bound.w = BEE_WIDTH;
	bound.h = BEE_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Bee::SetState(State s)
{
	this->state = s;
}

void Bee::SetDirection(Direction d)
{
	this->direction = d;
}

void Bee::ResetBee(int x, int y, Direction d, float vx, float vy)
{
	this->vx = (d == LEFT) ? -vx : vx;
	this->vy =-vy;
	this->direction = d;
	this->destroyed = false;
	this->SetState(FLAPPINGANDFLYING);
	this->x = x;
	this->y = y;

	this->folowMegaman = false;

	this->time_start_active = GetTickCount();
	this->hitpoints = BEE_MAX_HP;
	//MyDebugOUT("reset time create bee\n");
}
