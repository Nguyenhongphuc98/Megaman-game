#pragma once
#ifndef ItemBlood_H_
#define ItemBlood_H_
#include"Bullet.h"

#define ITEMBLOOD_WIDTH 22
#define ITEMBLOOD_HEIGHT 22
#define ITEMBLOOD_BLOOD -3

class ItemBlood :public Bullet
{
private:

public:
	ItemBlood(float x, float y);
	~ItemBlood();
	virtual void Update(DWORD dt, vector<Object*> *List_enemy_objects);//process col with enemi
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();
	void SetDestroying(bool destroying) { this->destroyed = destroying; this->destroying = destroying; }

};


#endif // !ItemBlood_H_
