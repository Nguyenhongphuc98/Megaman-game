#include"NotorBanger.h"

NotorBanger::NotorBanger()
{
	x = 1100;
	y = 7056 * G_Scale.y;

	center_region_x = x;
	jump_angle = PII/4;
	//time_animate_shoot90 = 1;

	this->hitpoints = NOTORBANGER_MAX_HP;

	this->ReSet();
	this->nameObject = NOTORBANGER;
	LoadResource();
}

NotorBanger::NotorBanger(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	center_region_x = x;
	jump_angle = PII / 6;
	//time_animate_shoot90 = 1;

	this->hitpoints = NOTORBANGER_MAX_HP;
	this->destroyed = false;
	this->ReSet();

	this->nameObject = NOTORBANGER;
	LoadResource();
}

NotorBanger::~NotorBanger()
{
}

void NotorBanger::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	

	float megaman_x, megaman_y;
	Megaman::Instance()->GetPosition(megaman_x, megaman_y);


	//==========reset if distance so far=================
	
	if (abs(this->x - megaman_x) > 300 &&this->destroyed)
	{
		
		this->destroyed = false;
		this->hitpoints = NOTORBANGER_MAX_HP;
		this->SetState(STAND);
//		MyDebugOUT("reset notorbanger ");
		this->animation->listSprite[DESTROY]->Set_current_frame(0);
		return;
	}

	//===================no update when destroy=====================
	if (this->destroyed)
		return;

	//=======================check life=============================
	if (this->hitpoints <= 0&&this->state!=DESTROY)
	{
		this->SetState(DESTROY);
		Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
		tempBullet->SetState(DESTROYBULLET);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
		return;
	}



	//===================================================

	this->vy += -0.0001*dt; //gravity
	Object::Update(dt,List_object_can_col);
	
	
#pragma region JumpAndShoot90

	//if (state == JUMP)
	//{
	//	x += dx;
	//	y = pre_y;
	//	//x=vx*t=Vo*Cos(a)*t
	//	//y=Vo*Sin(a)*t-1/2gt^2
	//	float t = GetTickCount() - time_begin_jump;
	//	//x =pre_x+ (dx*t*cos(jump_angle));
	//	//y = pre_y + ((dy*t*sin(jump_angle)) -((NOTORBANGER_GRAVITY * t)*(NOTORBANGER_GRAVITY * t)) / 2);

	//	if (/*direction == LEFT && */(x <= (center_region_x - 100)))
	//	{
	//		SetDirection(LEFT);
	//		SetState(SHOOT90);
	//	}

	//	if (/*direction == RIGHT && */(x >= (center_region_x + 100)))
	//	{
	//		SetDirection(RIGHT);
	//		SetState(SHOOT90);
	//	}
	//}
	//else
	//{
	//	y = pre_y + 6;
	//	if (animation->listSprite[SHOOT90]->GetCurrentFrame() == 2)
	//		time_animate_shoot90++;

	//	if (time_animate_shoot90 % 20 == 0)
	//	{
	//		time_begin_jump = GetTickCount();
	//		SetState(JUMP);
	//		time_animate_shoot90++;
	//	}
	//}

#pragma endregion

	//float megaman_x, megaman_y;
	//Megaman::Instance()->GetPosition(megaman_x, megaman_y);
	if(this->state!=JUMP)
	this->SetDirection((this->x > megaman_x) ? RIGHT : LEFT);
	distance_to_megaman = abs(this->x - megaman_x);


	bool isColl=false;
	if (this->state == JUMP)
	{
		this->t = GetTickCount() - this->time_begin_jump;

		dx = vx * t*cos(this->jump_angle) - this->distance_has_jumped_x;
		dy = vy * t*sin(this->jump_angle) - 0.5*0.0005*pow(t, 2) - this->distance_has_jumped_y;

		

		this->distance_has_jumped_x += dx;
		this->distance_has_jumped_y += dy;
	}
	
	vector<ResultCollision> List_result_col;
	List_result_col.clear();

	for (int i = 0; i < List_object_can_col->size(); i++) {
		ResultCollision r;
		r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), List_object_can_col->at(i)->GetBoundingBox());
		if (r.isCollision)
			List_result_col.push_back(r);
	}

	if (List_result_col.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx = 1.0f, min_ty = 1.0f;
		int nx = 0, ny = 0;

		for (int i = 0; i < List_result_col.size(); i++) {
			if (List_result_col[i].t < min_tx && List_result_col[i].nx != 0) {
				min_tx = List_result_col[i].t; nx = List_result_col[i].nx;
			}

			if (List_result_col[i].t < min_ty  && List_result_col[i].ny != 0) {
				min_ty = List_result_col[i].t; ny = List_result_col[i].ny;
			}
		}

		x += (min_tx * dx + nx * 0.4f);
		y += (min_ty * dy + ny * 0.4f);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		isColl = true;
	}

#pragma region CheckState
	
	if (this->active == false)
	{
		if (this->distance_to_megaman < 300)
		{
			this->active = true;
			if (this->distance_to_megaman > 100)
			{
				this->SetState(UPTHEGUN60);
			}
			else
			{
				this->SetState(UPTHEGUN90);
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		if (this->distance_to_megaman > 300)
		{
			this->ReSet(); return;
		}
			

		switch (this->state)
		{
		case UPTHEGUN60:
			if (this->animation->listSprite[UPTHEGUN60]->IsFinalFrame())
			{
				this->uped_the_gun60 = true;
				//time_begin_shot = GetTickCount();
				this->SetState(SHOOT60);
			}
			break;

		case SHOOT60:
			if (this->count_number_shots == 3)
			{
				this->count_number_shots = 0;
				//time_begin_shot = GetTickCount();
				/*if (abs(this->x - this->center_region_x) > 400)
				{
					ReSet();
				}*/
				this->shot60 = true;
				this->SetState(DOWNTHEGUN);
			}
			else
			{
				if (this->animation->listSprite[SHOOT60]->IsFinalFrame()
					&& (GetTickCount() - time_begin_shot) > 500)
				{
					this->count_number_shots++;
					this->time_begin_shot = GetTickCount();

					Bullet *bullet = new NotorbangerBullet((this->direction==RIGHT)?this->x - 25:this->x+25, this->y + 25,
						(this->direction==RIGHT)?LEFT:RIGHT, PII / 3);
					WeaponSystem::Instance()->AddBulletEnemy(bullet);
				}
			}
			break;

		case DOWNTHEGUN:
			if (this->animation->listSprite[DOWNTHEGUN]->IsFinalFrame())
			{
				this->time_begin_stand = GetTickCount();
				this->SetState(STAND);
			}
			break;

		case STAND:
			if (GetTickCount() - time_begin_stand > 500)
			{
				if (this->shot60&&this->jump)
				{
					if (this->shot90)
						this->ReSet();
					else
					{
						this->time_begin_shot = GetTickCount();
						this->SetState(SHOOT90);
					}

				}
				else
				{
					this->SetState(JUMP);
				}

			}
			else return;
			break;

		case JUMP:
			if (!isColl)// change to check if not colli
			{
				if (this->animation->listSprite[JUMP]->GetCurrentFrame() == 0)
					this->animation->listSprite[JUMP]->Set_current_frame(4);

			/*	t = GetTickCount() - time_begin_jump;
				x = this->pre_x + vx * t*cos(this->jump_angle);
				y = this->pre_y + vy * t*sin(this->jump_angle) - 0.5*0.0005*pow(t, 2);*/
			}
			else
			{
				this->jump = true;
				this->SetState(STAND);
			}
			break;

		case SHOOT90:
			if (this->count_number_shots == 3)
			{
				this->count_number_shots = 0;
				time_begin_shot = GetTickCount();
				if (abs(this->x - this->center_region_x) > 400)
				{
					ReSet();
				}
				this->shot60 = true;
				this->SetState(DOWNTHEGUN);
			}
			else
			{
				if (this->animation->listSprite[SHOOT90]->IsFinalFrame()
					&& (GetTickCount() - time_begin_shot) > 500)
				{
					this->count_number_shots++;
					this->time_begin_shot = GetTickCount();

					Bullet *bullet = new NotorbangerBullet(this->x, this->y + 60,
						(this->direction == RIGHT) ? LEFT : RIGHT, PII / 2.3);
					WeaponSystem::Instance()->AddBulletEnemy(bullet);
				}
			}
			break;

		default:
			break;
		}
	}
#pragma endregion

}

void NotorBanger::Render()
{
	if (this->destroyed)
		return;

	//======================check destroyed=================================
	if (this->state == DESTROY && this->animation->listSprite[state]->IsFinalFrame())
	{
		destroyed = true;
		Bullet* blood = new ItemBlood(this->x, this->y-45);
		WeaponSystem::Instance()->AddBulletEnemy(blood);
		return;
	}
		
	ActionObject::Render();
}

void NotorBanger::LoadResource()	
{

	MyTexture *texture = TXT::Instance()->GetTexture(TNOTORBANGER);

	vector<RECT*> list_source_rect_jump = TXT::Instance()->GetListSourceRect(SNOTORBANGERJUMP);
	animation->listSprite[JUMP] = new Sprite(texture, list_source_rect_jump, 4);

	vector<RECT*> list_source_rect_shoot90 = TXT::Instance()->GetListSourceRect(SNOTOBANGERSHOOT90);
	animation->listSprite[SHOOT90] = new Sprite(texture, list_source_rect_shoot90, 8);

	vector<RECT*> list_source_rect_shoot60 = TXT::Instance()->GetListSourceRect(SNOTOBANGERSHOOT60);
	animation->listSprite[SHOOT60] = new Sprite(texture, list_source_rect_shoot60, 8);

	vector<RECT*> list_source_rect_up_gun60 = TXT::Instance()->GetListSourceRect(SNOTOBANGERUPTHEGUN60);
	animation->listSprite[UPTHEGUN60] = new Sprite(texture, list_source_rect_up_gun60, 3);

	vector<RECT*> list_source_rect_up_gun90 = TXT::Instance()->GetListSourceRect(SNOTOBANGERUPTHEGUN90);
	animation->listSprite[UPTHEGUN90] = new Sprite(texture, list_source_rect_up_gun90, 3);

	vector<RECT*> list_source_rect_stand = TXT::Instance()->GetListSourceRect(SNOTORBANGERSTAND);
	animation->listSprite[STAND] = new Sprite(texture, list_source_rect_stand, 3);

	vector<RECT*> list_source_rect_down_gun = TXT::Instance()->GetListSourceRect(SNOTORBANGERDOWTHEGUN);
	animation->listSprite[DOWNTHEGUN] = new Sprite(texture, list_source_rect_down_gun, 3);

	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SNOTORBANGERDESTROY);
	animation->listSprite[DESTROY] = new Sprite(texture, list_source_rect_destroy, 1);
}

BoundingBox NotorBanger::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - NOTORBANGER_WIDTH / 2;
	bound.y = y - NOTORBANGER_HEIGHT / 2;
	bound.w = NOTORBANGER_WIDTH;
	bound.h = NOTORBANGER_HEIGHT;
	/*if (this->state != JUMP)
	{
		bound.vx = 0;
		bound.vy = 0;
	}
	else
	{*/
		bound.vx = dx;
		bound.vy = dy;
	//}
	return bound;
}

void NotorBanger::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case RUN:
		break;
	case JUMP:	
		vy = NOTORBANGER_VY;
		if (direction == RIGHT)
			vx = -NOTORBANGER_VX;
		else
		{
			vx = NOTORBANGER_VX;
		}

		time_begin_jump = GetTickCount();
		this->distance_has_jumped_y = 0;
		this->distance_has_jumped_x = 0;
		break;

	case SHOOT60:
	case SHOOT90:
		vx = 0;
		vy = -NOTORBANGER_VY;
		time_begin_shot = GetTickCount();
		break;
	case UPTHEGUN60:
	case UPTHEGUN90:
	case STAND:
		vx = 0;
		vy = -NOTORBANGER_VY;
		break;
	default:
		break;
	}
}

void NotorBanger::SetDirection(Direction d)
{
	this->direction = d;

}

void NotorBanger::ReSet()
{
	this->active = false;
	this->count_number_shots = 0;
	this->shot60 = false;
	this->shot90 = false;
	this->uped_the_gun60 = false;
	this->uped_the_gun90 = false;
	this->jump = false;
	this->SetState(STAND);
}
