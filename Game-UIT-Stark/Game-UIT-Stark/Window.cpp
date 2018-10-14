#include"Window.h"
#include "Game.h"
Window * Window::instance=NULL;

Window::Window()
{
	this->windowHinstance = NULL;
	this->windowHWND = NULL;
}

Window::~Window()
{
}

Window* Window::Instance()
{
	if (!instance)
		instance = new Window();
	return instance;
}

void Window::Init(HINSTANCE hInstance, char * title, int width, int height)
{
	this->windowHinstance = hInstance;
	this->windowTitle = title;
	this->windowWidth = width;
	this->windowHeight = height;

	//register window to use
	WNDCLASSEX wndclassex;
	wndclassex.lpszClassName = this->windowTitle;
	wndclassex.hInstance = this->windowHinstance;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = (WNDPROC)(this->WndProc);
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hbrBackground= (HBRUSH)GetStockObject(BLACK_BRUSH);
	
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hIcon = NULL;
	wndclassex.hIconSm = NULL;
	wndclassex.lpszMenuName = NULL;
	RegisterClassEx(&wndclassex);

	//create window
	this->windowHWND = CreateWindow(this->windowTitle,
		this->windowTitle,
		WS_OVERLAPPEDWINDOW,
		//WS_EX_TOPMOST|WS_VISIBLE|WS_POPUP,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		this->windowWidth,
		this->windowHeight,
		NULL, NULL, 
		this->windowHinstance, NULL);
	if (this->windowHWND == NULL)
	{
		Global::Notify("Can't create window", "Error");
		return;
	}

	//update window to screen
	ShowWindow(this->windowHWND, SW_SHOWNORMAL);
	UpdateWindow(this->windowHWND);

}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

char * Window::GetTitle()
{
	return this->windowTitle;
}



void Window::StartProgram()
{
	Game myGame;
	myGame.Init(windowHinstance, windowHWND);
	MSG msg;

	float tickPerFrame = 1000/MAX_FRAME_RATE; //tickPerframe max_frame_rate - 1k tick -> a tick=1k/max
	float delta = 0;
	float lastFrameTime = GetTickCount();
	float currentFrameTime;


	while (true)
	{
		Timer::Instance()->StartCounter();
		if (PeekMessageA(&msg, Window::Instance()->GetHWND(), 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta+= Timer::Instance()->GetCouter();
		if(delta>=tickPerFrame)
		{
			myGame.RunGame(delta);
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame-delta);
			delta = tickPerFrame;
			//Sleep(10);
		}

	}
}

int Window::GetWidth()
{
	return this->windowWidth;
}

int Window::GetHeight()
{
	return this->windowHeight;
}

HWND Window::GetHWND()
{
	return this->windowHWND;
}

HINSTANCE Window::GetHinstance()
{
	return this->windowHinstance;
}
