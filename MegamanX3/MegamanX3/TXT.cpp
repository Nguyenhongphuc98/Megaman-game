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
