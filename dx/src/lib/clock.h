#pragma once
#include "lib.h"
#include "../dx.h"

begin_LIB

class Clock
{
private:
	std::chrono::time_point<std::chrono::system_clock> _start, _end;
	uint _t;
public:
	void Start( );
	void End( );
	
	static std::chrono::time_point<std::chrono::system_clock> now( );
	double Milli( );
	double Nano( );
};


class Timer
{
private:
	float _secsPerCount;
	__int64 _prevTimeStamp;

public:
	Timer();
	~Timer() {}

	float GetDeltaTime();
};

end_LIB