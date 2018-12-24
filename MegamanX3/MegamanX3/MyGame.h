#pragma once
#ifndef MyGame_H_
#define MyGame_H_

#include"Game.h"
#include"Megaman.h"
#include"Camera.h"
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
#include"Launchers.h"
#include"DoorShurikein.h"
#include"QuadTree.h"
#include"Genjibo.h"
#include"SubBossCarry.h"
#include"CarryBox.h"
#include"TextStartGame.h"
#include"DoorBlasHornet.h"
#include"BoxBox.h"
#include"Elevator.h"
#include"DieBox.h"
#include"Sound.h"

class MyGame :public Game
{
private:
	Megaman* megaman;
	Map* map;
	Sound* sound;
	vector<Object*> ListObject;

	vector<Object*> ListEnemy;
	vector<Object*> ListVirtualObject; ///ground, launcher, door
	vector<Object*> ListStaticObject;//levator, diebox
	vector<Object*> ListItem;// added waponsystem, so don't need

	//Shurikein* shuri;
	//BlastHornet* hornet;
	//Bee* bee; //clear
	Launchers* launchers;
//	DoorShurikein* doorShuri;
	Genjibo* genjibo;
	//DoorRightShurikein* doorRightShuri;
	SubBossCarry* subboss;
	//CarryBox* carryBox;
	TextStartGame* textStartGame;

	//DoorBlasHornet* doorBlast1, *doorBlast2;
	//DoorBlasHornet* doorBlast3, *doorBlast4;
//	BoxBox* boxbox1,*boxbox2;

	//===============
//	Elevator* elevator;
	//DieBox* dieBox;

public:
	MyGame();
	MyGame(int cmd);
	~MyGame();

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	void Update();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


#endif // !MyGame_H_
