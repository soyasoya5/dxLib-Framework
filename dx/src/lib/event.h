#pragma once
#include "lib.h"
#include "../dx.h"
#include "clock.h"

begin_LIB


template<typename _Sig>
class timed_function
{
private:
	typedef std::function<_Sig> Signature;
	Signature _f;
	std::chrono::time_point<std::chrono::system_clock> _last;
	std::chrono::milliseconds _delay;
public:
	template<typename _Func>
	timed_function( _Func &&_func )
	{
		_f = _func;
		_delay = std::chrono::milliseconds( 0 );
		_last = __LIB Clock::now( );
	}

	template<typename..._Args>
	void invoke_if_time( std::chrono::time_point<std::chrono::system_clock> &_Now, _Args&&..._args )
	{
		if ( (_Now.time_since_epoch( ) - _last.time_since_epoch( )) >= _delay )
		{
			_last = _Now;
			if ( _f )
				_f( std::forward<_Args>( _args )... );
		}
	}

	void Every( const std::chrono::milliseconds &_By )
	{
		_delay = _By;
	}
};

template<typename _Sig>
class Event 
{
	typedef timed_function<_Sig>* Signature;
	std::vector<Signature> _fs;
public:
	Event( ) = default;
	~Event( )
	{
		for ( auto&x : _fs )
			delete x;
	}

	std::vector<Signature>& getF() { return _fs; }

	template<typename..._Args>
	void Invoke( _Args&&..._args )
	{
		auto now = __LIB Clock::now( );
		for ( auto&x : _fs )
			x->invoke_if_time( now, std::forward<_Args>( _args )... );
		
	}

	template<typename _Func>
	timed_function<_Sig>& operator+=( _Func&&f )
	{
		timed_function<_Sig>* func = new timed_function<_Sig>( std::forward<_Func>( f ) );
		_fs.push_back( func );
		return *func;
	}

};


	// Base class
class EventArgs
{
public:
	bool handled;
};

// Binding :)
#define BIND_METHOD( func, ptr, ... ) std::bind( func, ptr, __VA_ARGS__ )
#define BIND_METHOD_1( func, ptr, ... ) BIND_METHOD( func, ptr, std::placeholders::_1, __VA_ARGS__ )
#define BIND_METHOD_2( func, ptr, ... ) BIND_METHOD_1( func, ptr, std::placeholders::_2, __VA_ARGS__ )
#define BIND_METHOD_3( func, ptr, ... ) BIND_METHOD_2( func, ptr, std::placeholders::_3, __VA_ARGS__ )
#define BIND_METHOD_4( func, ptr, ... ) BIND_METHOD_3( func, ptr, std::placeholders::_4, __VA_ARGS__ )
#define BIND_METHOD_5( func, ptr, ... ) BIND_METHOD_4( func, ptr, std::placeholders::_5, __VA_ARGS__ )
#define BIND_METHOD_6( func, ptr, ... ) BIND_METHOD_5( func, ptr, std::placeholders::_6, __VA_ARGS__ )
#define BIND_METHOD_7( func, ptr, ... ) BIND_METHOD_6( func, ptr, std::placeholders::_7, __VA_ARGS__ )
#define BIND_METHOD_8( func, ptr, ... ) BIND_METHOD_7( func, ptr, std::placeholders::_8, __VA_ARGS__ )
#define BIND_METHOD_9( func, ptr, ... ) BIND_METHOD_8( func, ptr, std::placeholders::_9, __VA_ARGS__ )
#define BIND_METHOD_10( func, ptr, ... ) BIND_METHOD_9( func, ptr, std::placeholders::_10, __VA_ARGS__ )

end_LIB