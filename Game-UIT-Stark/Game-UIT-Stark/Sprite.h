#pragma once
#ifndef _Sprite_H_
#define _Sprite_H_
#include "Window.h" //thằng này là cái tự viết chứa phần khởi tạo cửa sổ chứ không có gì hết.
#include<vector>
#include "FGraphics.h"
using namespace std;

class  Sprite
{	
private:
	LPD3DXSPRITE		spriteHander; //Xài thằng này để thao tác với sprite
	LPDIRECT3DTEXTURE9	texture;// lưu sprite xí mà load lên
	D3DXVECTOR3			position; //vị trí vẽ
	D3DXVECTOR3			center; //tâm vẽ
	D3DXMATRIX			matScale; //ma trận thu phóng
	D3DXMATRIX			matTranslate; //ma trận dịch chuyển
	D3DXMATRIX			matRotation;

	int currentFrame; //frame hiện tại đang chiếu
	int countFrame; //tổng số frame có của sprite ,trong trường hợp này = listSourceRect.size;
	bool isFlipHorizontal; //can cu de xem neu do dang lat thi khi muon lat khong can lat nua
	bool isFlipVertical;

	vector<RECT*> listSourceRect; //list các ô chữ nhật lưu thông tin vùng ảnh sẽ lấy ra để vẽ

public:
	Sprite(char* path, vector<RECT*> listSourceRect);
	~Sprite();

	void Render(); //render ra để show lên màn hình
	void SetPosition(D3DXVECTOR3 p); //như cái tên
	void setCenter(D3DXVECTOR3 c); //như cái tên
	void SetCurrentFrame(int index); //như cái tên
	void SetScale(D3DXVECTOR3 vectorScale = D3DXVECTOR3(1, 1, 0)); //như cái tên
	void SetTranslate(D3DXVECTOR3 vectorTranslate = D3DXVECTOR3(0, 0, 0)); //như cái tên
	void SetRotation(float angle); //như cái tên

	void FlipVertical(bool flag); //flip theo truc
	void FlipHorizontal(bool flag);


	int GetCurrentFrame();
	vector<RECT*> GetListSourceRect();
};

#endif // !_Sprite_H_
