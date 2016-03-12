#pragma once
#include "streams.h"


begin_IO


template<typename _Iterator>
inline void stream::append(_Iterator _I1, _Iterator _I2)
{
	this->_Buffer.append( _I1, _I2 );
}

template<__DX uint _Length, typename _Tx>
inline void stream::extract(_Tx & _To)
{
	__DX byte *_Bytes = bytes_cast( _To );
	auto _MyIt = this->current( );
	auto _End = _MyIt + _Length;
	for ( ; _MyIt != _End; ++_MyIt, ++_Bytes)
		*_Bytes = *_MyIt;
	_Index += _Length;
}




template<typename _Tx>
inline stream &operator<<(stream & _Stream, const _Tx &_Rhs)
{
	_Stream.append( std::begin( &_Rhs ), std::end( (&_Rhs) + sizeof(_Tx) ) );
}

template<typename _Tx>
inline stream &operator>>(stream &_Stream, _Tx &_Rhs)
{
	_Stream.extract( _Rhs );
}

end_IO