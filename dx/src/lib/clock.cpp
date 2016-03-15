#include "clock.h"

#ifdef _WIN32
#include <Windows.h>
#endif

begin_LIB


void Clock::Start()
{
	_t = GetCurrentThreadId( );
	_start = now( );
}

void Clock::End()
{
	if (_t != GetCurrentThreadId())
		return;
	_end = now();
}

std::chrono::time_point<std::chrono::system_clock> Clock::now()
{
	return std::chrono::system_clock::now( );
}

double Clock::Milli()
{
	std::chrono::duration<double, std::milli> time = _start - _end;
	return std::abs( time.count( ) );
}

double Clock::Nano()
{
	std::chrono::duration<double, std::nano> time = _start - _end;
	return std::abs( time.count( ) );
}

Timer::Timer()
{
	__int64 countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	_secsPerCount = 1.0f / (float)countsPerSec;

	_prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&_prevTimeStamp);
}

float Timer::GetDeltaTime()
{
	__int64 currentTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTimeStamp);
	float timeDiff = (currentTimeStamp - _prevTimeStamp) * _secsPerCount;
	_prevTimeStamp = currentTimeStamp;

	return timeDiff;
}


end_LIB