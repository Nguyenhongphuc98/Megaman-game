#pragma once
#ifndef _Window_H_
#define _Window_H_

#include"define.h"
#include"Timer.h"

using namespace std;

class Window
{
private:
	HINSTANCE	windowHinstance;
	HWND		windowHWND;

	static Window* instance;

	char*		windowTitle;
	int			windowWidth;
	int			windowHeight;

public:
	Window();
	~Window();
	static Window* Instance();

	void Init(HINSTANCE hInstance, char* title, int width, int height);	
	void StartProgram();

	//cai nay phai xai static vi de binh thuong no co con tro this, khong tuong thich
	//voi WNDPROC
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	char* GetTitle();
	int GetWidth();
	int GetHeight();
	HWND GetHWND();
	HINSTANCE GetHinstance();

};

#endif // !_Window_H_
