#include "key.h"

begin_FILEIO

cipher_key::cipher_key(const __LIB String & _Key)
	: _key( _Key )
{
}

cipher_key::cipher_key()
	: _key( )
{
}

__DX uint cipher_key::length()
{
	return _key.length( );
}

__LIB String &cipher_key::string()
{
	return _key;
}

end_FILEIO


