#include "MegaMan.h"

void MegaMan::Update(float deltaTime)
{

}

void MegaMan::Render()
{
	animation->ListSprite[status]->Render();
}

MegaMan * MegaMan::Instance()
{
	if (!instance)
		instance = new MegaMan();
	return instance;
}
