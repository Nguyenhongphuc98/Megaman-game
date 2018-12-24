#include"ItemBlood.h"


ItemBlood::ItemBlood(float x, float y)
{
	this->destroyed = false;

	this->x = x;
	this->y = y;
	this->damage = ITEMBLOOD_BLOOD;
	this->SetState(STAND);

	this->nameObject = ITEMBLOOD;

	MyTexture *texture = TXT::Instance()->GetTexture(TMEGAMANSTAGE);
	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SITEMBLOOD);
	animation->listSprite[STAND] = new Sprite(texture, list_source_rect, 1);

}

ItemBlood::~ItemBlood()
{
}



void ItemBlood::Update(DWORD dt, vector<Object*>* List_enemy_objects)
{
}

void ItemBlood::Render()
{
	
	if (this->destroyed)
		return;

	Bullet::Render();

}

BoundingBox ItemBlood::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - ITEMBLOOD_WIDTH / 2;
	bound.y = y - ITEMBLOOD_HEIGHT / 2;
	bound.w = ITEMBLOOD_WIDTH;
	bound.h = ITEMBLOOD_HEIGHT;
	bound.vx = 0;
	bound.vy = 0;
	return bound;
}

void ItemBlood::SetState(State s)
{
	this->state = STAND;
}

void ItemBlood::SetDirection(Direction d)
{
	this->direction = d;
}

bool ItemBlood::IsDestroyed()
{
	return this->destroyed;
}
