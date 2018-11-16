#pragma once
#ifndef Map_H_
#define Map_H_

#include"Sprite.h"
#include"Camera.h"
#include<string>
#include<d3dx9.h>
#define WIDTH_MAP_IMAGE 7947
#define HEIGHT_MAP_IMAGE 2067

//When draw map, must convert position scale 
//change oy worldport to imageport(~cameraport)
class Map
{
private:
	MyTexture* texture;
	Sprite* background;

public:
	Map();
	~Map();

	void LoadResource();
	void Render();
};


#endif // !Map_H_
