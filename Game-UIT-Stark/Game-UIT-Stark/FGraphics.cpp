#include"FGraphics.h"
#include"Window.h"

Graphic* Graphic::_instance;

Graphic::Graphic()
{
	pD3d = NULL;
	pD3dDevice = NULL;
	Init();
}

Graphic::~Graphic()
{
}

Graphic * Graphic::Instance()
{
	if (!_instance)
		_instance = new Graphic();
	return _instance;
}

void Graphic::Init()
{
	Window *app = Window::Instance();

	//khoi tao doi tuong direct3D
	pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3d == NULL)
		return;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = app->GetWidth();
	d3dpp.BackBufferHeight = app->GetHeight();
	d3dpp.hDeviceWindow = app->GetHWND();


	//khoi tao thiet bi hien thi
	HRESULT result = pD3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		app->GetHWND(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pD3dDevice);

	if FAILED(result)
	{
		Global::Notify("Error create d3ddevice", "Notify");
		return;
	}
		

	//xoa bo dem
	//xoa toan bo bo dem nen 2 tham so dau la 0 va NULL
	//D3DCLEAR_TARGET de yeu cau xoa toan bo
	//1.0f dosau bo dem - vd canh nhin vat ca nguoi choi, gia tri cao thi tam nhin ng choi xa hon
	//bo dem stencil 0xai nen de 0 : vung chinh dien k hien thi
	pD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	pD3dDevice->GetBackBuffer(
		0, //gia tri the hien kieu chao doi
		0, //chi so bo dem - neu chi co 1 bodem thi la 0
		D3DBACKBUFFER_TYPE_MONO,  //doi so dinh kieu
		&this->backBuffer);

	if (D3DXCreateSprite(this->pD3dDevice, &this->spriteHandler) != D3D_OK)
	{
		Global::Notify("Can't create spritehandler", "Error");
		return;
	}

}

LPDIRECT3DSURFACE9 Graphic::GetBackBuffer()
{
	return this->backBuffer;
}

LPDIRECT3D9 Graphic::GetD3D()
{
	return this->pD3d;
}

LPDIRECT3DDEVICE9 Graphic::GetD3DDevice()
{
	return this->pD3dDevice;
}

LPD3DXSPRITE Graphic::GetSpriteHandler()
{
	return this->spriteHandler;
}

LPDIRECT3DSURFACE9 Graphic::LoadSurface(char * fileName, D3DCOLOR transparencyColor)
{
	LPDIRECT3DSURFACE9 surface;
	D3DXIMAGE_INFO infor;

	D3DXGetImageInfoFromFile(fileName, &infor);

	HRESULT result = pD3dDevice->CreateOffscreenPlainSurface(
		infor.Width,
		infor.Height,
		D3DFMT_X8R8G8B8,//Tham so dinh dang kieu bo dem cau truc D3DFORMAT
		D3DPOOL_DEFAULT,//vung nhi luu tru| default: he thong chon phu hopnhat
		&surface,
		NULL);

	if FAILED(result)
	{
		Global::Notify("Can't CreateOffscreenPlainSurface", "Notify");
		return NULL;
	}

	result = D3DXLoadSurfaceFromFile(
		surface, //con tro doi tuong quan ly anh duoc tai vao
		NULL,// con tro dioi tuong kieu PALLETTEENTRY- dung cho256 mau loai khac thi null
		NULL,	//vung chu nhat surface ma anh duoc tai vao
		fileName,
		NULL, //vi tri vung dulieu anh goc se duoc lay de tai vao
		D3DX_DEFAULT, //bo loc
		transparencyColor,
		NULL);// imageinfor

	if FAILED(result)
	{
		Global::Notify("Can't LoadSurfaceFromFile", "Notify");
		return NULL;
	}

	return surface;
}

LPDIRECT3DSURFACE9 Graphic::CreateSurface(D3DCOLOR fillColor)
{
	LPDIRECT3DSURFACE9 surface;

	HRESULT result = pD3dDevice->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,//Tham so dinh dang kieu bo dem cau truc D3DFORMAT
		D3DPOOL_DEFAULT,//vung nhi luu tru| default: he thong chon phu hopnhat
		&surface,
		NULL);

	if FAILED(result)
	{
		Global::Notify("Can't CreateOffscreenPlainSurface", "Notify");
		return NULL;
	}

	pD3dDevice->ColorFill(surface, 0, fillColor);
	return surface;
}

LPDIRECT3DTEXTURE9 Graphic::LoadTeture(char * filename, D3DCOLOR transparencyColor)
{
	LPDIRECT3DTEXTURE9  texture;
	D3DXIMAGE_INFO infor;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &infor);
	if FAILED(result)
	{
		Global::Notify("Lỗi lấy thông tin ảnh cho texture!!!","Notify");
		return NULL;
	}


	result = D3DXCreateTextureFromFileEx(
		this->pD3dDevice,  //device gắn với texture này *
		filename, //đường dẫn,tên file nếu trùng thư mục*
		infor.Width, //chiều rộng sprite
		infor.Height,//chiều cao sprite
		1,
		D3DUSAGE_DYNAMIC,//D3DPOOL_DEFAULT,// kiểu surface
		D3DFMT_UNKNOWN, //định dạng
		D3DPOOL_DEFAULT, //nơi lưu trữ ( bộ nhớ)
		D3DX_DEFAULT, // bọ lọc ảnh
		D3DX_DEFAULT, //bộ lọc mip
		transparencyColor, //màu trong suốt*
		&infor, //infor của ảnh*
		NULL, //đổ màu*
		&texture);

	if FAILED(result) {
		Global::Notify("lỗi load texture!!!","Notify");
		return NULL;
	}

	return texture;
}

void Graphic::DrawSurface(LPDIRECT3DSURFACE9 surface, RECT *source, RECT* des)
{
	HRESULT result = pD3dDevice->StretchRect(
		surface, //source can dua vao backbuffer
		source, //hinh cn chua vung duoc sao chep
		this->backBuffer,
		des, //vung chua doi tuong tren surface dich
		D3DTEXF_NONE); //kieu loc trong qua trinh sao chep | none -k loc

	if FAILED(result)
	{
		//Global::Notify("Can't draw surface", "Notify");
		Trace::Log("Can't draw surface");
		return;
	}
	
}

void Graphic::DrawTexture(LPDIRECT3DTEXTURE9 Texture, RECT* sourceRect, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR3 rotationCenter)
{
	D3DXVECTOR2 inRotationCenter = (rotationCenter != D3DXVECTOR3()) ? D3DXVECTOR2(rotationCenter.x, rotationCenter.y) : D3DXVECTOR2(position.x, position.y);

	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(position.x, position.y);
	D3DXMATRIX	mMatrixTransform;	//Ma trận hỗ trợ phép biến hình
	D3DXMatrixTransformation2D(
		&mMatrixTransform,
		&scalingCenter,
		0,
		&scale,
		&inRotationCenter,
		rotation,
		&translation);

	D3DXMATRIX oldMatrix;


	spriteHandler->SetTransform(&mMatrixTransform);

	spriteHandler->Draw(
		Texture,
		sourceRect,
		&rotationCenter,
		&position,
		D3DCOLOR_XRGB(255, 255, 255));

}