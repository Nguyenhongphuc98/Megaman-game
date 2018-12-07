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
	WeaponSystem::Instance()->Render();
	this->megaman->Render();		


	for (auto o : ListObject) {	
		o->Render();
	}

	this->hornet->Render();
	this->bee->Render();
//	this->shuri->Render();
	this->launchers->Render();

	

	G_SpriteHandler->End();
}

void MyGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	EControler controler =NoneControl;

	if (IsKeyDown(DIK_LEFT)) {
		this->megaman->SetDirection(LEFT);
		controler = LeftControl;
	}

	if (IsKeyDown(DIK_RIGHT)) {
		this->megaman->SetDirection(RIGHT);
		controler = RightControl;
	}

	if (IsKeyDown(DIK_X)) {
		controler = DashControl;
		if (megaman->IsCanDash())
		{
			Bullet *bullet, *bullet2;
			float x, y;
			megaman->GetPosition(x, y);
			bullet = new DashSpark(x-6, y, (megaman->GetDirection()==RIGHT)?LEFT:RIGHT);
			bullet2 = new DashSmoke(x - 6, y, (megaman->GetDirection() == RIGHT) ? LEFT : RIGHT);

			WeaponSystem::Instance()->AddBulletMegaman(bullet);
			WeaponSystem::Instance()->AddBulletMegaman(bullet2);
		}
	}

	if (IsKeyDown(DIK_A)) {
		if (!megaman->IsCharging())
		{
			controler = ShootControl;
			megaman->SetTimeStartPressA();
		}	
	}

	if (IsKeyDown(DIK_Z)) {
		controler = JumpControl;
	}



	State new_state= this->megaman->GetNewState(megaman->GetState(), controler);
	this->megaman->SetState(new_state);
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

	ListVirtualObject.push_back(this->launchers);
	this->launchers->Update(delta_time,&List_temp);

	megaman->Update(delta_time, &ListVirtualObject);
	WeaponSystem::Instance()->UpdateTeamEnemies(delta_time, &ListVirtualObject);
	WeaponSystem::Instance()->UpdateTeamMegaman(delta_time, &ListEnemy);

	this->hornet->Update(delta_time, &ListVirtualObject);
	this->bee->Update(delta_time, &ListVirtualObject);
	this->shuri->Update(delta_time, &ListVirtualObject);
}

void MyGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->megaman = Megaman::Instance();
	//this->megaman = new Megaman();
	this->megaman->SetDirection(RIGHT);
	this->megaman->SetState(STAND);

	this->shuri = new Shurikein();
	this->bee = new Bee();
	this->hornet = new BlastHornet();
	this->launchers = new Launchers();

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

void MyGame::OnKeyUp(int KeyCode)
{
	

	if (KeyCode == DIK_A)
	{
		//megaman->SetState(megaman->GetShootOldState());

		State new_state = this->megaman->GetNewState(megaman->GetState(), ShootControl);
		this->megaman->SetState(new_state);
		this->megaman->ResetAnimation();

		float x, y;
		megaman->GetPosition(x, y);

		(megaman->GetState() == STANDSHOOT)? y += 2:y += 6;
		(megaman->GetDirection() == RIGHT) ? x += 18 : x -= 18;
		
		//Bullet *bullet = new  Speedburner(x, y, megaman->GetDirection(), NORMALBULLET);
		Bullet *bullet;
		if(megaman->GetTimePressA()<500)
		bullet= new MegamanBullet1(x, y, megaman->GetDirection());
		else
		{
			if(megaman->GetTimePressA() < 1300)
			bullet = new MegamanBullet2(x, y, megaman->GetDirection());
			else
			{
				bullet = new MegamanBullet3(x, y, megaman->GetDirection());
			}
		}
		WeaponSystem::Instance()->AddBulletMegaman(bullet);
		megaman->ResetTimeStartPressA();
	}

	/*if (megaman->IsFinishUpGun() && megaman->IsGround())
		megaman->SetState(STAND);*/

	if (KeyCode == DIK_X) {
		megaman->SetAllowDash(true);
	}
}
