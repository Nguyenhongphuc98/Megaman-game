#include"Game.h"
RECT *rSource;


Game::Game()
{
	megaMan = MegaMan::Instance();
	ball = new Ball();

	bar = new Bar();
	bar->SetLocation(100, 180);
	barRight = new Bar();
	barRight->SetLocation(700, 200);

	//wall
	top = new Wall();
	top->SetStatus(Global::HORIZONTAL);
	top->SetLocation(0, 1);
	bottom = new Wall();
	bottom->SetStatus(Global::HORIZONTAL);
	bottom->SetLocation(0, 579);
	left = new Wall();
	left->SetStatus(Global::VERTICAL);
	left->SetLocation(0, 0);
	right = new Wall();
	right->SetStatus(Global::VERTICAL);
	right->SetLocation(780, 0);
}

Game::~Game()
{
}

void Game::Init(HINSTANCE hInstance, HWND hWnd)
{
	
	//khoi tao source
	_HInstance = hInstance;
	_HWnd = hWnd;

	FMouse::Init(_HInstance, _HWnd);
}

void Game::LoadResource()
{
	
	//load resource man dau tien

	
}

void Game::ProcessInput()
{
	//Trace::Log("on process input");
#pragma region Keyboard

	FKeyBoard *keyboard = FKeyBoard::getInstance();
	keyboard->Update();
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
		bar->SetDirection(Global::UP);
		bar->SetStatus(Global::RUN);
	}

	if (keyboard->IsKeyDown(DIK_DOWN))
	{
		bar->SetDirection(Global::DOWN);
		bar->SetStatus(Global::RUN);
	}

	if (keyboard->IsKeyUp(DIK_LEFT) || keyboard->IsKeyUp(DIK_RIGHT))
	{
		megaMan->SetStatus(Global::STAND);
		Trace::Log("key up");
	}

	if (keyboard->IsKeyUp(DIK_UP) || keyboard->IsKeyUp(DIK_DOWN))
	{
		bar->SetStatus(Global::STAND);
		Trace::Log("key up");
	}

#pragma endregion

#pragma region Mouse
	
	FMouse::ProcessMouseInformation();
	

		if (FMouse::GetMouse(0))
		{
			barRight->SetDirection(Global::DOWN);
			barRight->SetStatus(Global::RUN);
			Trace::Log("Mouse left");
		}
		if (FMouse::GetMouse(1))
		{
			barRight->SetDirection(Global::UP);
			barRight->SetStatus(Global::RUN);
			Trace::Log("Mouse right");
		}

		if (!(FMouse::GetMouse(1) || FMouse::GetMouse(0)))
		{
			barRight->SetStatus(Global::STAND);
			//Trace::Log("key up");
		}
	FMouse::ClearBuffedInput();
#pragma endregion

}

void Game::Update(float deta)
{
	//update current sense
	vector<Object*> list;
	list.clear();
	list.push_back(bar);
	list.push_back(barRight);
	list.push_back(top);
	list.push_back(bottom);
	list.push_back(left);
	list.push_back(right);

	//megaMan->Update(deta, list);
	bar->Update(deta, list);
	barRight->Update(deta, list);
	ball->Update(deta, list);
}

void Game::Render()
{
	//render current sence
	Graphic *graphics = Graphic::Instance();
	LPDIRECT3DDEVICE9 device = graphics->GetD3DDevice();
	LPD3DXSPRITE spriteHander = graphics->GetSpriteHandler();
	


	if (device->BeginScene())										//Begin draw
	{
			//Begin draw sprite
		device->ColorFill(											//Fill backbuffer
			graphics->GetBackBuffer(),
			NULL,
			D3DCOLOR_XRGB(0, 0, 0));

		//draw current sence here
		spriteHander->Begin(D3DXSPRITE_ALPHABLEND);

		
		ball->Render();
		bar->Render();
		barRight->Render();
		top->Render();
		bottom->Render();
		megaMan->Render();
		left->Render();
		right->Render();

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
