#include"MyGame.h"


MyGame::MyGame()
{
	
}

MyGame::MyGame(int cmd):Game(cmd)
{

}

MyGame::~MyGame()
{
}

void MyGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	this->map->Render();
	this->megaman->Render();
	this->notorBanger->Render();
	WeaponSystem::Instance()->Render();

	G_SpriteHandler->End();
}

void MyGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	megaman->SetState(STAND);

	if (IsKeyDown(DIK_RIGHT))
	{
		megaman->SetDirection(RIGHT);
		megaman->SetState(RUN);
	}

	if(IsKeyDown(DIK_LEFT))
	{
		megaman->SetDirection(LEFT);
		megaman->SetState(RUN);
	}

	if (IsKeyDown(DIK_SPACE))
	{
		megaman->SetState(JUMP);
	}

	if (IsKeyDown(DIK_A))
	{
		megaman->SetState(SHOOT);

		float x, y;
		megaman->GetPosition(x,y);
		Bullet *bullet = new  Speedburner(x, y, megaman->GetDirection(), NORMALBULLET);
		WeaponSystem::Instance()->AddBulletMegaman(bullet);
	}
}

void MyGame::Update()
{
	vector<Object*> *List_object_can_col = new vector<Object*>();
	List_object_can_col->push_back(O1);
	List_object_can_col->push_back(O2);
	List_object_can_col->push_back(O3);
	List_object_can_col->push_back(O4);
	List_object_can_col->push_back(O5);
	megaman->Update(delta_time,List_object_can_col);

	this->notorBanger->Update(delta_time,List_object_can_col);

	float x, y;
	megaman->GetPosition(x, y);
	Camera::Instance()->Update(x, y);
	WeaponSystem::Instance()->Update(delta_time, List_object_can_col);
}

void MyGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->megaman = new Megaman();
	this->megaman->SetDirection(RIGHT);
	this->megaman->SetState(RUN);

	this->notorBanger = new NotorBanger();
	this->notorBanger->SetDirection(RIGHT);
	this->notorBanger->SetState(JUMP);

	O1 = new VirtualObject(505 * G_Scale.y, 0 * G_Scale.x, 547 * G_Scale.x, 72 * G_Scale.y);
	O2 = new VirtualObject(504 * G_Scale.y, 547 * G_Scale.x, 150 * G_Scale.x, 64 * G_Scale.y);
	O3 = new VirtualObject(504 * G_Scale.y, 693 * G_Scale.x, 64 * G_Scale.x, 128 * G_Scale.y);
	O4 = new VirtualObject(504 * G_Scale.y, 757 * G_Scale.x, 66 * G_Scale.x, 111 * G_Scale.y);
	O5 = new VirtualObject(504 * G_Scale.y, 823 * G_Scale.x, 64 * G_Scale.x, 95 * G_Scale.y);
	map = new Map();
}

void MyGame::OnKeyDown(int KeyCode)
{
}
