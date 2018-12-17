#include"SubBossCarry.h"
SubBossCarry* SubBossCarry::instance;

SubBossCarry::SubBossCarry()
{
	x = 5028*G_Scale.x;
	y = (1146+G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;

	this->start_location_y = y;
	this->nameObject = SUBBOSSCARRY;

	this->vx = 0;
	this->vy = SUBBOSSCARRY_VY;
	this->destroyed = false;
	this->actived = false;
	this->can_create_box = false;
	this->cleared_box = false;
	this->count_box = 0;

	//===============leg===============
	this->leg_runing = false;
	this->location_leg_x = this->x + 120;
	this->location_leg_y = this->y - 200;

	//============carry box================
	carryBox1 = new CarryBox(this->x - 400, this->y, 144, 144, RIGHT);
	carryBox2 = new CarryBox(this->x - 256, this->y, 144, 144, RIGHT);

	//============carry arm================
	carryArm1 = new CarryArm(this->x - 400, this->y+130, 144, 144, RIGHT);
	carryArm2 = new CarryArm(this->x - 256, this->y+130, 144, 144, RIGHT);

	//=============meta capsule=============
	metaSapsule = new MetaCapsule(this->x, this->y - 540, 144, 144, RIGHT);

	////============carry box================
	//carryBox1 = new CarryBox(this->x - 400, this->y-160, 144, 144, RIGHT);
	//carryBox2 = new CarryBox(this->x - 256, this->y-160, 144, 144, RIGHT);

	////============carry arm================-30
	//carryArm1 = new CarryArm(this->x - 400, this->y-170 , 144, 144, RIGHT);
	//carryArm2 = new CarryArm(this->x - 256, this->y -170, 144, 144, RIGHT);

	this->direction = RIGHT;

	this->animation_leg = new Animation();
	LoadResource();
}

SubBossCarry::SubBossCarry(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	this->start_location_y = y;
	this->nameObject = SUBBOSSCARRY;

	this->vx = 0;
	this->vy = SUBBOSSCARRY_VY;
	this->destroyed = false;
	this->actived = false;
	this->can_create_box = false;
	this->cleared_box = false;
	this->count_box = 0;

	//===============leg===============
	this->leg_runing = false;
	this->location_leg_x = this->x + 120;
	this->location_leg_y = this->y - 200;

	//============carry box================
	carryBox1 = new CarryBox(this->x, this->y, 144, 144, RIGHT);
	carryBox2 = new CarryBox(this->x - 100, this->y, 144, 144, RIGHT);

	//============carry arm================
	carryArm1 = new CarryArm(this->x - 400, this->y + 130, 144, 144, RIGHT);
	carryArm2 = new CarryArm(this->x - 256, this->y + 130, 144, 144, RIGHT);

	//=============meta capsule=============
	metaSapsule = new MetaCapsule(this->x, this->y - 540, 144, 144, RIGHT);

	this->direction = RIGHT;

	this->animation_leg = new Animation();
	LoadResource();
}

SubBossCarry::~SubBossCarry()
{
}

SubBossCarry * SubBossCarry::Instance()
{
	if (!instance)
		instance = new SubBossCarry();
	return instance;
}

void SubBossCarry::Update(DWORD dt, vector<Object*>* List_object_can_col)
{

	if (destroyed||!this->actived)
		return;

	//=====go up when the box more MAX================
	if (this->count_box == SUBBOSSCARRY_BOX_SUM
		&& !this->carryBox1->IsActived()
		&& !this->carryBox2->IsActived())
	{
		if (this->y > this->start_location_y - 100)
		{
			this->actived = false;

			//========unlock camera===============
			Camera::Instance()->SetAutoMovingX(false);
			Camera::Instance()->SetLocked(false);
			Camera::Instance()->SetBonousX(5); //avoid loop lock camera
		}
			

		if (this->location_leg_y < this->start_location_y)
		{
			this->location_leg_y += 2;

			// deActived all eneymy sub.
			if (!this->cleared_box)
			{
				this->cleared_box = true;
				this->carryArm1->SetActived(false);
				this->carryArm2->SetActived(false);
				this->carryBox1->SetActived(false);
				this->carryBox2->SetActived(false);
				this->metaSapsule->SetActived(false);
			}
			
		}
		else
			this->vy = -SUBBOSSCARRY_VY;

		Object::Update(dt, List_object_can_col);
		x += dx;
		y += dy;
		return;
	}

	//===================body finish appear-> apear leg====================
	if (this->y < this->start_location_y - 390)
	{
		this->vy = 0;
		this->leg_runing = true;
	}

	//==================leg !touched ground -> run until touched ground===================
	if (this->leg_runing&& this->location_leg_y > this->start_location_y - 610)
	{
		this->location_leg_y -= 2;
	}
	
	//=============allow create box ==============================
	if (!this->can_create_box)
	{
		if (GetTickCount() - this->time_body_start_runing > 6000)
		{
			this->can_create_box = true;
			this->time_start_create_box = GetTickCount();
		}
			
	}
	else
	{
		// make box 1
		if (GetTickCount() - this->time_start_create_box > 1000
			&&count_box%2==0
			&&this->carryBox1->IsDestroy()
			&& !this->carryArm1->IsActived()
			&& this->count_box < SUBBOSSCARRY_BOX_SUM)
		{
			this->carryBox1->SetActived(true);
			this->carryArm1->SetActived(true);
			this->time_start_create_box = GetTickCount();
			count_box++;
		}
		
		//make box 2
		if (GetTickCount() - this->time_start_create_box > 1000 
			&& count_box % 2 == 1
			&& this->carryBox2->IsDestroy()
			&& !this->carryArm2->IsActived()
			&& this->count_box < SUBBOSSCARRY_BOX_SUM)
		{
			this->carryBox2->SetActived(true);
			this->carryArm2->SetActived(true);
			this->time_start_create_box = GetTickCount();
			count_box++;
		}
	}

	//===================create gun when have 2 box==============
	if (this->carryBox1->IsArrived() && this->carryBox2->IsArrived())
	{
		metaSapsule->SetActived(true);
	}

	//====================update carry box===========================
	this->carryBox1->Update(dt, List_object_can_col);
	this->carryBox2->Update(dt, List_object_can_col);

	//====================update carry arm===========================
	this->carryArm1->Update(dt, List_object_can_col);
	this->carryArm2->Update(dt, List_object_can_col);

	//====================update meta capsule===========================
	this->metaSapsule->Update(dt, List_object_can_col);
		

	//===================alive===================================
	Object::Update(dt, List_object_can_col);
	x += dx;
	y += dy;

}

void SubBossCarry::Render()
{
	if (destroyed)
		return;

	//===============render leg==================

	D3DXVECTOR2 position_leg = Camera::Instance()->GetPositionInViewPort(this->location_leg_x, this->location_leg_y);//502,327
	animation_leg->Render(RUN, this->direction, position_leg);

	//===================render body=================
	ActionObject::Render();

	//===============render carrybox=======================
	this->carryBox1->Render();
	this->carryBox2->Render();

	//===============render carryarm=======================
	this->carryArm1->Render();
	this->carryArm2->Render();

	//==============render metacapsule====================
	this->metaSapsule->Render();
}

void SubBossCarry::LoadResource()
{
	MyTexture* texture = TXT::Instance()->GetTexture(TCARRYARM);

	vector<RECT*> list_source_rect_body = TXT::Instance()->GetListSourceRect(SSUBBOSSCARRYBODY);
	
	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_body, 1);


	vector<RECT*> list_source_rect_leg = TXT::Instance()->GetListSourceRect(SSUBBOSSCARRYLEG);

	animation_leg->listSprite[State::RUN] = new Sprite(texture, list_source_rect_leg, 1);
}

BoundingBox SubBossCarry::GetBoundingBox()
{
	//==============get bound box to colli megaman , uu tien box1====
	float xb1, yb1, xb2, yb2;
	this->carryBox1->GetPosition(xb1, yb1);
	this->carryBox2->GetPosition(xb2, yb2);

	//==========b1 chua destroy thi neu no k cao hon b2 qua nhieu se lay no
	if (!this->carryBox1->IsDestroy() && yb1 < yb2 + 20)
	{
		this->box_colli = 1;
		return carryBox1->GetBoundingBox();
	}
		
	else
		if (!this->carryBox2->IsDestroy())
		{
			this->box_colli = 2; 
			return carryBox2->GetBoundingBox();
		}
		
		else
		{
			// if both destroy- no have colli
			return BoundingBox();
		}
}

void SubBossCarry::SetState(State s)
{
	this->state = s;
}

void SubBossCarry::SetDirection(Direction d)
{
	this->direction = d;
}

void SubBossCarry::SetActived(bool active)
{
	this->actived = active;
	this->time_body_start_runing = GetTickCount();
}

void SubBossCarry::SetBeingAttacked(int damage)
{
	if (box_colli==1)
	{
		this->carryBox1->SetBeingAttacked(damage);
	}
	else
	{
		this->carryBox2->SetBeingAttacked(damage);
	}
}
