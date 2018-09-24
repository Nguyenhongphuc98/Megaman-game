#pragma once
#include "define.h"

#ifndef _KeyBoard_H_
#define _KeyBoard_H_

class KeyBoard
{
private:
	static KeyBoard * Instance;

	LPDIRECTINPUT8 DInput;				// The DirectInput object         
	LPDIRECTINPUTDEVICE8 Keyboard;		// The keyboard device 
	BYTE CurrentKeyStates[256],			// DirectInput keyboard current state buffer 
		PreviousKeyStates[256];		// DirectInput keyboard previous state buffer

	KeyBoard();
public:
	
	~KeyBoard();
	// Key is down on this frame but not on previous frame
	bool IsFirstKeyDown(int KeyCode);
	// Key is currently down
	bool IsKeyDown(int KeyCode);
	// Key is down on previous frame but not on this frame
	bool IsKeyUp(int KeyCode);
	void Init(HWND hWnd, HINSTANCE hInstance);
	void Update();
	void Unacquire();
	void Acquire();
	static KeyBoard *getInstance();

};


#endif // !_KeyBoard_H_
