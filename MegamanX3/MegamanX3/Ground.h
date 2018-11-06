#pragma once
#ifndef Ground_H_
#define Ground_H_
#include"Object.h"
#include"Camera.h"

#define GROUNG_WIDTH 828
#define GROUND_HEIGHT 146

class Ground:public Object
{
public:
	Ground();
	~Ground();

	BoundingBox GetBoundingBox();

	void Update(DWORD dt) {};
	void Render();
	void LoadResource();
};


#endif