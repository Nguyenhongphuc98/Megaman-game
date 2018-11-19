#pragma once
#ifndef Node_H_
#define Node_H_
#include"Box.h"
#include<map>
#include"Object.h"
#include<vector>

using namespace std;

class Node
{
private:
	Box bound;
	Node* listChils[4];
	map<int, Object*> listObjects; //stt
public:
	Node();
	Node(Box b);
	Node(int x,int y,int w,int h);
	~Node();

	void AddObject(int key, Object* value);
	map<int, Object*> GetListObject();
	map<int, Object*> GetListObject(Box cam);
	Box GetBound();
	Node** GetChilds();
};


#endif // !Node_H_
