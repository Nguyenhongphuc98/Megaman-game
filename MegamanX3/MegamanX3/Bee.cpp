#include"Bee.h"

Bee::Bee()
{
	x = 850;
	y = 7060 * G_Scale.y;

	center_region_y = y;
	vy = BEE_VY;
	LoadResource();
}

Bee::~Bee()
{
}

void Bee::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt,List_object_can_col);
	x += dx;
	y += dy;

	if (vy > 0 && y > center_region_y + 100)
		vy = -BEE_VY;
	if (vy <0 && y < center_region_y - 100)
		vy = BEE_VY;
}

void Bee::Render()
{
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
}

BoundingBox Bee::GetBoundingBox()
{
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
