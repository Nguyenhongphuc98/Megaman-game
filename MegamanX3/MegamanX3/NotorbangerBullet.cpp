#include"NotorbangerBullet.h"

NotorbangerBullet::NotorbangerBullet(float x, float y, Direction d, float angle)
{
	this->x = x;
	this->y = y;
	this->vx = NOTORBANGER_BULLET_VX;
	this->vy = NOTORBANGER_BULLET_VY;
	this->angle = angle;
	this->damage = NOTORBANGER_BULLET_DAMAGE;

	SetDirection(d);
	SetState(SHOOTING);

	MyTexture *texture_shooting = TXT::Instance()->GetTexture(TNOTORBANGER);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SBULLETNOTORBANGERSTART);
	animation->listSprite[SHOOTING] = new Sprite(texture_shooting, list_source_rect_shooting, 1);

	MyTexture *texture_destroy = TXT::Instance()->GetTexture(TCARRYARM);
	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLETNOTORBANGERDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture_destroy, list_source_rect_destroy, 1);

	
	this->distance_has_shot_x = 0;
	this->distance_has_shot_y = 0;
	this->destroyed = false;
	this->finish_smoke = false;
}

NotorbangerBullet::~NotorbangerBullet()
{
}

void NotorbangerBullet::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->destroyed)
		return;

	if (this->state == DESTROYBULLET)
	{
		if (this->animation->listSprite[state]->IsFinalFrame())
		{
			this->destroyed = true;
			return;
		}		
	}

	if (this->state == SHOOTING)
	{
		if (this->animation->listSprite[state]->IsFinalFrame())
		{
			if (!finish_smoke)
			{
				this->time_start = GetTickCount();

				finish_smoke = true;
			}
		}
		else
		{
			return;
		}
	}
	

	this->vy += -0.0005*dt; //gravity
	Object::Update(dt, List_object_can_col);

	this->time_live = GetTickCount() - this->time_start;
	dx = vx * time_live*cos(this->angle) - this->distance_has_shot_x;
	dy = vy * time_live*sin(this->angle) - 0.5*0.0005*pow(time_live, 2) - this->distance_has_shot_y;

	this->distance_has_shot_x += dx;
	this->distance_has_shot_y += dy;

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

		if (this->state == SHOOTING && this->animation->listSprite[state]->IsFinalFrame())
			this->animation->listSprite[state]->Set_current_frame(6);
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

		int m = min(min_tx, min_ty);
		x += (m * dx + nx * 0.4f);
		y += (m * dy + ny * 0.4f);
		//x += dx;
		//y += dy;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		this->SetState(DESTROYBULLET);
	}
}

void NotorbangerBullet::Render()
{
	Bullet::Render();
}

BoundingBox NotorbangerBullet::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - NOTORBANGER_BULLET_WIDTH / 2;
	bound.y = y - NOTORBANGER_BULLET_HEIGHT / 2;
	bound.w = NOTORBANGER_BULLET_WIDTH;
	bound.h = NOTORBANGER_BULLET_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void NotorbangerBullet::SetState(State s)
{
	this->state = s;
	if (this->state == DESTROYBULLET)
		vx = vy = 0;
}

void NotorbangerBullet::SetDirection(Direction d)
{
	this->direction = d;
	vx = (this->direction == LEFT) ? -NOTORBANGER_BULLET_VX : NOTORBANGER_BULLET_VX;
}

bool NotorbangerBullet::IsDestroyed()
{
	return this->destroyed;
}
