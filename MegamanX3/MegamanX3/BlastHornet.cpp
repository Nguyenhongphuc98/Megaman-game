#include"BlastHornet.h"

BlastHornet::BlastHornet()
{
	x = 200;
	y = 1153 * G_Scale.y;
	LoadResource();
}

BlastHornet::~BlastHornet()
{
}

void BlastHornet::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
}

void BlastHornet::Render()
{
	ActionObject::Render();
}

void BlastHornet::LoadResource()
{
	vector<RECT*> list_source_rect_red_knee = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_red_knee.txt");
	MyTexture* texture_red_knee = new MyTexture((char*)"SourceImage\\blast_hornet_red_knee.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->listSprite[State::REDKNEE] = new Sprite(texture_red_knee, list_source_rect_red_knee, 1);

	vector<RECT*> list_source_rect_red_hands = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_red_hands.txt");
	MyTexture* texture_red_hands = new MyTexture((char*)"SourceImage\\blast_hornet_red_hands.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->listSprite[State::REDHANDS] = new Sprite(texture_red_hands, list_source_rect_red_hands, 2);

	vector<RECT*> list_source_rect_prepare_open_venom = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_prepare_open_venom.txt");
	MyTexture* texture_red_prepare_open_venom = new MyTexture((char*)"SourceImage\\blast_hornet_prepare_open_venom.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->listSprite[State::PREPAREOPENVENOM] = new Sprite(texture_red_prepare_open_venom, list_source_rect_prepare_open_venom, 1);

	vector<RECT*> list_source_rect_opening_venom = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_opening_venom.txt");
	MyTexture* texture_red_opening_venom = new MyTexture((char*)"SourceImage\\blast_hornet_opening_venom.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->listSprite[State::OPENINGVENOM] = new Sprite(texture_red_opening_venom, list_source_rect_opening_venom, 2);
}

BoundingBox BlastHornet::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - BLASTHORNET_WIDTH / 2;
	bound.y = y - BLASTHORNET_HEIGHT / 2;
	bound.w = BLASTHORNET_WIDTH;
	bound.h = BLASTHORNET_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void BlastHornet::SetState(State s)
{
	this->state = s;
}

void BlastHornet::SetDirection(Direction d)
{
	this->direction = d;
}
