#include"NotorBanger.h"

NotorBanger::NotorBanger()
{
	x = 1100;
	y = 7056 * G_Scale.y;

	center_region_x = x;
	jump_angle = PII/6;
	time_animate_shoot90 = 1;
	pre_y = y-12;
	LoadResource();
}

NotorBanger::NotorBanger(int x, int y, int w, int h, Direction d):ActionObject(x,y,w,h,d)
{
	center_region_x = x;
	jump_angle = PII / 6;
	time_animate_shoot90 = 1;
	pre_y = y - 12;
	LoadResource();
}

NotorBanger::~NotorBanger()
{
}

void NotorBanger::Update(DWORD dt, vector<Object*>* List_object_can_col)
{
	Object::Update(dt,List_object_can_col);
	
	

	if (state == JUMP) 
	{
		x += dx;
		y = pre_y;
		//x=vx*t=Vo*Cos(a)*t
		//y=Vo*Sin(a)*t-1/2gt^2
		float t = GetTickCount() - time_begin_jump;
		//x =pre_x+ (dx*t*cos(jump_angle));
		//y = pre_y + ((dy*t*sin(jump_angle)) -((NOTORBANGER_GRAVITY * t)*(NOTORBANGER_GRAVITY * t)) / 2);

		if (/*direction == LEFT && */(x <= (center_region_x - 100)))
		{
			SetDirection(LEFT);
			SetState(SHOOT90);
		}

		if (/*direction == RIGHT && */(x >= (center_region_x + 100)))
		{
			SetDirection(RIGHT);
			SetState(SHOOT90);
		}
	}
	else
	{
		y = pre_y +6;
		if (animation->listSprite[SHOOT90]->GetCurrentFrame() == 2)
			time_animate_shoot90++;

		if (time_animate_shoot90 % 20 == 0)
		{
			time_begin_jump = GetTickCount();
			SetState(JUMP);
			time_animate_shoot90++;			
		}	
	}
}

void NotorBanger::Render()
{
	ActionObject::Render();
}

void NotorBanger::LoadResource()	
{
	//MyTexture *texture = new MyTexture((char*)"SourceImage\\notorBanger.png", D3DCOLOR_XRGB(255, 255, 255));
	MyTexture *texture = TXT::Instance()->GetTexture(TNOTORBANGER);

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
	

	//vector<RECT*> list_source_rect_jump2 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\notorBangerJump.txt");
	vector<RECT*> list_source_rect_jump = TXT::Instance()->GetListSourceRect(SNOTORBANGERJUMP);
	animation->listSprite[JUMP] = new Sprite(texture, list_source_rect_jump, 2);

	//vector<RECT*> list_source_rect_shoot90 = TXT::Instance()->LoadListSourceRect((char*)"SourceImage\\notorBangerShoot90.txt");
	vector<RECT*> list_source_rect_shoot90 = TXT::Instance()->GetListSourceRect(SNOTOBANGERSHOOT90);
	animation->listSprite[SHOOT90] = new Sprite(texture, list_source_rect_shoot90, 2);
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
		if (direction == RIGHT)
			vx = -NOTORBANGER_VX;
		else
		{
			vx = NOTORBANGER_VX;
		}
		break;
	case STAND:
		break;
	case SHOOT:
		vx = 0;
		vy = 0;
		break;
	case SHOOT90:
		vx = 0;
		vy = 0;
	default:
		vx = 0;
		vy = 0;
		break;
	}
}

void NotorBanger::SetDirection(Direction d)
{
	this->direction = d;

}
