#pragma once
#include <functional>
#include <string>
#include <vector>


template<typename Rx, typename...Ax>
class Event 
{
	static_assert(!std::is_void<Rx>::value, "Event<void> is illegal.");

	typedef std::function<Rx(Ax...)> Signature;
	std::vector<Signature> _fs;
public:
	std::vector<Signature>& getF() { return _fs; }

	template<typename..._Args>
	std::vector<Rx> Invoke( _Args&&..._args )
	{
		std::vector<Rx> _r;
		for ( Signature&x : _fs )
			if ( x )
				_r.push_back( x( std::forward<_Args>( _args )... ) );
		return _r;
	}

	template<typename _Func>
	Event& operator+=( _Func&&f )
	{
		_fs.push_back( std::forward<_Func>(f) );
		return *this;
	}


// Binding :)
#define BIND_METHOD( ptr, func, ... ) std::bind( ptr, func, __VA_ARGS__ )
#define BIND_METHOD_1( ptr, func, ... ) BIND_METHOD( ptr, func, std::placeholders::_1, __VA_ARGS__ )
#define BIND_METHOD_2( ptr, func, ... ) BIND_METHOD_1( ptr, func, std::placeholders::_2, __VA_ARGS__ )
#define BIND_METHOD_3( ptr, func, ... ) BIND_METHOD_2( ptr, func, std::placeholders::_3, __VA_ARGS__ )
#define BIND_METHOD_4( ptr, func, ... ) BIND_METHOD_3( ptr, func, std::placeholders::_4, __VA_ARGS__ )
#define BIND_METHOD_5( ptr, func, ... ) BIND_METHOD_4( ptr, func, std::placeholders::_5, __VA_ARGS__ )
#define BIND_METHOD_6( ptr, func, ... ) BIND_METHOD_5( ptr, func, std::placeholders::_6, __VA_ARGS__ )
#define BIND_METHOD_7( ptr, func, ... ) BIND_METHOD_6( ptr, func, std::placeholders::_7, __VA_ARGS__ )
#define BIND_METHOD_8( ptr, func, ... ) BIND_METHOD_7( ptr, func, std::placeholders::_8, __VA_ARGS__ )
#define BIND_METHOD_9( ptr, func, ... ) BIND_METHOD_8( ptr, func, std::placeholders::_9, __VA_ARGS__ )
#define BIND_METHOD_10( ptr, func, ... ) BIND_METHOD_9( ptr, func, std::placeholders::_10, __VA_ARGS__ )

};


