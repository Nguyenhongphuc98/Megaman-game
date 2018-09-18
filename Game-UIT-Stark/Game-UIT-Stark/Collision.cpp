#include"Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

ResultColision Collision::ProcessCollisionSweptAABB(CollisionRect object1, CollisionRect object2)
{
	//Xét trường hợp cả 1 vật đều di chuyển, ta giả sử object2 đứng yên
	//bằng cách sử dụng công thức vận tốc tương đối
	object1.SetVelocityX(object1.GetVelocityX() - object2.GetVelocityX());
	object1.SetVelocityY(object1.GetVelocityY() - object2.GetVelocityY());

	//caculate SX to Collision and exit Collision
	if (object1.GetVelocityX() > 0.0f) {
		this->sXToCollision = object2.GetLeft() - (object1.GetLeft() + object1.GetWidth());
		this->sXToEndCollision = (object2.GetLeft() + object2.GetWidth()) - object1.GetLeft();
	}
	else
	{
		this->sXToCollision = object2.GetLeft() + object2.GetWidth() - object1.GetLeft();
		this->sXToEndCollision = object2.GetLeft() - (object1.GetLeft() + object1.GetWidth());
	}

	//caculate SY
	if (object1.GetVelocityY > 0.0f)
	{
		this->sYToCollision = object2.GetTop()-object2.GetHeight()-object1.GetTop(); 
		this->sYToEndCollision = object2.GetTop() - (object1.GetTop() - object1.GetHeight());
	}
	else
	{
		this->sYToCollision = object2.GetTop() - (object1.GetTop() - object1.GetHeight());
		this->sYToEndCollision = (object2.GetTop()-object2.GetHeight()) - object1.GetTop();
	}

	//tính thời gian để xảy ra va chạm	
	
	if (object1.GetVelocityX == 0.0f)
	{
		this->tXToCollision = -std::numeric_limits<float>::infinity(); //am vo cuc
		this->tXToEndCollision = std::numeric_limits<float>::infinity();
	}
	else
	{
		this->tXToCollision = this->sXToCollision / object1.GetVelocityX();
		this->tXToEndCollision = this->sXToEndCollision / object1.GetVelocityX();
	}

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

	//ở đây tính toán kết quả của va chạm
	///vieets sau
	//gio met qua roi :((
	return ResultColision();
}
