#pragma once
#include "lib.h"
#include <memory>
#include "../string.h"

begin_NET

enum ERRC
{
	ERRC_NOT_CREATED = 67,
	ERRC_SOCKET_FAILED
};

class TCPSocketImpl;

class TCPResult
{
public:
	TCPResult( ) : _errc( 0 ) { }
	TCPResult( const int &_Errc ) : _errc( _Errc ) {}
	operator bool( ) { return _errc == 0; }
	void set( const int &_Errc ) { _errc = _Errc; }
	int get( ) { return _errc; };
private:
	int _errc;
};

class TCPMessage
{
public:
	TCPMessage( );
	TCPMessage( const char *_Buffer, const uint &_Bufsz );

	String getString( );
	template<typename T>
	T getT( )
	{
		if ( _bufsz < sizeof(T) )
			return T( );
		return *(T*)_buffer;
	}

	operator bool( );

	char* buffer( ) const;
	uint length( ) const;

private:
	char* _buffer;
	uint _bufsz;
};


// A client socket only (Not server)
class TCPSocket
{
	TCPSocketImpl* _impl;
public:
	TCPSocket( );
	~TCPSocket( );

	TCPResult connect( const __LIB String &_Ip, const __DX uint &_Port );
	TCPResult close( );
	bool connected( );
	bool closed( );
	TCPMessage recv( );
	void send( const __LIB String &_Message );
	void send( const TCPMessage &_Message );
	
};

end_NET