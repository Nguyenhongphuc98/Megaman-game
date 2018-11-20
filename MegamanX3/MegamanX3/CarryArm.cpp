#include"CarryArm.h"

CarryArm::CarryArm()
{
	x = 2000;
	y = 7100 * G_Scale.y;
	count_time_change_animation = 0;
	LoadResource();
}

CarryArm::~CarryArm()
{
}

void CarryArm::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	count_time_change_animation++;
	if (count_time_change_animation % 50 == 0)
		SetState(STRAIGHTROPE);

	if (count_time_change_animation % 100 == 0)
		SetState(BREAKROPE);
}

void CarryArm::Render()
{
	ActionObject::Render();
}

void CarryArm::LoadResource()
{
	//MyTexture* texture = new MyTexture((char*)"SourceImage\\subboss_carryarm.png", D3DCOLOR_XRGB(50, 96, 166));
	//vector<RECT*> list_source_rect_straight_rope = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\subboss_carryarm_straight.txt");

	MyTexture* texture = TXT::Instance()->GetTexture(TCARRYARM);

	vector<RECT*> list_source_rect_straight_rope = TXT::Instance()->GetListSourceRect(SCARRYARMSTRAIGHT);
	animation->listSprite[State::STRAIGHTROPE] = new Sprite(texture, list_source_rect_straight_rope, 1);

	//vector<RECT*> list_source_rect_break_rope = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\subboss_carryarm_break.txt");
	vector<RECT*> list_source_rect_break_rope = TXT::Instance()->GetListSourceRect(SCARRYARMBREAK);
	animation->listSprite[State::BREAKROPE] = new Sprite(texture, list_source_rect_break_rope, 1);
}

BoundingBox CarryArm::GetBoundingBox()
{
	BoundingBox bound;
	if (state == STRAIGHTROPE)
	{
		bound.x = x - CARRYARM_STRAIGHT_HEIGHT / 2;
		bound.y = y - CARRYARM_STRAIGHT_WIDTH / 2;
		bound.w = CARRYARM_STRAIGHT_WIDTH;
		bound.h = CARRYARM_STRAIGHT_HEIGHT;
		bound.vx = dx;
		bound.vy = dy;
	}
	else
	{
		bound.x = x - CARRYARM_BREAK_HEIGHT / 2;
		bound.y = y - CARRYARM_BREAK_WIDTH / 2;
		bound.w = CARRYARM_BREAK_WIDTH;
		bound.h = CARRYARM_BREAK_HEIGHT;
		bound.vx = dx;
		bound.vy = dy;
	}
	return bound;
}

void CarryArm::SetState(State s)
{
	this->state = s;
}

void CarryArm::SetDirection(Direction d)
{
	this->direction = d;
}

State CarryArm::GetState()
{
	return this->state;
}

Direction CarryArm::GetDirection()
{
	return this->direction;
}
