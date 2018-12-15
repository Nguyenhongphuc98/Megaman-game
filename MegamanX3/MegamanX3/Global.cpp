#include"Global.h"




#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//
//GLOBAL CONSTANT
//


char*		G_GameName = (char*)"GAME MEGAMAN ";
int			G_FrameRate = 90;

bool		G_IsFullScreen = false;
D3DFORMAT	G_BackBufferFormat;


RECT		G_WindowSize;
int			G_ScreenWidth =  620; //640;	//640	//1024	//1366
int			G_ScreenHeight = 580; //480;	//480	//768	//768


//
//GLOBAL VARIANT
//

D3DXVECTOR2 G_Scale = D3DXVECTOR2(2.5, 2.5);
D3DXVECTOR2 G_ScaleFlipX = D3DXVECTOR2(-2.5, 2.5);
D3DXVECTOR2 G_ScaleFlipY = D3DXVECTOR2(2.5, -2.5);

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
	
}

void GLMessage(const char* text)
{
	MessageBox(G_hWnd, text, "Notify", MB_OK);
}

void GLTitle(char* text) {
	SetWindowText(G_hWnd, text);
}