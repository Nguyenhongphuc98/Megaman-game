#pragma once
#ifndef _QuadTee_H_
#define _QuadTee_H_

#define  MAX_OBJECTS=10;
#define  MAX_LEVELS=3; //phu thuoc vao do rong map +man hinh camera hien thi(view port)
#include"Window.h"


class QuadTree
{
private:
	int			level;
	//-list object in node
	RECT		borders;
	QuadTree*	childsNode[4];

public:
	QuadTree();
	~QuadTree();

	//vector<Object> GetListObject();
	//vector<Object> SetListObject();

};


#endif // !_QuadTee_H_
