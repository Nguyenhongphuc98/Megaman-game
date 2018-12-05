#include"WeaponSystem.h"
WeaponSystem* WeaponSystem::instance;

WeaponSystem::WeaponSystem()
{
}

WeaponSystem::~WeaponSystem()
{
}

WeaponSystem * WeaponSystem::Instance()
{
	if (!instance)
		instance = new WeaponSystem();
	return instance;
}

void WeaponSystem::UpdateTeamMegaman(DWORD dt, vector<Object*>* List_object_can_col)
{
	for (std::list<Bullet*>::iterator bullet = WeaponMegaman.begin(); bullet != WeaponMegaman.end();) 
	{
		(*bullet)->Update(dt, List_object_can_col);
		if ((*bullet)->IsDestroyed())
			WeaponMegaman.erase(bullet++);
		else
		{
			bullet++;
		}
	}	
}

void WeaponSystem::UpdateTeamEnemies(DWORD dt, vector<Object*>* List_object_can_col)
{
	for (std::list<Bullet*>::iterator bullet = WeaponEnemy.begin(); bullet != WeaponEnemy.end();)
	{
		(*bullet)->Update(dt, List_object_can_col);
		if ((*bullet)->IsDestroyed())
			bullet = WeaponEnemy.erase(bullet);
		else
		{
			bullet++;
		}
	}
}

void WeaponSystem::Render()
{
	for (std::list<Bullet*>::iterator bullet = WeaponMegaman.begin(); bullet != WeaponMegaman.end(); bullet++)
	{
		(*bullet)->Render();
	}

	for (std::list<Bullet*>::iterator bullet = WeaponEnemy.begin(); bullet != WeaponEnemy.end(); bullet++)
	{
		(*bullet)->Render();
	}
}

std::list<Bullet*> WeaponSystem::GetListWeaponMegaman()
{
	return this->WeaponMegaman;
}

std::list<Bullet*> WeaponSystem::GetListWeaponEnemy()
{
	return this->WeaponEnemy;
}

void WeaponSystem::AddBulletMegaman(Bullet * bullet)
{
	this->WeaponMegaman.push_back(bullet);
}

void WeaponSystem::AddBulletEnemy(Bullet * bullet)
{
	this->WeaponEnemy.push_back(bullet);
}
