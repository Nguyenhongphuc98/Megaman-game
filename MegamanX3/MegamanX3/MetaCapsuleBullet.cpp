#include"MetaCapsuleBullet.h"


MetaCapsuleBullet::MetaCapsuleBullet(float x, float y, Direction d)
{
	this->destroyed = false;

	this->x = x;
	this->y = y;
	this->direction = d;
	this->damage = MEGAMAN_BULLET1_DAMAGE;
	this->SetState(SHOOTING);

	this->nameObject = METACAPSULEBULLET;

	MyTexture *texture = TXT::Instance()->GetTexture(TCARRYARM);
	vector<RECT*> list_source_rect_shooting = TXT::Instance()->GetListSourceRect(SMETACAPSULEBULLET);
	animation->listSprite[SHOOTING] = new Sprite(texture, list_source_rect_shooting, 1);

	this->SetState(SHOOTING);
}

MetaCapsuleBullet::~MetaCapsuleBullet()
{
}

void MetaCapsuleBullet::Update(DWORD dt, vector<Object*>* List_virtual_objects)
{
	if (this->distance_has_shot_x > 600)
	{ 
		this->destroyed = true;
		return;
	}
		
	this->vy += -0.0005*dt; //gravity
	Object::Update(dt, List_virtual_objects);

	this->distance_has_shot_x += dx;

	vector<ResultCollision> List_result_col;
	List_result_col.clear();

	for (int i = 0; i < List_virtual_objects->size(); i++) {
		ResultCollision r;
		r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), List_virtual_objects->at(i)->GetBoundingBox());
		if (r.isCollision)
			List_result_col.push_back(r);
	}

	if (List_result_col.size() == 0)
	{
		x += dx;
		y += dy;

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

		Bullet* tempBullet = new NotorbangerBullet(this->x, this->y, RIGHT, 0);
		tempBullet->SetState(DESTROYBULLET);
		WeaponSystem::Instance()->AddBulletEnemy(tempBullet);
		this->destroyed = true;
	}

}

void MetaCapsuleBullet::Render()
{
	Bullet::Render();
}

BoundingBox MetaCapsuleBullet::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - METACAPSULE_BULLET_WIDTH / 2;
	bound.y = y - METACAPSULE_BULLET_HEIGHT / 2;
	bound.w = METACAPSULE_BULLET_WIDTH;
	bound.h = METACAPSULE_BULLET_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void MetaCapsuleBullet::SetState(State s)
{
	this->state = SHOOTING;
	switch (s)
	{
	case SHOOTING:
		vx =(this->direction==RIGHT)? METACAPSULE_BULLET_VX:-METACAPSULE_BULLET_VX;
		vy = METACAPSULE_BULLET_VY;
		break;

	case DESTROYBULLET:
		vx = vy = 0;
		this->destroyed = true;
		break;
	default:
		break;
	}
}

void MetaCapsuleBullet::SetDirection(Direction d)
{
	this->direction = d;
}

bool MetaCapsuleBullet::IsDestroyed()
{
	return this->destroyed;
}
