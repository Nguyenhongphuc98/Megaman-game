#include "FKeyBoard.h"

FKeyBoard* FKeyBoard::Instance = nullptr;

FKeyBoard::FKeyBoard() :
	DInput(nullptr),
	Keyboard(nullptr)
{
	Window* apps = Window::Instance();

	HRESULT result;
	result = DirectInput8Create(
		apps->GetHinstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DInput,
		NULL);

	if (result != DI_OK)
	{
		Global::Notify("Không thể tạo keyboard input", "Lỗi");
		return ;
	}

	result = DInput->CreateDevice(
		GUID_SysKeyboard,
		&Keyboard,
		NULL);

	if (result != DI_OK)
	{
		Global::Notify(" Can't create Keyboard device","[Error]");
		return ;
	}


	result = Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
	{
		Global::Notify("Không thể set data format keyboard", "Lỗi");
		return ;
	}

	result = Keyboard->SetCooperativeLevel(apps->GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (result != DI_OK)
	{
		Global::Notify("Không thể SetCooperativeLevel", "Lỗi");
		return ;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = GL_KEY_BUFFER_SIZE; // Arbitrary buffer size


	result = Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
		return ;
	Acquire();
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

	//Acquire();
	// Collect new key states
	Keyboard->GetDeviceState(sizeof(CurrentKeyStates), CurrentKeyStates);
	//Unacquire();
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





