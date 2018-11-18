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

void QuadTree::LoadListObject()
{
	//listObject= TXT::Instance()->LoadListObject((char*)"listobject.txt");
	fstream f;
	//map<int, Object*> list_object;

	f.open("path", ios::in);

	int number_of_object, map_width, map_height;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_object >> map_width >> map_height;

	int stt, id, x, y, w, h, direction; //stt=key
	for (int i = 0; i < number_of_object; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		stream_data >> stt >> id >> x >> y >> w >> h >> direction;

		this->listObject[stt] = CreateObject(id, x, y, w, h, direction);
	}

	f.close();
	//this->listObject = list_object;
}

void QuadTree::LoadListNode()
{
	//listNode = TXT::Instance()->LoadListNode((char*)"listnode.txt", this->listObject);

	fstream f;
	//map<int, Node*> list_node;
	string data;

	f.open("path", ios::in);

	stringstream stream_data;
	int id, x, y, w, sttObject; //stt=key
	int number_of_object_in_node;
	while (getline(f, data))
	{
		stream_data << data;

		stream_data >> id>> x>> y>> w;
		Node* node = new Node(x, y, w, w);

		number_of_object_in_node = CountWords(data) - 4;
		for (int i = 0; i < number_of_object_in_node; i++)
		{
			stream_data >> sttObject;
			//CTreeObject* obj = this->_listObject[key];
			node->AddObject(sttObject, this->listObject[sttObject]);// new CTreeObject(obj->getId(), obj->getBound().getX(), obj->getBound().getY(), obj->getBound().getWidth(), obj->getBound().getHeight(), obj->getDirect()));
		}
		this->listNode[id] = node;
	}
}

void QuadTree::BuildTree()
{
	LoadListObject();
	LoadListNode();

	//linking node there
}


Object * QuadTree::CreateObject(int id, int x, int y, int w, int h, int d)
{
	Direction dir;
	if (d == 0)
		dir = RIGHT;
	else
	{
		dir = LEFT;
	}

	Object* o;
	//convert to real scale
	y *= G_Scale.y;
	x *= G_Scale.x;
	w *= G_Scale.x;
	h *= G_Scale.y;
	switch (id)
	{
	case GROUND:
		o = new VirtualObject(y - h, x, w, h);
		break;
	case NOTORBANGER:
		o = new NotorBanger(y - h / 2, x + w / 2, w, h, dir);
		break;
	case HELIT:
		o = new Helit(y - h / 2, x + w / 2, w, h, dir);
		break;
	default:
		o = new VirtualObject(y - h, x, w, h);
		break;
	}
	return o;
}

int QuadTree::CountWords(string str)
{
	// breaking input into word using string stream 
	stringstream s(str); // Used for breaking words 
	string word; // to store individual words 

	int count = 0;
	while (s >> word)
		count++;
	return count;
}
