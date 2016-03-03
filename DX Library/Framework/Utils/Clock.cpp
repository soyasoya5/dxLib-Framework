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
