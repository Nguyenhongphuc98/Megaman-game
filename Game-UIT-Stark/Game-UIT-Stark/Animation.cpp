#include"Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::SetFrame(Global::Status status, int index)
{
	ListSprite[status]->SetCurrentFrame(index);
}

int Animation::GetCurrentFrame(Global::Status status)
{
	return this->ListSprite[status]->GetCurrentFrame();
}

void Animation::Render(Global::Direction direction,
	Global::Status status,
	D3DXVECTOR3 position,
	D3DXVECTOR3 scale,
	D3DXVECTOR3 translation,
	float		rotation,
	D3DXVECTOR3 rotationCenter)
{
	this->ListSprite[status]->SetPosition(position);
	//this->ListSprite[status]->SetTranslate(translation);
	//this->ListSprite[status]->SetRotation(rotation);
	//this->ListSprite[status]->setCenter(rotationCenter);

	//this->UpdateDirection(status, direction);
	this->ListSprite[status]->Render(D3DXVECTOR2(scale.x,scale.y));
}

void Animation::NextFrame(Global::Status status)
{
	int index = (this->GetCurrentFrame(status) + 1);
	int countFrame = this->ListSprite[status]->GetListSourceRect().size();
	index %= countFrame;
	this->SetFrame(status, index);
}

void Animation::UpdateDirection(Global::Status status, Global::Direction direction)
{
	this->ListSprite[status]->FlipVertical(direction == Global::LEFT);
}
