#pragma once
#ifndef _TIME_H_
#define _TIME_H_

#include <Windows.h>

class Timer
{
public:
	void StartCounter();
	float GetCouter();
	static Timer* Instance();
	~Timer();
	static LARGE_INTEGER temp;
private:
	Timer();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static Timer *__instance;
};

#endif

