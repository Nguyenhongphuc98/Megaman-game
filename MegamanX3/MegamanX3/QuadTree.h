#pragma once
#ifndef QuadTree_H_
#define QuadTree_H_
#include<map>
#include"Node.h"
using namespace std;

class QuadTree
{
private:
	static QuadTree* instance;
	map<int, Node*> listNode;
	map<int, Object*> listObject;
public:
	QuadTree();
	~QuadTree();

	static QuadTree* Instance();
	void LoadListObject();
	void LoadListNode();
	void BuildTree(); //linking node
};


#endif // !QuadTree_H_
