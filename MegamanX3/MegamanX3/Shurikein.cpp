#include"Shurikein.h"

Shurikein::Shurikein()
{
	x = 100;
	y = 1153 * G_Scale.y;
	LoadResource();
}

Shurikein::~Shurikein()
{
}

void Shurikein::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
}

void Shurikein::Render()
{
	/*if (animation->listSprite[APPEAR]->GetCurrentFrame() == 51)
		SetState(ROTATELEFT);

	if (animation->listSprite[ROTATELEFT]->GetCurrentFrame() == 10)*/
	{
		SetState(ROTATERIGHT);
	}
		
	ActionObject::Render();
}

void Shurikein::LoadResource()
{
	MyTexture* texture_appear = new MyTexture((char*)"SourceImage\\ShurikeinAppear.png", D3DCOLOR_XRGB(255, 255, 255));
	vector<RECT*> list_source_rect_appear = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\ShurikeinAppear.txt");
	animation->listSprite[State::APPEAR] = new Sprite(texture_appear, list_source_rect_appear, 2);

	MyTexture* texture_rotate_left = new MyTexture((char*)"SourceImage\\shurikein_rotate_left.png", D3DCOLOR_XRGB(255, 255, 255));
	vector<RECT*> list_source_rect_rotate_left = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\shurikein_rotate_left.txt");
	animation->listSprite[State::ROTATELEFT] = new Sprite(texture_rotate_left, list_source_rect_rotate_left, 1);

	//MyTexture* texture_rotate_right = new MyTexture((char*)"SourceImage\\shurikein_rotate_right.png", D3DCOLOR_XRGB(255, 255, 255));
	vector<RECT*> list_source_rect_rotate_right = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\shurikein_rotate_right.txt");
	animation->listSprite[State::ROTATERIGHT] = new Sprite(texture_rotate_left, list_source_rect_rotate_right, 1);
}

BoundingBox Shurikein::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - SHURIKEIN_WIDTH / 2;
	bound.y = y - SHURIKEIN_HEIGHT / 2;
	bound.w = SHURIKEIN_WIDTH;
	bound.h = SHURIKEIN_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Shurikein::SetState(State s)
{
	this->state = s;
}

void Shurikein::SetDirection(Direction d)
{
	this->direction = d;
}
