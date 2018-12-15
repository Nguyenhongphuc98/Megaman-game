#include"Shurikein.h"

Shurikein* Shurikein::instance;

Shurikein::Shurikein()
{
	x = 2499*G_Scale.x;
	y = (883+G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;
	animation_loop_rotate = 0;

	this->start_x = x;
	this->start_y = y;
	this->count_run_horizontal = 0;
	this->current_action = RunHorizontal;
	this->actived = false;
	this->hitpoints = SHURIKEIN_MAX_HP;

	this->SetState(APPEAR);
	this->nameObject = SHURIKEIN;
	LoadResource();
}

Shurikein::Shurikein(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{
	animation_loop_rotate = 0;
	this->start_x = x;
	this->start_y = y;
	this->count_run_horizontal = 0;
	this->current_action = RunHorizontal;
	this->actived = false;
	this->hitpoints = SHURIKEIN_MAX_HP;
	
	this->nameObject = SHURIKEIN;
	LoadResource();
}

Shurikein::~Shurikein()
{
}

Shurikein * Shurikein::Instance()
{
	if (!instance)
		instance = new Shurikein();
	return instance;
}

void Shurikein::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (!this->actived || this->destroyed)
		return;

	if (this->state == DESTROY&&this->animation->listSprite[DESTROY]->IsFinalFrame())
	{
		this->destroyed = true;
		DoorRightShurikein::Instance()->SetAllowOpen(true);
		return;
	}

	

	//========het mau détroying=============================
	if (this->hitpoints <= 0  )
	{
		if (this->state != DESTROY)
		{
			this->SetState(DESTROY);
			this->time_create_fire_start = GetTickCount();
		}

		if ((GetTickCount() - this->time_create_fire_start) > 300)
		{
			int temp = rand() % 100;
			Bullet* tempBullet = new NotorbangerBullet(this->x - 50+ temp, this->y, RIGHT, 0);
			tempBullet->SetState(DESTROYBULLET);
			
			/*temp = rand() % 100;
			Bullet* tempBullet1 = new NotorbangerBullet(this->x - 50 + temp, this->y + 50, RIGHT, 0);
			tempBullet1->SetState(DESTROYBULLET);

			temp = rand() % 100;
			Bullet* tempBullet2 = new NotorbangerBullet(this->x - 50 + temp, this->y, RIGHT, 0);
			tempBullet2->SetState(DESTROYBULLET);*/

			WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
			/*WeaponSystem::Instance()->AddBulletEnemy(tempBullet2);
			WeaponSystem::Instance()->AddBulletEnemy(tempBullet1);*/

			this->time_create_fire_start = GetTickCount();
		}
		
		return;
	}

	//===============gan het mau trnag thai nhay lo xo===================
	if (this->hitpoints < SHURIKEIN_MAX_HP / 3 &&this->state!=JUMP)
	{
		this->SetState(JUMP);
		vx = SHURIKEIN_JUMP_VX;
		vy = SHURIKEIN_JUMP_VY;
	}

	if (this->state == JUMP) {

		if (this->y > (this->start_y + 100))
			vy = -SHURIKEIN_JUMP_VY;

		if (this->y < this->start_y)
			vy = SHURIKEIN_JUMP_VY;

		if (this->x <( this->start_x-375))
			vx = SHURIKEIN_JUMP_VX;

		if (this->x > (this->start_x +70))
			vx = -SHURIKEIN_JUMP_VX;
		
		Object::Update(dt, List_object_can_col);
		this->x += dx;
		this->y += dy;

		return;
	}
	

	if (this->current_action == StandRotate)
	{
		if (GetTickCount() - this->time_start_stand > 2000)
		{
			this->current_action = RunAround;
			this->SetState(ROTATELEFT);
		}
		else return;
	}
	
	
	//================first state===============================
	if (this->state == APPEAR)
	{
		if (this->animation->listSprite[this->state]->IsFinalFrame())
		{
			this->state = STAND;
			this->time_start_stand = GetTickCount();
		}

		return;
	}

	//================second state===============================
	if (this->state == STAND)
	{
		if (GetTickCount() - this->time_start_stand > 3000)
		{
			this->SetState(ROTATELEFT);
			this->current_action = RunHorizontal;
		}
			
		else
			return;
	}

	//==================run horizontal or jump wall======================
	if (this->state == ROTATELEFT)
	{
		//=============jump wall==============================
		if (this->current_action == JumpWall  )
		{
			//=============collision left wall==============================
			if (abs(this->x - this->start_x) > 375)
			{
				this->vy = -SHURIKEIN_JUMP_WALL_VY;
				this->SetState(ROTATERIGHT);
			}
			else
			//=============collision mid way==============================
			if(abs(this->x - this->start_x) > 200)
			this->vy = SHURIKEIN_JUMP_WALL_VY;
		}

		//=============collision left wall==============================
		if (abs(this->x - this->start_x) > 375)
		{
			if (this->current_action == RunHorizontal)
			{
				this->SetState(ROTATERIGHT);
				this->count_run_horizontal++;
			}
			else
				if(this->current_action==RunAround)
			{
					//=====move to up==========
					this->vy = SHURIKEIN_JUMP_WALL_VY;
					this->vx = 0;
			}
		}
		
		//=============collision top wall==============================
		if (abs(this->y - this->start_y) > 270) //just runaround have y>270
		{
			//========move to right==========
			this->vx = SHURIKEIN_RUN_VX;
			this->vy = 0;
		}

		//=============collision right wall==============================
		if (this->current_action==RunAround&& this->x > (this->start_x + 73))
		{
			this->vx = 0;
			this->vy = -SHURIKEIN_JUMP_WALL_VY;
		}

		//=============collision ground ==============================
		if (this->current_action == RunAround && this->y<(this->start_y-10))
		{
			//===========MAKE IT TO NEXT LOOP========================
			/*this->vx = 0;
			this->vy = 0;
			this->state = ROTATELEFT;
			this->time_start_stand = GetTickCount();
			this->current_action = StandRotate;*/
			this->SetState(ROTATELEFT);
			this->current_action = RunHorizontal;

			//==============location y make loop, miss it to create other loop==============
			this->y += 11;
		}
	}

	if (this->state == ROTATERIGHT)
	{
		//=============collision right wall==============================
		if (this->current_action == RunHorizontal&&this->x > (this->start_x + 70))
		{
			this->SetState(ROTATELEFT);
			if (this->count_run_horizontal % 2 == 0)
			{
				//this->state = ROTATELEFT;
				this->current_action = JumpWall;
			}
		}
		else
		{
			if (this->current_action == JumpWall)
			{
				//=============collision right wall==============================
				if (this->x > (this->start_x + 70))
				{
					vx = vy = 0;
					this->state = ROTATELEFT;
					this->current_action = StandRotate;
					this->time_start_stand = GetTickCount();
				}
				else
					//=============mid========================
				if (this->x > (this->start_x - 200))
					this->vy = 0;		
			}
				
		}
			
	}

	Object::Update(dt,List_object_can_col);
	x += dx;
	y += dy;


}

void Shurikein::Render()
{
	if (!this->actived||destroyed)
		return;

	ActionObject::Render();
}

void Shurikein::LoadResource()
{
	//MyTexture* texture_appear = new MyTexture((char*)"SourceImage\\ShurikeinAppear.png", D3DCOLOR_XRGB(255, 255, 255));
	//vector<RECT*> list_source_rect_appear1 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\ShurikeinAppear.txt");

	MyTexture* texture_appear = TXT::Instance()->GetTexture(TSHURIKEINAPPEAR);
	vector<RECT*> list_source_rect_appear = TXT::Instance()->GetListSourceRect(SSHURIKEINRAPPEAR);
	animation->listSprite[State::APPEAR] = new Sprite(texture_appear, list_source_rect_appear, 2);

	//MyTexture* texture_rotate_left = new MyTexture((char*)"SourceImage\\shurikein_rotate_left.png", D3DCOLOR_XRGB(255, 255, 255));
	//vector<RECT*> list_source_rect_rotate_left1 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\shurikein_rotate_left.txt");

	MyTexture* texture_rotate_left = TXT::Instance()->GetTexture(TSHURIKEINROTATELEFT);
	vector<RECT*> list_source_rect_rotate_left = TXT::Instance()->GetListSourceRect(SSHURIKEINROTATERIGHT);
	animation->listSprite[State::ROTATELEFT] = new Sprite(texture_rotate_left, list_source_rect_rotate_left, 1);

	//MyTexture* texture_rotate_right = new MyTexture((char*)"SourceImage\\shurikein_rotate_right.png", D3DCOLOR_XRGB(255, 255, 255));
	vector<RECT*> list_source_rect_rotate_right = TXT::Instance()->GetListSourceRect(SSHURIKEINROTATELEFT);
	animation->listSprite[State::ROTATERIGHT] = new Sprite(texture_rotate_left, list_source_rect_rotate_right, 1);

	RECT* rStand = new RECT();
	rStand->top = 14;
	rStand->bottom = 65;
	rStand->left = 496;
	rStand->right = 545;

	vector<RECT*> list_source_rect_stand;
	list_source_rect_stand.push_back(rStand);
	animation->listSprite[State::STAND] = new Sprite(texture_rotate_left, list_source_rect_stand, 1);

	//================jump and destroy============================
	MyTexture* texture_jum_destroy = TXT::Instance()->GetTexture(TSHURIKEINJUMPANDDIE);

	vector<RECT*> list_source_rect_jump = TXT::Instance()->GetListSourceRect(SSHURIKEINJUMP);
	animation->listSprite[State::JUMP] = new Sprite(texture_jum_destroy, list_source_rect_jump, 1);

	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SSHURIKEINDESTROY);
	animation->listSprite[State::DESTROY] = new Sprite(texture_jum_destroy, list_source_rect_destroy, 4);
}

BoundingBox Shurikein::GetBoundingBox()
{
	BoundingBox bound;

	if (this->actived)
	{
		bound.x = x - SHURIKEIN_WIDTH / 2;
		bound.y = y - SHURIKEIN_HEIGHT / 2;
		bound.w = SHURIKEIN_WIDTH;
		bound.h = SHURIKEIN_HEIGHT;
		bound.vx = dx;
		bound.vy = dy;
	}
	else
	{
		bound.x = x - SHURIKEIN_WIDTH / 2;
		bound.y = y - 800;
		bound.w = SHURIKEIN_WIDTH;
		bound.h = SHURIKEIN_HEIGHT;
		bound.vx = dx;
		bound.vy = dy;
	}
	
	return bound;
}

void Shurikein::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case APPEAR:
		vx = vy = 0;
		break;
	case ROTATERIGHT:
		vx = SHURIKEIN_RUN_VX;
		break;
	case ROTATELEFT:
		vy = 0;
		vx = -SHURIKEIN_RUN_VX;
		break;
	default:
		break;
	}
}

void Shurikein::SetDirection(Direction d)
{
	this->direction = d;
}
