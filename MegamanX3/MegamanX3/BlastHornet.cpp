#include"BlastHornet.h"

BlastHornet::BlastHornet()
{
	x = 1800;
	y = 7100 * G_Scale.y;
	count_animation = 0;

	this->nameObject = BLASTHORNET;
	LoadResource();
}

BlastHornet::BlastHornet(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	count_animation = 0;

	this->nameObject = BLASTHORNET;
	LoadResource();
}

BlastHornet::~BlastHornet()
{
}

void BlastHornet::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	count_animation++;
	if (count_animation % 50 == 0)
		SetState(REDKNEE);
	if (count_animation % 100 == 0)
		SetState(REDHANDS);
	if (count_animation % 150 == 0)
		SetState(PREPAREOPENVENOM);
	if (count_animation % 200 == 0)
		SetState(OPENINGVENOM);
}

void BlastHornet::Render()
{
	ActionObject::Render();
}

void BlastHornet::LoadResource()
{
	//vector<RECT*> list_source_rect_red_knee = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_red_knee.txt");
	//MyTexture* texture_red_knee = new MyTexture((char*)"SourceImage\\blast_hornet_red_knee.png", D3DCOLOR_XRGB(255, 255, 255));

	vector<RECT*> list_source_rect_red_knee = TXT::Instance()->GetListSourceRect(SBLASTHORNETREDKNEE);
	MyTexture* texture_red_knee = TXT::Instance()->GetTexture(TBLASTHORNETREDKNEE);
	animation->listSprite[State::REDKNEE] = new Sprite(texture_red_knee, list_source_rect_red_knee, 1);

	//vector<RECT*> list_source_rect_red_hands = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_red_hands.txt");
	//MyTexture* texture_red_hands = new MyTexture((char*)"SourceImage\\blast_hornet_red_hands.png", D3DCOLOR_XRGB(255, 255, 255));

	vector<RECT*> list_source_rect_red_hands = TXT::Instance()->GetListSourceRect(SBLASTHORNETREDHANDS);
	MyTexture* texture_red_hands = TXT::Instance()->GetTexture(TBLASTHORNETREDHANDS);
	animation->listSprite[State::REDHANDS] = new Sprite(texture_red_hands, list_source_rect_red_hands, 2);

	//vector<RECT*> list_source_rect_prepare_open_venom = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_prepare_open_venom.txt");
	//MyTexture* texture_red_prepare_open_venom = new MyTexture((char*)"SourceImage\\blast_hornet_prepare_open_venom.png", D3DCOLOR_XRGB(255, 255, 255));

	vector<RECT*> list_source_rect_prepare_open_venom = TXT::Instance()->GetListSourceRect(SBLASTHORNETPREPAREOPENVENOM);
	MyTexture* texture_red_prepare_open_venom = TXT::Instance()->GetTexture(TBLASTHORNETPREPAREOPENVENOM);
	animation->listSprite[State::PREPAREOPENVENOM] = new Sprite(texture_red_prepare_open_venom, list_source_rect_prepare_open_venom, 1);

	//vector<RECT*> list_source_rect_opening_venom = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\blast_hornet_opening_venom.txt");
	//MyTexture* texture_red_opening_venom = new MyTexture((char*)"SourceImage\\blast_hornet_opening_venom.png", D3DCOLOR_XRGB(255, 255, 255));

	vector<RECT*> list_source_rect_opening_venom = TXT::Instance()->GetListSourceRect(SBLASTHORNETOPENINGVENOM);
	MyTexture* texture_red_opening_venom = TXT::Instance()->GetTexture(TBLASTHORNETOPENINGVENOM);
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
