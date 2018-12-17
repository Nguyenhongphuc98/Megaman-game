#include"MetaCapsule.h"

MetaCapsule::MetaCapsule()
{
	x = 4900 * G_Scale.x;
	y = (932 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	this->start_location_y = y;
	this->start_location_x = x;
	this->nameObject = METACAPSULE;

	this->vx = 0;
	this->vy = 0;
	this->destroyed = false;
	this->actived = false;
	this->can_shoot = false;

	this->time_start_shoot = GetTickCount();
	this->direction = RIGHT;
	this->state = RUN;

	LoadResource();
}

MetaCapsule::MetaCapsule(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	this->x = x;
	this->y = y;

	this->start_location_y = y;
	this->start_location_x = x;
	this->nameObject = METACAPSULE;

	this->vx = 0;
	this->vy = 0;
	this->destroyed = false;
	this->actived = false;
	this->can_shoot = false;

	this->time_start_shoot = GetTickCount();
	this->direction = RIGHT;
	this->state = RUN;

	LoadResource();
}

MetaCapsule::~MetaCapsule()
{
}


void MetaCapsule::Update(DWORD dt, vector<Object*>* List_object_can_col)
{

	if (destroyed || !this->actived)
		return;

	if (GetTickCount() - this->time_start_shoot > 3000&&this->can_shoot)
	{
		this->time_start_shoot = GetTickCount();
		//create bullet to shoot
		Bullet* tempBullet = new MetaCapsuleBullet(this->x, this->y, RIGHT);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
		return;
	}

}

void MetaCapsule::Render()
{
	if (destroyed||!this->actived)
		return;

	ActionObject::Render();

	if (this->can_shoot)
	{
		this->animation->listSprite[RUN]->Set_current_frame(18);
		return;
	}

	if (this->animation->listSprite[RUN]->IsFinalFrame())
	{
		this->animation->listSprite[RUN]->Set_current_frame(18);
		this->can_shoot = true;
	}
		
}

void MetaCapsule::LoadResource()
{
	MyTexture* texture = TXT::Instance()->GetTexture(TCARRYARM);

	vector<RECT*> list_source_rect_body = TXT::Instance()->GetListSourceRect(SMETACAPSULE);

	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_body, 5);
}

BoundingBox MetaCapsule::GetBoundingBox()
{
	return BoundingBox();
}

void MetaCapsule::SetState(State s)
{
	this->state = s;
}

void MetaCapsule::SetDirection(Direction d)
{
	this->direction = d;
}

