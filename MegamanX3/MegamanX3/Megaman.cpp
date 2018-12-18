#include"Megaman.h"
Megaman* Megaman::instance;

Megaman::Megaman()
{
	////============subboss box=====================
	//x = 4900*G_Scale.x;
	//y = (932 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;

	////============start=============================
	//x = 200 * G_Scale.x;
	//y = (1200 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;

	////============meet shurikein=============================
	//x = 2176 * G_Scale.x;
	//y = (917 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;

	//============meet blast hornet=============================
	x = 5520 * G_Scale.x;
	y = (1000 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;


	this->isGround = false;
	this->isAllowClimbWall = false;
	this->charging = false;
	this->isAllowDash = true;
	this->isAllowJump = true;
	this->time_start_press_A = 0;
	this->xStartDash = 0;
	this->hitpoints = MEGAMAN_MAX_HP;
	this->hurting = false;
	this->bounsed = false;
	this->autoMoving = false;
	this->state = FREEFALL;

	this->autoMoving = true;
	this->direction = RIGHT;

	animation_charging = new Animation();
	animation_lifebar = new Animation();
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

void Megaman::Update(DWORD dt, vector<Object*> *List__virtual_object_can_col)
{
	//===============make appear sub-boss and move camera to lock==============
	if (this->x > 4900 * G_Scale.x&&this->x < 4902 * G_Scale.x)
	{
		SubBossCarry::Instance()->SetActived(true);
		Camera::Instance()->SetAutoMovingX(true);
	}
		
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return;

	if (this->hurting&&GetTickCount()-this->time_start_huring>MEGAMAN_TIME_HURTING)
	{
		this->hurting = false;
	}

	vy += MEGAMAN_GRAVITY*dt;

	// =====change mode camera when met shurikein==========
	Object::Update(dt, List__virtual_object_can_col);

	/*if (this->x > 2300 * G_Scale.x&&this->x < 2323 * G_Scale.x)
	{
		this->x += 8;
		Camera::Instance()->SetMovingX(true);
		return;
	}*/


	yPre = y;

	vector<ResultCollision> List_result_col;
	List_result_col.clear();

	for (Object* O : *List__virtual_object_can_col) {

		if (O->GetNameObject()==DOOR)
		{
			MyDebugOUT("-");
		}
		ResultCollision r ;
		r=Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r.isCollision)
		{
			List_result_col.push_back(r);
			if (O->GetNameObject() == LAUNCHER&&r.ny!=0)
			{
				//======active laucher============
				O->SetState(RUN);
			}
				
			if (O->GetNameObject() == DOOR)
			{
				((ActionObject *) O)->SetActived(true);
				//this->autoMoving = true;
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

		x += (min_tx * dx + nx * 2.0f);		
		y += (min_ty * dy + ny * 0.3f);
		if (nx != 0)
		{
			//================================================================
			vx = (vx>0)?-0.05:0.05;
			this->isAllowClimbWall = true;		
			//this->SetState(JUMPWALL);
		}
		if (ny != 0)
		{
			vy = 0;
			this->isGround = true;
		}
	}

}

void Megaman::ProcessCollisionBullet(list<Bullet*> List__bullet_enemy)
{
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return;

	for (Bullet* O : List__bullet_enemy) {
		bool r;
		r = Collision::Instance()->CollisionAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r)
		{
			if (!O->IsDestroying()&&!this->hurting)
			{
				this->hurting = true;
				this->time_start_huring = GetTickCount();

				this->hitpoints -= O->GetDamege();
				this->SetState(INJURED);
				O->SetState(DESTROYBULLET);
				O->SetDestroying(true);
			}
		}
	}
}

void Megaman::ProcessCollisionEnemy(vector<Object*> List_enemy)
{
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return;

	

	for (Object* O : List_enemy) {

		if (((ActionObject*)O)->IsDestroy())
			continue;

		bool r;
		r = Collision::Instance()->CollisionAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r)
		{
			//if (O->GetNameObject() == DOOR)
			//{
			//	((ActionObject *)O)->SetActived(true);
			//	//this->autoMoving = true;
			//	return;
			//}

			if (!this->hurting)
			{
				this->hurting = true;
				this->time_start_huring = GetTickCount();

				this->hitpoints -= ((ActionObject*)O)->GetDamage();
				this->SetState(INJURED);
			}
		}
	}
}

void Megaman::Render()
{
	
	if (this->hitpoints < 0)
		return;

	//============life-bar==================================
	this->animation_lifebar->listSprite[STAND]->Set_current_frame(this->hitpoints);
	this->animation_lifebar->Render(STAND, RIGHT, D3DXVECTOR2(30, 100));
	
	//============nhap nhay khi khong khong the bi thuong==============

	if (this->hurting&&this->state != INJURED)
	{
		int x = rand();
		if (x % 2 == 0)
			return;
	}

	//==============================================

	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(x, y);

	//========================================================
	//this->animation_charging->Render(CHARGINGLV1, direction, position);
	//this->animation_charging->Next(CHARGINGLV1);


	//======== choose render charing lv ==============
	if (this->charging)
	{
		if (this->GetTimePressA() > 1300)
		{
			this->animation_charging->Render(CHARGINGLV2, direction, position);
			this->animation_charging->Next(CHARGINGLV2);
		}
		else
		{
			if (this->GetTimePressA() > 400)
			{
				this->animation_charging->Render(CHARGINGLV1, direction, position);
				this->animation_charging->Next(CHARGINGLV1);
			}
		}

	}
	
	//================== STAND JUMP=============================

	if (this->state == STANDJUMP)
	{
		if (this->GetDistanceJump() > MEGAMAN_DISTANCE_ALLOW_BOUNS+20)
			this->animation->listSprite[this->state]->Set_current_frame(2);
	}

	//================== JUMP -USING WHEN FREE FALL============

	if (this->state == FREEFALL)
	{
		this->animation->listSprite[this->state]->Set_current_frame(3);
	}



	//=======================JUMP WALL=========================

	if (this->state == JUMPWALL && this->isAllowClimbWall)
	{
		//if(this->animation->listSprite[state]->GetCurrentFrame()<=1)
		//this->animation->listSprite[state]->Set_current_frame(0);
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
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return;

	animation->Next(state);
}

void Megaman::LoadResource()
{
	//=====================Load Status Stand=============================
	
	MyTexture* texture = TXT::Instance()->GetTexture(TMEGAMANSTAGE);

	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SMEGAMANSTAND);
	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect, 4);

	vector<RECT*> list_source_rect_stand_talk = TXT::Instance()->GetListSourceRect(SMEGAMANSTANDTALK);
	animation->listSprite[State::STANDTALK] = new Sprite(texture, list_source_rect_stand_talk, 2);

	//=====================Load Status Run=============================

	vector<RECT*> list_source_rect_run = TXT::Instance()->GetListSourceRect(SMEGAMANRUN);
	animation->listSprite[State::RUN] = new Sprite(texture, list_source_rect_run, 2);

	vector<RECT*> list_source_rect_run_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANRUNSHOOT);
	animation->listSprite[State::RUNSHOOT] = new Sprite(texture, list_source_rect_run_shoot, 2);

	//=====================Load Status Jump=============================

	vector<RECT*> list_source_rect_jump = TXT::Instance()->GetListSourceRect(SMEGAMANJUMP);	
	animation->listSprite[State::STANDJUMP] = new Sprite(texture, list_source_rect_jump, 3);
	animation->listSprite[State::FREEFALL] = new Sprite(texture, list_source_rect_jump, 1);

	vector<RECT*> list_source_rect_jump_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANJUMPSHOOT);
	animation->listSprite[State::JUMPSHOOT] = new Sprite(texture, list_source_rect_jump_shoot, 3);

	vector<RECT*> list_source_rect_jump_wall = TXT::Instance()->GetListSourceRect(SMEGAMANJUMPWALL);
	animation->listSprite[State::JUMPWALL] = new Sprite(texture, list_source_rect_jump_wall, 1);

	//=====================Load Status Shoot=============================
	
	vector<RECT*> list_source_rect_stand_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANSTANDSHOOT);
	animation->listSprite[State::STANDSHOOT] = new Sprite(texture, list_source_rect_stand_shoot, 1);

	//=====================Load Status Climb=============================
	//vector<RECT*> list_source_rect_climb = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\megamanClimb.txt");
	//MyTexture* texture_climb = new MyTexture((char*)"SourceImage\\megamanClimb.png", D3DCOLOR_XRGB(50, 96, 166));

	//vector<RECT*> list_source_rect_climb = TXT::Instance()->GetListSourceRect(SMEGAMANCLIMB);
	//MyTexture* texture_climb = TXT::Instance()->GetTexture(TMEGAMANCLIMB);
	//animation->listSprite[State::CLIMB] = new Sprite(texture_climb, list_source_rect_climb, 1);
	
	//=====================Load Status Dash=============================

	vector<RECT*> list_source_rect_dash = TXT::Instance()->GetListSourceRect(SMEGAMANDASH);
	animation->listSprite[State::DASH] = new Sprite(texture, list_source_rect_dash, 1);

	vector<RECT*> list_source_rect_dash_shoot = TXT::Instance()->GetListSourceRect(SMEGAMANDASHSHOOT);
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

	//=====================Load lifebar=============================

	vector<RECT*> list_source_rect_lifebar = TXT::Instance()->GetListSourceRect(SLIFEBAR);
	animation_lifebar->listSprite[State::STAND] = new Sprite(texture, list_source_rect_lifebar, 1);

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
	if(this->state!=new_state)
		this->animation->Refresh(this->state);

	switch (new_state)
	{
	case RUN:
		vx = (this->direction==RIGHT)? MEGAMAN_WALK_SPEED:-MEGAMAN_WALK_SPEED;
		this->state = RUN;
		MyDebugOUT("runing \n");
		break;

	case RUNSHOOT:
		vx = (this->direction == RIGHT) ? MEGAMAN_WALK_SPEED : -MEGAMAN_WALK_SPEED;
		this->state = RUNSHOOT;
		MyDebugOUT("run shoot \n");
		break;

	case FREEFALL:
		MyDebugOUT("Free fall \n");
		//vx = (this->direction == RIGHT) ? MEGAMAN_WALK_SPEED : -MEGAMAN_WALK_SPEED;
		/*if (this->isGround)
		{
			MyDebugOUT(" start run jump \n");
			vy = MEGAMAN_RUN_JUMP_SPEED;
		}*/
		this->state = FREEFALL;
		this->isGround = false;
		
		break;

	case STAND:
		MyDebugOUT("stand \n");
		//if (this->state == STANDJUMP || this->state == FREEFALL)
		//	this->animation->Refresh(this->state);
		this->state = STAND;
		vx = 0;
		//vy = 0;
		break;

	case STANDJUMP:
		this->state = STANDJUMP;
		//vx = 0;
		MyDebugOUT("stand jump \n");
		if (this->isGround)
		{
			MyDebugOUT("start stand jump \n");
			vy = MEGAMAN_STAND_JUMP_SPEED;
		}	

		if(this->isAllowClimbWall)
		{
			MyDebugOUT("start jump wall\n");
			vy = MEGAMAN_JUMP_WALL_SPEED;
			isAllowClimbWall = false;
		}
		this->isGround = false;
		
		break;

	case STANDTALK:
		this->state = STANDTALK;

		break;

	case JUMPSHOOT:
		this->state = JUMPSHOOT;
		this->isGround = false;
		MyDebugOUT("jump shoot\n");
		
		break;

	case JUMPWALL:
		MyDebugOUT("jump wall \n");
		this->state = JUMPWALL;
		if (this->isAllowClimbWall)
		{
			MyDebugOUT("start jump wall \n");
			vy = MEGAMAN_JUMP_WALL_SPEED;
		}
		
		this->isAllowClimbWall = false;
		break;

	case STANDSHOOT:
		this->state = STANDSHOOT;	
		vx = 0;
		MyDebugOUT("stand  shoot\n");
		break;

	case DASH:
		vx = (this->direction==RIGHT)? MEGAMAN_DASH_SPEED:-MEGAMAN_DASH_SPEED;
		this->state = DASH;
		if (this->isAllowDash)
		{
			this->xStartDash = x;
			this->isAllowDash = false;
		}	
		else
		if (GetDistanceDash() > MEGAMAN_DISTANCE_DASH)
		{
			this->SetState(STAND);
			xStartDash = 0;
		}
		MyDebugOUT("dash \n");
		break;

	case DASHSHOOT:
		vx = (this->direction==RIGHT)? MEGAMAN_DASH_SPEED:-MEGAMAN_DASH_SPEED;
		this->state = DASHSHOOT;

		if (this->isAllowDash)
		{
			this->xStartDash = x;
			this->isAllowDash = false;
		}

		else
			if (GetDistanceDash() > MEGAMAN_DISTANCE_DASH)
			{
				this->SetState(STAND);
				xStartDash = 0;
			}
		MyDebugOUT("dash shoot \n");
		break;

	case INJURED:
		this->state = INJURED;
		vx = 0;
		vy = MEGAMAN_GRAVITY;
		break;

	default:
		this->state = new_state;
		vx = vy = 0;
		MyDebugOUT("default \n");
		break;
	}


	/*if (!this->state == new_state)
	this->animation->Refresh(this->state);*/
}

void Megaman::SetDirection(Direction d)
{
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return;

	switch (state)
	{
	case RUN:		
	case RUNSHOOT:
	case STANDJUMP:
		vx = (this->direction == RIGHT) ? MEGAMAN_WALK_SPEED : -MEGAMAN_WALK_SPEED;
		break;
	case FREEFALL:
		vx *= (this->direction == d) ? 1 : -1;
		break;
	}

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
		if (this->GetTimePressA() > MEGAMAN_TIME_NEED_TO_CHARING && !charging)
		{
			this->SetState(STAND);
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
	//==============auto moving when open door, door control===============
	if (this->autoMoving)
		return currentState;

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
		case JumpControl:
			if(isGround)
			new_state = STANDJUMP;break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case RUNSHOOT:
		/*if (!this->animation->listSprite[RUNSHOOT]->IsFinalFrame())
			return new_state;*/

		switch (controler)
		{
		case NoneControl: 
			if (!this->animation->listSprite[RUNSHOOT]->IsFinalFrame())
				return new_state;
			new_state = STAND; break;
		case LeftControl:new_state = STAND; break;
		case RightControl: new_state = STAND; break;
		case ShootControl: new_state = STANDSHOOT; break;
		case JumpControl:new_state = STANDJUMP; break;
		case DashControl:new_state = DASH; break;
		}
		break;

	case FREEFALL:
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
		/*if (!this->animation->listSprite[JUMPWALL]->IsFinalFrame())
			return JUMPWALL;*/
		switch (controler)
		{
		case NoneControl:
			//if(this->isGround)
			 new_state = STANDJUMP;
			break;
		case LeftControl:
		
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			if (this->isGround) new_state = STAND;
			break;
		case RightControl:
			//if (this->isGround) new_state = RUN;
			if (this->isAllowClimbWall) new_state = JUMPWALL;
			if (this->isGround) new_state = STAND;
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
		case LeftControl:
			if(this->IsGround())
				new_state = RUN;
			break;
		case RightControl: 
			if (this->IsGround())
				new_state = RUN;
			break;
		case ShootControl: break;
		case JumpControl: break;
		case DashControl: break;
		}
		break;

	case STAND:
		switch (controler)
		{
		case NoneControl:
			if(this->IsFreeFall())
				new_state = FREEFALL;
				break;
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
		case NoneControl:if (this->isGround) new_state = STAND; break;
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
		case DashControl: if (this->isGround) new_state = STAND; break;
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
		
		switch (controler)
		{
		case NoneControl:
			if (!this->animation->listSprite[STANDSHOOT]->IsFinalFrame())
				return new_state;
			new_state = STAND; break;
		case LeftControl: new_state = RUN; break;
		case RightControl: new_state = RUN; break;
		case ShootControl: break;
		case JumpControl:new_state = JUMPSHOOT; break;
		case DashControl:new_state = DASHSHOOT; break;
		}
		break;

	case DASH:
		switch (controler)
		{
		case NoneControl:new_state = STAND; break;
		case LeftControl:new_state = STAND; break;
		case RightControl:new_state = STAND; break;
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
		if (!this->animation->listSprite[INJURED]->IsFinalFrame())
		{
			return new_state;
		}
		//-==================================================================
		//this->hurting = false;
		switch (controler)
		{
		case NoneControl:new_state = STAND; break;
		case LeftControl:new_state = RUN; break;
		case RightControl:new_state = RUN; break;
		case ShootControl:new_state = STANDSHOOT; break;
		case JumpControl:
			if(this->IsGround())
			new_state = STANDJUMP; break;
		case DashControl:
			if (this->IsGround())
			new_state = DASH; break;
		}
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
