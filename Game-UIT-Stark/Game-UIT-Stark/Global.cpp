#include"Global.h"

Global::Global()
{
}

Global::~Global()
{
}

void Global::Notify(char * message,char *caption)
{
	MessageBox(NULL, message,caption, MB_OK | MB_ICONINFORMATION);
}

RECT Global::ConvertCollisionRectToRECT(CollisionRect rect)
{
	RECT result;
	result.top = rect.GetTop();
	result.left = rect.GetLeft();
	result.right = result.left + rect.GetWidth();
	result.bottom = result.top + rect.GetHeight();
	return result;
}
