#include"Map.h"

Map::Map()
{
	LoadResource();
}

Map::~Map()
{
}

void Map::LoadResource()
{
	vector<RECT*> list_source_rect;
	RECT* rect = new RECT();
	rect->top = 0;
	rect->left = 0;
	rect->right = WIDTH_MAP_IMAGE;
	rect->bottom = HEIGHT_MAP_IMAGE;
	list_source_rect.push_back(rect);
	texture = new MyTexture((char*)"SourceImage\\Blast_hornet_map_large.png",D3DCOLOR_XRGB(255,255,255));
	background = new Sprite(texture, list_source_rect, 1);
}

void Map::Render()
{
	float x, y;
	Camera::Instance()->GetCameraPosition(x, y);
	y -= G_ADDITIONS_TO_BECOME_THE_SQUARE*G_Scale.y; //background added 5880 to be square so have to sub.
	//Oy of image and worldport is different
	y = HEIGHT_MAP_IMAGE* G_Scale.y - y;
	RECT sourceDraw;
	sourceDraw.top =  y / G_Scale.y;
	sourceDraw.left =  x / G_Scale.x;
	sourceDraw.right =  x / G_Scale.x + G_ScreenWidth / G_Scale.x;
	sourceDraw.bottom =y / G_Scale.y + G_ScreenHeight / G_Scale.y;

	/*x = (sourceDraw.right - sourceDraw.left) / 2;
	y = (sourceDraw.bottom - sourceDraw.top) / 2;*/
	/*x += G_ScreenWidth / 2;
	y -= G_ScreenHeight / 2;
	D3DXVECTOR2 p = Camera::Instance()->GetPositionInViewPort(x, y);*/
	x = G_ScreenWidth / 2;
	y = G_ScreenHeight / 2;
	background->DrawRect(x, y, sourceDraw);
}
