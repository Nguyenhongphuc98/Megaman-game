#include"Window.h"


Window::Window()
{
	this->windowHinstance = NULL;
	this->windowHWND = NULL;
}

Window::~Window()
{
}

void Window::Init(HINSTANCE hInstance, char * title, int width, int height)
{
	this->windowHinstance = hInstance;
	this->windowTitle = title;
	this->windowWidth = width;
	this->windowHeight = height;

	//register window to use
	WNDCLASSEX wndclassex;
	wndclassex.lpszClassName = (LPCWSTR)this->windowTitle;
	wndclassex.hInstance = this->windowHinstance;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = (WNDPROC)(this->WndProc);
	wndclassex.cbSize = sizeof(wndclassex);
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.hbrBackground= (HBRUSH)GetStockObject(BLACK_BRUSH);
	
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hIcon = NULL;
	wndclassex.hIconSm = NULL;
	wndclassex.lpszMenuName = NULL;
	RegisterClassEx(&wndclassex);

	//create window
	this->windowHWND = CreateWindow((LPCWSTR)this->windowTitle,
		(LPCWSTR)this->windowTitle,
		WS_OVERLAPPEDWINDOW,
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

void Window::StartProgram()
{

	while (true)
	{

	}
}
