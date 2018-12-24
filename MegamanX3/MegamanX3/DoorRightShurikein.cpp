#include"DoorRightShurikein.h"
DoorRightShurikein* DoorRightShurikein::instance;


DoorRightShurikein::DoorRightShurikein(float top, float left, float w, float h)
{
	this->x = left;
	this->y = top;
	this->width = w;
	this->height = h;
	this->actived = false;
	this->moving_megaman = false;
	this->locked = true;

	this->allow_open = false;
	this->nameObject = DOOR;


	MyTexture* texture = TXT::Instance()->GetTexture(TDOOR);

	vector<RECT*> list_source_rect_open = TXT::Instance()->GetListSourceRect(SDOORSHURIKEINOPEN);
	animation->listSprite[State::DOOROPEN] = new Sprite(texture, list_source_rect_open, 5);

	vector<RECT*> list_source_rect_close = TXT::Instance()->GetListSourceRect(SDOORSHURIKEINCLOSE);
	animation->listSprite[State::DOORCLOSE] = new Sprite(texture, list_source_rect_close, 5);

	this->state = DOOROPEN;
}

DoorRightShurikein * DoorRightShurikein::Instance()
{
	if(!instance)
		instance=new DoorRightShurikein((878 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y, 2563 * G_Scale.x, 0, 0);
	return instance;
}

void DoorRightShurikein::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	//===========when door opened -> move megaman thought door==============
	if (this->moving_megaman)
	{
		float x_megaman, y_megman;
		Megaman::Instance()->GetPosition(x_megaman, y_megman);
		if (abs(x_megaman - x_start_megaman) > 153)
		{
			this->moving_megaman = false;
			this->SetState(DOORCLOSE);
			//this->x += 40;

			Megaman::Instance()->SetAutoMoving(false);
			return;
		}
		Megaman::Instance()->SetPosition(x_megaman + 3, y_megman);
		return;
	}

	//==========when door start completely open==================================
	if (this->state == DOOROPEN && this->animation->listSprite[this->state]->IsFinalFrame())
	{
		this->moving_megaman = true;
		//unlock camera to moving
		Camera::Instance()->SetLocked(false);
		Camera::Instance()->SetAutoMovingX(true);
		Camera::Instance()->SetBonousX(7);
	}

	if (this->state == DOORCLOSE && this->animation->listSprite[DOORCLOSE]->IsFinalFrame())
	{
		this->actived = false;
		//Genjibo::Instance()->SetActived(true);
	}
}

void DoorRightShurikein::Render()
{
	if (this->moving_megaman)
		return;

	if (!this->actived)
	{
		this->animation->listSprite[DOOROPEN]->Set_current_frame(0);
		if (this->state == DOORCLOSE)
			this->animation->listSprite[DOORCLOSE]->Set_current_frame(16);
	}

	ActionObject::Render();
}

BoundingBox DoorRightShurikein::GetBoundingBox()
{
	BoundingBox bound;

	if (this->locked)
	{
		bound.x = x - DOORRIGHTSHURIKEIN_WIDTH / 2;
		bound.y = y - DOORRIGHTSHURIKEIN_HEIGHT / 2;
		bound.w = DOORRIGHTSHURIKEIN_WIDTH;
		bound.h = DOORRIGHTSHURIKEIN_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}
	else
	{
		bound.x = x - DOORRIGHTSHURIKEIN_WIDTH / 2;
		bound.y = y + DOORRIGHTSHURIKEIN_HEIGHT / 2; //change possition to avoid colli
		bound.w = DOORRIGHTSHURIKEIN_WIDTH;
		bound.h = DOORRIGHTSHURIKEIN_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}

	return bound;
}

void DoorRightShurikein::SetActived(bool active)
{
	if (!this->allow_open)
		return;

	this->actived = active;
	this->allow_open = false;

	float x_megaman, y_megman;
	Megaman::Instance()->GetPosition(x_megaman, y_megman);
	Megaman::Instance()->SetAutoMoving(true);

	this->x_start_megaman = x_megaman;
}
