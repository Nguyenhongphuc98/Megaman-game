#include "FMouse.h"

HWND FMouse::_HWnd;
LPDIRECTINPUT8 FMouse::_DirectInput;		// The DirectInput object     
								


										  //Mouse
LPDIRECTINPUTDEVICE8 FMouse::_Mouse; // The mouse device
DIMOUSESTATE  FMouse::_MouseState; // DirectInput mouse state buffer 
DIDEVICEOBJECTDATA FMouse::_MouseEvents[16]; // Buffered keyboard data
std::vector<int> FMouse::_MouseCodesVector; //a vector of keycodes contained in buffered input
std::vector<int> FMouse::_MouseStatesVector; //a vector of keystates contained in buffered input
Vector2 FMouse::_MousePosition;


FMouse::FMouse()
{

}

FMouse::~FMouse()
{

}

void FMouse::Release()
{
	if (_DirectInput != NULL)
	{
		_DirectInput->Release();
		_DirectInput = NULL;
	}
	

	if (_Mouse != NULL)
	{
		_Mouse->Unacquire();
		_Mouse->Release();
		_Mouse = NULL;
	}
}

void FMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Release first for sure since we want to have just one class instance
	Release();
	ClearBuffedInput();

	_HWnd = hWnd;
	_MousePosition.Set(0, 0);

	HRESULT
		result = DirectInput8Create
		(
			hInstance, //handle for a window instance
			DIRECTINPUT_VERSION, //direct input version
			IID_IDirectInput8, //
			(VOID**)&_DirectInput,  //receive the interface pointer
			NULL //NULL if the interface is not aggregated
		);


	// TO-DO: put in exception handling
	if (result != DI_OK) return;
	//trace(L"DirectInput has been created");
	
	InitMouse();

}



bool FMouse::InitMouse()
{
	HRESULT result = _DirectInput->CreateDevice(
		GUID_SysMouse, //The default system keyboard
		&_Mouse,  //receive the IDirectInputDevice8 interface pointer 
		NULL //NULL if the interface is not aggregated.
	);

	// TO-DO: put in exception handling
	if (result != DI_OK) return false;
	//trace(L"DirectInput mouse has been created");


	// Set the data format to "mouse format" - a predefined data format 
	result = _Mouse->SetDataFormat(&c_dfDIMouse);
	//trace(L"SetDataFormat for mouse successfully");

	result = _Mouse->SetCooperativeLevel(_HWnd,
		DISCL_FOREGROUND |		//The application requires foreground access. 
								//If foreground access is granted, 
								//the device is automatically unacquired when the associated window moves to the background.
		DISCL_NONEXCLUSIVE		//The application requires nonexclusive access. 
								//Access to the device does not interfere with other applications that are accessing the same device.
	);
	//trace(L"SetCooperativeLevel for mouse successfully");



	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 16; // Arbitary buffer size

	result = _Mouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK) return false;
	//trace(L"SetProperty for keyboard successfully");




	result = _Mouse->Acquire();
	if (result != DI_OK) return false;
	//trace(L"Mouse has been acquired successfully");

	return true;
}




void FMouse::ProcessMouseInformation()
{
	HRESULT result;

	// Read the mouse device.
	result = _Mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_MouseState);

	// If the mouse lost focus or was not acquired then try to get control back.
	if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
	{
		_Mouse->Acquire();
		return;
	}

	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	_MousePosition.x += _MouseState.lX;
	_MousePosition.y += _MouseState.lY;



	// Handle key press event
	// NOTES: Buffered input is like an Event
	// Collect all buffered events (also clear them from DirectInput buffer)
	DWORD dwElements = 16;
	_Mouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _MouseEvents, &dwElements, 0);

	//insert keycodes and keystates into vectors
	_MouseCodesVector.insert(_MouseCodesVector.end(), &(_MouseEvents[0].dwOfs), &(_MouseEvents[0].dwOfs) + dwElements);
	_MouseStatesVector.insert(_MouseStatesVector.end(), &(_MouseEvents[0].dwData), &(_MouseEvents[0].dwData) + dwElements);

}


bool FMouse::GetMouse(int mouse)
{
	if (mouse > 3) return false;
	return _MouseState.rgbButtons[mouse] & 0x80;
}

bool FMouse::GetMouseDown(int mouse)
{
	//check if this keycode is pressed
	std::vector<int>::iterator it = std::find(_MouseCodesVector.begin(), _MouseCodesVector.end(), mouse);
	bool mouseCodePressed = (it != _MouseCodesVector.end());

	if (mouseCodePressed)
	{
		//check if it is key down
		return (_MouseStatesVector.at(it - _MouseCodesVector.begin()) & 0x80) > 0;
	}
	else
	{
		return false;
	}
}

bool FMouse::GetMouseUp(int mouse)
{
	//check if this keycode is pressed
	std::vector<int>::iterator it = std::find(_MouseCodesVector.begin(), _MouseCodesVector.end(), mouse);
	bool mouseCodePressed = (it != _MouseCodesVector.end());

	if (mouseCodePressed)
	{
		//check if it is key down
		return (_MouseStatesVector.at(it - _MouseCodesVector.begin()) & 0x80) <= 0;
	}
	else
	{
		return false;
	}
}

Vector2 FMouse::GetMousePosition()
{

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (_MousePosition.x < 0) { _MousePosition.x = 0; }
	if (_MousePosition.y < 0) { _MousePosition.y = 0; }

	//if (_MousePosition.X > 640) { _MousePosition.X = 640; }
	//if (_MousePosition.Y > 480) { _MousePosition.Y = 480; }

	return _MousePosition;

}

void FMouse::ClearBuffedInput()
{
	
	_MouseCodesVector.clear();
	_MouseStatesVector.clear();
}