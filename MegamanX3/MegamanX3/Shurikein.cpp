#include"Shurikein.h"

Shurikein::Shurikein()
{
	x = 230;
	y = 7030 * G_Scale.y;
	animation_loop_rotate = 0;

	this->nameObject = SHURIKEIN;
	LoadResource();
}

Shurikein::Shurikein(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	animation_loop_rotate = 0;

	this->nameObject = SHURIKEIN;
	LoadResource();
}

Shurikein::~Shurikein()
{
}

void Shurikein::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt,List_object_can_col);
	x += dx;
	y += dy;

	if (state == APPEAR && animation->listSprite[APPEAR]->GetCurrentFrame() == 50)
		SetState(ROTATELEFT);	

	if (state == ROTATELEFT && animation->listSprite[ROTATELEFT]->GetCurrentFrame() == 9)
	{
		animation_loop_rotate++;
		if (animation_loop_rotate % 3 == 0)
		{
			animation->listSprite[ROTATELEFT]->Next();
			SetState(ROTATERIGHT);
		}
	}
	else if (animation->listSprite[ROTATERIGHT]->GetCurrentFrame() == 9)
	{
		animation_loop_rotate++;
		if (animation_loop_rotate % 3 == 0)
		{
			animation->listSprite[ROTATERIGHT]->Next();
			SetState(ROTATELEFT);
		}
	}
}

void Shurikein::Render()
{		
	ActionObject::Render();
}

void Shurikein::LoadResource()
{
	//MyTexture* texture_appear = new MyTexture((char*)"SourceImage\\ShurikeinAppear.png", D3DCOLOR_XRGB(255, 255, 255));
	//vector<RECT*> list_source_rect_appear1 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\ShurikeinAppear.txt");

	MyTexture* texture_appear = TXT::Instance()->GetTexture(TSHURIKEINAPPEAR);
	vector<RECT*> list_source_rect_appear = TXT::Instance()->GetListSourceRect(SSHURIKEINRAPPEAR);
	animation->listSprite[State::APPEAR] = new Sprite(texture_appear, list_source_rect_appear, 2);

	//MyTexture* texture_rotate_left = new MyTexture((char*)"SourceImage\\shurikein_rotate_left.png", D3DCOLOR_XRGB(255, 255, 255));
	//vector<RECT*> list_source_rect_rotate_left1 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\shurikein_rotate_left.txt");

	MyTexture* texture_rotate_left = TXT::Instance()->GetTexture(TSHURIKEINROTATELEFT);
	vector<RECT*> list_source_rect_rotate_left = TXT::Instance()->GetListSourceRect(SSHURIKEINROTATELEFT);
	animation->listSprite[State::ROTATELEFT] = new Sprite(texture_rotate_left, list_source_rect_rotate_left, 1);

	//MyTexture* texture_rotate_right = new MyTexture((char*)"SourceImage\\shurikein_rotate_right.png", D3DCOLOR_XRGB(255, 255, 255));
	vector<RECT*> list_source_rect_rotate_right = TXT::Instance()->GetListSourceRect(SSHURIKEINROTATERIGHT);
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
	switch (s)
	{
	case APPEAR:
		vx = vy = 0;
		break;
	case ROTATERIGHT:
		vx = SHURIKEIN_VX;
		break;
	case ROTATELEFT:
		vx = -SHURIKEIN_VX;
		break;
	default:
		break;
	}
}

void Shurikein::SetDirection(Direction d)
{
	this->direction = d;
}
