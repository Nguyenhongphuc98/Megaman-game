#pragma once
#ifndef NotorbangerBullet_H_
#define NotorbangerBullet_H_
#include"Bullet.h"
#include"Sound.h"


#define NOTORBANGER_BULLET_VX 0.5
#define NOTORBANGER_BULLET_VY 0.5
#define NOTORBANGER_BULLET_WIDTH 10*G_Scale.x
#define NOTORBANGER_BULLET_HEIGHT 10*G_Scale.y
#define NOTORBANGER_BULLET_DAMAGE 1

class NotorbangerBullet:public Bullet
{
private:
	float time_start;
	float time_live;
	float distance_has_shot_x;
	float distance_has_shot_y;
	
	bool finish_smoke;

public:
	NotorbangerBullet(float x, float y, Direction d, float angle);
	~NotorbangerBullet();

	virtual void Update(DWORD dt, vector<Object*> *List_object_can_col);
	virtual void Render();
	virtual BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);

	bool IsDestroyed();
};


#endif // !NotorbangerBullet_H_
