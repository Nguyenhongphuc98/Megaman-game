#pragma once
#include "define.h"
#include"Window.h"

#ifndef _FMouse_H_
#define _FMouse_H_

class FMouse
{
private:
	static FMouse * Instance;

	LPDIRECTINPUT8 DInput;				// The DirectInput object         
	LPDIRECTINPUTDEVICE8 Mouse;		// The mouse device 
	DIMOUSESTATE Mouse_state;
	

	FMouse();
public:

	~FMouse();

	
	//void Init(HWND hWnd, HINSTANCE hInstance);
	int Init_DirectInput();
	void Poll_Mouse();
	int Init_Mouse();
	int Mouse_Button(int);
	int Mouse_X();
	int Mouse_Y();
	void Kill_Mouse();
	//void Update();
	//void Unacquire();
	//void Acquire();
	static FMouse* GetInstance();

};


#endif // !_FMouse_H_
