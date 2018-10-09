#include"Window.h"
#include"define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPre, LPSTR lpCmdLine, int cmdShow)
{
	Window  *window = Window::Instance();
	window->Init(hInstance, "UIT Stark", SCREEN_WIDTH, SCREEN_HEIGHT);
	window->StartProgram();

	return 1;
}
