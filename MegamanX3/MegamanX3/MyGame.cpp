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
	this->blastHornet->Render();
	this->helit->Render();
	this->bee->Render();
	this->shurikein->Render();
	this->head_gunner_customer->Render();

	G_Scale = D3DXVECTOR2(1, 1);
	G_ScaleFlipX= D3DXVECTOR2(-1, 1);
	WeaponSystem::Instance()->Render();
	G_Scale = D3DXVECTOR2(2.5, 2.5);
	G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);

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
		megaman->GetPosition(x, y);
		Bullet *bullet = new  Speedburner(x, y, megaman->GetDirection(), NORMALBULLET);
		WeaponSystem::Instance()->AddBulletMegaman(bullet);
	}

	if (IsKeyDown(DIK_UP)) {
		megaman->SetState(CLIMB);
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
	this->shurikein->Update(delta_time, List_object_can_col);
	this->helit->Update(delta_time, List_object_can_col);
	this->bee->Update(delta_time, List_object_can_col);
	this->head_gunner_customer->Update(delta_time, List_object_can_col);
	this->blastHornet->Update(delta_time, List_object_can_col);

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
	this->notorBanger->SetState(SHOOT90);
	
	this->blastHornet = new BlastHornet();
	this->blastHornet->SetDirection(RIGHT);
	this->blastHornet->SetState(REDKNEE);

	this->helit = new Helit();
	this-> helit->SetDirection(RIGHT);
	this->helit->SetState(RUN);

	this->bee = new Bee();
	this->bee->SetDirection(RIGHT);
	this->bee->SetState(FLAPPING);

	this->shurikein = new Shurikein();
	this->shurikein->SetDirection(RIGHT);
	this->shurikein->SetState(APPEAR);

	this->head_gunner_customer = new HeadGunnerCustomer();
	this->head_gunner_customer->SetDirection(RIGHT);
	this->head_gunner_customer->SetState(SHOOTABOVE);

	O1 = new VirtualObject(1030 * G_Scale.y, 4 * G_Scale.x, 351 * G_Scale.x, 77 * G_Scale.y);
	O2 = new VirtualObject(1030 * G_Scale.y, 359 * G_Scale.x, 160 * G_Scale.x, 128 * G_Scale.y);
	O3 = new VirtualObject(1030 * G_Scale.y, 519 * G_Scale.x, 126 * G_Scale.x, 177 * G_Scale.y);
	O4 = new VirtualObject(1030 * G_Scale.y, 645 * G_Scale.x, 210 * G_Scale.x, 80 * G_Scale.y);
	O5 = new VirtualObject(1030 * G_Scale.y, 950 * G_Scale.x, 80 * G_Scale.x, 80 * G_Scale.y);
	map = new Map();
}

void MyGame::OnKeyDown(int KeyCode)
{
	/*if (KeyCode == DIK_A)
	{
		float x, y;
		megaman->GetPosition(x, y);
		Bullet *bullet = new  Speedburner(x, y, megaman->GetDirection(), NORMALBULLET);
		WeaponSystem::Instance()->AddBulletMegaman(bullet);
	}*/
}
