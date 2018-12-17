#include "HelitBullet.h"

HelitBulet::HelitBulet(float x, float y, Direction d)
{
	this->x = x;
	this->y = y;
	this->vx = HELIT_BULLET_VX;
	this->vy = HELIT_BULLET_VY;
	this->damage = HELIT_BULLET_DAMAGE;
	this->nameObject = HELLITBULLET;

	SetDirection(d);
	SetState(SHOOTING);

	MyTexture *texture_shooting = TXT::Instance()->GetTexture(THELIT);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SHELITBULLET);
	animation->listSprite[SHOOTING] = new Sprite(texture_shooting, list_source_rect_shooting, 1);

	MyTexture *texture_destroy = TXT::Instance()->GetTexture(TCARRYARM);
	vector<RECT*> list_source_rect_destroy = TXT::Instance()->GetListSourceRect(SBULLETNOTORBANGERDESTROY);
	animation->listSprite[DESTROYBULLET] = new Sprite(texture_destroy, list_source_rect_destroy, 1);


	this->distance_has_shot_x = 0;
	this->destroyed = false;
}

HelitBulet::~HelitBulet()
{
}

void HelitBulet::Update(DWORD dt, vector<Object*>* List_objects)
{
	if (this->destroyed)
		return;

	if (this->state == DESTROYBULLET)
	{
		if (this->animation->listSprite[state]->IsFinalFrame())
		{
			this->destroyed = true;
		}
		return;
	}

	
	Object::Update(dt, List_objects);

	this->distance_has_shot_x += dx;
	if (this->distance_has_shot_x > 400)
	{
		this->SetState(DESTROYBULLET);
		return;
	}
		
	x += dx;

	//vector<ResultCollision> List_result_col;
	//List_result_col.clear();

	//for (int i = 0; i < List_objects->size(); i++) {
	//	ResultCollision r;
	//	r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), List_objects->at(i)->GetBoundingBox());
	//	if (r.isCollision)
	//		List_result_col.push_back(r);
	//}

	//if (List_result_col.size() == 0)
	//{
	//	x += dx;
	//	y += dy;

	//	if (this->state == SHOOTING && this->animation->listSprite[state]->IsFinalFrame())
	//		this->animation->listSprite[state]->Set_current_frame(6);
	//}
	//else
	//{
	//	float min_tx = 1.0f, min_ty = 1.0f;
	//	int nx = 0, ny = 0;

	//	for (int i = 0; i < List_result_col.size(); i++) {
	//		if (List_result_col[i].t < min_tx && List_result_col[i].nx != 0) {
	//			min_tx = List_result_col[i].t; nx = List_result_col[i].nx;
	//		}

	//		if (List_result_col[i].t < min_ty  && List_result_col[i].ny != 0) {
	//			min_ty = List_result_col[i].t; ny = List_result_col[i].ny;
	//		}
	//	}

	//	int m = min(min_tx, min_ty);
	//	x += (m * dx + nx * 0.4f);
	//	y += (m * dy + ny * 0.4f);
	//	//x += dx;
	//	//y += dy;

	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;

	//	this->SetState(DESTROYBULLET);
	//}
}

void HelitBulet::Render()
{
	Bullet::Render();
}

BoundingBox HelitBulet::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - HELIT_BULLET_WIDTH / 2;
	bound.y = y - HELIT_BULLET_HEIGHT / 2;
	bound.w = HELIT_BULLET_WIDTH;
	bound.h = HELIT_BULLET_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void HelitBulet::SetState(State s)
{
	this->state = s;
}

void HelitBulet::SetDirection(Direction d)
{
	this->direction = d;
	vx = (this->direction == LEFT) ? HELIT_BULLET_VX : -HELIT_BULLET_VX;
}

bool HelitBulet::IsDestroyed()
{
	return this->destroyed;
}
