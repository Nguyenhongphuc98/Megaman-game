#include "GameObject.h"

GameObject::GameObject()
{
	_Position.x = _Position.y = 0;
	_Size.x = _Size.y = 0;
	_Velocity.x = _Velocity.y = 0;
	isActive = true;
	_CategoryMask = NONE;
	_BitMask = NONE;
	parent = NULL;
}

GameObject::GameObject(GameObject* parent)
{
	this->parent = parent;
	_Position.x = _Position.y = 0;
	_Size.x = _Size.y = 0;
	_Velocity.x = _Velocity.y = 0;
	isActive = true;
	_CategoryMask = NONE;
	_BitMask = NONE;
}

GameObject::~GameObject()
{
}

POINT GameObject::getPosition() const
{
	return _Position;
}

POINT GameObject::getSize() const
{
	return _Size;
}

POINT GameObject::getVelocity() const
{
	return _Velocity;
}

unsigned long GameObject::getBitMask()
{
	return _BitMask;
}

unsigned long GameObject::getCategoryMask()
{
	return _CategoryMask;
}

CollisionType GameObject::getCollisionType()
{
	return collisionType;
}

void GameObject::setPosition(const POINT & p)
{
	_Position = p;
}

void GameObject::setSize(const POINT & p)
{
	_Size = p;
}

void GameObject::setVelocity(const float & x, const float & y)
{
	_Velocity.x = x;
	_Velocity.y = y;
}

void GameObject::setPosition(const float& x, const float& y)
{
	_Position.x = x;
	_Position.y = y;
}

void GameObject::setSize(const float& w, const float& h)
{
	_Size.x = w;
	_Size.y = h;
}

void GameObject::setCollisionType(CollisionType ct)
{
	collisionType = ct;
}

void GameObject::setBitMask(unsigned long bitmask)
{
	_BitMask = bitmask;
}

void GameObject::setCategoryMask(unsigned long categorymask)
{
	_CategoryMask = categorymask;
}

void GameObject::Next(float DeltaTime, bool moveX, bool moveY)
{
	if (moveX)
	{
		_Position.x += _Velocity.x * DeltaTime;
	}
	if (moveY)
	{
		_Position.y += _Velocity.y * DeltaTime;
	}
	else
	{
		//_Velocity.y = 0;
	}
}

void GameObject::Update(float)
{
}

void GameObject::UpdateVelocity(GameObject * Player)
{
}

//void GameObject::Render(SpriteBatch *batch)
//{
//}
