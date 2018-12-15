#include"Genjibo.h"

Genjibo* Genjibo::instance;

Genjibo::Genjibo(int x, int y, int w, int h, Direction d)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->direction = d;

	this->actived = false;
	this->SetState(GODOWN);

	LoadResource();
}

Genjibo::~Genjibo()
{
}

Genjibo * Genjibo::Instance()
{
	if (!instance)
		instance = new Genjibo(2499 * G_Scale.x, (1000 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y, 0, 0, RIGHT);
	return instance;
}

void Genjibo::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (!this->actived)
		return;

	Object::Update(dt, List_object_can_col);

	switch (state)
	{
	case STAND:
		if (GetTickCount() - this->time_start_stand > 2000)
			this->SetState(CREATESHURIKEIN);
		break;

	case GODOWN:
		this->y += dy;
		if (this->y < (910 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.x)
			this->SetState(STAND);
		break;
	case CREATESHURIKEIN:
		Shurikein::Instance()->SetActived(true);
		if (GetTickCount() - this->time_start_create_shurikein > 3000)
		{
			this->SetState(GOUP);
		}
			
		break;

	case GOUP:
		this->y += dy;
		if (this->y > (1000 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y)
			this->actived = false;
		break;

	default:
		break;
	}
}

void Genjibo::Render()
{
	if (!this->actived)
		return;

	ActionObject::Render();
}

void Genjibo::LoadResource()
{

	MyTexture* texture = TXT::Instance()->GetTexture(TGENJIBO);

	vector<RECT*> list_source_rect_godown = TXT::Instance()->GetListSourceRect(SGENJIBOGODOWN);
	animation->listSprite[State::GODOWN] = new Sprite(texture, list_source_rect_godown, 2);

	vector<RECT*> list_source_rect_stand = TXT::Instance()->GetListSourceRect(SGENJIBOSTAND);
	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect_stand, 2);

	vector<RECT*> list_source_rect_create = TXT::Instance()->GetListSourceRect(SGENJIBOCREATESHURIKEIN);
	animation->listSprite[State::CREATESHURIKEIN] = new Sprite(texture, list_source_rect_create, 2);

	vector<RECT*> list_source_rect_goup = TXT::Instance()->GetListSourceRect(SGENJIBOGOUP);
	animation->listSprite[State::GOUP] = new Sprite(texture, list_source_rect_goup, 2);
}

void Genjibo::SetState(State s)
{
	this->state = s;

	switch (state)
	{
	case STAND:
		this->time_start_stand = GetTickCount();
		this->vy = 0;
		break;

	case GODOWN:
		this->vy = -GENJIBO_VY;
		break;

	case CREATESHURIKEIN:
		this->time_start_create_shurikein = GetTickCount();
		this->vy = 0;
		break;

	case GOUP:
		this->vy = GENJIBO_VY;
		break;

	default:
		this->vy = 0;
		this->vx = 0;
		break;
	}
}

void Genjibo::SetDirection(Direction d)
{
	this->direction = d;
}
