#include"Launchers.h"


Launchers::Launchers()
{
	this->x = 903 * G_Scale.x;
	this->y = (1100 + G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y;

	this->vx = LAUNCHERS_VX;
	this->vy = LAUNCHERS_VY;

	this->nameObject = LAUNCHER;
	LoadResource();
}

Launchers::Launchers(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->is_allow_runing = false;

	this->vx = LAUNCHERS_VX;
	this->vy = LAUNCHERS_VY;

	this->nameObject = LAUNCHER;
	LoadResource();
}

Launchers::~Launchers()
{
}

void Launchers::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	
	if (is_allow_runing)
	{
		if (this->y > (1610 + G_ADDITIONS_TO_BECOME_THE_SQUARE) * G_Scale.y)
			return;

		float temp_X, temp_Y;
		Camera::Instance()->GetCameraPosition(temp_X, temp_Y);
		if (this->y > temp_Y + 100)
				this->y -= 800;
		else
		{
			Object::Update(dt, List_object_can_col);
			this->y += dy;

			//float megaman_x, megaman_y;
		//	Megaman::Instance()->GetPosition(megaman_x, megaman_y);
			
			Megaman::Instance()->GetPosition(temp_X, temp_Y);

			if (abs(this->x - temp_X) > 100)
				return;
			Megaman::Instance()->SetPosition(temp_X, temp_Y + dy);
		}
	
		return;
	}
	//else
	//{
	//	ResultCollision r;
	//	r = Collision::Instance()->CollisionSweptAABB(this->GetBoundingBox(), Megaman::Instance()->GetBoundingBox());
	//	if (r.isCollision)
	//		is_allow_runing = true;
	//}
}

void Launchers::Render()
{
	ActionObject::Render();
}

void Launchers::LoadResource()
{
	MyTexture *texture = TXT::Instance()->GetTexture(TLAUNCHERS);
	vector<RECT*> list_source_rect = TXT::Instance()->GetListSourceRect(SLAUNCHERS);
	animation->listSprite[RUN] = new Sprite(texture, list_source_rect, 1);
}

BoundingBox Launchers::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - LAUNCHERS_WIDTH / 2;
	bound.y = y - LAUNCHERS_HEIGHT / 2;
	bound.w = LAUNCHERS_WIDTH;
	bound.h = LAUNCHERS_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;

	return bound;
}

void Launchers::SetState(State s)
{
	this->state = s;
	if (state == RUN)
		is_allow_runing = true;
}

void Launchers::SetDirection(Direction d)
{
	this->direction = d;
}
