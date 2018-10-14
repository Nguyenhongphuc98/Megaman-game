#include"Wall.h"

Wall::Wall()
{
}

Wall::~Wall()
{
}

CollisionRect Wall::GetBound()
{
	return CollisionRect(locationY, locationX, WALL_WIDTH, WALL_HEIGHT, 0.0f, 0.0f);
}

void Wall::Render()
{
	Object::RenderBoundingBox();
}
