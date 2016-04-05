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

	///<summary>
	/// Construct this with '_Func' being a function.
	///</summary>
	template<typename _Func>
	timed_function( const _Func &_func )
	{
		_f = _func;
		_delay = std::chrono::milliseconds( 0 );
		_last = __LIB Clock::now( );
	}

	///<summary>
	/// Invoke the function if enough time has passed since the last call to the function.
	///</summary>
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

	///<summary>
	/// Set the minimum delay per invoke to this function, meaning:
	/// Invoke only if N time has passed since last call.
	///</summary>
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

	///<summary>
	/// Construct this EventHandler with a Name and Function.
	///</summary>
	template<typename _Func>
	EventHandler( const __LIB String &_Name, const _Func &_Function )
		: _name( _Name ), _func( _Function )
	{}

	///<summary>
	/// Return a reference to the timed_function that is held by this handler.
	///</summary>
	auto& get( ) { return _func; }

	///<summary>
	/// Return the name of this EventHandler.
	///</summary>
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

	///<summary>
	/// Return the vector of EventHandlers that this contains.
	///</summary>
	auto& getF( ) { return _fs; }

	///<summary>
	/// Clear all the EventHandlers that this contains.
	///</summary>
	void clear( )
	{
		for ( auto&x : _fs )
			delete x;
		_fs.clear( );
	}

	///<summary>
	/// Raise the event.
	///</summary>
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

	///<summary>
	/// Remove a event handler from this Event by name.
	///</summary>
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

	///<summary>
	///	Add an EventHandler to this Event.
	///</summary>
	template<typename T>
	timed_function<_Sig>& operator+=(const T &_Function )
	{
		// Create an unamed handler
		auto handler = new EventHandler<_Sig>( "unamed", _Function );

		// Push it
		_fs.push_back( handler );

		// Return a reference to the function
		return handler->get( );
	}
	
	///<summary>
	///	Add an EventHandler to this Event.
	///</summary>
	template<>
	timed_function<_Sig>& operator+=<EventHandler<_Sig>>( const EventHandler<_Sig> &_Function )
	{
		// Copy _Function and push the copy into the array
		_fs.push_back( new EventHandler<_Sig>( _Function ) );

		// Return function
		return _fs.back( )->get( );
	}

	///<summary>
	/// Remove a event handler from this Event by name.
	///</summary>
	auto& operator-=( const __LIB String &_Name )
	{
		remove_handler( _Name );
		return *this;
	}


};


// Base EventArgs class
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