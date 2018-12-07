#include"DashSpark.h"

DashSpark::DashSpark(float x, float y, Direction d)
{
	this->x = x;
	this->y = y;
	this->direction = d;

	MyTexture *texture = TXT::Instance()->GetTexture(TEFFECT);
	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SDASHSPARK);
	this->animation->listSprite[RUN] = new Sprite(texture, list_source_rect, 1);
	this->state = RUN;
}

DashSpark::~DashSpark()
{
}

void DashSpark::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->animation->listSprite[state]->IsFinalFrame())
		this->destroyed = true;
}

void DashSpark::Render()
{
	Bullet::Render();
}

void DashSpark::SetState(State s)
{
	this->state = s;
}

void DashSpark::SetDirection(Direction d)
{
	this->direction = d;
}

bool DashSpark::IsDestroyed()
{
	return destroyed;
}
