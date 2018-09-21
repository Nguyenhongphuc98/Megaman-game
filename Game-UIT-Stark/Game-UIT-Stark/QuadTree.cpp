#include"QuadTree.h"

QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
}

vector<Object*> QuadTree::GetListObjectInViewort(CollisionRect cam)
{
	vector<Object*> ListObject;
	ListObject.clear();

	map<int, Object*>listTemp = mapNode[0]->GetlistObjectInView(cam);

	for each(auto o in listTemp) {
		ListObject.push_back(o.second);
	}
	return ListObject;
}
