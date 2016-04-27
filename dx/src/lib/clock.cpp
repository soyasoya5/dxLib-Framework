#include "clock.h"

#ifdef _WIN32
#include <Windows.h>
#endif

begin_LIB


void StopWatch::Start()
{
	t_ = GetCurrentThreadId( );
	start_ = now( );
}

void StopWatch::End()
{
	if ( t_ != GetCurrentThreadId( ) )
		return;
	end_ = now( );
}

std::chrono::time_point<std::chrono::system_clock> StopWatch::now()
{
	return std::chrono::system_clock::now( );
}

double StopWatch::Milli()
{
	std::chrono::duration<double, std::milli> time = start_ - end_;
	return std::abs( time.count( ) );
}

double StopWatch::Nano()
{
	std::chrono::duration<double, std::nano> time = start_ - end_;
	return std::abs( time.count( ) );
}

DeltaTimer::DeltaTimer()
{
	__int64 countsPerSec = 0;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&countsPerSec );
	secsPerCount_ = 1.0f / (float)countsPerSec;

	prevTimeStamp_ = 0;
	QueryPerformanceCounter( (LARGE_INTEGER*)&prevTimeStamp_ );
}

float DeltaTimer::GetDeltaTime()
{
	__int64 currentTimeStamp = 0;
	QueryPerformanceCounter( (LARGE_INTEGER*)&currentTimeStamp );
	float timeDiff = (currentTimeStamp - prevTimeStamp_) * secsPerCount_;
	prevTimeStamp_ = currentTimeStamp;
	return timeDiff;
}


end_LIB