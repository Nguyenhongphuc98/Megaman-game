#pragma once
#ifndef Animation_H_
#define Animation_H_
#include<map>
using namespace std;

#include"Global.h"
#include"Sprite.h"

class Animation
{
public:
	map<State, Sprite*> listSprite;
public:
	Animation();
	~Animation();

	void Next(State state);
	void Render(State state, Direction direction, D3DXVECTOR2 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));
	void Refresh(State s);
};


#endif // !Animation_H_
