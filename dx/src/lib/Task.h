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
	TimedTask( const function &function, const time_point &when )
		: function_( function ), when_( when )
	{ }

	///<summary>
	///	Calls the tasks function if enough time has past.
	///</summary>
	template<typename ..._Ax>
	bool call_task_if_time( const time_point &now, _Ax&&...args )
	{
		if ( when_.time_since_epoch( ) <= now.time_since_epoch( ) )
		{
			if ( function_ )
				function_( std::forward<_Ax>( args )... );
			Completed( ).Invoke( this );
			return true;
		}
		return false;
	}

	///<summary>
	///	Raised when the task is completed.
	///</summary>
	__LIB Event<void(TimedTask*)>& Completed( )
	{
		return _Completed;
	}

private:
	function function_;
	time_point when_;
	__LIB Event<void(TimedTask*)> _Completed;
};


end_LIB
