#include"Global.h"

Global::Global()
{
}

Global::~Global()
{
}

void Global::Notify(char * message,char *caption)
{
	MessageBox(NULL, (LPCWSTR)message, (LPCWSTR)caption, MB_OK | MB_ICONINFORMATION);
}
