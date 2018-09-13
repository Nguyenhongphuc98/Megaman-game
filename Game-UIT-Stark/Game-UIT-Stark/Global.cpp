#include"Global.h"

Global::Global()
{
}

Global::~Global()
{
}

void Global::Notify(char * message,char *caption)
{
	MessageBox(NULL, message, caption, MB_OK | MB_ICONINFORMATION);
}
