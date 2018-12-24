#pragma once
#ifndef BlastHornet_H_
#define BlastHornet_H_
#include"ActionObject.h"
#include"Megaman.h"
#include"Bee.h"
#include"Honey.h"

#define BLASTHORNET_WIDTH 33*2.5
#define BLASTHORNET_HEIGHT 51*2.5

#define BLASTHORNET_ATTACK_VX 3 //don't use because caculate theo vy.
#define BLASTHORNET_ATTACK_VY 3

#define BLASTHORNET_TOP 15317
#define BLASTHORNET_LEFT 7700*G_Scale.x
#define BLASTHORNET_RIGHT 7925*G_Scale.x

#define BLASTHORNET_MID_Y 15155
#define BLASTHORNET_MID_X 19569

#define BLASTHORNET_MAX_HP 31*3
#define BLASTHORNET_TIME_DESTROY 10000

#define GROUND (107+G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.x
#define MID (172+G_ADDITIONS_TO_BECOME_THE_SQUARE)*G_Scale.y

enum BlastHornetAction {
	Appear,
	PrepareAttack,
	Attack,
	GoExtremely
};

class BlastHornet:public ActionObject
{
private:
	BlastHornetAction currentAction;
	static BlastHornet* instance;

	Bee* Bees[5];
	Honey* honey;
	Animation * animation_lifebar;

	bool godown; //luc xuat hien
	bool stand; //luc xuat hien
	bool moving_attack_venom; // chich doc
	bool appeared; //de render thanh mau
	bool allow_attack; // chi tan cong luc dau thoi. gan he mau chi chay vo cung
	float time_start_change_state;

	float a, b; //using for pt duong thang khi tan cong

	int count_to_attack;

public:
	BlastHornet();
	BlastHornet(int x, int y, int w, int h, Direction d);
	~BlastHornet();

	static BlastHornet* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();
	void LoadResource();

	BoundingBox GetBoundingBox();
	BoundingBox GetBoundBee(int i);

	void SetState(State s);
	void SetDirection(Direction d);

	void SetBeeSBeingAttack(int indexBee, int damage);
};


#endif // !BlastHornet_H_
