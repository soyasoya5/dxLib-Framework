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
	: _identifier( ), _type( SmlUnknown ), _value( )
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
	auto state = std::unique_ptr<SmlParserState>( _parser->CreateState( ) );

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
	auto error = [this, &_OutTable]( const SmlResult &result ) { OnError( ).Invoke( result ); _OutTable->clear( ); return result; };


	// Check grammar
	auto grammar = std::unique_ptr<SmlGrammarCheck>( SmlGrammarCheck::Create( this ) );
	auto res = grammar->DoGrammarCheck( _OnError );
	if ( !res )
		return SmlResult( "Grammar check failed (See OnError event)", { }, 0 );

	// Clear table
	_OutTable->clear( );

	// Create state
	auto state = std::unique_ptr<SmlParserState>( this->CreateState( ) );

	auto it = state->begin( ), end = state->end( );
	while( it < end )
	{
		if ( *(it++) == "var" )
		{
			SmlObject object;
			if ( *it != token_identifier )
				return error( { "Expected identifier after var keyword", *it, (int)it->getLine( ) } );
			object.setIdentifier( it->getIdentifier( ) );

			// No assign
			if ( *(++it) == token_semicolon )
			{
				if ( _OutTable->getObj( object.getIdentifier( ) ) )
					return error( { object.getIdentifier( ) + " already exists in this context.", *it, (int)it->getLine( ) } );
				_OutTable->add( object );
				++it; // eat next
				continue;
			}
			// Assign
			else if ( *it == "=" )
			{
				// var IDENTIFIER '=' expr + expr RECURSIVE(15) ';'
				if ( this->is_expression( it, end ) )
				{
					try {
						if ( this->is_valid_expression( it, end ) )
						{
							auto result = do_assignment_expr( _OutTable, &object, it, end );
							if ( !result )
								return error( result );
							_OutTable->add(object);
							continue;
						}
						else
							throw InvalidExpression( "Invalid expression" );
					} 
					catch( InvalidExpression e )
					{
						return error( { e.what( ), *it, (int)it->getLine( ) } );
					}
				}

				else
				{
					auto result = do_assignment( _OutTable, &object, it, end );
					if ( !result )
						return error( result );
					_OutTable->add( object );
					continue;
				}
			} 				
			return error( { "Expected semicolon or assignment operation in declaration of var " + object.getIdentifier( ), *it, (int)it->getLine( ) } );
		}
		
	}
	
	return SmlResult( "", { }, 0 );
}

SmlDocument * SmlParser::Document()
{
	return _document;
}

__LIB Event<void(SmlResult)>& SmlParser::OnError()
{
	return _OnError;
}

// Does not check if valid expression
bool SmlParser::is_expression(SmlIterator it, const SmlIterator & end) const
{
	if ( *it == token_string )
	{ 
		if ( *(++it) == token_plus )
			return true;
	}
	else if ( *it == token_decimal || *it == token_hexadecimal || *it == token_identifier )
	{
		if ( *(++it) == token_plus || *it == token_minus || *it == token_indirect || *it == token_divides )
			return true;
	}
	return false;
}

bool SmlParser::is_one_operator(const SmlIterator & it) const
{
	return *it == token_plus || *it == token_minus || *it == token_indirect || *it == token_divides;
}

bool SmlParser::find_expr_type(SmlIterator it, const SmlIterator & end) const
{
	// We know for sure it isn't a string expr if it uses any of these operators
	if (  *(++it) == token_minus || *it == token_indirect || *it == token_divides )
		return false;

	if ( *it == token_plus && *(it + 1) == token_string )
		return true;
	else if ( *(it + 1) == token_identifier )
		return find_expr_type( it, end );
	else if ( *(it + 1) == token_decimal || *(it + 1) == token_hexadecimal )
		return false;

	// unkown result, unfortunately might mean we got a syntax error.
	return false;
}

SmlResult SmlParser::do_assignment_expr( SmlSymbolTable *_Table, SmlObject * _Object, SmlIterator & it, const SmlIterator & end)
{
	auto valid_symbol = []( SmlObject *lhs, SmlObject* rhs, SmlIterator it )->SmlResult
	{
		auto type = lhs->getType( );
		if ( !rhs )
			return SmlResult( "Symbol not found " + it->getIdentifier( ), *it, it->getLine( ) );
		
		auto symType = rhs->getType( );
		if ( symType == SmlUnknown )
			return SmlResult( "Symbol " + rhs->getIdentifier( ) + " does not have a type.", *it, it->getLine( ) );
		
		if ( type == SmlUnknown )
			type = symType;

		if ( type != symType )
			return SmlResult( "No operation found for " + lhs->getIdentifier( ) + " and " + lhs->getIdentifier( ) + ".", *it, it->getLine( ) );

		return SmlResult( "", {}, 0 );
	};

	if ( *it != "=" )
		return SmlResult( "Invalid SmlIterator send to SmlParser::do_assignment_expr, this is a compiler error", *it, it->getLine( ) );
	
	{
		auto type = _Object->getType( );
		if ( *(++it) == token_string && (type != SmlString || type != SmlUnknown) )
			return SmlResult( "No operation where " + _Object->getIdentifier( ) + " can be assigned to string is possible.", *it, it->getLine( ) );
		else if ( (*(it) == token_hexadecimal || *it == token_decimal) && (type != SmlInt || type != SmlUnknown) )
			return SmlResult( "No operation where " + _Object->getIdentifier( ) + " can be assigned to int is possible.", *it, it->getLine( ) );
	}

	SmlValue value;
	--it; // Decrement token ptr
	while ( *it != token_semicolon && it < end )
	{
		if ( *(++it) == token_identifier )
		{
			auto lhs = _Table->getObj( it->getIdentifier( ) );
			
			auto valid = valid_symbol( _Object, lhs, it );
			if ( !valid )
				return valid;

			auto type = _Object->getType( );
			if ( type == SmlString )
			{
				if ( *(++it) != token_plus )
					return SmlResult( "Invalid operator for type SmlString", *it, it->getLine( ) );

				if ( *(++it) != token_string && *it != token_identifier )
					return SmlResult( "A string can only be concatinated with another string or variable of type string", *it, it->getLine( ) );

				SmlValue rhs;
				if ( *it == token_identifier )
				{
					auto sym = _Table->getObj( it->getIdentifier( ) );
					auto valid = valid_symbol( _Object, sym, it );
					if ( !valid )
						return valid;
					rhs = sym->getValue( );
				}
				else
					rhs.set_value( it->getIdentifier( ) );

				value.set_value( value.as_string( ) + rhs.as_string( ) );
			}
			else if ( type == SmlInt )
			{
				if ( !is_one_operator( ++it ) )
					return SmlResult( "Invalid operator for type SmlInt", *it, it->getLine( ) );
				auto op = it->getIdentifier( );

				if ( *(++it) != token_identifier && *it != token_decimal && *it != token_hexadecimal )
					return SmlResult( "Invalid RHS element in integral expression", *it, it->getLine( ) );

				SmlValue rhs;
				if ( *it == token_identifier )
				{
					auto sym = _Table->getObj( it->getIdentifier( ) );
					auto valid = valid_symbol( _Object, sym, it );
					if ( !valid )
						return valid;
					rhs = sym->getValue( );
				}
				else
					rhs.set_value( it->getIdentifier( ) );

				if ( op == "+" )
					value.set_value( to_string( value.as_integer( ) + rhs.as_integer( ) ) );
				else if ( op == "-" )
					value.set_value( to_string( value.as_integer( ) - rhs.as_integer( ) ) );
				else if ( op == "*" )
					value.set_value( to_string( value.as_integer( ) * rhs.as_integer( ) ) );
				else
					value.set_value( to_string( value.as_integer( ) / rhs.as_integer( ) ) );
			}
		}
		else if ( *it == token_string )
		{
			
		}


	}

	_Object->setValue( value );
	return SmlResult( "", { }, 0 );
}

SmlResult SmlParser::do_assignment(SmlSymbolTable * _Table, SmlObject * _Object, SmlIterator & it, const SmlIterator & end)
{
	return SmlResult( "", { }, 0 );
}

bool SmlParser::is_valid_expression_rec(SmlIterator it, const SmlIterator & end, const bool & is_str, int count) const
{
	if ( count >= 15 )
		throw InvalidExpression( "One single expression can only contain 15 sub expressions" );

	if ( is_str )
	{
		if ( *(++it) == token_semicolon )
			return true;
		else if ( *it != token_plus )
			return false;

		if ( *(++it) == token_string || *it == token_identifier )
			return is_valid_expression_rec( it, end, true, ++count );
	}
	else
	{
		if ( *(++it) == token_semicolon )
			return true;
		else if ( !is_one_operator( it ) )
			return false;

		if ( *(++it) == token_decimal || *it == token_hexadecimal || *it == token_identifier )
			return is_valid_expression_rec( it, end, true, ++count );
	}

	return false;
}

bool SmlParser::is_valid_expression(SmlIterator it, const SmlIterator & end) const
{
	if ( *it == token_string )
	{ 
		if ( *(++it) == token_plus )
		{
			if ( *(++it) == token_string || *it == token_identifier )
				return is_valid_expression_rec( it, end, true, 0 );
			else
				return false;
		}
	}
	else if ( *it == token_identifier )
	{
		// Is + - * or /
		if ( is_one_operator( ++it ) )
		{
			if ( *(++it) == token_identifier ) // Unknown type, we could run a check on existance check on identifier but nah
				return is_valid_expression_rec( it, end, find_expr_type( it, end ), 0 );
			else if ( *it == token_string ) // Known type, run recursive function
				return is_valid_expression_rec( it, end, true, 0 );
			else if ( *it == token_decimal || *it == token_hexadecimal ) // Known type, run recursive function
				return is_valid_expression_rec( it, end, false, 0 );
		}
		else
			return false;
	}
	return false;
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


SmlSymbolTable * SmlSymbolTable::Create()
{
	auto ptr = new SmlSymbolTable( );
	return ptr;
}

SmlObject * SmlSymbolTable::getObj(const __LIB String & _Name)
{
	for ( auto &obj : _objects )
	{
		if ( obj.getIdentifier( ) == _Name )
			return &obj;
	}
	return nullptr;
}

void SmlSymbolTable::add(const SmlObject & _Object)
{
	AsyncGuard guard{ _kpr };
	_objects.push_back( _Object );
}

void SmlSymbolTable::clear()
{
	AsyncGuard guard{ _kpr };
	_objects.clear( );
}


end_FILEIO


