#include"Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPre, LPSTR lpCmdLine, int cmdShow)
{
	Window  *window = Window::Instance();
	window->Init(hInstance, "UIT Stark", 800, 600);
	window->StartProgram();

	return 1;
}
