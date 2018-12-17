#include"Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	if (texture != NULL)
		delete texture;
}

Sprite::Sprite(const Sprite & sprite)
{
	this->animation_time = sprite.animation_time;
	this->texture = sprite.texture;
}

Sprite::Sprite(MyTexture * texture, vector<RECT*> List_source_rect, int animation_t):texture(texture)
{
	this->List_source_rect = List_source_rect;
	this->animation_time = animation_t;
	this->animation_count_time = 0;
	this->number_of_frame = List_source_rect.size();
	this->current_frame = 0;
}

void Sprite::Next()
{
	animation_count_time++;
	if (animation_count_time==animation_time)
	{
		current_frame++;
		animation_count_time = 0;
		if (current_frame > number_of_frame - 1)
			current_frame = 0;
	}
	
}

void Sprite::Reset()
{
	current_frame = 0;
}

void Sprite::Set_current_frame(int index)
{
	current_frame = index;
}

void Sprite::Draw(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	RECT *srect = List_source_rect[current_frame];

	//tam thu phong
	D3DXVECTOR2 center = D3DXVECTOR2(x, y);
	//D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &G_Scale, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);


	D3DXVECTOR3 position(0, 0, 0);
	//diem neo
	D3DXVECTOR3 fcenter(0, 0, 0); //top left
	position.x = x -(srect->right - srect->left) / 2;
	position.y = y -(srect->bottom - srect->top) / 2;
	G_SpriteHandler->Draw(
		texture->texture,
		srect,
		&fcenter,
		&position,
		0xFFFFFFFF //color
	);

	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	RECT *srect = List_source_rect[current_frame];

	//tam thu phong
	D3DXVECTOR2 center = D3DXVECTOR2(x, y);
	//D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &G_ScaleFlipX, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	//vi ve nguoc lai nen phai dich chuyen x sang phai w don vi
	//x += (srect->right - srect->left);
	//this->Draw(x, y);

	D3DXVECTOR3 position(0, 0, 0);
	//diem neo
	D3DXVECTOR3 fcenter(0, 0, 0); //top left - ve binh thuong
	position.x = x -(srect->right - srect->left) / 2;
	position.y = y -(srect->bottom - srect->top) / 2;
	G_SpriteHandler->Draw(
		texture->texture,
		srect,
		&fcenter,
		&position,
		0xFFFFFFFF //color
	);

	//set lai neu khong no se to dan so voi frame truoc
	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	RECT *srect = List_source_rect[current_frame];

	D3DXVECTOR2 center = D3DXVECTOR2(x + (srect->right - srect->left) / 2, y + (srect->bottom - srect->top) / 2);
	//D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &G_ScaleFlipX, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	//vi ve nguoc lai nen phai dich chuyen y sang phai h don vi
	y += (srect->bottom - srect->top);
	//this->Draw(x, y);

	D3DXVECTOR3 position(0, 0, 0);
	//diem neo
	D3DXVECTOR3 fcenter(0, 0, 0); //top left - ve binh thuong
	position.x = x - (srect->right - srect->left) / 2;
	position.y = y - (srect->bottom - srect->top) / 2;
	G_SpriteHandler->Draw(
		texture->texture,
		srect,
		&fcenter,
		&position,
		0xFFFFFFFF //color
	);

	//set lai neu khong no se to dan so voi frame truoc
	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawRect(int X, int Y, RECT SrcRect)
{
	/*D3DXVECTOR3 position((float)X, (float)Y, 0);
	G_SpriteHandler->Draw(
		texture->texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);*/

	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);
	D3DXMATRIX newMt;

	//tam thu phong
	D3DXVECTOR2 center = D3DXVECTOR2(X, Y);
	//D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &G_Scale, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);


	D3DXVECTOR3 position(0, 0, 0);
	//diem neo
	D3DXVECTOR3 fcenter(0, 0, 0); //top left
	position.x = X -(SrcRect.right - SrcRect.left) / 2;
	position.y = Y -(SrcRect.bottom - SrcRect.top) / 2;
	G_SpriteHandler->Draw(
		texture->texture,
		&SrcRect,
		&fcenter,
		&position,
		0xFFFFFFFF //color
	);

	G_SpriteHandler->SetTransform(&oldMt);
}

void Sprite::DrawCurrentFrame(int index, int X, int Y)
{
	RECT *srect =List_source_rect[index];

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - (srect->right - srect->left) / 2;
	position.y = Y - (srect->bottom - srect->top) / 2;
	G_SpriteHandler->Draw(
		texture->texture,
		srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

int Sprite::GetCurrentFrame()
{
	return current_frame;
}

bool Sprite::IsFinalFrame()
{
	if(current_frame == (number_of_frame - 1))
	return true;
	else
	{
		return false;
	}
}


