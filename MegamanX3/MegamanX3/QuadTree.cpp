#include"QuadTree.h"
QuadTree* QuadTree::instance;

QuadTree::QuadTree()
{
}

QuadTree::~QuadTree()
{
}

QuadTree * QuadTree::Instance()
{
	if (!instance)
		instance = new QuadTree();
	return instance;
}
