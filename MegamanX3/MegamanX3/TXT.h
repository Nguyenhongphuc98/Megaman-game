#pragma once
#ifndef TXT_H_
#define TXT_H_
#include<vector>
#include<d3dx9.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

class TXT
{
private:
	static TXT* instance;
public:
	TXT();
	~TXT();

	static TXT* Instance();
	
	vector<RECT*> LoadListSourceRect(char* path);
};


#endif // !TXT_H_
