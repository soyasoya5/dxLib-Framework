#pragma once
#include "lib.h"
#include "../string.h"
#include "../Math/Vector2.h"
#include "../Math/Region.h"
#include "token.h"
#include "tokenizer.h"

begin_FILEIO

// Style modelling language??? not sure yet if thats the final name.

class InvalidSmlVector;
class InvalidSmlString;
class InvalidSmlInt;
class InvalidSmlRegion;
class SmlValue;
class SmlObject;
class SmlDocument;
class SmlGrammarCheck;
class SmlParser;
class SmlParserState;
class SmlSymbolTable;
class SmlResult;
using SmlIterator = Tokenizer::iterator;
enum SmlTypes;


enum SmlTypes
{
	SmlVector2,
	SmlString,
	SmlInt,
	SmlRegion,
	Unknown
};

class SmlValue
{
public:
	__LIB String as_string( );
	__MATH Vector2 as_vector( );
	__MATH Region as_region( );
	int as_integer( );

	void set_value( const __LIB String &_Value );
private:
	__LIB String _value;
};

class SmlObject
{
public:
	SmlObject( );
	SmlObject( const __FILEIO SmlTypes &_Type, const __LIB String &_Identifier, const __FILEIO SmlValue &_Value );

	__LIB String getIdentifier( ) const;
	void setIdentifier( const __LIB String &_Identifier );

	__FILEIO SmlTypes getType( ) const;
	void setType( const __FILEIO SmlTypes &_Type );

	__FILEIO SmlValue getValue( ) const;
	void setValue( const __FILEIO SmlValue &_Value );

private:
	__LIB String _identifier;
	__FILEIO SmlTypes _type;
	__FILEIO SmlValue _value;
};

class SmlDocument
{
private:
	SmlDocument( );
public:
	static SmlDocument *Create( const __LIB String &_Filename );
	static SmlDocument *Create( const __LIB String &_Name, const __LIB String &_Contents );

	void setContents( const __LIB String &_Contents );
	__LIB String getContents( );

	__LIB String getName( );
	void setName( const __LIB String &_Name );

private:
	__LIB String _name, _contents;
};

class SmlGrammarCheck
{
public:
	static SmlGrammarCheck *Create( SmlParser *_Parser );

	bool DoGrammarCheck( Event<void(SmlResult)>& _ErrorEvent );
private:
	SmlGrammarCheck( );
	SmlParser* _parser;
};

class SmlParserState
{
public:
	static SmlParserState *Create( const SmlIterator &_Begin, const SmlIterator &_End );

	SmlIterator& begin( );
	SmlIterator& end( );

private:
	SmlParserState( );
	SmlIterator _beg, _end;
};

class SmlParser
{
public:
	static SmlParser *Create( SmlDocument *_Document );

	SmlParserState* CreateState( );
	SmlResult ParseSml( SmlSymbolTable *_OutTable );
	SmlDocument *Document( );
private:
	SmlParser( );
	SmlDocument *_document;
	Tokenizer* _tokenizer;
};

class SmlResult
{
public:
	SmlResult( const __LIB String &_Msg, const __FILEIO Token &_Token, const int &_Line );
	operator bool ( );

	__LIB String Message( );
	__FILEIO Token Token( );
	int Line( );
private:
	__LIB String _msg;
	__FILEIO Token _token;
	int _line;
};



#pragma region EXCEPTIONS

class InvalidSmlVector : std::exception
{
public:
	InvalidSmlVector( const __LIB String &_Message )
		: _msg( _Message )
	{
	}

	const char* what( ) const override
	{
		return _msg.c_str( );
	}

private:
	const __LIB String _msg;
};

class InvalidSmlString : std::exception
{
public:
	InvalidSmlString( const __LIB String &_Message )
		: _msg( _Message )
	{
	}

	const char* what( ) const override
	{
		return _msg.c_str( );
	}

private:
	const __LIB String _msg;
};

class InvalidSmlInt : std::exception
{
public:
	InvalidSmlInt( const __LIB String &_Message )
		: _msg( _Message )
	{
	}

	const char* what( ) const override
	{
		return _msg.c_str( );
	}

private:
	const __LIB String _msg;
};

class InvalidSmlRegion : std::exception
{
public:
	InvalidSmlRegion( const __LIB String &_Message )
		: _msg( _Message )
	{
	}

	const char* what( ) const override
	{
		return _msg.c_str( );
	}

private:
	const __LIB String _msg;
};

#pragma endregion


end_FILEIO
