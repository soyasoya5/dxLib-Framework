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
	
	///<summary>
	/// Construct this TokenizerMessage
	///</summary>
	TokenizerMessage( const Message_t &_Type, const __LIB String &_Msg, const __DX uint &_Line );

	///<summary>
	/// Convert '_Type' to a String.
	///</summary>
	static __LIB String TypeToString( const Message_t &_Type );
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
	///<summary>
	/// Tokenize the code contained in this Tokenizer.
	///</summary>
	bool Tokenize( );

	///<summary>
	/// The begin iterator of tokens.
	///</summary>
	__FILEIO Tokenizer::iterator begin( );

	///<summary>
	/// The end iterator of tokens.
	///</summary>
	__FILEIO Tokenizer::iterator end( );

	///<summary>
	/// Raise 'OnMessage' event.
	///</summary>
	bool SendMessage( const __FILEIO TokenizerMessage& );

	///<summary>
	/// Return the code contents of this Tokenizer.
	///</summary>
	__LIB String ContentsFile( );

	///<summary>
	/// Clear the tokens.
	///</summary>
	void Clear( );

	///<summary>
	/// Messages from this Tokenizer.
	///</summary>
	__LIB Event<void( __FILEIO TokenizerMessage )>& OnMessage( );
	
	///<summary>
	/// Create tokenizer from code.
	///</summary>
	static __FILEIO Tokenizer* CreateFromHeader( const __LIB String &contents );

	///<summary>
	/// Create tokenizer from file.
	///</summary>
	static __FILEIO Tokenizer* CreateFromFile( const __LIB String &file );
};


end_FILEIO