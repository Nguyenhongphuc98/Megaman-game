#pragma once
#ifndef Texture_H_
#define Texture_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class MyTexture
{
public:
	char* path;
	RECT size;
	D3DCOLOR transparent_color;
	LPDIRECT3DTEXTURE9 texture;


public:
	MyTexture();
	~MyTexture();

	MyTexture(const MyTexture &texture);
	MyTexture(char* path,D3DCOLOR transparent_color);
	//vẽ texture tại vị trí (x, y) trên màn hình

	void Load();
	void Draw(int x, int y);

};


#endif // !Texture_H_
