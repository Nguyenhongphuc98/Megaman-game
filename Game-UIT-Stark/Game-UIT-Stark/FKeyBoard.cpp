#include "FKeyBoard.h"

FKeyBoard* FKeyBoard::Instance = nullptr;

FKeyBoard::FKeyBoard() :
	DInput(nullptr),
	Keyboard(nullptr)
{

}
// Check input  
FKeyBoard::~FKeyBoard() {
	if (DInput) {
		DInput->Release();
		DInput = nullptr;
	}
	if (Keyboard) {
		Keyboard->Release();
		Keyboard = nullptr;
	}
}

bool FKeyBoard::IsFirstKeyDown(int KeyCode) {
	return (CurrentKeyStates[KeyCode] & 0x80) > 0 && (PreviousKeyStates[KeyCode] & 0x80) <= 0;
}

bool FKeyBoard::IsKeyDown(int KeyCode)
{
	return (CurrentKeyStates[KeyCode] & 0x80) > 0;
}

bool FKeyBoard::IsKeyUp(int KeyCode)
{
	return (CurrentKeyStates[KeyCode] & 0x80) <= 0 &&
		(PreviousKeyStates[KeyCode] & 0x80) > 0;
}

void FKeyBoard::Init(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT
		hr = DirectInput8Create
		(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&DInput, NULL
		);

	if (hr != DI_OK)
	{
		Trace::Log("[ERROR] Unable to create DirectInput.");
		return;
	}

	hr = DInput->CreateDevice(GUID_SysKeyboard, &Keyboard, NULL);

	if (hr != DI_OK)
	{
		Trace::Log("[ERROR] Unable to create Device Keyboard.");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.
	hr = Keyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	Acquire();
}

void FKeyBoard::Update()
{
	// Current -> Previous
	for (int i = 0; i < 256; i++)
		PreviousKeyStates[i] = CurrentKeyStates[i];

	// Collect new key states
	Keyboard->GetDeviceState(sizeof(CurrentKeyStates), CurrentKeyStates);
}

void FKeyBoard::Unacquire()
{
	HRESULT hr = Keyboard->Unacquire();
	if (hr == S_FALSE)
	{
		Trace::Log("Keyboard unacquired.");
	}
}

void FKeyBoard::Acquire()
{
	HRESULT hr = Keyboard->Acquire();
	if (hr != DI_OK)
	{
		//Global::Notify("content", "title");
		Trace::Log("[ERROR] Unable to acquire keyboard.");
	}
	else
	{
		//Global::Notify("content", "title");
		Trace::Log("Keyboard acquired.");
	}
}

FKeyBoard * FKeyBoard::getInstance()
{
	if (!Instance)
		Instance = new FKeyBoard();

	return Instance;
}





