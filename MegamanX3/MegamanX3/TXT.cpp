#include"TXT.h"
TXT* TXT::instance;

TXT::TXT()
{
	LoadAllSourceRect();
	LoadAllTexture();
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
	stream_data >> number_of_source_rect;

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

void TXT::LoadAllSourceRect()
{
	fstream f;
	f.open("SourceImage\\ListSourceRect.txt", ios::in);

	int number_of_sprite;
	string data;

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_sprite;

	int type_sprite, number_of_source_rect;
	for (int i = 0; i < number_of_sprite; i++)
	{

		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		stream_data >> type_sprite >> number_of_source_rect;
		for (int t = 0; t < number_of_source_rect; t++) {

			data = "";
			stream_data.clear();

			getline(f, data);
			stream_data << data;

			RECT* r = new RECT();
			stream_data >> r->top;
			stream_data >> r->bottom;
			stream_data >> r->left;
			stream_data >> r->right;

			this->listSourceRect[(TypeSprite)type_sprite].push_back(r);
		}
		getline(f, data);
	}

	f.close();
}

void TXT::LoadAllTexture()
{
	//===============================MEGAMAN SPRITE=====================================
	//listTexture[TMEGAMANSTAND] = new MyTexture((char*)"SourceImage\\megamanstand.png", D3DCOLOR_XRGB(50, 96, 166));
	//listTexture[TMEGAMANRUN] = new MyTexture((char*)"SourceImage\\megamanrun.png", D3DCOLOR_XRGB(50, 96, 166));
	//listTexture[TMEGAMANJUMP] = new MyTexture((char*)"SourceImage\\megamanjump.png", D3DCOLOR_XRGB(50, 96, 166));
	//listTexture[TMEGAMANRUNSHOOT]= new MyTexture((char*)"SourceImage\\megamanrunshoot.png", D3DCOLOR_XRGB(50, 96, 166));
	//listTexture[TMEGAMANCLIMB] = new MyTexture((char*)"SourceImage\\megamanClimb.png", D3DCOLOR_XRGB(50, 96, 166));
	//listTexture[TMEGAMANDASH] = new MyTexture((char*)"SourceImage\\megamanDash.png", D3DCOLOR_XRGB(50, 96, 166));
	listTexture[TMEGAMANSTAGE] = new MyTexture((char*)"SourceImage\\megamanstage.png", D3DCOLOR_XRGB(50, 96, 166));

	//===============================BEE SPRITE=====================================
	listTexture[TBEE] = new MyTexture((char*)"SourceImage\\bee.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================BLASTHORNET SPRITE=====================================
	listTexture[TBLASTHORNETREDKNEE] = new MyTexture((char*)"SourceImage\\blast_hornet_red_knee.png", D3DCOLOR_XRGB(255, 255, 255));
	listTexture[TBLASTHORNETREDHANDS] = new MyTexture((char*)"SourceImage\\blast_hornet_red_hands.png", D3DCOLOR_XRGB(255, 255, 255));
	listTexture[TBLASTHORNETPREPAREOPENVENOM] = new MyTexture((char*)"SourceImage\\blast_hornet_prepare_open_venom.png", D3DCOLOR_XRGB(255, 255, 255));
	listTexture[TBLASTHORNETOPENINGVENOM]= new MyTexture((char*)"SourceImage\\blast_hornet_opening_venom.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================CARRY ARM SPRITE=====================================
	listTexture[TCARRYARM] = new MyTexture((char*)"SourceImage\\subboss_carryarm.png", D3DCOLOR_XRGB(50, 96, 166));

	//===============================HEAD GUNNER CUSTOMER SPRITE=====================================
	listTexture[THEADGUNNERCUSTOMER] = new MyTexture((char*)"SourceImage\\HeadGunnerCustomer.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================HELIT SPRITE=====================================
	listTexture[THELIT] = new MyTexture((char*)"SourceImage\\helit.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================NOTORBANGER SPRITE=====================================
	listTexture[TNOTORBANGER] = new MyTexture((char*)"SourceImage\\notorBanger.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================SHURIKEIN SPRITE=====================================
	listTexture[TSHURIKEINAPPEAR] = new MyTexture((char*)"SourceImage\\ShurikeinAppear.png", D3DCOLOR_XRGB(255, 255, 255));
	listTexture[TSHURIKEINROTATELEFT] = new MyTexture((char*)"SourceImage\\shurikein_rotate_left.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================BULLET1 MEGAMAN SPRITE=====================================
	listTexture[TBULLETMEGAMAN] = new MyTexture((char*)"SourceImage\\megamanbullet.png", D3DCOLOR_XRGB(50, 96, 166));

	//===============================LAUNCHERS SPRITE=====================================
	listTexture[TLAUNCHERS] = new MyTexture((char*)"SourceImage\\launchers.png", D3DCOLOR_XRGB(255, 255, 255));

	//===============================EFFECT SPRITE=====================================
	listTexture[TEFFECT] = new MyTexture((char*)"SourceImage\\effect.png", D3DCOLOR_XRGB(64, 102, 232));
}

vector<RECT*> TXT::GetListSourceRect(TypeSprite type_sprite)
{
	return this->listSourceRect[type_sprite];
}

MyTexture * TXT::GetTexture(TypeTexture type_texture)
{
	return listTexture[type_texture];
}
