#include "buf.h"

begin_IO

template<typename _Tx>
inline _Streambuf<_Tx>::_Streambuf( )
	: _Buf( nullptr ), _Length( _Base::bad )
{ }

template<typename _Tx>
inline _Streambuf<_Tx>::_Streambuf(_MyTx * _Buffer, __DX uint _Length)
	: _Buf( _Buffer ), _Length( _Length )
{
}

template<typename _Tx>
inline _Streambuf<_Tx>::_Streambuf(const _Base & _Other)
	: _Buf( _Other._Buf ), _Length( _Other._Length )
{
}

template<typename _Tx>
inline _Streambuf<_Tx>::_Streambuf(_Base && _Rvalue)
{
	swap( _Rvalue );
}

template<typename _Tx>
inline _Streambuf<_Tx>::_Streambuf(const std::initializer_list<_MyTx>& _List)
{
	reserve( _List.size( ) );
	assign( _List.begin( ), _List.end( ) );
}

template<typename _Tx>
inline _Streambuf<_Tx>::~_Streambuf()
{
	clean( );
}

template<typename _Tx>
inline void _Streambuf<_Tx>::reserve(const __DX uint &_Length)
{
	clean( );
	this->_Length = _Length;
	this->_Buf = new _MyTx[_Length];
}

template<typename _Tx>
template<typename _Iterator>
inline void _Streambuf<_Tx>::assign(_Iterator _I1, _Iterator _I2)
{
	this->assign( 0, _I1, _I2 );
}


template<typename _Tx>
template<typename _Iterator>
inline void _Streambuf<_Tx>::assign(const __DX uint & _Offset, _Iterator _I1, _Iterator _I2)
{
	auto _MyIt = (this->begin( ) + _Offset);
	auto _MyEnd = (this->end( ));
	for ( ; _MyIt != _MyEnd && _I1 != _I2; ++_MyIt, ++_I1 )
		*_MyIt = *_I1;
}

template<typename _Tx>
template<typename _Iterator>
inline void _Streambuf<_Tx>::append(_Iterator _I1, _Iterator _I2)
{
	auto _Old = this->resize( _I2 - _I1 );
	this->assign( _Old, _I1, _I2 );
}

template<typename _Tx>
inline uint _Streambuf<_Tx>::resize(const __DX uint & _Length)
{
	_Base _Tmp = this->copy( );
	this->reserve( _Length );
	this->assign( _Tmp.begin( ), _Tmp.end( ) );
	return _Tmp.length( );
} 

template<typename _Tx>
inline void _Streambuf<_Tx>::clean()
{
	if ( _Length != bad && _Buf )
		delete[_Length] _Buf;
	_Buf = nullptr;
	_Length = bad;
}

template<typename _Tx>
inline __DX uint _Streambuf<_Tx>::length()
{
	return _Length;
}

template<typename _Tx>
inline bool _Streambuf<_Tx>::good()
{
	return _Length != bad;
}

template<typename _Tx>
inline _Streambuf<_Tx>::_Base _Streambuf<_Tx>::operator=(const _Base & _Other)
{
	this->reserve( _Other.length( ) );
	this->assign( _Other.begin( ), _Other.end( ) );
}

template<typename _Tx>
inline void _Streambuf<_Tx>::swap(_Base & _Other)
{
	std::swap( this->_Buf, _Other._Buf );
	std::swap( this->_Length, _Other._Length );
}

template<typename _Tx>
inline _Streambuf<_Tx>::_Base _Streambuf<_Tx>::copy() const
{
	return *this;
}

template<typename _Tx>
inline _Streambuf<_Tx>::_FwdIter _Streambuf<_Tx>::begin()
{
	return _Buf;
}

template<typename _Tx>
inline _Streambuf<_Tx>::_FwdIter _Streambuf<_Tx>::end()
{
	return _Buf + _Length;
}




end_IO