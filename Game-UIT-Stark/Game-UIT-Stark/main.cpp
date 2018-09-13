#include"Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPre, LPSTR lpCmdLine, int cmdShow)
{
	Window  *window = new Window();
	window->Init(hInstance, "UIT_Stark", 800, 600);
	window->StartPrograme();

	return 1;
}
