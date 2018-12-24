#include"DoorBlasHornet.h"
DoorBlasHornet* DoorBlasHornet::instance;

DoorBlasHornet::DoorBlasHornet(float top, float left, float w, float h)
{

	this->x = left;
	this->y = top;
	this->width = w;
	this->height = h;

	if (this->x > 18750)// door 4	
	{
		this->x = 19187;
		this->y = 14973;
	}
	else
	if (this->x > 18000)// door 3
	{
		this->x = 18545;
		this->y = 14973;
	}
	else
		if(this->x>14375) //door2
		{
			this->x = 14712;
			this->y = 16895;
		}
		else
			if (this->x > 13755) //door1
			{
				this->x = 14067;
				this->y = 16895;
			}

	this->actived = false;
	this->moving_megaman = false;
	this->locked = true;

	this->allow_open = true;
	this->nameObject = DOOR;

	MyTexture* texture = TXT::Instance()->GetTexture(TDOOR);

	vector<RECT*> list_source_rect_open = TXT::Instance()->GetListSourceRect(SDOORBLASTHORNETOPEN);
	animation->listSprite[State::DOOROPEN] = new Sprite(texture, list_source_rect_open, 5);

	vector<RECT*> list_source_rect_close = TXT::Instance()->GetListSourceRect(SDOORBLASTHORNETCLOSE);
	animation->listSprite[State::DOORCLOSE] = new Sprite(texture, list_source_rect_close, 5);

	this->state = DOOROPEN;
}

DoorBlasHornet * DoorBlasHornet::Instance()
{
	if (!instance)
		instance = new DoorBlasHornet((878 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y, 5627 * G_Scale.x, 0, 0);
	return instance;
}

void DoorBlasHornet::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	//==========don't update but, we render still========
	if (this->destroyed)
		return;

	//===========when door opened -> move megaman thought door==============
	if (this->moving_megaman)
	{
		float x_megaman, y_megman;
		Megaman::Instance()->GetPosition(x_megaman, y_megman);
		if (abs(x_megaman - x_start_megaman) > 153)
		{
			this->moving_megaman = false;
			this->SetState(DOORCLOSE);
			this->x += 40;

			Megaman::Instance()->SetAutoMoving(false);
			//Camera::Instance()->SetAutoMovingX(false);

			return;
		}
		Megaman::Instance()->SetPosition(x_megaman + 3, y_megman);
		return;
	}

	//==========when door start completely open==================================
	if (this->state == DOOROPEN && this->animation->listSprite[this->state]->IsFinalFrame())
	{
		this->moving_megaman = true;
		Camera::Instance()->SetAutoMovingX(true);
		Camera::Instance()->SetLocked(false);
		Camera::Instance()->SetBonousX(5);
	}

	if (this->state == DOORCLOSE && this->animation->listSprite[DOORCLOSE]->IsFinalFrame())
	{
		this->actived = false;
		this->destroyed = true;
		//Genjibo::Instance()->SetActived(true);
		
		if (this->x > 18750)// door 4	
		{
			BlastHornet::Instance()->SetActived(true);
		}
		
	}

}

void DoorBlasHornet::Render()
{
	if (this->moving_megaman)
		return;

	if (!this->actived)
	{
		this->animation->listSprite[DOOROPEN]->Set_current_frame(0);
		if (this->state == DOORCLOSE)
			this->animation->listSprite[DOORCLOSE]->Set_current_frame(8);
	}

	ActionObject::Render();

}

BoundingBox DoorBlasHornet::GetBoundingBox()
{
	BoundingBox bound;

	if (this->locked)
	{
		bound.x = x - DOORSHURIKEIN_WIDTH / 2;
		bound.y = y - DOORSHURIKEIN_HEIGHT / 2;
		bound.w = DOORSHURIKEIN_WIDTH;
		bound.h = DOORSHURIKEIN_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}
	else
	{
		bound.x = x - DOORSHURIKEIN_WIDTH / 2;
		bound.y = y + DOORSHURIKEIN_HEIGHT / 2; //change possition to avoid colli
		bound.w = DOORSHURIKEIN_WIDTH;
		bound.h = DOORSHURIKEIN_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}

	return bound;
}

void DoorBlasHornet::SetActived(bool active)
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
