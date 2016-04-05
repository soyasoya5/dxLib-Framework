#pragma once
#include "lib.h"
#include "../dx.h"
#include "clock.h"

begin_LIB


// Wrapper to contain a function
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
	timed_function( const _Func &_func )
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

// Wrapper to contain a name for an event function
template<typename _Sig>
class EventHandler
{
private:
	__LIB String _name;
	timed_function<_Sig> _func;
public:

	template<typename _Func>
	EventHandler( const __LIB String &_Name, const _Func &_Function )
		: _name( _Name ), _func( _Function )
	{}

	auto& get( ) { return _func; }
	auto& name( ) { return _name; }
};

// An Event(Raiser)
template<typename _Sig>
class Event
{
	typedef EventHandler<_Sig>* Signature;
	std::vector<Signature> _fs;
public:
	// Default
	Event( ) = default;

	~Event( )
	{
		// Clear and delete handlers
		clear( );
	}

	// Get list of handlers
	auto& getF( ) { return _fs; }

	// Clear the handlers
	void clear( )
	{
		for ( auto&x : _fs )
			delete x;
		_fs.clear( );
	}

	// Invoke
	template<typename ..._Args>
	void Invoke( _Args&&..._args )
	{
		auto now = __LIB Clock::now( );
		for ( auto&x : _fs )
		{
			// Invoke if time
			x->get( ).invoke_if_time( now, std::forward<_Args>( _args )... );
			std::this_thread::sleep_for( std::chrono::nanoseconds( 5000 ) );
		}
	}

	void remove_handler( const __LIB String &name )
	{
		for ( auto it = _fs.begin( ); it < _fs.end( ); ++it )
		{
			if ( (*it)->name( ) == name )
			{
				_fs.erase( it );
				delete (*it);
				break;
			}
		}
	}



	template<typename T>
	timed_function<_Sig>& operator+=(const T &f )
	{
		// Create an unamed handler
		auto handler = new EventHandler<_Sig>( "unamed", f );

		// Push it
		_fs.push_back( handler );

		// Return a reference to the function
		return handler->get( );
	}
	
	template<>
	timed_function<_Sig>& operator+=<EventHandler<_Sig>>( const EventHandler<_Sig> &_Function )
	{
		// Copy _Function and push the copy into the array
		_fs.push_back( new EventHandler<_Sig>( _Function ) );

		// Return function
		return _fs.back( )->get( );
	}


};


//template<typename _Sig>
//class Event 
//{
//	typedef timed_function<_Sig>* Signature;
//	std::vector<Signature> _fs;
//public:
//	Event( ) = default;
//	~Event( )
//	{
//		for ( auto&x : _fs )
//			delete x;
//	}
//
//	std::vector<Signature>& getF() { return _fs; }
//
//	void clear( )
//	{
//		for ( auto&x : _fs )
//			delete x;
//		_fs.clear( );
//	}
//
//	template<typename..._Args>
//	void Invoke( _Args&&..._args )
//	{
//		auto now = __LIB Clock::now( );
//		for ( auto&x : _fs ) {
//			x->invoke_if_time( now, std::forward<_Args>( _args )... );
//			std::this_thread::sleep_for( std::chrono::nanoseconds( 5000 ) );
//		}
//	}
//
//	template<typename _Func>
//	timed_function<_Sig>& operator+=( _Func&&f )
//	{
//		timed_function<_Sig>* func = new timed_function<_Sig>( std::forward<_Func>( f ) );
//		_fs.push_back( func );
//		return *func;
//	}
//
//};


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