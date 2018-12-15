#include"MegamanBullet2.h"


MegamanBullet2::MegamanBullet2(float x, float y, Direction d)
{
	this->destroyed = false;

	this->x = x;
	this->y = y;
	this->direction = d;
	this->damage = MEGAMAN_BULLET2_DAMAGE;
	this->SetState(SHOOTING);

	MyTexture *texture = TXT::Instance()->GetTexture(TBULLETMEGAMAN);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SBULLET2MEGAMANSTART);
	animation->listSprite[SHOOTING] = new Sprite(texture, list_source_rect_shooting, 1);

	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLET2MEGAMANDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture, list_source_rect_destroy, 1);
}

MegamanBullet2::~MegamanBullet2()
{
}

void MegamanBullet2::Update(DWORD dt, vector<Object*>* List_enemy_objects)
{
	if (this->distance_has_shot_x > 600 || (this->state == DESTROYBULLET && this->animation->listSprite[state]->IsFinalFrame()))
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

		//=============AABB With Shurikein to chinh xac hon=================
		if (O->GetNameObject() == SHURIKEIN)
		{
			bool r = false;
			r = Collision::Instance()->CollisionAABB(this->GetBoundingBox(), O->GetBoundingBox());

			//======avoid loop because AABB==================
			if (r&&this->state != DESTROYBULLET)
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

			O->GetPosition(x_temp, y_temp);
			//O->SetPosition(x_temp+ 10, y_temp);
			((ActionObject*)O)->SetBeingAttacked(this->damage);

			this->SetPosition(x_temp + 5, y);
			this->SetState(DESTROYBULLET);
		}

	}

	if (!check_coll)
	{
		x += dx;
		//y += dy;
	}
}

void MegamanBullet2::Render()
{
	//G_Scale = D3DXVECTOR2(1, 1);
	//G_ScaleFlipX = D3DXVECTOR2(-1, 1);
	Bullet::Render();
	//G_Scale = D3DXVECTOR2(2.5, 2.5);
	//G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);
}

BoundingBox MegamanBullet2::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - MEGAMAN_BULLET2_WIDTH / 2;
	bound.y = y - MEGAMAN_BULLET2_HEIGHT / 2;
	bound.w = MEGAMAN_BULLET2_WIDTH;
	bound.h = MEGAMAN_BULLET2_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void MegamanBullet2::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case SHOOTING:
		vx = (this->direction == RIGHT) ? MEGAMAN_BULLET2_VX : -MEGAMAN_BULLET2_VX;
		vy = MEGAMAN_BULLET2_VY;
		break;

	case DESTROYBULLET:
		vx = vy = 0;
		break;
	default:
		break;
	}
}

void MegamanBullet2::SetDirection(Direction d)
{
	this->direction = d;
}

bool MegamanBullet2::IsDestroyed()
{
	return this->destroyed;
}
