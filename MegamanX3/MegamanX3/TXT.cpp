#include"TXT.h"
TXT* TXT::instance;

TXT::TXT()
{
}

TXT::~TXT()
{
}

TXT * TXT::Instance()
{
	if (!instance)
		instance = new TXT();
	return instance;
}

vector<RECT*> TXT::LoadListSourceRect(char * path)
{
	vector<RECT*> list_source_rect;

	fstream f;
	f.open(path, ios::in);

	int number_of_source_rect;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data>>number_of_source_rect;
	
	//top-bottom-left-right
	//int top, bottom, left, right;
	for (int i = 0; i < number_of_source_rect; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		RECT* r = new RECT();
		stream_data >> r->top;
		stream_data >> r->bottom;
		stream_data >> r->left;
		stream_data >> r->right;

		//r->top = top;
		//r->bottom = bottom;
		//r->left = left;
		//r->right = right;

		list_source_rect.push_back(r);
	}

	f.close();
	return list_source_rect;
}
//
//map<int, Object*> TXT::LoadListObject(char * path)
//{
//	fstream f;
//	map<int, Object*> list_object;
//
//	f.open(path, ios::in);
//
//	int number_of_object,map_width,map_height;
//	string data;
//
//	getline(f, data);
//	stringstream stream_data;
//	stream_data << data;
//	stream_data >> number_of_object>>map_width>>map_height;
//
//	int stt, id,x, y, w, h,direction; //stt=key
//	for (int i = 0; i < number_of_object; i++)
//	{
//		data = "";
//		stream_data.clear();
//
//		getline(f, data);
//		stream_data << data;
//
//		stream_data >> stt>>id>>x>>y>>w>>h>> direction;
//
//		list_object[stt] = CreateObject(id, x, y, w, h, direction);
//	}
//
//	f.close();
//	return list_object;
//}
//
//map<int, Node*> TXT::LoadListNode(char * path, map<int, Object*> list_object)
//{
//	fstream f;
//	map<int, Node*> list_node;
//	string data;
//
//	f.open(path, ios::in);
//
//	stringstream stream_data;
//	int id, x, y, w,sttObject; //stt=key
//	int number_of_object_in_node;
//	while (getline(f, data))
//	{
//		stream_data << data;
//
//		stream_data >> id, x, y, w;
//		Node* node = new Node(x, y, w, w);
//
//		number_of_object_in_node = CountWords(data) - 4;
//		for (int i = 0; i < number_of_object_in_node; i++)
//		{
//			stream_data >> sttObject;
//			//CTreeObject* obj = this->_listObject[key];
//			node->AddObject(sttObject, list_object[sttObject]);// new CTreeObject(obj->getId(), obj->getBound().getX(), obj->getBound().getY(), obj->getBound().getWidth(), obj->getBound().getHeight(), obj->getDirect()));
//		}
//		list_node[id] = node;
//	}
//	return list_node;
//}
//
//Object * TXT::CreateObject(int id, int x, int y, int w, int h, int d)
//{
//	Direction dir;
//	if (d == 0)
//		dir = RIGHT;
//	else
//	{
//		dir = LEFT;
//	}
//
//	Object* o;
//	//convert to real scale
//	y *= G_Scale.y;
//	x *= G_Scale.x;
//	w *= G_Scale.x;
//	h *= G_Scale.y;
//	switch (id)
//	{
//	case GROUND:
//		o= new VirtualObject(y - h, x, w, h);
//		break;
//	case NOTORBANGER:
//		o= new NotorBanger(y - h/2, x+w/2, w, h,dir);
//		break;
//	case HELIT:
//		o= new Helit(y - h / 2, x + w / 2, w, h, dir);
//		break;
//	default:
//		break;
//	}
//	return o;
//}
//
//int TXT::CountWords(string str)
//{
//		// breaking input into word using string stream 
//		stringstream s(str); // Used for breaking words 
//		string word; // to store individual words 
//
//		int count = 0;
//		while (s >> word)
//			count++;
//		return count;
//}
