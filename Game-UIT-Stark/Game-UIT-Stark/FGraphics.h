#pragma once
#ifndef _Graphic_H_
#define _Graphic_H_
#include<d3d9.h>
#include<d3dx9.h>
#include"Global.h"

class Graphic
{
private:
	LPDIRECT3D9			pD3d;
	LPDIRECT3DDEVICE9	pD3dDevice;
	LPDIRECT3DSURFACE9	backBuffer;
	LPD3DXSPRITE		spriteHandler;

	static Graphic*		_instance;
	Graphic();

public:

	~Graphic();

	static Graphic*		Instance();
	void Init();

	LPDIRECT3DSURFACE9	GetBackBuffer();
	LPDIRECT3D9			GetD3D();
	LPDIRECT3DDEVICE9	GetD3DDevice();
	LPD3DXSPRITE		GetSpriteHandler();

	LPDIRECT3DSURFACE9	LoadSurface(char *fileName, D3DCOLOR transparencyColor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DSURFACE9	CreateSurface(D3DCOLOR fillColor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9	LoadTeture(char *filename, D3DCOLOR transparencyColor = D3DCOLOR_XRGB(0, 0, 0));
	void				DrawSurface(LPDIRECT3DSURFACE9 surface, RECT* source, RECT* des);
	void				DrawTexture(LPDIRECT3DTEXTURE9 Texture, RECT* sourceRect, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR3 rotationCenter = D3DXVECTOR3(0,0, 0));
};
#endif