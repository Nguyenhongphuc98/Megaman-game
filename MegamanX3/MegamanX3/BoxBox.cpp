#include"BoxBox.h"


BoxBox::BoxBox(float top, float left, float w, float h)
{
	this->x = left;
	if (x > 6478 * G_Scale.x& x < 6600 * G_Scale.x)
		this->x = 6542 * G_Scale.x;
	this->y = top;
	this->width = w;
	this->height = h;
	this->actived = false;
	this->destroyed = false;
	this->hitpoints = BOXBOX_MAX_HP;

	this->nameObject = BOXBOX;
	this->damage = BOXBOX_DAMAGE;


	MyTexture* texture = TXT::Instance()->GetTexture(TBOXBOX);

	vector<RECT*> list_source_rect_box5 = TXT::Instance()->GetListSourceRect(SBOXBOX5);
	animation->listSprite[State::STAND] = new Sprite(texture, list_source_rect_box5, 5);

	vector<RECT*> list_source_rect_box1 = TXT::Instance()->GetListSourceRect(SBOXBOX1);
	animation->listSprite[State::DESTROY] = new Sprite(texture, list_source_rect_box1, 5);

	this->state = STAND;
}



void BoxBox::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->destroyed)
		return;

	/*if (this->state == STAND)
	{
		MyDebugOUT("stand======================================\n");
	}
	else
	{
		if (this->state == DESTROY)
		{
			MyDebugOUT("destroy======================================\n");
		}
		else
			MyDebugOUT("undefine======================================\n");
	}*/
	
	

	//===========when stand ( box don't die)==============
	if (this->state == STAND)
	{
		if (this->hitpoints <= 0)
		{
			this->state = DESTROY;
			//=========avoid make megaman hurting when state is stand=======
			//destroy -> hurting (box1)
			if (x > 6478 * G_Scale.x& x < 6600 * G_Scale.x)
			this->damage = BOX_POSITINON1_DAMAGE;
			else
			{
				this->damage = BOX_POSITINON2_DAMAGE;
			}
			
			Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
			tempBullet->SetState(DESTROYBULLET);
			WeaponSystem::Instance()->AddBulletEnemy(tempBullet);

			Bullet* tempBullet2 = new NotorbangerBullet(this->x, this->y-30, RIGHT, 0);
			tempBullet2->SetState(DESTROYBULLET);
			WeaponSystem::Instance()->AddBulletEnemy(tempBullet2);

			Bullet* tempBullet3 = new NotorbangerBullet(this->x, this->y+30, RIGHT, 0);
			tempBullet3->SetState(DESTROYBULLET);
			WeaponSystem::Instance()->AddBulletEnemy(tempBullet3);

			Bullet* tempBullet4 = new NotorbangerBullet(this->x, this->y-100, RIGHT, 0);
			tempBullet4->SetState(DESTROYBULLET);
			WeaponSystem::Instance()->AddBulletEnemy(tempBullet4);
			
			//change animation to box1(dextroy) and location
			this->y += 500; // up to top.
			
		}
		return;
	}

	//=================box die -> create box1 to free fall===============
	if (this->state == DESTROY)
	{
		this->y -= 10; //falling

		// we have alot position use box, so need know that where is it location
		if (x > 6478 * G_Scale.x& x < 6600 * G_Scale.x)
		{
			// type box position 1 ( left)
			if (this->y < G_ADDITIONS_TO_BECOME_THE_SQUARE*G_Scale.y)
			{
				Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
				tempBullet->SetState(DESTROYBULLET);
				WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
				this->destroyed = true;
			}
			
		}
		else
		{
			// box in other position left=====================
			if (this->y < 168+G_ADDITIONS_TO_BECOME_THE_SQUARE*G_Scale.y)
			{
				Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
				tempBullet->SetState(DESTROYBULLET);
				WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
				this->destroyed = true;
			}
		}
	}
	
}

void BoxBox::Render()
{
	if (this->destroyed)
		return;

	ActionObject::Render();
}

BoundingBox BoxBox::GetBoundingBox()
{
	if (this->destroyed)
		return BoundingBox();

	BoundingBox bound;

	if (this->state==STAND)
	{
		bound.x = x - BOXBOX_WIDTH / 2;
		bound.y = y - BOXBOX_HEIGHT / 2;
		bound.w = BOXBOX_WIDTH;
		bound.h = BOXBOX_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}
	else
	{
		// =====only  one box falling=============
		bound.x = x - BOX_WIDTH / 2;
		bound.y = y - BOX_HEIGHT / 2; //change possition to avoid colli
		bound.w = BOX_WIDTH;
		bound.h = BOX_HEIGHT;
		bound.vx = 0;
		bound.vy = 0;
	}

	return bound;
}

