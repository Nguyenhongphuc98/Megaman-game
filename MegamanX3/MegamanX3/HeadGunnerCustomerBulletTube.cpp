#include"HeadGunnerCustomerBulletTube.h"
#include"Megaman.h"

HeadGunnerCustomerBulletTube::HeadGunnerCustomerBulletTube(float x, float y, Direction d)
{
	this->x = x;
	this->y = y;
	this->start_x = x;
	this->vx = HEADGUNNERCUSTOMER_BULLET_TUBE_VX;
	float xmegaman, ymegaman;
	Megaman::Instance()->GetPosition(xmegaman, ymegaman);
	if(this->y>ymegaman+50)
	this->vy = -HEADGUNNERCUSTOMER_BULLET_TUBE_VY;
	else
		if (this->y < ymegaman - 50)
	{
			this->vy = HEADGUNNERCUSTOMER_BULLET_TUBE_VY;
	}
		else
		{
			this->vy = 0;
		}

	this->nameObject = HEADGUNNERCUSTOMERBULLET;

	SetDirection(d);
	SetState(SHOOTING);

	MyTexture *texture_shooting = TXT::Instance()->GetTexture(THEADGUNNERCUSTOMER);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SHEADGUNNERCUSTOMERBULLETTUBE);
	animation->listSprite[SHOOTING] = new Sprite(texture_shooting, list_source_rect_shooting, 1);

	MyTexture *texture_destroy = TXT::Instance()->GetTexture(TCARRYARM);
	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLETNOTORBANGERDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture_destroy, list_source_rect_destroy, 1);
}

HeadGunnerCustomerBulletTube::~HeadGunnerCustomerBulletTube()
{
}

void HeadGunnerCustomerBulletTube::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	if (this->destroyed)
		return;
	if (abs(this->x - this->start_x) > 300)
		this->destroyed = true;

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

		if (this->state == SHOOTING && finish_smoke)
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

void HeadGunnerCustomerBulletTube::Render()
{
	Bullet::Render();
}

BoundingBox HeadGunnerCustomerBulletTube::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - HEADGUNNERCUSTOMER_BULLET_TUBE_WIDTH / 2;
	bound.y = y - HEADGUNNERCUSTOMER_BULLET_TUBE_HEIGHT / 2;
	bound.w = HEADGUNNERCUSTOMER_BULLET_TUBE_WIDTH;
	bound.h = HEADGUNNERCUSTOMER_BULLET_TUBE_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void HeadGunnerCustomerBulletTube::SetState(State s)
{
	this->state = s;
	if (this->state == DESTROYBULLET)
		vx = vy = 0;
}

void HeadGunnerCustomerBulletTube::SetDirection(Direction d)
{
	this->direction = d;
	vx = (this->direction == LEFT) ? -HEADGUNNERCUSTOMER_BULLET_TUBE_VX : HEADGUNNERCUSTOMER_BULLET_TUBE_VX;
}

bool HeadGunnerCustomerBulletTube::IsDestroyed()
{
	return this->destroyed;
}
