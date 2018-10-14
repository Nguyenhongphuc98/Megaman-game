#include "Timer.h"

Timer* Timer::__instance = NULL;

Timer::Timer()
{

}

Timer::~Timer()
{
}

Timer* Timer::Instance()
{
	if (!__instance)
		__instance = new Timer();

	return __instance;
}

void Timer::StartCounter()
{
	if (!QueryPerformanceFrequency(&mClockRate))
	{
		return;
	}

	QueryPerformanceCounter(&mStartTime);

}

float Timer::GetCouter()
{
	QueryPerformanceCounter(&mEndTime);
	mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;

	return ((float)mDelta.QuadPart / mClockRate.QuadPart);
}
