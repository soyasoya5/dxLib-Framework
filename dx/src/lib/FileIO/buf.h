#pragma once
#include "lib.h"
#include "../../dx.h"


begin_FILEIO

	// a dynamic array of T
template<typename _Tx>
class Buffer
{
public:
	using _MyT = typename __DX remove_all<_Tx>::type;
	Buffer( )
		: _buffer( nullptr ), _length( 0 )
	{}
	Buffer( _MyT* _Buffer, const __DX uint &_Length )
	{
		this->copy_from( _Buffer, _Length );
	}
	Buffer( const Buffer &_Other )
	{
		this->copy_from( _Other._buffer, _Other._length );
	}
	Buffer( Buffer &&_Other )
		: Buffer( )
	{
		std::swap( this->_buffer, _Other._buffer );
		std::swap( this->_length, _Other._length );
	}


	void reserve( const __DX uint &_Length )
	{
		this->tidy( );
		_length = _Length;
		_buffer = new _MyT[_Length];
	}

	__DX uint resize( const __DX uint &_Length )
	{
		Buffer<_MyT> tmp = std::move( *this );
		this->reserve( _Length );
		this->assign( 0, tmp.begin( ), tmp.end( ) );
		return tmp._length;
	}

	void assign( _MyT *_It, _MyT *_It2 )
	{
		auto _myIt = this->begin( );
		auto _end = this->end( );
		for ( ; _myIt < _end && _It < _It2; ++_myIt, ++_It )
			*_myIt = *_It;
	}

	void assign( const __DX uint &_Offset, _MyT *_It, _MyT *_It2 )
	{
		auto _myIt = this->begin( ) + _Offset;
		auto _end = this->end( );
		for ( ; _myIt < _end && _It < _It2; ++_myIt, ++_It )
			*_myIt = *_It;
	}

	void append( _MyT *_It, _MyT *_It2 )
	{
		auto old = this->resize( _length + (_It2 - _It) );
		this->assign( old, _It, _It2 );
	}

	void append( _MyT *_Buffer, __DX uint _Length )
	{
		append( _Buffer, _Buffer + _Length );
	}

	void tidy( )
	{
		if ( _buffer )
			delete[] _buffer;
		_buffer = nullptr;
		_length = 0;
	}

	void copy_from( _MyT *_Buffer, const __DX uint &_Length )
	{
		this->resize( _Length );
		this->assign( _Buffer, _Buffer + _Length );
	}

	_MyT* data( )
	{
		return _buffer;
	}

public:

	_MyT *begin( )
	{	// get the first iterator
		return _buffer;
	}

	_MyT *end( )
	{
		return _buffer + _length;
	}

private:
	_MyT *_buffer;
	__DX uint _length;
};



end_FILEIO