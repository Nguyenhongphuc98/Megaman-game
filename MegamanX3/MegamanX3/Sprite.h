#pragma once
#ifndef Sprite_H_
#define Sprite_H_
#include <d3d9.h>
#include<d3dx9.h>
#include<vector>
using namespace std;
#include"MyTexture.h"

class Sprite
{
public:
	MyTexture* texture;
	int current_frame;
	int number_of_frame;
	int animation_time;
	int animation_count_time;
	vector<RECT*> List_source_rect;

public:
	Sprite();
	~Sprite();

	Sprite(const Sprite &sprite);
	Sprite(MyTexture* texture,vector<RECT*> List_source_rect, int animation_t);

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	//chọn 1 frame nào đó
	void Set_current_frame(int index);


	// Render current sprite at location (X,Y) at the target surface
	void Draw(int x, int y);

	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y);

	//render with scale (1, -1)
	void DrawFlipY(int x, int y);

	//Render Rect of texture at (x,y)
	void DrawRect(int X, int Y, RECT SrcRect);

	void DrawCurrentFrame(int index, int X, int Y);

	int GetCurrentFrame();

	bool IsFinalFrame();
};


#endif // !Sprite_H_
