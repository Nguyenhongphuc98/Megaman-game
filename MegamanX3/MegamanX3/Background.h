#pragma once
#ifndef BackGound_H_
#define BackGround_H_
#include"MyTexture.h"
#include"Object.h"
#include"Camera.h"

class BackGround:public Object
{
public:
	BackGround(MyTexture* texture,float x,float y);
	~BackGround();

	void Render();
	BoundingBox GetBoundingBox() { return BoundingBox(); };

};


#endif // !BackGound_H_
