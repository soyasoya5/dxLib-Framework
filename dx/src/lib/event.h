#pragma once
#include "lib.h"
#include "../dx.h"


begin_LIB

template<typename Rx, typename...Ax>
class Event 
{
	typedef std::function<Rx(Ax...)> Signature;
	std::vector<Signature> _fs;
public:
	std::vector<Signature>& getF() { return _fs; }

	template<typename..._Args>
	void Invoke( _Args&&..._args )
	{
		for ( auto &f : _fs ) 
			if ( f )
				f( std::forward<_Args>( _args )... );
	}

	template<typename _Func>
	Event& operator+=( _Func&&f )
	{
		_fs.push_back( std::forward<_Func>(f) );
		return *this;
	}

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