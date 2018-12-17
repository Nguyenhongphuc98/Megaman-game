#include"TextStartGame.h"

TextStartGame::TextStartGame()
{
	x = 4900 * G_Scale.x;
	y = (932 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	this->nameObject = TEXTSTARTGAME;

	this->vx = 0;
	this->vy = CARRYBOX_VY;
	this->destroyed = false;
	this->actived = false;

	this->direction = RIGHT;

	LoadResource();
}

TextStartGame::TextStartGame(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	this->nameObject = TEXTSTARTGAME;

	this->vx = 0;
	this->vy = CARRYBOX_VY;
	this->destroyed = false;
	this->actived = false;

	this->direction = RIGHT;

	LoadResource();
}

TextStartGame::~TextStartGame()
{
}


void TextStartGame::Update(DWORD dt, vector<Object*>* List_object_can_col)
{

	if (destroyed || !this->actived)
		return;

	if (this->animation->listSprite[this->state]->IsFinalFrame())
		this->destroyed = true;
}

void TextStartGame::Render()
{
	if (destroyed)
		return;

	D3DXVECTOR2 position = D3DXVECTOR2(300, 300);
	animation->Render(state, direction, position);
	animation->Next(state);
}

void TextStartGame::LoadResource()
{
	MyTexture* texture = TXT::Instance()->GetTexture(TTEXTSTARTGAME);

	vector<RECT*> list_source_rect_body = TXT::Instance()->GetListSourceRect(STEXTSTARTGAME);

	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_body, 3);
}

BoundingBox TextStartGame::GetBoundingBox()
{
	return BoundingBox();
}

void TextStartGame::SetState(State s)
{
	this->state = s;
}

void TextStartGame::SetDirection(Direction d)
{
	this->direction = d;
}
