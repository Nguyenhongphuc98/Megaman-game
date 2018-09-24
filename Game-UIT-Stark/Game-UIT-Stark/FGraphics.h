#pragma once
#ifndef _Graphic_H_
#define _Graphic_H_
#include<d3d9.h>
#include<d3dx9.h>

class Graphic
{
private:
	LPDIRECT3D9			pD3d;
	LPDIRECT3DDEVICE9	pD3dDevice;
	LPDIRECT3DSURFACE9	backBuffer;

	static Graphic*		_instance;
	Graphic();

public:

	~Graphic();

	static Graphic*		Instance();
	void Init();

	LPDIRECT3DSURFACE9	GetBackBuffer();
	LPDIRECT3D9			GetD3D();
	LPDIRECT3DDEVICE9	GetD3DDevice();

	LPDIRECT3DSURFACE9	LoadSurface(char *fileName, D3DCOLOR transparencyColor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DSURFACE9	CreateSurface(D3DCOLOR fillColor = D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9	LoadTeture(char *filename, D3DCOLOR transparencyColor = D3DCOLOR_XRGB(0, 0, 0));
	void				DrawSurface(LPDIRECT3DSURFACE9 surface, RECT* source, RECT* des);

};
#endif