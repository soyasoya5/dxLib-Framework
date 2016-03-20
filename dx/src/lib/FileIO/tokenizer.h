#pragma once
#include "lib.h"
#include "../string.h"
#include "../event.h"

begin_FILEIO

class Token;

struct TokenizerMessage
{
	enum Message_t
	{
		Error,
		Warning,
		Info,
	};
	Message_t type;
	__LIB String message;
	__LIB String formated_mesasge; // e.g [Error] Not found: 25 (where syntax: [type] message: line\n)
	uint line;

	TokenizerMessage( ) = default;
	TokenizerMessage( const Message_t &type, const __LIB String &msg, const __DX uint &line );

	static __LIB String TypeToString( const Message_t &type );
};

class Tokenizer
{
public:
	typedef std::vector<__FILEIO Token> vector;
	typedef vector::iterator iterator;

private:
	std::vector<__FILEIO TokenizerMessage> _msgs;
	vector _tokens;
	__LIB String _filename;
	__LIB String _filecontent;
	__LIB Event<void( __FILEIO TokenizerMessage )> _OnMessage;

	Tokenizer( );
public:
	bool Tokenize( );

	__FILEIO Tokenizer::iterator begin( );
	__FILEIO Tokenizer::iterator end( );
	bool SendMessage( const __FILEIO TokenizerMessage& );
	__LIB String ContentsFile( );

	void Clear( );

	__LIB Event<void( __FILEIO TokenizerMessage )>& OnMessage( );
	
	static __FILEIO Tokenizer* CreateFromHeader( const __LIB String &contents );
	static __FILEIO Tokenizer* CreateFromFile( const __LIB String &file );
};


end_FILEIO