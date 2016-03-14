#pragma once
#include "lib.h"
#include "key.h"
#include "buf.h"

begin_FILEIO

	
class Encrypter
{
private:
	__FILEIO cipher_key _key;
public:
	Encrypter( ) = default;
	Encrypter( const __FILEIO cipher_key &_Key );
	

	__FILEIO Buffer<__DX byte> encrypt( const __LIB String &_Sequence );
	__FILEIO Buffer<__DX byte> encrypt( const __FILEIO Buffer<__DX byte> &_Bytes );

	void setCipher( const __FILEIO cipher_key &_Key );
};



end_FILEIO