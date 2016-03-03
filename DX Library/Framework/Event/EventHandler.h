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
};


