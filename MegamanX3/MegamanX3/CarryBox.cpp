#include"CarryBox.h"

CarryBox::CarryBox()
{
	x = 4900 * G_Scale.x;
	y = (932 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	this->start_location_y = y;
	this->start_location_x = x;
	this->hitpoints = CARRYBOX_MAX_HP;
	this->nameObject = CARRYBOX;

	this->vx = CARRYBOX_VX;
	this->vy = CARRYBOX_VY;
	this->destroyed = true;
	this->actived = false;
	this->arrived = false;

	this->direction = RIGHT;

	LoadResource();
}

CarryBox::CarryBox(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	this->x = x;
	this->y = y;
	this->start_location_y = y;
	this->start_location_x = x;
	this->hitpoints = CARRYBOX_MAX_HP;
	this->nameObject = CARRYBOX;

	this->vx = CARRYBOX_VX;
	this->vy = CARRYBOX_VY;
	this->destroyed = true;
	this->actived = false;
	this->arrived = false;

	this->direction = RIGHT;

	LoadResource();
}

CarryBox::~CarryBox()
{
}


void CarryBox::Update(DWORD dt, vector<Object*>* List_object_can_col)
{

	if (destroyed || !this->actived)
		return;

	if (this->hitpoints <= 0)
	{
		this->destroyed = true;
		this->actived = false;
		
		Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
		tempBullet->SetState(DESTROYBULLET);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
		return;
	}

	//========moving cheo'====================
	if (this->y < this->start_location_y - 500)
		this->vx = 0;

	//===================alive===================================
	Object::Update(dt, List_object_can_col);
	x += dx;
	y += dy;

	if (this->y < this->start_location_y - 618)
	{
		this->arrived = true;
		this->vy = 0;
	}

}

void CarryBox::Render()
{
	if (destroyed)
		return;

	ActionObject::Render();
}

void CarryBox::LoadResource()
{
	MyTexture* texture = TXT::Instance()->GetTexture(TCARRYARM);

	vector<RECT*> list_source_rect_body = TXT::Instance()->GetListSourceRect(SCARRYBOX);

	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_body, 1);
}

BoundingBox CarryBox::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - CARRYBOX_WIDTH / 2;
	bound.y = y - CARRYBOX_HEIGHT / 2;
	bound.w = CARRYBOX_WIDTH;
	bound.h = CARRYBOX_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void CarryBox::SetState(State s)
{
	this->state = s;
}

void CarryBox::SetDirection(Direction d)
{
	this->direction = d;
}

void CarryBox::Reset()
{
	this->x = this->start_location_x;
	this->y = this->start_location_y;

	this->hitpoints = CARRYBOX_MAX_HP;

	this->vx = CARRYBOX_VX;
	this->vy = CARRYBOX_VY;

	this->destroyed = false;
	this->actived = false;
}
