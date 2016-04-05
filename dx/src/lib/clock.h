#pragma once
#include "lib.h"
#include "../dx.h"

begin_LIB

class StopWatch
{
private:
	std::chrono::time_point<std::chrono::system_clock> _start, _end;
	uint _t;
public:
	///<summary>
	/// Set the starting point.
	///</summary>
	void Start( );

	///<sumamry>
	/// Set the stopping point.
	///</summary>
	void End( );
	
	///<summary>
	/// Return now as a time_point.
	///</summary>
	static std::chrono::time_point<std::chrono::system_clock> now( );

	///<summary>
	/// Return the time passed from Start to End as milliseconds.
	///<summary>
	double Milli( );

	///<summary>
	/// Return the time passed from Start to End as nanoseconds.
	///<summary>
	double Nano( );
};

using Clock = StopWatch;


class DeltaTimer
{
private:
	float _secsPerCount;
	__int64 _prevTimeStamp;

public:
	DeltaTimer( );
	~DeltaTimer( ) {}

	///<summary>
	/// Get the time past since the last call to 'GetDeltaTime' as float (1.0 is one second).
	///</summary>
	float GetDeltaTime( );
};

using Timer = DeltaTimer;

end_LIB