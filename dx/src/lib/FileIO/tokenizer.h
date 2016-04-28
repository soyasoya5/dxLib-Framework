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
	::dx::lib::String message;
	::dx::lib::String formated_mesasge; // e.g [Error] Not found: 25 (where syntax: [type] message: line\n)
	uint line;

	TokenizerMessage( ) = default;
	
	///<summary>
	/// Construct this TokenizerMessage
	///</summary>
	TokenizerMessage( const Message_t &_Type, const ::dx::lib::String &_Msg, const ::dx::uint &_Line );

	///<summary>
	/// Convert '_Type' to a String.
	///</summary>
	static ::dx::lib::String TypeToString( const Message_t &_Type );
};

class Tokenizer
{
public:
	typedef std::vector<::dx::lib::FileIO::Token> vector;
	typedef vector::iterator iterator;

private:
	std::vector<::dx::lib::FileIO::TokenizerMessage> _msgs;
	vector _tokens;
	::dx::lib::String _filename;
	::dx::lib::String _filecontent;
	::dx::lib::Event<void( ::dx::lib::FileIO::TokenizerMessage )> _OnMessage;

	Tokenizer( );
public:
	///<summary>
	/// Tokenize the code contained in this Tokenizer.
	///</summary>
	bool Tokenize( );

	///<summary>
	/// The begin iterator of tokens.
	///</summary>
	::dx::lib::FileIO::Tokenizer::iterator begin( );

	///<summary>
	/// The end iterator of tokens.
	///</summary>
	::dx::lib::FileIO::Tokenizer::iterator end( );

	///<summary>
	/// Raise 'OnMessage' event.
	///</summary>
	bool SendMessage( const ::dx::lib::FileIO::TokenizerMessage& );

	///<summary>
	/// Return the code contents of this Tokenizer.
	///</summary>
	::dx::lib::String ContentsFile( );

	///<summary>
	/// Clear the tokens.
	///</summary>
	void Clear( );

	///<summary>
	/// Messages from this Tokenizer.
	///</summary>
	::dx::lib::Event<void( ::dx::lib::FileIO::TokenizerMessage )>& OnMessage( );
	
	///<summary>
	/// Create tokenizer from code.
	///</summary>
	static ::dx::lib::FileIO::Tokenizer* CreateFromHeader( const ::dx::lib::String &contents );

	///<summary>
	/// Create tokenizer from file.
	///</summary>
	static ::dx::lib::FileIO::Tokenizer* CreateFromFile( const ::dx::lib::String &file );
};


end_FILEIO