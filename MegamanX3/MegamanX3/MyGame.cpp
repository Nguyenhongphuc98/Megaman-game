#include"MyGame.h"


//MyGame::MyGame()
//{
//	
//}

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

	this->background->Render();
	this->ground1->Render();
	this->megaman->Render();
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
	List_object_can_col->push_back(ground1);
	List_object_can_col->push_back(vO1);
	megaman->Update(delta_time,List_object_can_col);

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

	this->ground1 = new Ground();
	MyTexture *t = new MyTexture((char*)"SourceImage\\bg1.png", D3DCOLOR_XRGB(255, 255, 255));
	this->background = new BackGround(t, 1413, 257);

	vO1 = new VirtualObject(0, 828, 526, 142);
}

void MyGame::OnKeyDown(int KeyCode)
{
}
