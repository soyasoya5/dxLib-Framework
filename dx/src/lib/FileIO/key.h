#pragma once
#include "lib.h"
#include "../string.h"

begin_FILEIO

class cipher_key
{
private:
	__LIB String _key;
public:
	cipher_key( );
	cipher_key( const __LIB String &_Key );
	
	__DX uint length( );
	__LIB String &string( );
};

end_FILEIO