#include"NotorBanger.h"

NotorBanger::NotorBanger()
{
	x = 200;
	y = 1647;

	LoadResource();
}

NotorBanger::~NotorBanger()
{
}

void NotorBanger::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt,List_object_can_col);

	x += dx;
	//y += dy;

	if (direction == LEFT && x < 0)
	{
		SetDirection(RIGHT);
	}

	if(direction==RIGHT&&x>1730)
		SetDirection(LEFT);

}

void NotorBanger::Render()
{
	ActionObject::Render();
}

void NotorBanger::LoadResource()
{
	vector<RECT*> list_source_rect_jump=TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\notorBanger.txt");

	/*RECT* r1 = new RECT();
	r1->top = 5;
	r1->bottom = 38;
	r1->left = 4;
	r1->right = 44;

	RECT* r2 = new RECT();
	r2->top = 6;
	r2->bottom = 38;
	r2->left = 48;
	r2->right = 89;

	RECT* r3 = new RECT();
	r3->top = 8;
	r3->bottom = 38;
	r3->left = 100;
	r3->right = 141;

	RECT* r4 = new RECT();
	r4->top = 1;
	r4->bottom = 44;
	r4->left = 145;
	r4->right = 194;
	
	list_source_rect_jump.push_back(r1);
	list_source_rect_jump.push_back(r2);
	list_source_rect_jump.push_back(r3);
	list_source_rect_jump.push_back(r4);*/
	MyTexture *texture_jump = new MyTexture((char*)"SourceImage\\notorBanger.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->listSprite[JUMP] = new Sprite(texture_jump, list_source_rect_jump, 1);
}

BoundingBox NotorBanger::GetBoundingBox()
{
	BoundingBox bound;
	bound.x = x - NOTORBANGER_WIDTH / 2;
	bound.y = y - NOTORBANGER_HEIGHT / 2;
	bound.w = NOTORBANGER_WIDTH;
	bound.h = NOTORBANGER_HEIGHT;
	bound.vx = dx;
	bound.vy = dy;
	return bound;
}

void NotorBanger::SetState(State s)
{
	this->state = s;
	switch (s)
	{
	case RUN:
		break;
	case JUMP:
		
		vy = NOTORBANGER_VY;
		break;
	case STAND:
		break;
	case SHOOT:
		break;
	default:
		vx = 0;
		vy = 0;
		break;
	}
}

void NotorBanger::SetDirection(Direction d)
{
	this->direction = d;
	if (direction == RIGHT)
		vx = NOTORBANGER_VX;
	else
	{
		vx = -NOTORBANGER_VX;
	}
}
