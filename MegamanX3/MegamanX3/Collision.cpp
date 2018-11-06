#include"Collision.h"
Collision*	Collision::instance;

Collision::Collision()
{
}

Collision::~Collision()
{
}

Collision * Collision::Instance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

bool Collision::CollisionAABB(BoundingBox b1, BoundingBox b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

ResultCollision Collision::CollisionSweptAABB(BoundingBox b1, BoundingBox b2)
{
	//=============Khoi tao gia tri mac dinh la khong va cham===========
	ResultCollision r;
	r.isCollision = false;
	r.t = 1;
	r.nx = r.ny = 0;

	vx = b1.vx - b2.vx;
	vy = b1.vy - b2.vy;

	//==================broadphase======================================
	BoundingBox btemp;
	btemp.x = b1.vx > 0 ? b1.x : b1.x + b1.vx;
	btemp.y = b1.vy > 0 ? b1.y : b1.y + b1.vy;
	btemp.w = b1.vx > 0 ? b1.vx + b1.w : b1.w - b1.vx;
	btemp.h = b1.vy > 0 ? b1.vy + b1.h : b1.h - b1.vy;

	if (!CollisionAABB(btemp, b2))
		return r;

	//==================quang duong va cham va ket thuc=================
	if (vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	//Theo y
	if (vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	//===========Xác định thời gian va chạm==============================
	//Theo x
	if (vx == 0.0f)
	{
		//Trường hợp vận tốc = 0 thì các giá trị vô cực ( không va chạm )
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		//Khoảng thời gian bắt đầu va chạm theo x
		xEntry = xInvEntry / (vx);
		//Khoảng thời gian kết thúc va chạm
		xExit = xInvExit / (vx);
	}

	//Theo y
	if (vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (vy);
		yExit = yInvExit / (vy);
	}

	//Tính thời gian bắt đầu va chạm và kết thúc va chạm
	entryTime = max(xEntry, yEntry);
	exitTime = min(xExit, yExit);

	//Nếu không có va chạm
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		return r;
	}
	else
	{
		r.isCollision = true;
		r.t = entryTime;

		if (xEntry > yEntry)
		{
			r.ny = 0.0f;
			if (vx > 0)
			{
				r.nx = -1.0f;
			}
			else
			{
				r.nx = 1.0f;
			}
		}
		else
		{
			r.nx = 0.0f;
			if (vy > 0)
			{
				r.ny = -1.0f;
			}
			else
			{
				r.ny = 1.0f;
			}
		}
		// Trả về thời gian bắt đầu va chạm
		return r;
	}
}
