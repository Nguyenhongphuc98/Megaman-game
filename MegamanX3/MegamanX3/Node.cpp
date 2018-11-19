#include"Node.h"

Node::Node()
{
	for (int i = 0; i < 4; i++)
		listChils[i] = NULL;
}

Node::Node(Box b)
{
	this->bound = b;

	for (int i = 0; i < 4; i++)
		listChils[i] = NULL;
}

Node::Node(int x, int y, int w, int h)
{
	bound.SetingBox(x, y, w, h);

	for (int i = 0; i < 4; i++)
		listChils[i] = NULL;
}

Node::~Node()
{
}

void Node::AddObject(int key, Object * value)
{
	this->listObjects[key] = value;
}

map<int, Object*> Node::GetListObject()
{
	return this->listObjects;
}

map<int, Object*> Node::GetListObject(Box cam)
{
	map<int, Object*> list_object;
	list_object.clear();

	if (!this->listChils[0])
		return this->listObjects;
	else
	{
		for (int i = 0; i < 4; i++) 
		{
			if (this->listChils[i]->GetBound().IsOverlap(cam))
				{
				map<int, Object*> list_object_in_childs = listChils[i]->GetListObject(cam);
				for(auto o : list_object_in_childs) {
					list_object[o.first] = o.second;
				}
			}
		}
	}

	return list_object;
}

Box Node::GetBound()
{
	return this->bound;
}

Node ** Node::GetChilds()
{
	return listChils;
}
