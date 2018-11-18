#pragma once
#ifndef TXT_H_
#define TXT_H_
#include<vector>
#include<d3dx9.h>
#include<fstream>
#include<string>
#include<string.h>
#include<sstream>
#include<map>

//#include"Global.h"
//#include"Node.h"
//#include"VirtualObject.h"
//#include"Helit.h"
//#include"NotorBanger.h"
//#include"HeadGunnerCustomer.h"

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
	//map<int, Object*> LoadListObject(char* path);
	//map<int, Node*> LoadListNode(char* path, map<int, Object*>);

	//Object* CreateObject(int id, int x, int y, int w, int h, int d);
	//int CountWords(string str);
};


#endif // !TXT_H_
