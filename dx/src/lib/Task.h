#pragma once
#include "lib.h"
#include "../dx.h"
#include "event.h"


begin_LIB


template<typename _Sig>
class TimedTask
{
public:
	typedef std::chrono::system_clock clock;
	typedef std::chrono::time_point<clock> time_point;
	typedef std::function<_Sig> function;

public:
	TimedTask( const function &_Function, const time_point &_When )
		: _function( _Function ), _when( _When )
	{ }

	template<typename ..._Ax>
	bool call_task_if_time( const time_point &_Now, _Ax&&..._Args )
	{
		if ( _when.time_since_epoch( ) <= _Now.time_since_epoch( ) )
		{
			if ( _function )
				_function( std::forward<_Ax>( _Args )... );
			Completed( ).Invoke( this );
			return true;
		}
		return false;
	}

	// An event that is called whenever a task is called
	__LIB Event<void(TimedTask*)>& Completed( )
	{
		return _Completed;
	}

private:
	function _function;
	time_point _when;
	__LIB Event<void(TimedTask*)> _Completed;
};


end_LIB
