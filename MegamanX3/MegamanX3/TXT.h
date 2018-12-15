#pragma once
#ifndef TXT_H_
#define TXT_H_
#include<vector>
#include<d3dx9.h>
#include<fstream>
#include<string>
#include<string.h>
#include<sstream>
#include<map>
#include<vector>
#include"MyTexture.h"


using namespace std;

enum TypeSprite {
	SBEEFLAPING,
	SBEEFLAPINGANDFLYING,
	SBEESTAND,

	SBLASTHORNETOPENINGVENOM,
	SBLASTHORNETPREPAREOPENVENOM,
	SBLASTHORNETREDHANDS,
	SBLASTHORNETREDKNEE,

	SHEADGUNNERCUSTOMERSHOOTABOVE,
	SHEADGUNNERCUSTOMERSHOOTBELOW,

	SHELITSTAND,

	SMEGAMANSTANDTALK,
	SMEGAMANDASH,
	SMEGAMANDASHSHOOT,
	SMEGAMANJUMP,
	SMEGAMANJUMPSHOOT,
	SMEGAMANJUMPWALL,
	SMEGAMANRUN,
	SMEGAMANRUNSHOOT,
	SMEGAMANSTANDSHOOT,
	SMEGAMANSTAND,
	SMEGAMANINJURED,

	SNOTORBANGERJUMP,
	SNOTOBANGERSHOOT90,
	SNOTOBANGERUPTHEGUN90,
	SNOTOBANGERSHOOT60,
	SNOTOBANGERUPTHEGUN60,
	SNOTORBANGERDOWTHEGUN,
	SNOTORBANGERSTAND,
	SNOTORBANGERDESTROY,

	SSHURIKEINROTATELEFT,
	SSHURIKEINROTATERIGHT,
	SSHURIKEINRAPPEAR,

	SCARRYARMSTRAIGHT,
	SCARRYARMBREAK,

	SBULLETNOTORBANGERSTART,
	SBULLETNOTORBANGERDESTROY,

	SBULLET1MEGAMANSTART,
	SBULLET1MEGAMANDESTROY,
	SBULLET2MEGAMANSTART,
	SBULLET2MEGAMANDESTROY,
	SBULLET3MEGAMANSTART,
	SBULLET3MEGAMANDESTROY,

	SLAUNCHERS,

	SHEADGUNNERCUSTOMERBULLETTUBE,

	SCHARGINGLV1,
	SCHARGINGLV2,

	SDASHSPARK,
	SDASHSSMOKE,
	SWALLKIK,
	SWALLSLIDE,

	SLIFEBAR,

	SHEADGUNNERCUSTOMERDESTROY,

	SDOOROPEN,
	SDOORCLOSE,

	SHELITBULLET,

	SGENJIBOGODOWN,
	SGENJIBOSTAND,
	SGENJIBOCREATESHURIKEIN,
	SGENJIBOGOUP,

	SSHURIKEINJUMP, //gan die
	SSHURIKEINDESTROY,
};

enum TypeTexture {
	TBEE,

	TBLASTHORNETOPENINGVENOM,
	TBLASTHORNETPREPAREOPENVENOM,
	TBLASTHORNETREDHANDS,
	TBLASTHORNETREDKNEE,

	THEADGUNNERCUSTOMER,

	THELIT,

	TMEGAMANCLIMB,
	TMEGAMANDASH,
	TMEGAMANJUMP,
	TMEGAMANRUN,
	TMEGAMANRUNSHOOT,
	TMEGAMANSTAND,
	TBULLETMEGAMAN,
	TMEGAMANSTAGE,

	TNOTORBANGER,

	TSHURIKEINROTATERIGHT,
	TSHURIKEINROTATELEFT,
	TSHURIKEINAPPEAR,

	TCARRYARM,

	TLAUNCHERS,

	TEFFECT,

	TDOOR,

	TGENJIBO,

	TSHURIKEINJUMPANDDIE,
};


class TXT
{
private:
	static TXT* instance;

	map<TypeSprite, vector<RECT*>> listSourceRect;
	map<TypeTexture, MyTexture*> listTexture;

public:
	TXT();
	~TXT();

	static TXT* Instance();

	vector<RECT*> LoadListSourceRect(char* path);
	void LoadAllSourceRect();
	void LoadAllTexture();

	vector<RECT*> GetListSourceRect(TypeSprite type_sprite);
	MyTexture* GetTexture(TypeTexture type_texture);
};


#endif // !TXT_H_
