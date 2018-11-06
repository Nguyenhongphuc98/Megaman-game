#include"Global.h"




#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//
//GLOBAL CONSTANT
//


char*		G_GameName = (char*)"GAME MEGAMAN";
int			G_FrameRate = 60;

bool		G_IsFullScreen = false;
D3DFORMAT	G_BackBufferFormat;


RECT		G_WindowSize;
int			G_ScreenWidth = 800; //640;	//640	//1024	//1366
int			G_ScreenHeight = 600; //480;	//480	//768	//768


//
//GLOBAL VARIANT
//

D3DXVECTOR2 G_Scale = D3DXVECTOR2(2, 2);
D3DXVECTOR2 G_ScaleFlipX = D3DXVECTOR2(-2, 2);
D3DXVECTOR2 G_ScaleFlipY = D3DXVECTOR2(2, -2);

HINSTANCE					G_hInstance;		// Handle of the game instance
HWND						G_hWnd;				// Handle of the Game Window

LPDIRECT3D9					G_DirectX;
LPDIRECT3DDEVICE9			G_Device;
LPDIRECT3DSURFACE9			G_BackBuffer;

LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8		G_KeyBoard;			// The keyboard device 
LPD3DXSPRITE				G_SpriteHandler;	// spriteHandler to draw texture


void GLTrace(char* format, ...)
{
	//char *_traceFile = "C:\\Temp\\Sample_TH_game.log";
	//int _traceNum = 1;

	//if (!_traceNum) return;

	//FILE *f = stderr;
	//if (_traceFile != NULL)
	//{
	//	if (fopen_s(&f, _traceFile, "a") != 0)
	//	{
	//		fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
	//		return;
	//	}
	//}
	//va_list ap;
	//va_start(ap, format);
	//fprintf(f, format, ap);
	//va_end(ap);
	//fprintf(f, "\n");
	//if (_traceFile != NULL) fclose(f);
}

void GLMessage(const char* text)
{
	MessageBox(G_hWnd, text, "Notify", MB_OK);
}

void GLTitle(char* text) {
	SetWindowText(G_hWnd, text);
}