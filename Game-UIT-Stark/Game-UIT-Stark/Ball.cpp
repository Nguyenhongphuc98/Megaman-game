#include"Ball.h"

Ball::Ball()
{
	locationX = 200;
	locationY = 200;

	velocityX = velocityY = BALL_SPEED;
	

	vector<RECT*> listSourceRectStand;
	RECT *r1 = new RECT;
	r1->top = 344;
	r1->left = 692;
	r1->right = 805;
	r1->bottom = 458;

	listSourceRectStand.push_back(r1);
	animation->ListSprite[Global::STAND] = new Sprite("ball.jpg", listSourceRectStand, D3DCOLOR_XRGB(12, 19, 19));
	boundingbox = Graphic::Instance()->CreateSurface(D3DCOLOR_XRGB(235, 130, 70));
	//Graphic::Instance()->GetD3DDevice()->ColorFill(boundingbox, NULL, D3DCOLOR_XRGB(50, 30, 70));
}

Ball::~Ball()
{
}

CollisionRect Ball::GetBound()
{
	return CollisionRect(locationY, locationX,BALL_WIDTH,BALL_HEIGHT,velocityX,velocityY);
}

void Ball::Render()
{
	
	animation->Render(Global::RIGHT, Global::STAND, D3DXVECTOR3(locationX, locationY, 0), D3DXVECTOR3(0.5, 0.5, 0));
	//animation->NextFrame(Global::STAND);
//	RenderBoundingBox();
}

void Ball::Update(float deltaTime, vector<Object*> List_Object_Can_Collision)
{
	Object::Update(deltaTime);
	
	ResultColision r;
	for (int i = 0; i < List_Object_Can_Collision.size(); i++)
	{
		r = this->ProcessCollision(List_Object_Can_Collision[i]);
		if (r.collision)
			break;
	}


	if (r.collision == false)
	{
		locationX += dx;
		locationY += dy;
	}
	else
	{
		Trace::Log("collision");
		//Global::Notify("collision", "notify");
		// block 
		locationX += (r.timeToColision * dx + r.velocityX * 0.4f);		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		locationY += (r.timeToColision * dy + r.velocityY * 0.4f);

		if (r.velocityX == -1)
		{
			velocityX = -BALL_SPEED;
			Trace::Log("X=-1");
		}

		if (r.velocityX == 1)
		{
			velocityX = BALL_SPEED;
			Trace::Log("X=1");
		}

		if (r.velocityY == -1)
		{
			velocityY = -BALL_SPEED;
			Trace::Log("Y=-1");
		}
		if (r.velocityY == 1)
		{
			velocityY = BALL_SPEED;
			Trace::Log("Y=1");
		}
	}
}

void Ball::RenderBoundingBox()
{
	RECT r;
	r = Global::ConvertCollisionRectToRECT(GetBound());

	Graphic::Instance()->DrawSurface(boundingbox, NULL, &r);
}
