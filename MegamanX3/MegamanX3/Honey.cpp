#include"Honey.h"

Honey::Honey()
{
	x = 2420;
	y = (1481 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	center_region_y = y;
	vy = HONEY_VY;

	this->destroyed = true;
	this->touchedMegaman = false;


	this->nameObject = HONEY;
	this->SetState(STAND);
	LoadResource();
}

Honey::Honey(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	center_region_y = y;
	vy = HONEY_VY;
	this->destroyed = true;
	this->nameObject = HONEY;
	this->SetState(STAND);
	LoadResource();
}

Honey::~Honey()
{
}

void Honey::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->destroyed)
		return;

	float megaman_x, megaman_y;
	Megaman::Instance()->GetPosition(megaman_x, megaman_y);

	if (this->touchedMegaman)
	{
		this->x = megaman_x;
		this->y = megaman_y;
		return;
	}

	if (abs(megaman_x - this->x) < 30 && abs(megaman_y - this->y) < 30)
		this->touchedMegaman = true;

	float a = (this->y - megaman_y) / (this->x - megaman_x);
	float b = megaman_y - a * megaman_x;

	this->y += (this->y < megaman_y) ? 1 : -1;
	this->x = (this->y - b) / a;

}

void Honey::Render()
{
	if (this->destroyed)
		return;

	ActionObject::Render();
}

void Honey::LoadResource()
{
	MyTexture* texture2 = TXT::Instance()->GetTexture(TBLASHORNETHONEY);
	vector<RECT*> list_source_rect_stand = TXT::Instance()->GetListSourceRect(BLASTHORNETHONEY);
	animation->listSprite[State::STAND] = new Sprite(texture2, list_source_rect_stand, 2);
}

BoundingBox Honey::GetBoundingBox()
{
	if (this->destroyed)
		return BoundingBox();

	BoundingBox bound;
	bound.x = x - HONEY_WIDTH / 2;
	bound.y = y - HONEY_HEIGHT / 2;
	bound.w = HONEY_WIDTH;
	bound.h = HONEY_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Honey::SetState(State s)
{
	this->state = s;
}

void Honey::SetDirection(Direction d)
{
	this->direction = d;
}

void Honey::ResetHoney(int x, int y)
{
	this->destroyed = false;
	this->touchedMegaman = false;
	this->x = x;
	this->y = y;	
}

