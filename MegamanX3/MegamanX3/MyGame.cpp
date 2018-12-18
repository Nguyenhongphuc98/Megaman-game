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
		
	this->textStartGame->Render();

	for (auto o : ListObject) {	
		o->Render();
	}

	this->hornet->Render();
	this->bee->Render();
	this->launchers->Render();
	this->doorShuri->Render();
	this->genjibo->Render();
	//this->shuri->Render();
	//this->doorRightShuri->Render();
	this->subboss->Render();
	//this->carryBox->Render();

	//======================================
	this->doorBlast1->Render();

	WeaponSystem::Instance()->Render();
	this->megaman->Render();

	G_SpriteHandler->End();
}

void MyGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (IsKeyDown(DIK_RETURN)) {
		this->megaman->SetAutoMoving(false);
		this->textStartGame->SetDestroy(true);
	}

	EControler controler =NoneControl;

	if (IsKeyDown(DIK_LEFT)&& IsKeyDown(DIK_A)&&(this->megaman->GetTimePressA() < MEGAMAN_TIME_NEED_TO_CHARING)) {
		this->megaman->SetDirection(LEFT);
		this->megaman->SetState(RUNSHOOT);
		return;
	}

	if (IsKeyDown(DIK_RIGHT) && IsKeyDown(DIK_A)&&(this->megaman->GetTimePressA() < MEGAMAN_TIME_NEED_TO_CHARING)) {
		this->megaman->SetDirection(RIGHT);
		this->megaman->SetState(RUNSHOOT);
		return;
	}

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

		float x, y;
		megaman->GetPosition(x, y);
		if (megaman->IsCanDash())
		{
			Bullet *bullet;
			
			bullet = new DashSpark(x-6, y, (megaman->GetDirection()==RIGHT)?LEFT:RIGHT);
			WeaponSystem::Instance()->AddBulletMegaman(bullet);
			
			Bullet  *bullet2;
			bullet2 = new DashSmoke(x - 6, y, (megaman->GetDirection() == RIGHT) ? LEFT : RIGHT);
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
		if (megaman->IsCanJump())
		{
			controler = JumpControl;
			this->megaman->SetAllowJump(false);
			this->megaman->SetStartJump();
		}
		
		if (megaman->GetDistanceJump() > MEGAMAN_DISTANCE_ALLOW_BOUNS&&!megaman->IsBounused())
		{
			megaman->SetBonus(MEGAMAN_JUMP_BONUS_SPEED);
		}
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
		case SHURIKEIN:
		//case DOOR:
			ListEnemy.push_back(o);
			break;

		case VIRTUALOBJECT:
		case DOOR:
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
	ListVirtualObject.push_back(this->doorShuri);
	//ListVirtualObject.push_back(this->doorRightShuri);

	//=====================================
	ListVirtualObject.push_back(this->doorBlast1);
	this->doorBlast1->Update(delta_time, &List_temp);


	this->launchers->Update(delta_time,&List_temp);
	this->doorShuri->Update(delta_time, &List_temp);
	this->genjibo->Update(delta_time, &List_temp);
	DoorRightShurikein::Instance()->Update(delta_time, &List_temp);
	this->subboss->Update(delta_time, &List_temp);

	//ListEnemy.push_back(this->shuri);
	ListEnemy.push_back(this->subboss);

	megaman->Update(delta_time, &ListVirtualObject);
	megaman->ProcessCollisionBullet(WeaponSystem::Instance()->GetListWeaponEnemy());
	megaman->ProcessCollisionEnemy(ListEnemy);

	WeaponSystem::Instance()->UpdateTeamEnemies(delta_time, &ListVirtualObject);
	WeaponSystem::Instance()->UpdateTeamMegaman(delta_time, &ListEnemy);

	this->hornet->Update(delta_time, &ListVirtualObject);
	this->bee->Update(delta_time, &ListVirtualObject);
	//this->shuri->Update(delta_time, &ListVirtualObject);
	
}

void MyGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->megaman = Megaman::Instance();
	//this->megaman = new Megaman();
	this->megaman->SetDirection(RIGHT);
	
	this->textStartGame = new TextStartGame();

//	this->shuri = Shurikein::Instance();
	this->bee = new Bee();
	this->hornet = new BlastHornet();
	this->launchers = new Launchers();
	this->doorShuri = DoorShurikein::Instance();
	this->genjibo = Genjibo::Instance();
	//this->doorRightShuri = DoorRightShurikein::Instance();
	this->subboss = SubBossCarry::Instance();
	//this->carryBox = new CarryBox();


	this->doorBlast1 = DoorBlasHornet::Instance();

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

	if (KeyCode == DIK_Z) {
		megaman->SetAllowJump(true);
	}
	
}
