#pragma once
#ifndef WeaponSystem_H_
#define WeaponSystem_H_
#include<list>
#include"Speedburner.h"
#include"NotorbangerBullet.h"
#include"MegamanBullet1.h"
#include"MegamanBullet2.h"
#include"MegamanBullet3.h"
#include"DashSpark.h"
#include"DashSmoke.h"
#include"HelitBullet.h"
#include"MetaCapsuleBullet.h"

class WeaponSystem
{
private:
	std::list<Bullet*> WeaponMegaman;
	std::list<Bullet*> WeaponEnemy;

	static WeaponSystem* instance;
public:
	WeaponSystem();
	~WeaponSystem();

	static WeaponSystem* Instance();

	void UpdateTeamMegaman(DWORD dt, vector<Object*> *List_object_can_col);
	void UpdateTeamEnemies(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();

	std::list<Bullet*> GetListWeaponMegaman();
	std::list<Bullet*> GetListWeaponEnemy();

	void AddBulletMegaman(Bullet* bullet);
	void AddBulletEnemy(Bullet* bullet);
};


#endif // !WeaponSystem_H_
