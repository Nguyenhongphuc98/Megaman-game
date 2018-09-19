#include "QuadNode.h"

QuadNode::QuadNode()
{
}

QuadNode::~QuadNode()
{
}

std::map<int, Object*> QuadNode::GetlistObjectInView(CollisionRect cam)
{
	std::map<int, Object*> templist;

	if (this->childsNode[0] == NULL)// no la node la
		return this->listObject;

	if (this->childsNode[0]->borders.IsIntersect(cam)) {
		std::map<int, Object *> childlist = this->childsNode[0]->GetlistObjectInView(cam);

		for each(auto object in childlist) {
			if (templist[object.first] != NULL)
				templist[object.first] = object.second;
		}
	}

	if (this->childsNode[1]->borders.IsIntersect(cam)) {
		std::map<int, Object *> childlist = this->childsNode[1]->GetlistObjectInView(cam);

		for each(auto object in childlist) {
			if (templist[object.first] != NULL)
				templist[object.first] = object.second;
		}
	}

	if (this->childsNode[2]->borders.IsIntersect(cam)) {
		std::map<int, Object *> childlist = this->childsNode[2]->GetlistObjectInView(cam);

		for each(auto object in childlist) {
			if (templist[object.first] != NULL)
				templist[object.first] = object.second;
		}
	}

	if (this->childsNode[3]->borders.IsIntersect(cam)) {
		std::map<int, Object *> childlist = this->childsNode[3]->GetlistObjectInView(cam);

		for each(auto object in childlist) {
			if (templist[object.first] != NULL)
				templist[object.first] = object.second;
		}
	}
	return templist;
}

std::map<int, Object *> QuadNode::GetListObject()
{
	return this->listObject;
}

void QuadNode::AddtObject(int key, Object *object)
{
	this->listObject[key] = object;
}

void QuadNode::Clear()
{
	for (int i = 0; i < 4; i++) {
		if (this->childsNode[i] != NULL) {
			this->childsNode[i]->Clear();
			this->childsNode[i] = NULL;
		}
	}
	this->listObject.clear();
}

