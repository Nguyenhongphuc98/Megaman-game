#pragma once
#ifndef MyGame_H_
#define MyGame_H_

#include"Game.h"
#include"Megaman.h"
#include"Ground.h"
#include"Camera.h"
#include"Background.h"
#include"VirtualObject.h"
#include"WeaponSystem.h"
#include"Map.h"
#include"NotorBanger.h"
#include"BlastHornet.h"
#include"Helit.h"
#include"Bee.h"
#include"Shurikein.h"
#include"HeadGunnerCustomer.h"
#include"CarryArm.h"

class MyGame :public Game
{
private:
	Megaman* megaman;
	Map* map;
	VirtualObject* O1,*O2,*O3,*O4,*O5;
	NotorBanger* notorBanger;
	BlastHornet* blastHornet;
	Helit* helit;
	Bee* bee;
	Shurikein* shurikein;
	HeadGunnerCustomer* head_gunner_customer;
	CarryArm* carryArm;
	
public:
	MyGame();
	MyGame(int cmd);
	~MyGame();

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void Update();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};


#endif // !MyGame_H_
