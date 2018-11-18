#pragma once
#ifndef BlastHornet_H_
#define BlastHornet_H_
#include"ActionObject.h"

#define BLASTHORNET_WIDTH 33*2.5
#define BLASTHORNET_HEIGHT 51*2.5

class BlastHornet:public ActionObject
{
private:
	int count_animation;

public:
	BlastHornet();
	~BlastHornet();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();

	void SetState(State s);
	void SetDirection(Direction d);
};


#endif // !BlastHornet_H_
