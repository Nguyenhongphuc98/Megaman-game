#include"Wall.h"

Wall::Wall()
{
}

Wall::~Wall()
{
}

CollisionRect Wall::GetBound()
{
	return CollisionRect(locationY, locationX, WALL_WIDTH, WALL_HEIGHT, 0, 0);
}

void Wall::Render()
{
	Object::RenderBoundingBox();
}
