#pragma once
#include <thread>
#include "../dx.h"

namespace Utils {

	// Simple high resolution timer. 
	// Use start to start the timer, use End to end the timer.
	// (Note that they must be called in the same thread)
	class Clock
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
		uint _t;
	public:
		void Start( );
		void End( );
		
		static std::chrono::time_point<std::chrono::high_resolution_clock> now( );
		double Milli( );
		double Nano( );
	};


	class Timer
	{
	private:
		float secsPerCount;
		__int64 prevTimeStamp;

	public:
		Timer();
		~Timer() {}

		float GetDeltaTime();
	
	};

}