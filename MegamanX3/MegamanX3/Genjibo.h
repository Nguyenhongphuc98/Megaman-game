#pragma once
#ifndef Genjibo_H_
#define Genjibo_H_

#define GENJIBO_VY 0.05f

#include"ActionObject.h"
#include"Shurikein.h"

class Genjibo:public ActionObject
{
private:
	bool actived;
	float time_start_stand;
	float time_start_create_shurikein;

	static Genjibo* instance;

public:
	Genjibo(int x, int y, int w, int h, Direction d);
	~Genjibo();

	static Genjibo* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	void SetState(State s);
	void SetDirection(Direction d);
	void SetActived(bool allow) { this->actived = allow; }
};


#endif // !Genjibo_H_
