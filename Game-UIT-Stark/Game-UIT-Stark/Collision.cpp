#include"Collision.h"
Collision* Collision::instance;

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

ResultColision Collision::ProcessCollisionSweptAABB(CollisionRect object1, CollisionRect object2)
{
	ResultColision result;
	result.collision = false;

	/*Xét trường hợp cả 1 vật đều di chuyển, ta giả sử object2 đứng yên */
	/*bằng cách sử dụng công thức vận tốc tương đối                     */

	//int top1 = object1.GetTop();
	//int left1 = object1.GetLeft();
	//int top2 = object2.GetTop();
	//int left2 = object2.GetLeft();

	float vx = object1.GetVelocityX() - object2.GetVelocityX();
	float vy = object1.GetVelocityY() - object2.GetVelocityY();

	int o1right = object1.GetLeft() + object1.GetWidth();
	int o1bottom = object1.GetTop() + object1.GetHeight();
	int o2right = object2.GetLeft() + object2.GetWidth();
	int o2bottom = object2.GetTop() + object2.GetHeight();

	/* caculate SX to Collision and exit Collision */
	if (vx > 0.0f) {
		this->sXToCollision = object2.GetLeft() - o1right;
		this->sXToEndCollision = o2right - object1.GetLeft();
	}
	else
	{
		this->sXToCollision = o2right - object1.GetLeft();
		this->sXToEndCollision = object2.GetLeft() - o1right;
	}

	/* caculate SY */
	if (vy > 0.0f)
	{
		this->sYToCollision = object2.GetTop() - o1bottom;
		this->sYToEndCollision = o2bottom - object1.GetTop();
	}
	else
	{
		this->sYToCollision = o2bottom - object1.GetTop();
		this->sYToEndCollision = object2.GetTop() - o1bottom;
	}

	/* tính thời gian để xảy ra va chạm theo X	*/

	if (vx == 0.0f)
	{
		this->tXToCollision = -std::numeric_limits<float>::infinity(); //am vo cuc
		this->tXToEndCollision = std::numeric_limits<float>::infinity();
	}
	else
	{
		this->tXToCollision = this->sXToCollision / vx;
		this->tXToEndCollision = this->sXToEndCollision / vx;
	}

	/* tính thời gian để xảy ra va chạm theo Y	*/
	if (vy == 0.0f)
	{
		this->tYToCollision = -std::numeric_limits<float>::infinity();
		this->tYToEndCollision = std::numeric_limits<float>::infinity();
	}
	else
	{
		this->tYToCollision = this->sYToCollision / vy;
		this->tYToEndCollision = this->sYToEndCollision / vy;
	}

	/* tính toán kết quả của va chạm */


	/*cả 2 trục va chạm thì va chạm mới chính xác là xảy ra */
	/*1 trong 2 kết thúc thì va chạm kết thúc               */

	this->timeToCollision = std::fmax(this->tXToCollision, this->tYToCollision);
	this->timeToEndCollision = std::fmin(this->tXToEndCollision, this->tYToEndCollision);

	result.timeToColision = 1.0f;
	/* trường hợp không có va chạm */
	if (this->timeToCollision > this->timeToEndCollision //chưa va chạm đã kết thúc
		|| (this->tXToCollision < 0.0f && tYToCollision < 0.0f) //time va chạm <0
		|| this->tXToCollision > 1.0f
		|| this->tYToCollision > 1.0f) //time va chạm >1 thì xem như k có mà mình sẽ chỉ xét ở frame kế tiếp
	{
		result.velocityX = 0.0f;
		result.velocityY = 0.0f;
	}
	else /* Có va chạm */
	{
		result.timeToColision = this->timeToCollision;
		result.collision = true;
		/* va chạm theo Y trước -> trái hoặc phải*/
		if (this->tXToCollision > this->tYToCollision)
		{
			result.velocityY = 0.0f;
			//sx
			if (vx < 0.0f)
				result.velocityX = 1.0f;
			else
				result.velocityX = -1.0f;
		}
		else /* va chạm theo X trước -> trên hoặc dưới*/
		{
			result.velocityX = 0.0f;
			//sy
			if (vy < 0.0f)
				result.velocityY = 1.0f;
			else
				result.velocityY = -1.0f;
		}
	}

	return result;
}	
