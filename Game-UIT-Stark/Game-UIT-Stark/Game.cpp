#include"Game.h"
RECT *rSource;

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
	//Trace::Log("on process input");
	FKeyBoard *keyboard = FKeyBoard::getInstance();
	keyboard->Update();
	if (keyboard->IsKeyDown(DIK_LEFT))
	{
		megaMan->SetDirection(Global::LEFT);
		megaMan->SetStatus(Global::RUN);
		Trace::Log("on left key");
	}

	if (keyboard->IsKeyDown(DIK_RIGHT))
	{
		megaMan->SetDirection(Global::RIGHT);
		megaMan->SetStatus(Global::RUN);
		Trace::Log("on right key");
	}

	if(keyboard->IsKeyUp(DIK_LEFT)|| keyboard->IsKeyUp(DIK_RIGHT))
		megaMan->SetStatus(Global::STAND);
}

void Game::Update(float deta)
{
	//update current sense
	vector<Object*> list;
	megaMan->Update(deta, list);
}

void Game::Render()
{
	//render current sence
	Graphic *graphics = Graphic::Instance();
	LPDIRECT3DDEVICE9 device = graphics->GetD3DDevice();
	LPD3DXSPRITE spriteHander = graphics->GetSpriteHandler();
	LPDIRECT3DSURFACE9 t = graphics->LoadSurface("bground.png");


	if (device->BeginScene())										//Begin draw
	{
			//Begin draw sprite
		device->ColorFill(											//Fill backbuffer
			graphics->GetBackBuffer(),
			NULL,
			D3DCOLOR_XRGB(0, 0, 0));

		//draw current sence here
		spriteHander->Begin(D3DXSPRITE_ALPHABLEND);
		RECT *rSource=new RECT;
		rSource->top = 10;
		rSource->left = 590;
		rSource->right = 846;
		rSource->bottom = 175;
		//spriteHander->Draw(t, rSource, &D3DXVECTOR3(-100, -100, 0),
		//	&D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
		graphics->DrawSurface(t, rSource, NULL);
		megaMan->Render();
		spriteHander->End();

		
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
