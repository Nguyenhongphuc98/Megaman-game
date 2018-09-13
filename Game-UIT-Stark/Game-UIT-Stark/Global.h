#pragma once
#ifndef _Global_H_
#define _Global_H_
#include<Windows.h>

class Global
{
private:

public:
	Global();
	~Global();

	static void Notify(char* message,char* caption);
};



#endif // !_Global_H_
