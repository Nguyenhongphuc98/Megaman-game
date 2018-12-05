#include"Megaman.h"
Megaman* Megaman::instance;

Megaman::Megaman()
{
	x = 100;
	y = 7200*G_Scale.y;
	this->isGround = false;
	this->isAllowClimbWall = false;
	this->charging = false;
	this->time_start_press_A = 0;

	animation_charging = new Animation();
	LoadResource();
}

Megaman::~Megaman()
{
}

Megaman * Megaman::Instance()
{
	if (!instance)
		instance = new Megaman();
	return instance;
}

void Megaman::Update(DWORD dt, vector<Object*> *List_object_can_col)
{
	

	vy += MEGAMAN_GRAVITY*dt;
	Object::Update(dt, List_object_can_col);
	//x += dx;
	//y += dy;

	//if (y > 410)
	//	y = 410;
	yPre = y;

	vector<ResultCollision> List_result_col;
	List_result_col.clear();

	for (Object* O : *List_object_can_col) {
		ResultCollision r ;
		r=Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r.isCollision)
		{
			List_result_col.push_back(r);
			if (O->GetNameObject() == LAUNCHER&&r.ny!=0)
			{
				/*vector<Object*> l;
				O->Update(dt, &l);
				this->y += 0.1*dt;*/
				O->SetState(RUN);
			}
				
		}
			
	}

	if (List_result_col.size() == 0) {
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx = 1.0f, min_ty = 1.0f;
		int nx = 0, ny = 0;

		for (int i = 0; i <List_result_col.size(); i++) {
			if (List_result_col[i].t < min_tx && List_result_col[i].nx != 0) {
				min_tx = List_result_col[i].t; nx = List_result_col[i].nx;
			}

			if (List_result_col[i].t < min_ty  && List_result_col[i].ny != 0) {
				min_ty = List_result_col[i].t; ny = List_result_col[i].ny;
			}
		}

		x += (min_tx * dx + nx * 0.4f);		
		y += (min_ty * dy + ny * 0.4f);
		if (nx != 0)
		{
			vx = 0;
			this->isAllowClimbWall = true;			
		}
		if (ny != 0)
		{
			vy = 0;
			this->isGround = true;
		}
	}

}

void Megaman::Render()
{
	

	//==============================================

	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(x, y);

	//========================================================
	//this->animation_charging->Render(CHARGINGLV1, direction, position);
	//this->animation_charging->Next(CHARGINGLV1);

	this->animation_charging->Render(CHARGINGLV2, direction, position);
	this->animation_charging->Next(CHARGINGLV2);


	/*
	if (this->state == JUMP)
	{
		if (animation->listSprite[JUMP]->GetCurrentFrame() >= 3)
		{
			animation->listSprite[JUMP]->Set_current_frame(3);
		}
	}

	if (y < yPre)
	{
		animation->listSprite[JUMP]->Set_current_frame(4);
		animation->Render(JUMP, direction, position);
		return;
	}*/



	//=======================STAND JUMP=========================
	/*if (this->state == STANDJUMP)
	{

	}*/

	if (this->state == JUMPWALL && this->isAllowClimbWall)
	{
		if(this->animation->listSprite[state]->IsFinalFrame())
		this->animation->listSprite[state]->Set_current_frame(3);
	}
	
	animation->Render(state, direction, position);

	if (this->state == RUN)
	{
		if (this->animation->listSprite[state]->IsFinalFrame())
			this->animation->listSprite[state]->Set_current_frame(5);
	}

	
	
	if (state == DASH && animation->listSprite[DASH]->GetCurrentFrame() == 1)
		return;
	if (state == DASHSHOOT && animation->listSprite[DASHSHOOT]->GetCurrentFrame() == 1)
		return;
	animation->Next(state);
}

void Megaman::LoadResource()
{
	//=====================Load Status Stand=============================
	

	//vector<RECT*> list_source_rect = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanstand.txt");
	//MyTexture* texture_stand = new MyTexture((char*)"SourceImage\\megamanstand.png", D3DCOLOR_XRGB(50, 96, 166));

	MyTexture* texture = TXT::Instance()->GetTexture(TMEGAMANSTAGE);

	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SMEGAMANSTAND);
	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect, 4);

	vector<RECT*> list_source_rect_stand_talk = TXT::Instance()->GetListSourceRect(SMEGAMANSTANDTALK);
	animation->listSprite[State::STANDTALK] = new Sprite(texture, list_source_rect_stand_talk, 2);

	//=====================Load Status Run=============================


	//vector<RECT*> list_source_rect_run = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanrun.txt");
	//MyTexture* texture_run = new MyTexture((char*)"SourceImage\\megamanrun.png", D3DCOLOR_XRGB(50, 96, 166));

	vector<RECT*> list_source_rect_run = TXT::Instance()->GetListSourceRect(SMEGAMANRUN);
	//MyTexture* texture_run = TXT::Instance()->GetTexture(TMEGAMANRUN);
	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_run, 1);

	vector<RECT*> list_source_rect_run_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANRUNSHOOT);
	//MyTexture* texture_run = TXT::Instance()->GetTexture(TMEGAMANRUN);
	animation->listSprite[State::RUNSHOOT] = new Sprite(texture, list_source_rect_run_shoot, 1);

	//=====================Load Status Jump=============================

	//vector<RECT*> list_source_rect_jump = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanjump.txt");
	//MyTexture* texture_jump = new MyTexture((char*)"SourceImage\\megamanjump.png", D3DCOLOR_XRGB(50, 96, 166));

	vector<RECT*> list_source_rect_jump = TXT::Instance()->GetListSourceRect(SMEGAMANJUMP);
	//MyTexture* texture_jump = TXT::Instance()->GetTexture(TMEGAMANJUMP);
	animation->listSprite[State::STANDJUMP] = new Sprite(texture, list_source_rect_jump, 1);
	animation->listSprite[State::RUNJUMP] = new Sprite(texture, list_source_rect_jump, 1);

	vector<RECT*> list_source_rect_jump_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANJUMPSHOOT);
	animation->listSprite[State::JUMPSHOOT] = new Sprite(texture, list_source_rect_jump_shoot, 3);

	vector<RECT*> list_source_rect_jump_wall = TXT::Instance()->GetListSourceRect(SMEGAMANJUMPWALL);
	animation->listSprite[State::JUMPWALL] = new Sprite(texture, list_source_rect_jump_wall, 1);

	//=====================Load Status Shoot=============================
	

	//vector<RECT*> list_source_rect_runshoot = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanrunshoot.txt");
	//MyTexture* texture_runshoot = new MyTexture((char*)"SourceImage\\megamanrunshoot.png", D3DCOLOR_XRGB(50, 96, 166));

	vector<RECT*> list_source_rect_stand_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANSTANDSHOOT);
	//MyTexture* texture_runshoot = TXT::Instance()->GetTexture(TMEGAMANRUN);
	animation->listSprite[State::STANDSHOOT] = new Sprite(texture, list_source_rect_stand_shoot, 1);

	//=====================Load Status Climb=============================
	//vector<RECT*> list_source_rect_climb = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanClimb.txt");
	//MyTexture* texture_climb = new MyTexture((char*)"SourceImage\\megamanClimb.png", D3DCOLOR_XRGB(50, 96, 166));

	//vector<RECT*> list_source_rect_climb = TXT::Instance()->GetListSourceRect(SMEGAMANCLIMB);
	//MyTexture* texture_climb = TXT::Instance()->GetTexture(TMEGAMANCLIMB);
	//animation->listSprite[State::CLIMB] = new Sprite(texture_climb, list_source_rect_climb, 1);
	
	//=====================Load Status Dash=============================
	//vector<RECT*> list_source_rect_dash = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanDash.txt");
	//MyTexture* texture_dash = new MyTexture((char*)"SourceImage\\megamanDash.png", D3DCOLOR_XRGB(50, 96, 166));

	vector<RECT*> list_source_rect_dash = TXT::Instance()->GetListSourceRect(SMEGAMANDASH);
	//MyTexture* texture_dash = TXT::Instance()->GetTexture(TMEGAMANDASH);
	animation->listSprite[State::DASH] = new Sprite(texture, list_source_rect_dash, 1);

	vector<RECT*> list_source_rect_dash_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANDASHSHOOT);
	//MyTexture* texture_dash = TXT::Instance()->GetTexture(TMEGAMANDASH);
	animation->listSprite[State::DASHSHOOT] = new Sprite(texture, list_source_rect_dash_shoot, 1);

	//=====================Load Status Injured=============================

	vector<RECT*> list_source_rect_injured = TXT::Instance()->GetListSourceRect(SMEGAMANINJURED);
	animation->listSprite[State::INJURED] = new Sprite(texture, list_source_rect_injured, 1);

	//=====================Load Status charging=============================

	MyTexture* texture_effect = TXT::Instance()->GetTexture(TEFFECT);
	vector<RECT*> list_source_rect_charinglv1 = TXT::Instance()->GetListSourceRect(SCHARGINGLV1);
	animation_charging->listSprite[State::CHARGINGLV1] = new Sprite(texture_effect, list_source_rect_charinglv1, 1);

	vector<RECT*> list_source_rect_charinglv2 = TXT::Instance()->GetListSourceRect(SCHARGINGLV2);
	animation_charging->listSprite[State::CHARGINGLV2] = new Sprite(texture_effect, list_source_rect_charinglv2, 1);

}

BoundingBox Megaman::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x- MEGAMAN_WIDTH/2;
	bound.y = y- MEGAMAN_HEIGHT/2;
	bound.w = MEGAMAN_WIDTH;
	bound.h = MEGAMAN_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void Megaman::SetState(State new_state)
{
	if (this->state == new_state)
		return;

	this->animation->Refresh(this->state);
	
	switch (new_state)
	{
	case RUN:
		vx = (this->direction==RIGHT)? MEGAMAN_WALK_SPEED:-MEGAMAN_WALK_SPEED;
		this->state = RUN;
		break;

	case RUNSHOOT:
		vx = (this->direction == RIGHT) ? MEGAMAN_WALK_SPEED : -MEGAMAN_WALK_SPEED;
		this->state = RUNSHOOT;
		this->shoot_state_old = this->state;
		break;

	case RUNJUMP:
		vx = (this->direction == RIGHT) ? MEGAMAN_WALK_SPEED : -MEGAMAN_WALK_SPEED;
		vy = MEGAMAN_RUN_JUMP_SPEED;
		this->state = RUNJUMP;
		this->isGround = false;
		break;

	case STAND:
		this->state = STAND;
		vx = vy = 0;
		break;

	case STANDJUMP:
		this->state = STANDJUMP;
		vx = 0;
		vy = MEGAMAN_STAND_JUMP_SPEED;
		this->isGround = false;
		break;

	case STANDTALK:
		this->state = STANDTALK;
		break;

	case JUMPSHOOT:
		this->state = JUMPSHOOT;
		this->isGround = false;
		this->shoot_state_old = this->state;
		break;

	case STANDSHOOT:
		this->state = STANDSHOOT;		
		this->shoot_state_old = this->state;
		break;

	case DASH:
		vx = (this->direction==RIGHT)? MEGAMAN_DASH_SPEED:-MEGAMAN_DASH_SPEED;
		this->state = DASH;
		break;

	case INJURED:
		this->state = INJURED;
		break;

	default:
		this->state = new_state;
		vx = vy = 0;
		break;
	}


}

void Megaman::SetDirection(Direction d)
{
	this->direction = d;
}

bool Megaman::SetTimeStartPressA()
{		
	if (!this->time_start_press_A)
	{
		//this->SetState(SHOOT);
		this->time_start_press_A = GetTickCount();
		return true;
	}
	else
		if (this->GetTimePressA() > 400 && !charging)
		{
			this->SetState(RUN);
			charging = true;
		}
			
	return false;
}

void Megaman::ResetTimeStartPressA()
{
	this->time_start_press_A = 0;
	this->charging = false;
}

State Megaman::GetState()
{
	return state;
}

State Megaman::GetNewState(State currentState, EControler controler)
{
	State new_state = currentState;
	int temp;

	switch (currentState)
	{
	case RUN:
		switch (controler)
		{
		case NoneControl: new_state = STAND;break;
		case LeftControl:break;
		case RightControl:break;
		case ShootControl:new_state = RUNSHOOT;break;
		case JumpControl:new_state = RUNJUMP;break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case RUNSHOOT:
		if (!this->animation->listSprite[RUNSHOOT]->IsFinalFrame())
			return new_state;

		switch (controler)
		{
		case NoneControl:  new_state = STAND; break;
		case LeftControl:new_state = STAND; break;
		case RightControl: new_state = STAND; break;
		case ShootControl: break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case RUNJUMP:
		/*if (!this->animation->listSprite[RUNJUMP]->IsFinalFrame())
			return new_state;*/

		switch (controler)
		{
		case NoneControl:if (this->IsCanJump()) new_state = STAND; break;
		case LeftControl:
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;	
			break;
		case RightControl: 
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			break;
		case ShootControl:new_state = JUMPSHOOT; break;
		case JumpControl: break;
		case DashControl: break;
		}
		break;

	case JUMPWALL:
		switch (controler)
		{
		case NoneControl:
			if (this->isGround) new_state = STAND; break;
		case LeftControl:
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			break;
		case RightControl:
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			break;
		case ShootControl: break;
		case JumpControl: break;
		case DashControl: break;
		}
		break;

	case JUMPSHOOT:
		/*if (!this->animation->listSprite[RUNJUMP]->IsFinalFrame())
			return STAND;*/

		switch (controler)
		{
		case NoneControl:
			if (this->IsCanJump()) new_state = STAND; break;
		case LeftControl: break;
		case RightControl: break;
		case ShootControl: break;
		case JumpControl: break;
		case DashControl: break;
		}
		break;

	case STAND:
		switch (controler)
		{
		case NoneControl: break;
		case LeftControl:new_state = RUN; break;
		case RightControl:new_state = RUN; break;
		case ShootControl:new_state = STANDSHOOT; break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case STANDTALK:
		switch (controler)
		{
		case NoneControl: break;
		case LeftControl:new_state = RUN; break;
		case RightControl:new_state = RUN; break;
		case ShootControl:new_state = STANDSHOOT; break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case STANDJUMP:
		/*if (!this->animation->listSprite[STANDJUMP]->IsFinalFrame())
			return new_state;*/
		switch (controler)
		{
		case NoneControl:if (this->IsCanJump()) new_state = STAND; break;
		case LeftControl:
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			break;
		case RightControl:
			if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			break;
		case ShootControl:  new_state = JUMPSHOOT; break;
		case JumpControl: break;
		case DashControl: break;
		}

		/*switch (controler)
		{
		case NoneControl: if (this->IsCanJump()) new_state = STAND; break;
		case LeftControl: 
			if (this->isGround)
				new_state = RUN; break;
		case RightControl: if (this->isGround) new_state = RUN; break;
		case ShootControl:  new_state = JUMPSHOOT; break;
		case JumpControl: break;
		case DashControl: break;
		}*/
		break;

	case STANDSHOOT:
		if (!this->animation->listSprite[STANDSHOOT]->IsFinalFrame())
			return new_state;
		switch (controler)
		{
		case NoneControl: new_state = STAND; break;
		case LeftControl: break;
		case RightControl: break;
		case ShootControl: break;
		case JumpControl:new_state = JUMPSHOOT; break;
		case DashControl:new_state = DASHSHOOT; break;
		}
		break;

	case DASH:
		switch (controler)
		{
		case NoneControl:new_state = STAND; break;
		case LeftControl: break;
		case RightControl: break;
		case ShootControl:new_state = DASHSHOOT; break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl: break;
		}
		break;

	case DASHSHOOT:
		switch (controler)
		{
		case NoneControl:new_state = STAND; break;
		case LeftControl: break;
		case RightControl: break;
		case ShootControl: break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case INJURED:
		break;

	default:
		break;
	}

	return new_state;
}

Direction Megaman::GetDirection()
{
	return direction;
}

float Megaman::GetTimePressA()
{
	return GetTickCount()-time_start_press_A;
}

bool Megaman::IsFinishUpGun()
{
	if (this->state != SHOOT)
		return true;
	return this->animation->listSprite[SHOOT]->IsFinalFrame();
}

bool Megaman::IsFinshAction()
{
	return this->animation->listSprite[state]->IsFinalFrame();
}
