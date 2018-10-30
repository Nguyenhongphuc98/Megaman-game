#include "Sprite.h"

Sprite::Sprite(char *path, vector<RECT*> listSourceRect, D3DCOLOR transparencyColor)
{
	//Window *app = Window::Instance();
	Graphic *graphic = Graphic::Instance();
	this->listSourceRect = listSourceRect;
	countFrame = listSourceRect.size();
	currentFrame = 0;

	//khi khởi tạo cho nó là không scale, không translate.
	SetScale();
	SetTranslate();

	HRESULT result; //xài thằng này để coi kết quả trả về là ok hay failed

					//cái này liên quan đến vẽ nên cần device bên graphic
					//như kiểu gắn sprite hander vào device ấy cho dễ hiểu
	/*result = D3DXCreateSprite(graphic->GetD3DDevice(), &this->spriteHander);
	if FAILED(result)
		Global::Notify("Lỗi rồi,không gắn thằng sprite hander vô device được!!","Notify");*/

	//đổ màu trong suốt là cái màu hồng hồng tím tím (màu background bên sprite) -248,0,248.
	//mục đích để lúc load lên nó xóa màu đó trùng vơis màu nền.
	this->texture = graphic->LoadTeture(path, transparencyColor);
}

Sprite::~Sprite()
{
	if (this->texture)
		texture->Release();
}

void Sprite::Render(D3DXVECTOR2 scale)
{

	//if (Graphic::Instance()->GetD3DDevice()->BeginScene())
	//{
		//set cái này để thực hiện mấy phép chuyển đổi.
		//this->spriteHander->SetTransform(&(matScale*matTranslate));

	Graphic::Instance()->DrawTexture(
		texture, 
		this->listSourceRect[currentFrame],
		position,
		scale);
}

void Sprite::SetPosition(D3DXVECTOR3 p)
{
	this->position = p;
}

void Sprite::setCenter(D3DXVECTOR3 c)
{
	this->center = c;
}

void Sprite::SetCurrentFrame(int index)
{
	if (index < 0)
		currentFrame = 0;

	else
	{
		currentFrame = index % countFrame;
	}
}

void Sprite::SetScale(D3DXVECTOR3 vectorScale)
{
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixScaling(&this->matScale, vectorScale.x, vectorScale.y, vectorScale.z);
}

void Sprite::SetTranslate(D3DXVECTOR3 vectorTranslate)
{
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixTranslation(&this->matTranslate, vectorTranslate.x, vectorTranslate.y, vectorTranslate.z);
}

void Sprite::SetRotation(float angle)
{
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixRotationZ(&this->matTranslate,angle);
}

void Sprite::FlipVertical(bool flag)
{
	if (this->isFlipVertical != flag) {
		this->isFlipVertical = flag;
		this->matScale._31 *= -1;
	}
}

void Sprite::FlipHorizontal(bool flag)
{
	if (this->isFlipHorizontal != flag) {
		this->isFlipHorizontal = flag;
		this->matScale._32 *= -1;
	}
}

int Sprite::GetCurrentFrame()
{
	return this->currentFrame;
}

vector<RECT*> Sprite::GetListSourceRect()
{
	return listSourceRect;
}
