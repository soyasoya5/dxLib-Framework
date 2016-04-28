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

	///<summary>
	/// Empty constructor
	///</summary>
	TCPMessage( );

	///<summary>
	/// Construct this message with a buffer and the length of the buffer.
	///</summary>
	TCPMessage( const char *_Buffer, const uint &_Bufsz );

	///<summary>
	/// Return this message as a string.
	///</summary>
	String getString( );
	
	///<summary>
	/// Return this message as T.
	///</summary>
	template<typename T>
	T getT( )
	{
		if ( _bufsz < sizeof(T) )
			return T( );
		return *(T*)_buffer;
	}

	///<summary>
	/// Wether or not this message is good.
	///</summary>
	operator bool( );

	///<summary>
	/// Returns the internal message buffer.
	///</summary>
	char* buffer( ) const;

	///</summary>
	/// Returns the length of the internal message buffer.
	///<summary>
	uint length( ) const;

private:
	char* _buffer;
	uint _bufsz;
};


class TCPSocket
{
	TCPSocketImpl* _impl;
public:
	///<summary>
	/// Default constructor
	///</summary>
	TCPSocket( );

	~TCPSocket( );

	///<summary>
	/// Connect the socket to an ip with port.
	///</summary>
	TCPResult connect( const ::dx::lib::String &_Ip, const ::dx::uint &_Port );

	///<summary>
	/// Shutdown the connection.
	///</summary>
	TCPResult close( );

	///<summary>
	/// Returns true if this connection is connected to anything, else false.
	///</summary>
	bool connected( );

	///<summary>
	/// Returns true if this connection is not connected to anything.
	///</summary>
	bool closed( );

	///<summary>
	/// Receive the next message in the message queue.
	///</summary>
	TCPMessage recv( );

	///<summary>
	/// Send a message.
	///</summary>
	void send( const ::dx::lib::String &_Message );

	///<summary>
	/// Send a message.
	///</summary>
	void send( const TCPMessage &_Message );
	
};

end_NET