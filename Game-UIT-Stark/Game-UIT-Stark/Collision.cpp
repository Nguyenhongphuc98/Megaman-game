#include"Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

ResultColision Collision::ProcessCollisionSweptAABB(CollisionRect object1, CollisionRect object2)
{
	/*Xét trường hợp cả 1 vật đều di chuyển, ta giả sử object2 đứng yên */
	/*bằng cách sử dụng công thức vận tốc tương đối                     */

	object1.SetVelocityX(object1.GetVelocityX() - object2.GetVelocityX());
	object1.SetVelocityY(object1.GetVelocityY() - object2.GetVelocityY());

	/* caculate SX to Collision and exit Collision */
	if (object1.GetVelocityX() > 0.0f) {
		this->sXToCollision = object2.GetLeft() - (object1.GetLeft() + object1.GetWidth());
		this->sXToEndCollision = (object2.GetLeft() + object2.GetWidth()) - object1.GetLeft();
	}
	else
	{
		this->sXToCollision = object2.GetLeft() + object2.GetWidth() - object1.GetLeft();
		this->sXToEndCollision = object2.GetLeft() - (object1.GetLeft() + object1.GetWidth());
	}

	/* caculate SY */
	if (object1.GetVelocityY() > 0.0f)
	{
		this->sYToCollision = object2.GetTop()-object2.GetHeight()-object1.GetTop(); 
		this->sYToEndCollision = object2.GetTop() - (object1.GetTop() - object1.GetHeight());
	}
	else
	{
		this->sYToCollision = object2.GetTop() - (object1.GetTop() - object1.GetHeight());
		this->sYToEndCollision = (object2.GetTop()-object2.GetHeight()) - object1.GetTop();
	}

	/* tính thời gian để xảy ra va chạm theo X	*/
	
	if (object1.GetVelocityX() == 0.0f)
	{
		this->tXToCollision = -std::numeric_limits<float>::infinity(); //am vo cuc
		this->tXToEndCollision = std::numeric_limits<float>::infinity();
	}
	else
	{
		this->tXToCollision = this->sXToCollision / object1.GetVelocityX();
		this->tXToEndCollision = this->sXToEndCollision / object1.GetVelocityX();
	}

	/* tính thời gian để xảy ra va chạm theo Y	*/
	if (object1.GetVelocityY() == 0.0f)
	{
		this->tYToCollision = -std::numeric_limits<float>::infinity();
		this->tYToEndCollision = std::numeric_limits<float>::infinity();
	}
	else
	{
		this->tYToCollision = this->sYToCollision / object1.GetVelocityY();
		this->tYToEndCollision = sYToEndCollision / object1.GetVelocityY();
	}

	/* tính toán kết quả của va chạm */
	ResultColision result;

	/*cả 2 trục va chạm thì va chạm mới chính xác là xảy ra */
	/*1 trong 2 kết thúc thì va chạm kết thúc               */

	this->timeToCollision = std::fmax(this->tXToCollision, this->tYToCollision);
	this->timeToEndCollision=std::fmin(this->tXToEndCollision, this->tYToEndCollision);

	/* trường hợp không có va chạm */
	if (this->timeToCollision > this->timeToEndCollision //chưa va chạm đã kết thúc
		|| this->tXToCollision < 0.0f &&this->tYToCollision<0.0f //time va chạm <0
		|| this->timeToCollision>1.0f) //time va chạm >1 thì xem như k có mà mình sẽ chỉ xét ở frame kế tiếp
	{
		result.velocityX = 0.0f;
		result.velocityY = 0.0f;
		result.timeToColision = this->timeToCollision;		
	}
	else /* Có va chạm */
	{
		/* va chạm theo Y trước -> trái hoặc phải*/
		if (this->tXToCollision > this->tYToCollision)
		{
			result.velocityY - 0.0f;
			if (this->sXToCollision < 0.0f)
				result.velocityY = 1.0f;
			else
				result.velocityY = -1.0f;
		}
		else /* va chạm theo X trước -> trên hoặc dưới*/
		{
			result.velocityX = 0.0f;
			if (this->sYToCollision < 0.0f)
				result.velocityY = 1.0f;
			else
				result.velocityY = -1.0f;
		}
	}


	return result;
}	
