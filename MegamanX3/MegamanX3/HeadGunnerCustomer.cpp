#include"HeadGunnerCustomer.h"

HeadGunnerCustomer::HeadGunnerCustomer()
{
	x = 1400;
	y = 7108 * G_Scale.y;

	this->count_animation = 0;
	this->count_bulet_tube = 0;
	this->nameObject = HEADGUNNERCUSTOMER;
	LoadResource();
}

HeadGunnerCustomer::HeadGunnerCustomer(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	this->count_animation = 0;
	this->count_bulet_tube = 0;
	this->nameObject = HEADGUNNERCUSTOMER;
	LoadResource();
}

HeadGunnerCustomer::~HeadGunnerCustomer()
{
}

void HeadGunnerCustomer::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	count_animation++;
	if (count_animation % 100 == 0)
		SetState(STAND);
	if (count_animation % 200 == 0)
		SetState(SHOOTABOVE);
	if (count_animation % 300 == 0)
		SetState(SHOOTBELOW);

	if (this->state != SHOOTABOVE)
		count_bulet_tube = 0;

	if(this->state== SHOOTABOVE&&this->animation->listSprite[state]->IsFinalFrame())
	{
		if (count_bulet_tube < 3)
		{
			Bullet* bullet = new HeadGunnerCustomerBulletTube(this->x, this->y, (this->direction == RIGHT) ? LEFT : RIGHT);
			WeaponSystem::Instance()->AddBulletEnemy(bullet);
			count_bulet_tube++;
		}
	}
}

void HeadGunnerCustomer::Render()
{
	ActionObject::Render();
}

void HeadGunnerCustomer::LoadResource()
{
	RECT* r11 = new RECT();
	r11->top = 1;
	r11->bottom = 46;
	r11->left = 82;
	r11->right = 120;
	vector<RECT*> list_source_rect_stand;
	list_source_rect_stand.push_back(r11);

	//MyTexture* texture = new MyTexture((char*)"SourceImage\\HeadGunnerCustomer.png", D3DCOLOR_XRGB(255, 255, 255));

	MyTexture* texture = TXT::Instance()->GetTexture(THEADGUNNERCUSTOMER);

	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect_stand, 1);

	//vector<RECT*> list_source_rect_shoot_above = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\HeadGunnerCustomerShootAbove.txt");

	vector<RECT*> list_source_rect_shoot_above = TXT::Instance()->GetListSourceRect(SHEADGUNNERCUSTOMERSHOOTABOVE);
	animation->listSprite[State::SHOOTABOVE] = new Sprite(texture, list_source_rect_shoot_above, 1);

	//vector<RECT*> list_source_rect_shoot_below = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\HeadGunnerCustomerShootBelow.txt");

	vector<RECT*> list_source_rect_shoot_below = TXT::Instance()->GetListSourceRect(SHEADGUNNERCUSTOMERSHOOTBELOW);
	animation->listSprite[State::SHOOTBELOW] = new Sprite(texture, list_source_rect_shoot_below, 1);
}

BoundingBox HeadGunnerCustomer::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - HEADGUNNERCUSTOMER_WIDTH/ 2;
	bound.y = y - HEADGUNNERCUSTOMER_HEIGHT / 2;
	bound.w = HEADGUNNERCUSTOMER_WIDTH;
	bound.h = HEADGUNNERCUSTOMER_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void HeadGunnerCustomer::SetState(State s)
{
	this->state = s;
}

void HeadGunnerCustomer::SetDirection(Direction d)
{
	this->direction = d;
}
