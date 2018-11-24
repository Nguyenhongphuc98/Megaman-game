#include"Animation.h"
Animation::Animation()
{

}

Animation::~Animation()
{
}

void Animation::Next(State state)
{
	listSprite[state]->Next();
}

void Animation::Render(State state, Direction direction, D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	if (direction == Direction::LEFT)
		listSprite[state]->DrawFlipX(position.x, position.y);
	else
	{
		listSprite[state]->Draw(position.x, position.y);
	}
}

void Animation::Refresh(State s)
{
	this->listSprite[s]->Reset();
}
