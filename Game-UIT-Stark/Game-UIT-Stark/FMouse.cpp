#include "FMouse.h"
#define BUTTON_DOWN(obj,button) (obj.rgbButtons[button] & 0x80)

FMouse* FMouse::Instance = nullptr;

FMouse::FMouse() {
	Init_DirectInput();
	Init_Mouse();
}

FMouse::~FMouse()
{
	Kill_Mouse();
}

int FMouse::Init_DirectInput() {
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		Window::Instance()->GetHinstance(),
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

int FMouse::Init_Mouse() {
	
	//set the data format for mouse input
	HRESULT result = Mouse->SetDataFormat(&c_dfDIMouse);
	if (result != DI_OK)
		return 0;
	//set the cooperative level
	//this will also hode the mouse pointer 
	result = Mouse->SetCooperativeLevel(Window::Instance()->GetHWND(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;
	//acquire the mouse 
	result = Mouse->Acquire();
	if (result != DI_OK)
	{
		Trace::Log("error init mouse");
		return 0;
	}
		
	//give the go_ahead
	return 1;
}

int FMouse::Mouse_X() {
	return Mouse_state.lX;
}
int FMouse::Mouse_Y() {
	return Mouse_state.lY;
}

int FMouse::Mouse_Button(int button) {
	return BUTTON_DOWN(Mouse_state, button);
}

void FMouse::Poll_Mouse() {
	Mouse->GetDeviceState(sizeof(Mouse_state), (LPVOID)&Mouse_state);
}

void FMouse::Kill_Mouse() {
	if (Mouse != NULL) {
		Mouse->Unacquire();
		Mouse->Release();
		Mouse = NULL;
	}
}

FMouse * FMouse::GetInstance()
{
	if (!Instance)
		Instance = new FMouse();
	return Instance;
}
