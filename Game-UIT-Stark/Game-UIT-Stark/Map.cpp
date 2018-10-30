#include"Map.h"

Map::Map()
{
	position= D3DXVECTOR3(0, 1804, 0);
	mapWidth = WORLD_X;
	mapHeight = WORLD_Y;

	LoadResource();
}

Map::~Map()
{
}

void Map::LoadResource()
{
	Graphic *g = Graphic::Instance();
	mapBackground = g->LoadTeture("spriteSheet.png", D3DCOLOR_XRGB(255, 255, 255));
}

void Map::Render()
{
	Camera *camera = Camera::Instance();
	D3DXVECTOR3 inPosition = camera->GetPositionInCamera(position.x, position.y);

	Trace::Log("%f, %f", inPosition.x, inPosition.y);
	Graphic *g = Graphic::Instance();
	RECT *source = new RECT();
	source->top = 0;
	source->left = 0;
	source->bottom = 1804;
	source->right = 5000;
	
	//g->DrawTexture(mapBackground, source, inPosition,D3DXVECTOR2(1,1));
}

void Map::SetLocation(float x, float y)
{
	position = D3DXVECTOR3(x, y, 0);
}
