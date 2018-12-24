#include"MegamanBullet1.h"


MegamanBullet1::MegamanBullet1(float x, float y, Direction d)
{
	this->destroyed = false;

	this->x = x;
	this->y = y;
	this->direction = d;
	this->damage = MEGAMAN_BULLET1_DAMAGE;
	this->SetState(SHOOTING);

	this->nameObject = MEGAMANBULLLET1;

	MyTexture *texture = TXT::Instance()->GetTexture(TBULLETMEGAMAN);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SBULLET1MEGAMANSTART);
	animation->listSprite[SHOOTING] = new Sprite(texture, list_source_rect_shooting, 1);

	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLET1MEGAMANDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture, list_source_rect_destroy, 1);
}

MegamanBullet1::~MegamanBullet1()
{
}

void MegamanBullet1::Update(DWORD dt, vector<Object*>* List_enemy_objects)
{
	if (this->distance_has_shot_x > 600||(this->state==DESTROYBULLET&& this->animation->listSprite[state]->IsFinalFrame()))
	{ 
		this->destroyed = true;
		return;
	}
		
	Object::Update(dt, List_enemy_objects);
	this->distance_has_shot_x += dx;

	bool check_coll = false;
	for (Object* O : *List_enemy_objects) {

		if (((ActionObject*)O)->IsDestroy())
			continue;

		if (O->GetNameObject() == BLASTHORNET)
		{
			//============bosss main===================
			ResultCollision r;
			r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), O->GetBoundingBox());
			if (r.isCollision)
			{
				((ActionObject*)O)->SetBeingAttacked(this->damage);

				this->SetPosition(x, y);
				this->SetState(DESTROYBULLET);
			}

			//============bosss bee===================
			bool result;
			for (int i = 0; i < 5; i++)
			{
				result = Collision::Instance()->CollisionAABB(this->GetBoundingBox(), ((ActionObject*)O)->GetBoundBee(i));
				if (result)
				{
					((ActionObject*)O)->SetBeeSBeingAttack(i, damage);

					this->SetPosition(x, y);
					this->SetState(DESTROYBULLET);
				}
			}

			continue;
		}

		//=============AABB With Shurikein to chinh xac hon=================
		if (O->GetNameObject() == SHURIKEIN||O->GetNameObject()==HELIT)
		{
			bool r = false;
			r = Collision::Instance()->CollisionAABB(this->GetBoundingBox(), O->GetBoundingBox());

			//======avoid loop because AABB==================
			if (r&&this->state!=DESTROYBULLET)
			{
				check_coll = true;
				float x_temp, y_temp;

				O->GetPosition(x_temp, y_temp);
				//O->SetPosition(x_temp+ 10, y_temp);
				((ActionObject*)O)->SetBeingAttacked(this->damage);

				this->SetPosition(x_temp + 5, y);
				this->SetState(DESTROYBULLET);
			}

			continue;
		}

		//=================else process swept AABB=============================
		ResultCollision r;
		r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), O->GetBoundingBox());
		if (r.isCollision)
		{
			check_coll = true;
			float x_temp, y_temp;

			//O->GetPosition(x_temp, y_temp);
			//O->SetPosition(x_temp+ 10, y_temp);
			((ActionObject*)O)->SetBeingAttacked(this->damage);

			//this->SetPosition(x_temp+5, y);
			this->SetPosition(this->x+10, y);
			this->SetState(DESTROYBULLET);
		}
			
	}

	if (!check_coll)
	{
		x += dx;
		//y += dy;
	}
	else
	{
		/*float min_tx = 1.0f;
		int nx = 0;

		for (int i = 0; i < List_result_col.size(); i++)
		{
			if (List_result_col[i].t < min_tx && List_result_col[i].nx != 0) 
			{
				min_tx = List_result_col[i].t; nx = List_result_col[i].nx;
			}
		}
*/
		//x += (min_tx * dx + nx * 0.4f);
		/*x += dx;
		if (nx != 0) vx = 0;

		this->SetState(DESTROYBULLET);*/
	}
}

void MegamanBullet1::Render()
{
	G_Scale = D3DXVECTOR2(1, 1);
	G_ScaleFlipX = D3DXVECTOR2(-1, 1);
	Bullet::Render();
	G_Scale = D3DXVECTOR2(2.5, 2.5);
	G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);
}

BoundingBox MegamanBullet1::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - MEGAMAN_BULLET1_WIDTH / 2;
	bound.y = y - MEGAMAN_BULLET1_HEIGHT / 2;
	bound.w = MEGAMAN_BULLET1_WIDTH;
	bound.h = MEGAMAN_BULLET1_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void MegamanBullet1::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case SHOOTING:
		vx =(this->direction==RIGHT)? MEGAMAN_BULLET1_VX:-MEGAMAN_BULLET1_VX;
		vy = MEGAMAN_BULLET1_VY;
		break;

	case DESTROYBULLET:
		vx = vy = 0;
		break;
	default:
		break;
	}
}

void MegamanBullet1::SetDirection(Direction d)
{
	this->direction = d;
}

bool MegamanBullet1::IsDestroyed()
{
	return this->destroyed;
}
