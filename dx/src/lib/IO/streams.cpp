#include "streams.h"

begin_IO

stream::operator bool()
{
	return _Buffer.good( ) && _Index < _Buffer.length( );
}

stream::Streambuf::_FwdIter stream::begin()
{
	return _Buffer.begin( );
}

stream::Streambuf::_FwdIter stream::current()
{
	return _Buffer.begin( ) + _Index;
}

stream::Streambuf::_FwdIter stream::end()
{
	return _Buffer.end( );
}

stream & stream::operator=(const stream & _Lhs)
{
	this->_Buffer = _Lhs._Buffer;
	this->_Index = _Lhs._Index;
	return *this;
}

stream &operator<<( stream &_Lhs, stream &_Rhs )
{
	_Lhs.append( _Rhs.current( ), _Rhs.end( ) );
}

stream &operator>>( stream &_Lhs, stream &_Rhs )
{
	_Rhs = _Lhs;
}

end_IO

