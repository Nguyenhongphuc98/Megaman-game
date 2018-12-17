#include"DashSmoke.h"

DashSmoke::DashSmoke(float x, float y, Direction d)
{
	this->x = x;
	this->y = y;
	this->direction = d;

	MyTexture *texture = TXT::Instance()->GetTexture(TEFFECT);
	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SDASHSSMOKE);
	this->animation->listSprite[RUN] = new Sprite(texture, list_source_rect, 1);
	this->state = RUN;
}

DashSmoke::~DashSmoke()
{
}

void DashSmoke::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->animation->listSprite[state]->IsFinalFrame())
		this->destroyed = true;
}

void DashSmoke::Render()
{
	Bullet::Render();
}

void DashSmoke::SetState(State s)
{

}

void DashSmoke::SetDirection(Direction d)
{
	this->direction = d;
}

bool DashSmoke::IsDestroyed()
{
	return destroyed;
}