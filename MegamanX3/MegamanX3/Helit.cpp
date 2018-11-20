#include"Helit.h"
Helit::Helit()
{
	x = 400;
	y = 7050 * G_Scale.y;

	center_region_x = x;
	LoadResource();
}

Helit::Helit(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	center_region_x = x;
	LoadResource();
}

Helit::~Helit()
{
}

void Helit::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt, List_object_can_col);
	x += dx;
	y += dy;

	if (direction == RIGHT && (x < center_region_x - 200))
		SetDirection(LEFT);

	if (direction == LEFT && (x > center_region_x + 200))
		SetDirection(RIGHT);
}

void Helit::Render()
{
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
	return BoundingBox();
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
		vx = HELIT_VX;
		break;
	case RIGHT:
		vx = -HELIT_VX;
		break;
	default:
		vx = 0;
		break;
	}
}
