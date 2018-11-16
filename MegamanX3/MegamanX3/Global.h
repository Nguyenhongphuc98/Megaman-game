#pragma once

#ifndef Global_H_
#define Global_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>


//GLOBAL CONSTANT

//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024



//
//GLOBAL VARIANT
//

extern D3DXVECTOR2 G_Scale;
extern D3DXVECTOR2 G_ScaleFlipX;
extern D3DXVECTOR2 G_ScaleFlipY;

extern bool			G_IsFullScreen;

extern bool			G_IsInitedDX;		//check if dx is inited

extern char*		G_GameName;		//name of game, view in caption
extern int			G_FrameRate;		//frame rate(30 -> 60)

extern int			G_ScreenWidth;			//width of game screen
extern int			G_ScreenHeight;			//height of game screen
extern RECT			G_WindowSize;			//size of game screen

extern HINSTANCE					G_hInstance;		// Handle of the game instance
extern HWND							G_hWnd;			// Handle of the Game Window

extern LPDIRECT3D9					G_DirectX;			//handle dx
extern LPDIRECT3DDEVICE9			G_Device;			//dx device
extern LPDIRECT3DSURFACE9			G_BackBuffer;		//backbuffer
extern D3DFORMAT					G_BackBufferFormat;//backbuffer format, used in initing dx

extern LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8			G_KeyBoard;			// The keyboard device 
extern LPD3DXSPRITE					G_SpriteHandler;	// spriteHandler to draw texture


// Pause
extern bool Pause;
extern bool PauseOfWatch;

// 
// Weapon
extern bool pause_Sound;
//GLOBAL METHOD


//=============================================================
//-----------------ENUM----------------------------------------
//=============================================================

enum State {
	//megaman
	RUN,
	JUMP,
	STAND,
	SHOOT,
	CLIMB,
	//weapons
	NORMALBULLET,
	SUPERBULLET,
	DESTROYBULLET,
	//blast_hornet
	REDKNEE,
	REDHANDS,
	PREPAREOPENVENOM,
	OPENINGVENOM,
	//bee
	FLAPPING, //vo canh
	FLAPPINGANDFLYING,
	//notorbanger
	SHOOT90,
	//shurikein
	APPEAR,
	ROTATERIGHT,
	ROTATELEFT,
	//HeadGunnerCustomer
	SHOOTABOVE,
	SHOOTBELOW,
};

enum Direction {
	LEFT,
	RIGHT
};

//write string to a tracing file
void GLTrace(char* format, ...);

//show a message box
void GLMessage(const char* text);

//show string to the caption of window
void GLTitle(char* text);



#endif