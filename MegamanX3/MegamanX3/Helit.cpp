#include"Helit.h"
Helit::Helit()
{
	x = 400;
	y = 1153 * G_Scale.y;
	LoadResource();
}

Helit::~Helit()
{
}

void Helit::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
}

void Helit::Render()
{
	ActionObject::Render();
}

void Helit::LoadResource()
{
	vector<RECT*> list_source_rect_helit = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\helit.txt");
	MyTexture* texture_helit = new MyTexture((char*)"SourceImage\\helit.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->listSprite[State::RUN] = new Sprite(texture_helit, list_source_rect_helit, 1);
}

BoundingBox Helit::GetBoundingBox()
{
	return BoundingBox();
}

void Helit::SetState(State s)
{
	this->state = s;
}

void Helit::SetDirection(Direction d)
{
	this->direction = d;
}
