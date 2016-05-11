#pragma once
#include "lib.h"
#include "../dx.h"
#include "clock.h"

begin_LIB


template<typename Fty>
class function
{
private:
	using callable = std::function<Fty>;
	callable callable_;

public:
	template<typename _Callable>
	function( _Callable &&callable )
		: callable_( std::forward<_Callable>( callable ) )
	{}

	function( )
		: callable_( )
	{}

	template<typename..._Ax>
	typename callable::result_type invoke( _Ax&&...args )
	{
		if ( callable_ )
			return callable_( std::forward<_Ax>( args )... );
		return typename callable::result_type( );
	}

	auto& target( ) { return callable_; }

	operator bool( ) { return callable_.operator bool(); }
};


template<typename Fty>
class EventHandler
{
private:
	function<Fty> f_;
	String name_;

public:
	template<typename _Callable>
	EventHandler( _Callable&&callable )
		: name_( "unknown" ), f_( std::forward<_Callable>( callable ) )
	{}

	template<typename _Callable>
	EventHandler( String name, _Callable&&callable )
		: name_( std::move( name ) ), f_( std::forward<_Callable>( callable ) )
	{}

	template<typename..._Ax>
	void invoke( _Ax&&...args )
	{
		f_.invoke( std::forward<_Ax>( args )... );
	}

	const auto& name( ) const { return name_; }

	auto& name( ) { return name_; }

	const auto& fty( ) const { return f_; }

	auto &fty( ) { return f_; }
};


template<typename Fty>
class Event
{
private:
	std::vector<EventHandler<Fty>> handlers_;

public:
	Event( )
		: handlers_( )
	{ }

	auto &getHandlers( ) { return handlers_; }

	void clear( ) { handlers_.clear( ); }

	template<typename..._Ax>
	void Invoke( _Ax&&...args )
	{
		for ( auto &x : handlers_ )
			x.invoke( std::forward<_Ax>( args )... );
	}

	void remove_handler( const String &name )
	{
		for ( auto it = handlers_.begin( ), end = handlers_.end( );
			  it < end;
			  ++it )
		{
			if ( it->name( ) == name )
			{
				handlers_.erase( it );
				break;
			}
		}
	}

	Event& operator+=( EventHandler<Fty> lhs )
	{
		handlers_.push_back( std::move( lhs ) );
		return *this;
	}

	Event& operator-=( const String &name )
	{
		remove_handler( name );
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