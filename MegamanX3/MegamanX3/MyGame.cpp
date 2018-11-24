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


	for (auto o : ListObject) {	
		o->Render();
	}

	/*G_Scale = D3DXVECTOR2(1, 1);
	G_ScaleFlipX= D3DXVECTOR2(-1, 1);*/
	WeaponSystem::Instance()->Render();
	//G_Scale = D3DXVECTOR2(2.5, 2.5);
	//G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);

	G_SpriteHandler->End();
}

void MyGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
//	megaman->SetState(STAND);

	int check_key_down = false;
	if (IsKeyDown(DIK_RIGHT))
	{
		megaman->SetDirection(RIGHT);
		megaman->SetState(RUN);
		check_key_down = true;
	}

	if(IsKeyDown(DIK_LEFT))
	{
		megaman->SetDirection(LEFT);
		megaman->SetState(RUN);
		check_key_down = true;
	}

	if (IsKeyDown(DIK_Z)&&megaman->IsGround())
	{
		megaman->SetState(JUMP);
		check_key_down = true;
		megaman->SetGround(false);
	}

	if (IsKeyDown(DIK_A))
	{
		megaman->SetState(SHOOT);
		float x, y;
		megaman->GetPosition(x, y);
		Bullet *bullet = new  Speedburner(x, y, megaman->GetDirection(), NORMALBULLET);
		WeaponSystem::Instance()->AddBulletMegaman(bullet);
		check_key_down = true;
	}

	if (IsKeyDown(DIK_UP)) {
		megaman->SetState(CLIMB);
		check_key_down = true;
	}

	if (IsKeyDown(DIK_D)) {
		megaman->SetState(DASH);
		check_key_down = true;
	}

	if (!check_key_down&&megaman->IsGround())
		megaman->SetState(STAND);
}

void MyGame::Update()
{
	float x, y;
	megaman->GetPosition(x, y);
	Camera::Instance()->Update(x, y);

	this->ListObject.clear();
	this->ListObject = QuadTree::Instance()->GetListObject(Camera::Instance()->GetBound());

	this->ListEnemy.clear();
	this->ListItem.clear();
	this->ListVirtualObject.clear();
	
	vector<Object*> List_temp;
	for (auto o : ListObject) 
	{
		switch (o->GetNameObject())
		{
		case CARRYARM:
		case HEADGUNNERCUSTOMER:
		case HELIT:
		case NOTORBANGER:
			ListEnemy.push_back(o);
			break;

		case VIRTUALOBJECT:
			ListVirtualObject.push_back(o);
			break;

			//item object
		default:
			break;
		}	
	}

	for (auto o : ListEnemy) {
		o->Update(delta_time, &ListVirtualObject);
	}

	megaman->Update(delta_time, &ListVirtualObject);
	WeaponSystem::Instance()->Update(delta_time, &ListObject);
}

void MyGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->megaman = Megaman::Instance();
	//this->megaman = new Megaman();
	this->megaman->SetDirection(RIGHT);
	this->megaman->SetState(STAND);

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
