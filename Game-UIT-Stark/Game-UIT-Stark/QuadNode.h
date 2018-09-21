#pragma once
#ifndef _QuadNode_H_
#define _QuadNode_H_

#define  MAX_OBJECTS 10;
#define  MAX_LEVELS 3; //phu thuoc vao do rong map +man hinh camera hien thi(view port)

#include"Window.h"
#include"Object.h"
#include"CollisionRect.h"
#include<map>


class QuadNode
{
private:
	int						level;
	std::map<int, Object*>	listObject;
	CollisionRect			borders;
	QuadNode*				childsNode[4];

public:
	QuadNode();
	~QuadNode();

	std::map<int,Object*>	GetlistObjectInView(CollisionRect cam);
	std::map<int,Object*>	GetListObject();
	void					AddtObject(int key,Object* object);
	void					Clear();

};


#endif // !_QuadNode_H_
