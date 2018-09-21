#pragma once
#ifndef _QuadTree_H_
#define _QuadTree_H_


#include"QuadNode.h"



class QuadTree
{
private:
	map<int, QuadNode*> mapNode;
	map<int, Object*> mapObject;

public:
	QuadTree();
	~QuadTree();

	void LoadSource(); //load data from txt to mapNode and mapObject
	void BuildTree(); //build tree when mapNode available

	vector<Object*> GetListObjectInViewort(CollisionRect cam);

};


#endif // !_QuadTree_H_
