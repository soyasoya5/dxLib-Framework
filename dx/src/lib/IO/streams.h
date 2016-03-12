#pragma once
#include "lib.h"
#include "buf.h"

begin_IO

class stream
{
public:
	using Streambuf = _Streambuf<__DX byte>;





public: // IO functions
	template<typename _Iterator>
	void append( _Iterator _I1, _Iterator _I2 );

	template<__DX uint _Length, typename _Tx>
	void extract( _Tx &_To );

	Streambuf::_FwdIter begin( );
	Streambuf::_FwdIter current( );
	Streambuf::_FwdIter end( );
public: // operators
	operator bool( );
	stream& operator=( const stream &_Lhs );
private:
	__IO _Streambuf<__DX byte> _Buffer;
	__DX uint _Index;
};


template<typename _Tx>
stream& operator<<( stream &_Stream, const _Tx &_Rhs );
template<typename _Tx>
explicit stream& operator>>( stream &_Stream, _Tx &_Rhs );

stream& operator<<( stream &_Lhs, stream &_Rhs );
stream& operator>>( stream &_Lhs, stream &_Rhs );
end_IO

#include "streams.inl"

