#include "TCP.h"
#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "mswsock.lib")
#include "../../api"
#include <queue>

begin_NET

class TCPSocketImpl
{
private:
	static int _refs;
	static ::WSADATA _data;
	SOCKET _socket;
	::dx::AsyncKeeper _Mtx;
	struct ::addrinfo *_result, _hints;
	std::queue<TCPMessage> _msgs;
	std::thread _recvThread;

public:
	TCPSocketImpl( );
	~TCPSocketImpl( );

	TCPResult create( const ::dx::String &_Ip, const ::dx::uint &_Port );
	TCPResult destroy( );
	bool isConnected( );
	TCPResult Setup( );
	TCPResult Cleanup( );
	TCPResult socket( const ::dx::String &_Ip, const ::dx::uint &_Port );
	TCPResult connect( );
	TCPMessage front( );
	void send( char *_Data, const ::dx::uint &_Length );
	void push( const TCPMessage &_Message );
	void recvThread( );
};


TCPSocket::TCPSocket()
{
	_impl = new TCPSocketImpl( );
}

TCPSocket::~TCPSocket()
{
	delete _impl;
}

TCPResult TCPSocket::connect(const ::dx::lib::String & _Ip, const ::dx::uint & _Port)
{
	return _impl->create( _Ip, _Port );
}

TCPResult TCPSocket::close()
{
	return _impl->destroy( );
}

bool TCPSocket::connected()
{
	return _impl->isConnected( );
}

bool TCPSocket::closed()
{
	return !_impl->isConnected( );
}

TCPMessage TCPSocket::recv()
{
	return _impl->front( );
}

void TCPSocket::send(const ::dx::lib::String & _Message)
{
	_impl->send( (char*)_Message.c_str( ), _Message.length( ) );
}

void TCPSocket::send(const TCPMessage & _Message)
{
	_impl->send( _Message.buffer( ), _Message.length( ) );
}



int TCPSocketImpl::_refs = 0;
::WSADATA TCPSocketImpl::_data;

TCPSocketImpl::TCPSocketImpl()
	: _socket( INVALID_SOCKET )
{
	_recvThread = std::thread{ &TCPSocketImpl::recvThread, this };
}

TCPSocketImpl::~TCPSocketImpl()
{
	TerminateThread( _recvThread.native_handle( ), 0 );
	this->destroy( );
}

TCPResult TCPSocketImpl::create(const::dx::String & _Ip, const::dx::uint & _Port)
{
	if ( !_refs )
		Setup( );
	TCPResult result;
	if ( !(result = this->socket( _Ip, _Port )) )
		return result;

	if ( !(result = this->connect( )) )
		return result;

	++_refs;
	return result;
}

TCPResult TCPSocketImpl::destroy()
{
	if ( !isConnected( ) )
		return TCPResult( ERRC_NOT_CREATED );
	--_refs;
	if ( !_refs )
		Cleanup( );

	auto res = ::shutdown( _socket, SD_SEND );
	if ( res != 0 )
		return TCPResult( res );
	return TCPResult( ::closesocket( _socket ) );
}

bool TCPSocketImpl::isConnected()
{
	return _socket != INVALID_SOCKET;
}

TCPResult TCPSocketImpl::Setup()
{
	return ::WSAStartup( MAKEWORD(2, 2),  &_data );
}

TCPResult TCPSocketImpl::Cleanup()
{
	return ::WSACleanup( );
}

TCPResult TCPSocketImpl::socket(const ::dx::String &_Ip, const ::dx::uint &_Port)
{
	memset( &_hints, 0, sizeof(::addrinfo) );
	_hints.ai_family = AF_UNSPEC;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_protocol = IPPROTO_TCP;

	auto res = ::getaddrinfo( _Ip.c_str( ), ::dx::lib::to_string( _Port ).c_str( ), &_hints, &_result );
	if ( res != 0 ) // Failed
		return TCPResult( res );

	_socket = ::socket( _result->ai_family, _result->ai_socktype, _result->ai_protocol );
	if ( !isConnected( ) )
	{
		::freeaddrinfo( _result );
		return TCPResult( ERRC_SOCKET_FAILED );
	}

	return TCPResult();
}

TCPResult TCPSocketImpl::connect()
{
	auto res = ::connect( _socket, _result->ai_addr, _result->ai_addrlen );
	freeaddrinfo( _result );
	if ( res != 0 )
	{
		::closesocket( _socket );
		_socket = INVALID_SOCKET;
		return TCPResult( res );
	}

	return TCPResult();
}

TCPMessage TCPSocketImpl::front()
{
	AsyncGuard guard{ _Mtx };
	if ( _msgs.empty( ) )
		return TCPMessage( );

	auto _Front = _msgs.front( );
	_msgs.pop( );
	return _Front;
}

void TCPSocketImpl::send(char * _Data, const::dx::uint & _Length)
{
	// Send data
	::send( _socket, _Data, _Length, 0 );
}

void TCPSocketImpl::push(const TCPMessage & _Message)
{
	AsyncGuard guard{ _Mtx };
	this->_msgs.push( _Message );
}

void TCPSocketImpl::recvThread()
{
	while( true )
	{
		if ( !isConnected( ) ) {
			std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
			continue;
		}

		uint len;
		auto read = ::recv( _socket, reinterpret_cast<char*>( &len ), sizeof(uint), 0 );

		if ( read <= 0 )
		{
			this->destroy( );
			break;
		}

		auto buf = std::make_unique<char*>( new char[len] );
		
		TCPMessage msg{ *buf, len };
		this->push( msg );
	}
}


TCPMessage::TCPMessage()
	: _buffer( nullptr ), _bufsz( 0 )
{
}

TCPMessage::TCPMessage(const char * _Buffer, const uint & _Bufsz)
{
	_buffer = new char[_Bufsz];
	memcpy( _buffer, _Buffer, _Bufsz );
	this->_bufsz = _Bufsz;
}

String TCPMessage::getString()
{
	if ( *this )
		return String(_buffer, _bufsz);
	return "";
}

TCPMessage::operator bool()
{
	return _buffer != nullptr;
}

char * TCPMessage::buffer() const
{
	return _buffer;
}

uint TCPMessage::length() const
{
	return _bufsz;
}

end_NET


