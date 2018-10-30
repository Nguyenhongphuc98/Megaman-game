#include"Game.h"
RECT *rSource;


Game::Game()
{
	LoadResource();
}

Game::~Game()
{
}

void Game::Init()
{
	FMouse::Init(Window::Instance()->GetHinstance(), Window::Instance()->GetHWND());
}

void Game::LoadResource()
{
	
	//load resource man dau tien
	megaMan = MegaMan::Instance();
	map = new Map();
	br1 = new Brick();
	br1->SetLocation(0, 100);
	br2 = new Brick();
	br2->SetLocation(150, 200);
	br3 = new Brick();
	br3->SetLocation(240, 250);
	br4 = new Brick();
	br4->SetLocation(310, 300);
	br5 = new Brick();
	br5->SetLocation(374, 300);
	br6 = new Brick();
	br6->SetLocation(438, 300);
	br7 = new Brick();
	br7->SetLocation(502, 300);
	br8 = new Brick();
	br8->SetLocation(566, 300);
}

void Game::ProcessInput()
{
	//Trace::Log("on process input");
#pragma region Keyboard

	FKeyBoard *keyboard = FKeyBoard::getInstance();
	keyboard->Update();

	//megaMan->SetStatus(Global::STAND);
	if (keyboard->IsKeyDown(DIK_LEFT))
	{
		megaMan->SetDirection(Global::LEFT);
		megaMan->SetStatus(Global::RUN);
		//Trace::Log("on left key");
	}

	if (keyboard->IsKeyDown(DIK_RIGHT))
	{
		megaMan->SetDirection(Global::RIGHT);
		megaMan->SetStatus(Global::RUN);
		//Trace::Log("on right key");
	}

	if (keyboard->IsKeyDown(DIK_UP))
	{
		//megaMan->SetDirection(Global::UP);
		megaMan->SetStatus(Global::JUMP);
	}

	if (keyboard->IsKeyDown(DIK_DOWN))
	{
		megaMan->SetDirection(Global::DOWN);
		megaMan->SetStatus(Global::JUMP);
	}

	if (keyboard->IsKeyUp(DIK_LEFT) || keyboard->IsKeyUp(DIK_RIGHT))
	{
		megaMan->SetStatus(Global::STAND);
		Trace::Log("key up");
	}

	if (keyboard->IsKeyUp(DIK_UP))
	{
		megaMan->SetDirection(Global::RIGHT);
		megaMan->SetStatus(Global::STAND);
		Trace::Log("key up");
	}

#pragma endregion

#pragma region Mouse
	
	//FMouse::ProcessMouseInformation();
	//

	//	if (FMouse::GetMouse(0))
	//	{
	//		barRight->SetDirection(Global::DOWN);
	//		barRight->SetStatus(Global::RUN);
	//		Trace::Log("Mouse left");
	//	}
	//	if (FMouse::GetMouse(1))
	//	{
	//		barRight->SetDirection(Global::UP);
	//		barRight->SetStatus(Global::RUN);
	//		Trace::Log("Mouse right");
	//	}

	//	if (!(FMouse::GetMouse(1) || FMouse::GetMouse(0)))
	//	{
	//		barRight->SetStatus(Global::STAND);
	//		//Trace::Log("key up");
	//	}
	//FMouse::ClearBuffedInput();
#pragma endregion

}

void Game::Update(float deta)
{
	//update current sense
	vector<Object*> list;
	list.push_back(br1);
	list.push_back(br2);
	list.push_back(br3);
	list.push_back(br4);
	list.push_back(br5);
	list.push_back(br6);
	list.push_back(br7);
	list.push_back(br8);
	megaMan->Update(deta, list);
	Camera::Instance()->Update(megaMan->GetLocationX(),megaMan->GetLocationY());
}

void Game::Render()
{
	//render current sence
	Graphic *graphics = Graphic::Instance();
	LPDIRECT3DDEVICE9 device = graphics->GetD3DDevice();
	LPD3DXSPRITE spriteHander = graphics->GetSpriteHandler();
	

	if (device->BeginScene())//Begin draw
	{
		//Begin draw sprite
		//Fill backbuffer
		device->ColorFill(graphics->GetBackBuffer(),NULL,D3DCOLOR_XRGB(0, 0, 0));
			
		//draw current sence here
		spriteHander->Begin(D3DXSPRITE_ALPHABLEND);

		//map->Render();

		megaMan->Render();
		br1->Render();
		br2->Render();
		br3->Render();
		br4->Render();
		br5->Render();
		br6->Render();
		br7->Render();
		br8->Render();

		spriteHander->End();
		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

void Game::RunGame(float delta)
{
	//Trace::Log("run game");
	this->ProcessInput();	//Input
	this->Update(delta);	//Update sence
	this->Render();			//Render
}
