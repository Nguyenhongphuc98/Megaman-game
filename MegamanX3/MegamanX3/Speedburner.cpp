#include"Speedburner.h"


Speedburner::Speedburner(float x, float y, Direction d, State s)
{
	this->x = x;
	this->y = y;
	this->vx = SPEEDBURNER_VX;
	this->vy = SPEEDBURNER_VY;
	SetDirection(d);
	SetState(s);

	//====================Load source======================
	//=====================Load Status normal==============
	RECT* r1 = new RECT();
	r1->top = 7;
	r1->bottom = 48;
	r1->left = 64;
	r1->right = 73;

	RECT* r2 = new RECT();
	r2->top = 7;
	r2->bottom = 48;
	r2->left = 74;
	r2->right = 91;

	RECT* r3 = new RECT();
	r3->top = 7;
	r3->bottom = 48;
	r3->left = 92;
	r3->right = 116;

	RECT* r4 = new RECT();
	r4->top = 7;
	r4->bottom = 48;
	r4->left = 118;
	r4->right = 149;

	RECT* r5 = new RECT();
	r5->top = 7;
	r5->bottom = 48;
	r5->left = 153;
	r5->right = 185;

	RECT* r6 = new RECT();
	r6->top = 7;
	r6->bottom = 48;
	r6->left = 187;
	r6->right = 218;

	RECT* r7 = new RECT();
	r7->top = 7;
	r7->bottom = 48;
	r7->left = 220;
	r7->right = 245;

	vector<RECT*> list_source_rect;
	list_source_rect.push_back(r1);
	list_source_rect.push_back(r2);
	list_source_rect.push_back(r3);
	list_source_rect.push_back(r4);
	list_source_rect.push_back(r5);
	list_source_rect.push_back(r6);
	list_source_rect.push_back(r7);
	MyTexture* texture_normal = new MyTexture((char*)"SourceImage\\speedburner.png", D3DCOLOR_XRGB(50, 96, 166));
	animation->listSprite[State::NORMALBULLET] = new Sprite(texture_normal, list_source_rect, 1);
}

Speedburner::~Speedburner()
{
}

void Speedburner::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt,List_object_can_col);
	x += dx;
	y += dy;
}

void Speedburner::Render()
{
	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(this->x, this->y);
	this->animation->Render(this->state, this->direction, position);
	this->animation->Next(this->state);
}

BoundingBox Speedburner::GetBoundingBox()
{
	BoundingBox bound;
	
	switch (state)
	{
	case NORMALBULLET:
		bound.x = this->x - SPEEDBURNER_WIDTH_NORMAL / 2;
		bound.y = this->y - SPEEDBURNER_HEIGHT_NORMAL / 2;
		bound.w = SPEEDBURNER_WIDTH_NORMAL;
		bound.h = SPEEDBURNER_HEIGHT_NORMAL;
		break;

	case SUPERBULLET:
		break;
	case DESTROYBULLET:
		break;
	default:
		bound.x = this->x - SPEEDBURNER_WIDTH_NORMAL / 2;
		bound.y = this->y - SPEEDBURNER_HEIGHT_NORMAL / 2;
		bound.w = SPEEDBURNER_WIDTH_NORMAL;
		bound.h = SPEEDBURNER_HEIGHT_NORMAL;
		break;
	}
	return bound;
}

void Speedburner::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case NORMALBULLET:
		this->damage = SPEEDBURNER_DAMAGE;
		break;
	case SUPERBULLET:
		break;
	case DESTROYBULLET:
		break;
	default:
		break;
	}
}

void Speedburner::SetDirection(Direction d)
{
	this->direction = d;
	switch (d)
	{
	case LEFT:
		vx = -SPEEDBURNER_VX;
		break;
	case RIGHT:
		vx = SPEEDBURNER_VX;
		break;
	default:
		break;
	}
}
