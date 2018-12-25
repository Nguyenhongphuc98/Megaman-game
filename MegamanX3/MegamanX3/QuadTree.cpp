#include"QuadTree.h"
QuadTree* QuadTree::instance;

QuadTree::QuadTree()
{
	BuildTree();
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

	f.open((char*)"SourceImage\\quadtreelistobject.txt", ios::in);

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

	f.open((char*)"SourceImage\\quadtreelistnode.txt", ios::in);

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

		data = "";
		stream_data.clear();
	}
}

void QuadTree::BuildTree()
{
	LoadListObject();
	LoadListNode();

	//linking node there
	int id, parent_id,child_id;
	for (auto node : listNode) {
		id = node.first;
		parent_id = id / 10;

		if (this->listNode[parent_id]) {
			child_id = id % 10;
			this->listNode[parent_id]->GetChilds()[child_id] = node.second;
		}
	}
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
	case VIRTUALOBJECT:
		o = new VirtualObject(y - h, x, w, h);
		break;
	case NOTORBANGER:
		o = new NotorBanger(x + w / 2, y - h / 2,  w, h, dir);
		o->SetState(STAND);
		break;
	case HELIT:
		o = new Helit(x + w / 2, y - h / 2, w, h, dir);
		o->SetState(RUN);
		break;
	case CARRYARM:
		o = new CarryArm(x + w / 2, y - h / 2, w, h, dir);
		o->SetState(STRAIGHTROPE);
		break;
	case HEADGUNNERCUSTOMER:
		if(x<900*2.5)
			y += 5;
		//else
		//if (x < 3202)
		//	y += 5;
		o = new HeadGunnerCustomer(x + w / 2, y - h / 2, w, h, dir);
		o->SetState(SHOOTABOVE);
		break;
	case DOORLEFTSHURI:
		o = DoorShurikein::Instance();
		break;
	case DOORRIGHTSHURI:
		o = DoorRightShurikein::Instance();
		break;
	case SHURIKEIN:
		o = Shurikein::Instance();
		break;
	case SUBBOSSCARRY:
		o = SubBossCarry::Instance();
		break;
	case DOORBLASHORNET:
		o = new DoorBlasHornet(y - h / 2, x + w / 2,  0,0);
		break;
	case BOXBOX:
		o= new BoxBox(y - h / 2, x + w / 2,  0, 0);
		break;
	case BLASTHORNET:
		o = BlastHornet::Instance();
		break;
	case ELEVATOR:
		o = new Elevator(y - h, x, w, h,dir);
		break;
	case DIEBOX:
		o = new DieBox(y - h, x, w, h);
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

vector<Object*> QuadTree::GetListObject(Box cam)
{
	if(!this->listNode[1])
	return vector<Object*>();

	vector<Object*> listObject;
	map<int, Object*> list = this->listNode[1]->GetListObject(cam);

	for (auto obj : list)
	{
		//Object* object = obj.second;
		listObject.push_back(obj.second);
	}

	return listObject;
}
