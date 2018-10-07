#include "FMouse.h"
#define BUTTON_DOWN(obj,button) (obj.rgbButtons[button] & 0x80)

FMouse* FMouse::Instance = nullptr;


LPDIRECTINPUT8 DInput;
LPDIRECTINPUTDEVICE8 Mouse;		// The mouse device 
DIMOUSESTATE Mouse_state;

int Init_DirectInput(HWND hwnd) {
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DInput,
		NULL);
		if (result != DI_OK)
			return 0;
		//initialize the mouse 
		result = DInput->CreateDevice(GUID_SysMouse, &Mouse, NULL);
		if (result != DI_OK)
			return 0;
		

		//clean return 
		return 1;

}

int Init_Mouse(HWND hwnd) {
	//set the data format for mouse input
	HRESULT result = Mouse->SetDataFormat(&c_dfDIMouse);
	if (result != DI_OK)
		return 0;
	//set the cooperative level
	//this will also hode the mouse pointer 
	result = Mouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;
	//acquire the mouse 
	result = Mouse->Acquire();
	if (result != DI_OK)
		return 0;
	//give the go_ahead
	return 1;
}

int Mouse_X() {
	return Mouse_state.lX;
}
int Mouse_Y() {
	return Mouse_state.lY;
}

int Mouse_Button(int button) {
	return BUTTON_DOWN(Mouse_state, button);
}

void Poll_Mouse() {
	Mouse->GetDeviceState(sizeof(Mouse_state), (LPVOID)&Mouse_state);
}

void Kill_Mouse() {
	if (Mouse != NULL) {
		Mouse->Unacquire();
		Mouse->Release();
		Mouse = NULL;
	}
}
