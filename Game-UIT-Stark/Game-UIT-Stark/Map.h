#pragma once
#ifndef _Map_H_
#define _Map_H_
#include"FGraphics.h"
#include"define.h"
#include"Camera.h"

#define WIDTH_IMAGE_BACKGROUND 5388
#define HEIGHT_IMAGE_BACKGROUND 1804

class  Map
{
private:
	D3DXVECTOR3 position;
	LPDIRECT3DTEXTURE9 mapBackground;
	int mapWidth;
	int mapHeight;

public:
	 Map();
	~ Map();

	void LoadResource();
	void Render();
	void SetLocation(float x, float y);
};


#endif // !_Map_H_
