#include"Bullet.h"

Bullet::Bullet()
{
	this->damage = 1;
}

Bullet::~Bullet()
{
}

void Bullet::Render()
{
	D3DXVECTOR2 position = Camera::Instance()->GetPositionInViewPort(this->x, this->y);
	this->animation->Render(this->state, this->direction, position);
	this->animation->Next(this->state);
}

bool Bullet::IsDestroyed()
{
	return false;
}

int Bullet::GetDamege()
{
	return this->damage;
}
