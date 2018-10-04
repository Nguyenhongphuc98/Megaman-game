#include"Game.h"

Game::Game()
{
	megaMan = MegaMan::Instance();
}

Game::~Game()
{
}

void Game::Init()
{
	//khoi tao source
}

void Game::LoadResource()
{
	//load resource man dau tien

	
}

void Game::ProcessInput()
{
}

void Game::Update(float deta)
{
	//update current sense
}

void Game::Render()
{
	//render current sence
	Graphic *graphics = Graphic::Instance();
	LPDIRECT3DDEVICE9 device = graphics->GetD3DDevice();
	LPD3DXSPRITE spriteHander = graphics->GetSpriteHandler();


	if (device->BeginScene())										//Begin draw
	{
		spriteHander->Begin(D3DXSPRITE_ALPHABLEND);				//Begin draw sprite
		device->ColorFill(											//Fill backbuffer
			graphics->GetBackBuffer(),
			NULL,
			D3DCOLOR_XRGB(0, 0, 0));

		//draw current sence here
		
		spriteHander->End();
		megaMan->Render();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
}

void Game::RunGame(float delta)
{

	this->ProcessInput();												//Input
	this->Update(delta);//Update sence
	this->Render();	//Render
}
