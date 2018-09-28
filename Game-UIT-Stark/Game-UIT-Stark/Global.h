#pragma once
#ifndef _Global_H_
#define _Global_H_
#include<Windows.h>
#include"Collision.h"

class Global
{
private:

public:
	Global();
	~Global();

	static void Notify(char* message,char* caption);
	static RECT ConvertCollisionRectToRECT(CollisionRect rect);


	//emum in game
	enum IdObject {
		GROUND
	};

	enum Status
	{
		RUN,
		JUMP
	};

	enum  Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		UNKNOW
	};

	enum Team
	{
		PROTAGONIST
	};
};



#endif // !_Global_H_
