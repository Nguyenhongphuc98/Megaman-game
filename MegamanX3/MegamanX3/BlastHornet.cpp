#include"BlastHornet.h"
BlastHornet* BlastHornet::instance;

BlastHornet::BlastHornet()
{
	x = 7893*G_Scale.x;
	y = (307+G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y;


	this->nameObject = BLASTHORNET;
	this->SetState(REDKNEE);

	this->currentAction = Appear;
	this->actived = false;
	this->godown = true;
	this->stand = false;
	this->moving_attack_venom = false;
	this->appeared = false;
	this->allow_attack = true;

	this->count_to_attack = 0;

	for (int i = 0; i < 5; i++)
	{
		Bees[i] = new Bee();
	}
	this->honey = new Honey();

	animation_lifebar = new Animation();
	this->hitpoints = 0;
	this->time_start_change_state = GetTickCount();

	LoadResource();
}

BlastHornet::BlastHornet(int x, int y, int w, int h, Direction d) :ActionObject(x, y, w, h, d)
{


	this->nameObject = BLASTHORNET;
	LoadResource();
}

BlastHornet::~BlastHornet()
{
}

BlastHornet * BlastHornet::Instance()
{
	if (!instance)
		instance = new BlastHornet();
	return instance;
}

void BlastHornet::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (!this->actived)
		return;

	if (this->hitpoints <= 0&&appeared)
	{
		if (!destroyed)
		{
			this->state = DESTROY;
			this->destroyed = true;
			this->a = (this->y - 14965) / (this->x - 19685);
			this->b = 14965 - a * 19685;
			this->dy = -1;

			//count time to  set active =false; ( khong process nua)
			this->time_start_change_state = GetTickCount();
		}
		
		this->y += dy;
		this->x = (this->y - this->b) / this->a;

		if (this->y < GROUND + 20)
		{
			if(GetTickCount()- this->time_start_change_state>BLASTHORNET_TIME_DESTROY)
			this->actived = false;

			this->dx = this->dy = 0;
			if (rand() % 10 == 0)
			{
				Bullet* tempBullet = new NotorbangerBullet(this->x - 100 + rand() % 150, this->y - 20 + rand() % 100, RIGHT, 0);
				tempBullet->SetState(DESTROYBULLET);
				WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
			}
			
		}
		return;
	}


	//=========== to update life bar================
	if (!this->appeared)
	{
		if (this->hitpoints < BLASTHORNET_MAX_HP&&GetTickCount()>500)
		{
			this->hitpoints++;
			this->time_start_change_state = GetTickCount();
			return;
		}
			
		else
			appeared = true;
	}

	//=============UPDATE BEE=============================
	Bees[0]->Update(dt,List_object_can_col);
	Bees[1]->Update(dt, List_object_can_col);
	Bees[2]->Update(dt, List_object_can_col);
	Bees[3]->Update(dt, List_object_can_col);
	Bees[4]->Update(dt, List_object_can_col);
	
	honey->Update(dt, List_object_can_col);

	if (this->honey->IsTouchedMegaman())
		for (int i = 0; i < 5; i++)
			Bees[i]->SetFollowMegaman(true);

	switch (this->currentAction)
	{
	case Appear:
		this->direction = RIGHT;
		if (this->godown)
		{
			this->y -= 5;
			if (this->y <= GROUND)
				this->godown = false;
			return;
		}
		else
		{
			// ===========6====================
			if (this->state == CLOSEVENOM)
			{
				if (this->animation->listSprite[CLOSEVENOM]->IsFinalFrame())
				{
					this->currentAction = PrepareAttack;
					this->time_start_change_state = GetTickCount();
					this->animation->listSprite[this->state]->Reset();
					this->state = REDKNEE;
				}
				
				return;
			}

			// ===========5====================
			if (this->state == OPENINGVENOM)
			{
				if (this->animation->listSprite[OPENINGVENOM]->IsFinalFrame())
				{
					this->animation->listSprite[this->state]->Reset();
					this->state = CLOSEVENOM;
				}
				
				return;
			}

			// ===========4====================
			if (this->state == PREPAREOPENVENOM)
			{
				if (this->animation->listSprite[PREPAREOPENVENOM]->IsFinalFrame())
				{
					this->animation->listSprite[this->state]->Reset();
					this->state = OPENINGVENOM;
				}
					
				return;
			}

			// ===========3====================
			if (this->state == REDHANDS)
			{
				if (this->animation->listSprite[REDHANDS]->IsFinalFrame())
				{
					this->animation->listSprite[this->state]->Reset();
					this->state = PREPAREOPENVENOM;
				}
					
				return;
			}

			// ===========2====================
			if (this->state == HANDCARYBLADE)
			{
				if (this->animation->listSprite[HANDCARYBLADE]->IsFinalFrame())
				{
					this->animation->listSprite[this->state]->Reset();
					this->state = REDHANDS;
				}
					
				return;
			}

			// ===========1====================
			if (this->stand&&GetTickCount()-this->time_start_change_state  > 1000)
			{
				this->animation->listSprite[this->state]->Reset();
				this->SetState(HANDCARYBLADE);
				return;
			}

			if(this->y<MID)
			this->y += 3;
			else
			{
				if (!this->stand)
				{
					this->stand = true;
					this->time_start_change_state = GetTickCount();
				}
				
			}
		}
		
		break;

	case PrepareAttack:
		if (GetTickCount() - this->time_start_change_state > 1500)
		{
			this->currentAction = Attack;
			this->state = PREPAREOPENVENOM;
		}
			
		else
		{
			this->y += 1;
			this->x -= 1;
		}
		break;

	case Attack:

		if (this->state == PREPAREOPENVENOM)
		{
			if (this->animation->listSprite[PREPAREOPENVENOM]->IsFinalFrame())
			{
				this->animation->Refresh(this->state);
				this->state = OPENINGVENOM;
			}	
			return;
		}

		if (this->state == OPENINGVENOM)
		{
			if (this->animation->listSprite[OPENINGVENOM]->IsFinalFrame())
			{
				this->animation->Refresh(this->state);
				this->state = VENOMLIGHT;
			}
			return;
		}

		if (this->state == VENOMLIGHT)
		{
			if (!this->moving_attack_venom )
			{
				if (this->animation->listSprite[VENOMLIGHT]->IsFinalFrame())
				{
					this->moving_attack_venom = true;
					
					// cacula dx,dy to meet megaman
					// y= ax+b -> a, b
					//float megaman_x, megaman_y; //(x1,y1)
					//Megaman::Instance()->GetPosition(megaman_x, megaman_y);

					float megaman_x, megaman_y;
					Megaman::Instance()->GetPosition(megaman_x, megaman_y);
				//	this->direction = (this->x > megaman_x) ? RIGHT : LEFT;
					// >mid => go to mid.
					if (megaman_y > 15155)
						megaman_y = 15155;

					this->a = (this->y - megaman_y) / (this->x - megaman_x);
					this->b = megaman_y - a * megaman_x;

					//this->dx = (this->x > megaman_x) ? -BLASTHORNET_ATTACK_VX : BLASTHORNET_ATTACK_VX;
					this->dy = -BLASTHORNET_ATTACK_VY;
				}
			
			}
			else
			{
				this->animation->listSprite[VENOMLIGHT]->Set_current_frame(2);

				//tinh theo x thi neu gan nhau, x thay doi nho y se thay doi lon-> v nhanh cham that thuong
				//this->x += dx;
				//this->y = this->a * this->x + this->b;

				//y=ax+b => x= (y-b)/a
				this->y += dy;
				this->x = (this->y - this->b) / this->a;

				//re-position
				if (this->y < GROUND+20||this->x<BLASTHORNET_LEFT||this->x>BLASTHORNET_RIGHT)
				{
					this->dy = BLASTHORNET_ATTACK_VY;
					this->state = REDKNEE;
					this->direction = (this->direction==LEFT) ? RIGHT : LEFT;
					

					/*this->a = (this->y - 15155) / (this->x - 19762);
					this->b = 15155 - a * 19762;*/

					//============go to top right================
					if (this->direction == LEFT)
					{
						this->a = (this->y - 15242) / (this->x - 19685);
						this->b = 15242 - a * 19685;
					}
					else
					{
						//=========go to top left=============
						this->a = (this->y - 15243) / (this->x - 19378);
						this->b = 15243 - a * 19378;
					}
					
				}
			}
			return;
		}

		if (this->state == REDKNEE)
		{

			//tinh theo x thi neu gan nhau, x thay doi nho y se thay doi lon-> v nhanh cham that thuong
			//this->x += dx;
			//this->y = this->a * this->x + this->b;

			//y=ax+b => x= (y-b)/a
			this->y += dy;
			this->x = (this->y - this->b) / this->a;

			if (this->y > BLASTHORNET_TOP-60)
			{
				dx = 0;
				this->currentAction = GoExtremely;
				this->animation->Refresh(REDKNEE);
				this->state = HANDCARYBLADE;

				
				//==========create bee===============================================
				//===================================================================
				this->time_start_change_state = GetTickCount();
				Bees[0]->ResetBee(this->x , this->y, this->direction,0.1,0.15);
				Bees[1]->ResetBee(this->x, this->y-50, this->direction,0.15,0.15);
				Bees[2]->ResetBee(this->x, this->y-50, this->direction,0.2,0.15);
				Bees[3]->ResetBee(this->x , this->y-20, this->direction,0.25,0.15);
				Bees[4]->ResetBee(this->x , this->y, this->direction,0.3,0.15);
			}
				
		}

		break;

	case GoExtremely:
		if (this->state == HANDCARYBLADE)
		{
			if (this->animation->listSprite[HANDCARYBLADE]->IsFinalFrame()
				&&GetTickCount()-this->time_start_change_state>2000)
			{
				this->animation->Refresh(HANDCARYBLADE);
				this->state = REDKNEE;
				float megaman_x, megaman_y;
				Megaman::Instance()->GetPosition(megaman_x, megaman_y);
				this->direction = (this->x > megaman_x) ? RIGHT : LEFT;

				this->dx = -1;
			}
			return;
		}


		if (this->state = REDKNEE)
		{
			////left- bottom
			//if (this->x<BLASTHORNET_LEFT+100&&this->y<MID)
			//{
			//	this->dy = 2;
			//	this->dx = -1;
			//}

			////left- mid
			//if (this->x < BLASTHORNET_LEFT + 20)
			//{
			//	this->dy = 2;
			//	this->dx = 1;
			//	this->direction = LEFT;
			//}

			////left- top
			//if ((this->x > BLASTHORNET_LEFT + 60||this->y>GROUND+500)
			//	&& this->y > MID+50
			//	&&this->x < BLASTHORNET_RIGHT - 400)
			//{
			//	this->dy = -1;
			//	this->dx = 2;
			//	if (this->count_to_attack % 2 == 0)
			//	{
			//		this->currentAction = Attack;
			//		this->state = PREPAREOPENVENOM;
			//		this->moving_attack_venom = false;
			//		count_to_attack++;
			//	}
			//	
			//}

			////right- bottom
			//if (this->x > BLASTHORNET_RIGHT - 100 && this->y < MID)
			//{
			//	this->dy = 1;
			//	this->dx = 1;
			//}

			////right- mid
			//if (this->x > BLASTHORNET_RIGHT - 20)
			//{
			//	this->dy = 2;
			//	this->dx = -1;
			//	this->direction = RIGHT;
			//}

			////right- top
			//if ((this->x < BLASTHORNET_RIGHT - 70||this->y>GROUND + 500)
			//	&& this->y > MID+100
			//	&&this->x > BLASTHORNET_LEFT +400)
			//{
			//	this->dy = -1;
			//	this->dx = -2;
			//	if (this->count_to_attack % 2 == 1)
			//	{
			//		this->currentAction = Attack;
			//		this->state = PREPAREOPENVENOM;
			//		this->moving_attack_venom = false;
			//		count_to_attack++;
			//	}
			//}

			//===============bottom=================================
			if (this->y < GROUND+20) //dy=-2
			{
				this->dy = 2;
				count_to_attack++;

				//go to mid location
				if (this->x < BLASTHORNET_MID_X) //in left => goto left- mid
				{
					this->a = (this->y - 15155) / (this->x - 19300);
					this->b = 15155 - a * 19300;
				}
				else
				{
					//in right => goto right- mid
					this->a = (this->y - 15155) / (this->x - 19763);
					this->b = 15155 - a * 19763;

				}
			}

			//==============left- mid===============================
			if (this->x < BLASTHORNET_LEFT + 20)
			{
				this->dy = 0.5;
				this->direction = LEFT;

				//in mid-left => goto top- left
				this->a = (this->y - 15243) / (this->x - 19378);
				this->b = 15243 - a * 19378;

			}

			//===============top=================================
			if (this->y>BLASTHORNET_TOP-60)
			{
				//go to bottom location
				if (this->x > BLASTHORNET_MID_X) //in right => goto left- bottom
				{
					this->a = (this->y - 14965) / (this->x - 19377);
					this->b = 14965 - a * 19377;
				}
				else
				{
					//in left => goto right- bottom
					this->a = (this->y - 14965) / (this->x - 19685);
					this->b = 14965 - a * 19685;

				}

				this->dy = -2;
				if (this->hitpoints>BLASTHORNET_MAX_HP/3)
				{
					if (this->count_to_attack % 2 == 0)
					{
						this->currentAction = Attack;
						this->state = PREPAREOPENVENOM;
						this->moving_attack_venom = false;
						this->count_to_attack++;
					}
				}
				else
				{
				//==========create bee===============================================
				//===================================================================

					bool check = true;
					for (int i = 0; i < 5; i++)
					{
						if (!this->Bees[i]->IsDestroy())
							check = false;
					}

					// ========all be die, moi reset================
					if (check)
					{
						this->time_start_change_state = GetTickCount();
						Bees[0]->ResetBee(this->x, this->y, this->direction, 0.1, 0.15);
						Bees[1]->ResetBee(this->x, this->y - 50, this->direction, 0.15, 0.15);
						Bees[2]->ResetBee(this->x, this->y - 50, this->direction, 0.2, 0.15);
						Bees[3]->ResetBee(this->x, this->y - 20, this->direction, 0.25, 0.15);
						Bees[4]->ResetBee(this->x, this->y, this->direction, 0.3, 0.15);

						Bees[0]->SetFollowBlastHornet(true);
						Bees[1]->SetFollowBlastHornet(true);
						Bees[2]->SetFollowBlastHornet(true);
						Bees[3]->SetFollowBlastHornet(true);
						Bees[4]->SetFollowBlastHornet(true);

						honey->ResetHoney(this->x, this->y);
					}
					
				}
				
				
			}


			//==============right- mid===============================
			if (this->x > BLASTHORNET_RIGHT - 20)
			{
				this->dy = 0.5;
				this->direction = RIGHT;

				//in mid-right => goto top- right
				this->a = (this->y - 15242) / (this->x - 19685);
				this->b = 15242 - a * 19685;
			}


			this->y += dy;
			this->x = (this->y - this->b) / this->a;
			/*this->x += dx;
			this->y += dy;*/
			return;
		}

		break;
	default:
		break;
	}
}

void BlastHornet::Render()
{

	if (!this->actived)
		return;

	if(this->hitpoints<=0 && appeared)
		this->animation_lifebar->listSprite[STAND]->Set_current_frame(0);
	else
	{
		this->animation_lifebar->listSprite[STAND]->Set_current_frame(this->hitpoints / 3);
		Bees[0]->Render();
		Bees[1]->Render();
		Bees[2]->Render();
		Bees[3]->Render();
		Bees[4]->Render();

		honey->Render();
	}
	
	this->animation_lifebar->Render(STAND, RIGHT, D3DXVECTOR2(580, 100));

	

	ActionObject::Render();
}

void BlastHornet::LoadResource()
{

	vector<RECT*> list_source_rect_red_knee = TXT::Instance()->GetListSourceRect(SBLASTHORNETREDKNEE);
	MyTexture* texture_red_knee = TXT::Instance()->GetTexture(TBLASTHORNETREDKNEE);
	animation->listSprite[State::REDKNEE] = new Sprite(texture_red_knee, list_source_rect_red_knee, 1);

	
	vector<RECT*> list_source_rect_red_hands = TXT::Instance()->GetListSourceRect(SBLASTHORNETREDHANDS);
	MyTexture* texture_red_hands = TXT::Instance()->GetTexture(TBLASTHORNETREDHANDS);
	animation->listSprite[State::REDHANDS] = new Sprite(texture_red_hands, list_source_rect_red_hands, 5);


	vector<RECT*> list_source_rect_prepare_open_venom = TXT::Instance()->GetListSourceRect(SBLASTHORNETPREPAREOPENVENOM);
	MyTexture* texture_red_prepare_open_venom = TXT::Instance()->GetTexture(TBLASTHORNETPREPAREOPENVENOM);
	animation->listSprite[State::PREPAREOPENVENOM] = new Sprite(texture_red_prepare_open_venom, list_source_rect_prepare_open_venom, 5);


	vector<RECT*> list_source_rect_opening_venom = TXT::Instance()->GetListSourceRect(SBLASTHORNETOPENINGVENOM);
	MyTexture* texture_red_opening_venom = TXT::Instance()->GetTexture(TBLASTHORNETOPENINGVENOM);
	animation->listSprite[State::OPENINGVENOM] = new Sprite(texture_red_opening_venom, list_source_rect_opening_venom, 3);

	vector<RECT*> list_source_rect_close_venom = TXT::Instance()->GetListSourceRect(SBLASTHORNETCLOSEVENOM);
	//MyTexture* texture_red_opening_venom = TXT::Instance()->GetTexture(TBLASTHORNETOPENINGVENOM);
	animation->listSprite[State::CLOSEVENOM] = new Sprite(texture_red_opening_venom, list_source_rect_close_venom, 3);

	vector<RECT*> list_source_rect_han_cary_blade = TXT::Instance()->GetListSourceRect(SBLASTHORNETHANDCARRYBLADE);
	MyTexture* texture_red_han_cary_blade = TXT::Instance()->GetTexture(TBLASTHORNETCARRYBLADE);
	animation->listSprite[State::HANDCARYBLADE] = new Sprite(texture_red_han_cary_blade, list_source_rect_han_cary_blade, 5);

	vector<RECT*> list_source_rect_han_venomlight = TXT::Instance()->GetListSourceRect(SBLASTHORNETVENOMLIGHT);
	MyTexture* texture_red_han_venomlight = TXT::Instance()->GetTexture(TBLASTHORNETVENOMLIGHT);
	animation->listSprite[State::VENOMLIGHT] = new Sprite(texture_red_han_venomlight, list_source_rect_han_venomlight, 3);

	vector<RECT*> list_source_rect_lifebar = TXT::Instance()->GetListSourceRect(SBLASTHORNETLIFEBAR);
	MyTexture* texture_lifebar = TXT::Instance()->GetTexture(TBLASTHORNETLIFEBAR);
	animation_lifebar->listSprite[State::STAND] = new Sprite(texture_lifebar, list_source_rect_lifebar, 3);

	vector<RECT*> list_source_rect_die = TXT::Instance()->GetListSourceRect(SBLASTHORNETDIE);
	MyTexture* texture_die = TXT::Instance()->GetTexture(TBLASTHORNETDIE);
	animation->listSprite[State::DESTROY] = new Sprite(texture_die, list_source_rect_die, 3);
}

BoundingBox BlastHornet::GetBoundingBox()
{
	if (!this->actived)
		return BoundingBox();

	BoundingBox bound;
	bound.x = x - BLASTHORNET_WIDTH / 2;
	bound.y = y - BLASTHORNET_HEIGHT / 2;
	bound.w = BLASTHORNET_WIDTH;
	bound.h = BLASTHORNET_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

BoundingBox BlastHornet::GetBoundBee(int i)
{
	return Bees[i]->GetBoundingBox();
}

void BlastHornet::SetState(State s)
{
	this->state = s;

}

void BlastHornet::SetDirection(Direction d)
{
	this->direction = d;
}

void BlastHornet::SetBeeSBeingAttack(int indexBee, int damage)
{
	this->Bees[indexBee]->SetBeingAttacked(damage);
}
