#include"CarryArm.h"

CarryArm::CarryArm()
{
	x = 2000;
	y = 7100 * G_Scale.y;
	count_time_change_animation = 0;

	this->start_location_y = this->y;
	this->start_location_x = this->x;
	this->destroyed = false;
	this->actived = false;
	this->uping = false;
	this->state = STRAIGHTROPE;

	this->vx = CARRYARM_VX;
	this->vy = CARRYARM_VY;

	this->nameObject = CARRYARM;
	LoadResource();
}

CarryArm::CarryArm(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	this->x = x;
	this->y = y;
	this->start_location_y = this->y;
	this->start_location_x = this->x;
	this->destroyed = false;
	this->actived = false;
	this->uping = false;
	this->state = STRAIGHTROPE;

	this->vx = CARRYARM_VX;
	this->vy = CARRYARM_VY;

	this->nameObject = CARRYARM;
	LoadResource();
}

CarryArm::~CarryArm()
{
}

void CarryArm::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (destroyed || !this->actived)
		return;

	//=================uping==================
	if (this->y > this->start_location_y &&uping)
		this->actived = false;

	//========moving cheo'=> down===================
	if (this->y < this->start_location_y - 500)
		this->vx = 0;

	//====================colli with ground=====================
	if (this->y < this->start_location_y - 620&&this->state!=SLACKROPE&&!uping)
	{
		this->vy = 0;
		this->SetState(SLACKROPE);
	}

	if (this->state == SLACKROPE&&this->animation->listSprite[SLACKROPE]->GetCurrentFrame()==2)
	{
		this->y -= 10;
		this->vy = -CARRYARM_VY;
	}

	if (this->state == SLACKROPE && this->animation->listSprite[SLACKROPE]->IsFinalFrame())
	{
		this->SetState(STRAIGHTROPE);
		this->uping = true;
	}

	//===================alive===================================
	Object::Update(dt, List_object_can_col);
	x += dx;
	y += dy;


	/*if (this->y > this->start_location_y&&this->uping)
		this->Reset();*/
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

	vector<RECT*> list_source_rect_slack_rope = TXT::Instance()->GetListSourceRect(SCARRYARMSLACK);
	animation->listSprite[State::SLACKROPE] = new Sprite(texture, list_source_rect_slack_rope, 1);
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
	this->animation->Refresh(SLACKROPE);
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

void CarryArm::Reset()
{
	this->x = this->start_location_x;
	this->y = this->start_location_y;

	this->destroyed = false;
	this->actived = false;
	this->uping = false;

	this->vx = CARRYARM_VX;
	this->vy = CARRYARM_VY;
}
