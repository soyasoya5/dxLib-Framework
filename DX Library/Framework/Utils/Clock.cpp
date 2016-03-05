#include "Clock.h"

void Utils::Clock::Start()
{
	_t = GetCurrentThreadId( );
	_start = now( );
}

void Utils::Clock::End()
{
	if (_t != GetCurrentThreadId())
		return;
	_end = now();
}

std::chrono::time_point<std::chrono::high_resolution_clock> Utils::Clock::now()
{
	return std::chrono::high_resolution_clock::now( );
}

double Utils::Clock::Milli()
{
	std::chrono::duration<double, std::milli> time = _start - _end;
	return std::abs( time.count( ) );
}

double Utils::Clock::Nano()
{
	std::chrono::duration<double, std::nano> time = _start - _end;
	return std::abs( time.count( ) );
}

Utils::Timer::Timer()
{
	__int64 countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	secsPerCount = 1.0f / (float)countsPerSec;

	prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);
}

float Utils::Timer::GetDeltaTime()
{
	_int64 currentTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTimeStamp);
	float timeDiff = (currentTimeStamp - prevTimeStamp) * secsPerCount;
	prevTimeStamp = currentTimeStamp;

	return timeDiff;
}
