#include "sml.h"

begin_FILEIO

__LIB String SmlValue::as_string()
{
	return _value;
}

__MATH Vector2 SmlValue::as_vector()
{
	auto vec = _value.split( ',' );
	if ( vec.empty( ) || vec.size( ) < 2 )
		throw InvalidSmlVector( "Invalid sml vector: " + _value );
	return __MATH Vector2{ vec[0].to<float>( ), vec[1].to<float>( ) };
}

__MATH Region SmlValue::as_region()
{
	auto vec = _value.split( ',' );
	if ( vec.empty( ) || vec.size( ) < 4 )
		throw InvalidSmlRegion( "Invalid Sml region: " + _value );
	return __MATH Region{ { vec[0].to<float>( ), vec[1].to<float>( ) },
						  { vec[2].to<float>( ), vec[3].to<float>( ) } };
}

int SmlValue::as_integer()
{
	return _value.to<int>( );
}

void SmlValue::set_value(const __LIB String & _Value)
{
	this->_value = _Value;
}

SmlObject::SmlObject()
	: _identifier( ), _type( Unknown ), _value( )
{
}

SmlObject::SmlObject(const __FILEIO SmlTypes & _Type, const __LIB String & _Identifier, const __FILEIO SmlValue & _Value)
	: _type( _Type ), _identifier( _Identifier ), _value( _Value )
{
}

__LIB String SmlObject::getIdentifier() const
{
	return _identifier;;
}

void SmlObject::setIdentifier(const __LIB String & _New)
{
	_identifier = _New;
}

__FILEIO SmlTypes SmlObject::getType() const
{
	return _type;
}

void SmlObject::setType(const __FILEIO SmlTypes & _Type)
{
	_type = _Type;
}

__FILEIO SmlValue SmlObject::getValue() const
{
	return _value;
}

void SmlObject::setValue(const __FILEIO SmlValue & _Value)
{
	_value = _Value;
}


SmlDocument::SmlDocument()
	: _name( ), _contents( )
{
}

SmlDocument * SmlDocument::Create(const __LIB String & _Filename)
{
	std::ifstream f( _Filename.c_str( ) );
	if ( !f.good( ) )
		return nullptr;

	auto doc = new SmlDocument( );
	f.seekg( 0, std::ios::end );
	doc->_contents.reserve( f.tellg( ) );
	f.seekg( 0, std::ios::beg );
	doc->_contents.assign( std::istreambuf_iterator<char>( f ), 
						   std::istreambuf_iterator<char>( ) );

	doc->_name = _Filename;
	return doc;
}

SmlDocument * SmlDocument::Create(const __LIB String & _Name, const __LIB String & _Contents)
{
	auto doc = new SmlDocument( );
	doc->_name = _Name;
	doc->_contents = _Contents;
	return doc;
}

void SmlDocument::setContents(const __LIB String & _Contents)
{
	_contents = _Contents;
}

__LIB String SmlDocument::getContents()
{
	return _contents;
}

__LIB String SmlDocument::getName()
{
	return _name;
}

void SmlDocument::setName(const __LIB String & _Name)
{
	_name = _Name;
}

SmlGrammarCheck::SmlGrammarCheck()
{
}

SmlGrammarCheck * SmlGrammarCheck::Create(SmlParser * _Parser)
{
	auto ptr = new SmlGrammarCheck( );
	ptr->_parser = _Parser;
	return ptr;
}

bool SmlGrammarCheck::DoGrammarCheck(Event<void(SmlResult)>& _ErrorEvent)
{
	auto error = [&_ErrorEvent]( const SmlResult &error )mutable->bool { _ErrorEvent.Invoke( error ); return false; };
	auto state = std::shared_ptr<SmlParserState>( _parser->CreateState( ) );

	for ( auto it = state->begin( ), end = state->end( ); it < end; )
	{
		// Variable
		if ( *(it++) == "var" )
		{
			if ( *(it) != token_identifier )
				return error( SmlResult( "Expected identifier after 'var' keyword.", *it, it->getLine( ) ) );

			if ( *(++it) == token_semicolon ) 
				{ ++it; continue; }

			if ( *it != token_assign )
				return error( SmlResult( "Expected eos or assignment operator after identifier.", *it, it->getLine( ) ) );

			while ( true )
			{
				if ( *(++it) == ";" )
					{ ++it; break; }
				else if ( *it == "{" )
				{
					while( *it != "}" )
						++it;
				}
				else if ( *it != token_identifier 
						  && *it != token_decimal 
						  && *it != token_hexadecimal 
						  && *it != token_string 
						  && *it != token_plus
						  && *it != token_minus 
						  && *it != token_indirect 
						  && *it != token_divides )
						return error( SmlResult( "Invalid expression.", *it, it->getLine( ) ) );
			}
			++it;
			continue;
		} 
		else if ( *it != ";" && *it != "endl" && *it != "eof" )
			return error( SmlResult( "Unknown error, the grammar checker is not very advanced and can only handle a var statement.", *it, it->getLine( ) ) );
	}
	return true;
}

SmlParserState * SmlParserState::Create(const SmlIterator & _Begin, const SmlIterator & _End)
{
	auto ptr = new SmlParserState( );
	ptr->_beg = _Begin;
	ptr->_end = _End;
	return ptr;
}

SmlIterator & SmlParserState::begin()
{
	return _beg;
}

SmlIterator & SmlParserState::end()
{
	return _end;
}

SmlParserState::SmlParserState()
{
}


SmlParser * SmlParser::Create(SmlDocument * _Document)
{
	auto ptr = new SmlParser( );
	ptr->_document = _Document;
	ptr->_tokenizer = Tokenizer::CreateFromHeader( _Document->getContents( ) );
	ptr->_tokenizer->Tokenize( );
	return ptr;
}

SmlParserState * SmlParser::CreateState()
{
	return SmlParserState::Create( _tokenizer->begin( ), _tokenizer->end( ) );
}

SmlResult SmlParser::ParseSml(SmlSymbolTable * _OutTable)
{
	
}

SmlDocument * SmlParser::Document()
{
	return _document;
}

SmlParser::SmlParser()
{
}

SmlResult::SmlResult(const __LIB String & _Msg, const __FILEIO Token & _Token, const int & _Line)
	: _msg( _Msg ), _token( _Token ), _line( _Line )
 {
}

SmlResult::operator bool()
{
	return _msg.empty( );
}

__LIB String SmlResult::Message()
{
	return _msg;
}

__FILEIO Token SmlResult::Token()
{
	return _token;
}

int SmlResult::Line()
{
	return _line;
}


end_FILEIO


