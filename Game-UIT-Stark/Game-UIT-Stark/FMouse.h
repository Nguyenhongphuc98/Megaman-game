//#pragma once
//#include "define.h"
//#include"Window.h"
//
//#ifndef _FMouse_H_
//#define _FMouse_H_
//
//class FMouse
//{
//private:
//	static FMouse * Instance;
//
//	LPDIRECTINPUT8 DInput;				// The DirectInput object         
//	LPDIRECTINPUTDEVICE8 Mouse;		// The mouse device 
//	DIMOUSESTATE Mouse_state;
//	
//
//	FMouse();
//public:
//
//	~FMouse();
//
//	
//	//void Init(HWND hWnd, HINSTANCE hInstance);
//	int Init_DirectInput();
//	void Poll_Mouse();
//	int Init_Mouse();
//	int Mouse_Button(int);
//	int Mouse_X();
//	int Mouse_Y();
//	void Kill_Mouse();
//	//void Update();
//	//void Unacquire();
//	//void Acquire();
//	static FMouse* GetInstance();
//
//};
//
//
//#endif // !_FMouse_H_
//
//
//


#pragma once
#include "define.h"
#include"Window.h"
//#include "..\extensions\directX9\Include\d3d9.h"
//#include "..\extensions\directX9\Include\d3dx9.h" //please read the readme.txt file if you have any problems with this include line. 
#include<vector>
#include "dinput.h"
#include <algorithm>    // std::find
#include "Vector2.h"
#define KEYBOARD_BUFFER_SIZE	1024

#ifndef _FMouse_H_
#define _FMouse_H_
#define KEYBOARD_BUFFER_SIZE	1024

class FMouse
{
private:
	static HWND _HWnd;
	static LPDIRECTINPUT8       _DirectInput;

	//Mouse
	static LPDIRECTINPUTDEVICE8 _Mouse; // The mouse device
	static DIMOUSESTATE  _MouseState; // DirectInput mouse state buffer 
	static DIDEVICEOBJECTDATA _MouseEvents[16]; // Buffered keyboard data
	static std::vector<int> _MouseCodesVector; //a vector of keycodes contained in buffered input
	static std::vector<int> _MouseStatesVector; //a vector of keystates contained in buffered input
	static Vector2 _MousePosition;

	static bool InitMouse();
	


	FMouse();
public:

	~FMouse();
	//RECOMMEND: Do not call this function because game class will take care of this.
	//If you do call this function, consider to release it first 
	static void Init(HINSTANCE hInstance, HWND hWnd);

	

	//RECOMMEND: Do not call this function because game class will take care of this.
	static void ProcessMouseInformation();

	//clear buffed input. It means in the same frame after you call this function, getkeydown and getkeyup is disposed  
	//Note that this function just has its affect in the frame after you call it 
	static void ClearBuffedInput();

	

	//return true while the user holds dow the key, such as auto fire
	static bool GetMouse(int mouse);

	//NOTE: weird action
	//return true during the time user stars pressing the key until it reaches the very bottom of the key.  
	static bool GetMouseDown(int mouse);

	//NOTE: weird action
	//return true during the time user stars releasing the key until it reaches the very top of the key.  
	static bool GetMouseUp(int mouse);

	//Get Mouse Position
	static Vector2 GetMousePosition();

	static void Release();



};


#endif // !_FMouse_H_
