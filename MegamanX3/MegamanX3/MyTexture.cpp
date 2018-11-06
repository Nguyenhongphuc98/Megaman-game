#include"MyTexture.h"

MyTexture::MyTexture()
{
}

MyTexture::~MyTexture()
{
}

MyTexture::MyTexture(const MyTexture & My_texture)
{
	this->path = My_texture.path;
	this->size = My_texture.size;
	this->transparent_color = My_texture.transparent_color;

	if(My_texture.texture==NULL)
	this->texture = My_texture.texture;
	else
	{
		Load();
	}
}

MyTexture::MyTexture(char * path, D3DCOLOR transparent_color)
{
	this->path = path;
	this->transparent_color = transparent_color;

	Load();
}

void MyTexture::Load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(path, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->size = s;


	if (result != D3D_OK)
	{
		GLMessage("Can not load texture");
		OutputDebugString(path);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		path,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparent_color, //color
		&info,
		NULL,
		&texture
	);

	if (result != D3D_OK)
	{
		GLMessage("Can not load texture");
		return;
	}
}

void MyTexture::Draw(int x, int y)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(texture, &size, NULL, &position, 0xFFFFFFFF);
}
