#include "tokenizer.h"

using namespace ::dx;
using namespace ::dx::lib;
using namespace ::dx::lib::FileIO;

Tokenizer::Tokenizer(File file)
	: file_( std::move( file ) ), tokens_( )
{
}

void Tokenizer::tokenize()
{
	if ( !file_.loaded )
	{
		file_.contents.clear( );
		file_.contents.append( std::istreambuf_iterator<char>( std::ifstream( file_.name ) ), std::istreambuf_iterator<char>( ) );
	}

	tokens_.clear( );
	line_ = 1;
	auto it = file_.contents.begin( ), end = file_.contents.end( );
	while( good( it, end ) )
	{
		if ( *it == '/' && *(it + 1) == '/' )
		{
			while( good( it, end ) && *it != '\n' )
				++it;
			line_++;
			++it;
			continue;
		}

		if ( *it == '/' && *(it + 1) == '*' )
		{
			while( good( it, end ) )
			{
				if ( *it == '*' && *(it + 1) == '/' )
				{ ++it, ++it; break; }
				
				++it;
			}
			continue;
		}

		// Advance line and it
		if ( good( it, end ) && *it == '\n' )
		{ ++it, ++line_; continue; }

		// Eat commets
		if ( good( it, end ) && ::isspace( *it ) )
		{ ++it; continue;  }

		// Is alpha
		if ( !good( it, end ) )
			break;
		else if ( ::isalpha( *it ) || *it == '_' ) // Identifiers can only start with an alphabetic or '_' character.
			tokens_.push_back( std::move( get_identifier( it, end ) ) );
		else if ( *it == '"' ) // String ""
			tokens_.push_back( std::move( get_literal_string( it, end ) ) );
		else if ( *it == '0' && *(it + 1) == 'x' )
			tokens_.push_back( std::move( get_literal_hexadecimal( it, end ) ) );
		else if ( ::isdigit( *it ) )
			tokens_.push_back( std::move( get_literal_decimal( it, end ) ) );
		else
			tokens_.push_back( std::move( get_operation( it, end ) ) );
	}
}

void Tokenizer::setFile(File file)
{
	this->file_ = std::move( file );
}

std::vector<Token>::const_iterator Tokenizer::begin() const
{
	return tokens_.begin( );
}

std::vector<Token>::const_iterator Tokenizer::end() const
{
	return tokens_.end( );
}

Token Tokenizer::get_identifier(std::string::iterator & it, const std::string::iterator & end)
{
	Token token;
	while( good( it, end ) && (::isalnum( *it ) || *it == '_') )
		token.value.push_back( *(it++) );

	token.kw = get_keyword( token.value );
	if ( token.kw != kw_unknown )
		token.type = token_keyword;
	else
		token.type = token_identifier;

	token.line = line_;
	return token;
}

Token Tokenizer::get_literal_string(std::string::iterator & it, const std::string::iterator & end)
{
	++it; // Eat '"'
	Token token;
	while( good( it, end ) && *it != '"' )
		token.value.push_back( *(it++) );

	++it; // eat '"'
	token.kw = kw_unknown;
	token.type = token_string_literal;
	token.line = line_;
	return token;
}

Token Tokenizer::get_literal_decimal(std::string::iterator & it, const std::string::iterator & end)
{
	Token token;
	while( good( it, end ) && ::isdigit( *it ) )
		token.value.push_back( *(it++) );

	token.kw = kw_unknown;
	token.type = token_numerical;
	token.line = line_;
	return token;
}

Token Tokenizer::get_literal_hexadecimal(std::string::iterator & it, const std::string::iterator & end)
{
	++it, ++it; // Eat '0x'
	Token token;
	while( good( it, end ) && ::isxdigit( *it ) )
		token.value.push_back( *(it++) );

	token.kw = kw_unknown;
	token.type = token_numerical;
	token.value = to_string( atoi( token.value.c_str( ) ) );
	token.line = line_;
	return token;
}

Token Tokenizer::get_operation(std::string::iterator & it, const std::string::iterator & end)
{
	switch ( *(it++) )
	{
	case '=':
		if ( *(it++) == '=' )
			return Token( token_operation, op_equal_to, line_, "==" );
		--it;
		return Token( token_operation, op_assign, line_, "=" );
	case ':':
		if ( *(it++) == ':' )
			return Token( token_operation, op_scope_resolution, line_, "::" );
		--it;
		return Token( token_operation, op_colon, line_, ":" );
	case '+':
		if ( *(it++) == '+' )
			return Token( token_operation, op_postfix_increment, line_, "++" );
		else if ( *(it-1) == '=' )
			return Token( token_operation, op_assign_add, line_, "+=" );
		--it;
		return Token( token_operation, op_unary_add, line_, "+" );
	case '-':
		if ( *(it++) == '-' )
			return Token( token_operation, op_postfix_decrement, line_, "--" );
		else if ( *(it - 1) == '=' )
			return Token( token_operation, op_assign_sub, line_, "-=" );
		else if ( *(it - 1) == '>' )
			return Token( token_operation, op_ptm_access, line_, "->" ); // Pointer to member access from pointer
		--it;
		return Token( token_operation, op_unary_sub, line_, "-" );
	case '*':
		if ( *(it++) == '=' )
			return Token( token_operation, op_assign_mul, line_, "*=" );
		--it;
		return Token( token_operation, op_mul, line_, "*" );
	case '/':
		if ( *(it++) == '=' )
			return Token( token_operation, op_assign_div, line_, "/=" );
		--it;
		return Token( token_operation, op_div, line_, "/" );
	case '&':
		if ( *(it++) == '&' )
			return Token( token_operation, op_logical_and, line_, "&&" );
		else if ( *(it - 1) == '=' )
			return Token( token_operation, op_assign_bitwise_and, line_, "&=" );
		--it;
		return Token( token_operation, op_bitwise_and, line_, "&" );
	case '|':
		if ( *(it++) == '|' )
			return Token( token_operation, op_logical_or, line_, "||" );
		else if ( *(it - 1) == '=' )
			return Token( token_operation, op_assign_bitwise_or, line_, "|=" );
		--it;
		return Token( token_operation, op_bitwise_or, line_, "|" );
	case '^':
		if ( *(it++) == '=')
			return Token( token_operation, op_assign_bitwise_xor, line_, "^=" );
		--it;
		return Token( token_operation, op_bitwise_xor, line_, "^" );
	case '>':
		if ( *(it++) == '>' )
		{
			if ( *(it++) == '=' )
				return Token( token_operation, op_assign_bitwise_right, line_, ">>=" );
			--it;
			return Token( token_operation, op_bitwise_right, line_, ">>" );
		}
		else if ( *(it - 1) == '=' )
			return Token( token_operation, op_greater_than_equals, line_, ">=" );
		--it;
		return Token( token_operation, op_greater, line_, ">" );
	case '<':
		if ( *(it++) == '<' )
		{
			if ( *(it++) == '=' )
				return Token( token_operation, op_assign_bitwise_left, line_, "<<=" );
			--it;
			return Token( token_operation, op_bitwise_left, line_, "<<" );
		}
		else if ( *(it - 1) == '=' )
			return Token( token_operation, op_less_than_equals, line_, "<=" );
		--it;
		return Token( token_operation, op_less, line_, "<" );
	case '%':
		if ( *(it++) == '=' )
			return Token( token_operation, op_assign_modulu, line_, "%=" );
		--it;
		return Token( token_operation, op_modulo, line_, "%" );
	case '!':
		if ( *(it++) == '=' )
			return Token( token_operation, op_not_equal_to, line_, "!=" );
		--it;
		return Token( token_operation, op_logical_not, line_, "!" );
	case '~':
		return Token( token_operation, op_bitwise_not, line_, "~" );
	case ',':
		return Token( token_operation, op_comma, line_, "," );
	case '.':
		if ( *(it++) == '*' )
			return Token( token_operation, op_ptm_period, line_, ".*" );
		--it;
		return Token( token_operation, op_period, line_, "." );
	case '(':
		return Token( token_operation, op_roundbracket_open, line_, "(" );
	case ')':
		return Token( token_operation, op_roundbracket_close, line_, ")" );
	case '[':
		return Token( token_operation, op_squarebracket_open, line_, "[" );
	case ']':
		return Token( token_operation, op_squarebracket_close, line_, "]" );
	case '{':
		return Token( token_operation, op_squigglybracket_open, line_, "{" );
	case '}':
		return Token( token_operation, op_squigglybracket_close, line_, "}" );
	case ';':
		return Token( token_operation, op_semicolon, line_, ";" );
	case '#':
		return Token( token_operation, op_preprocessor_hash, line_, "#" );
	default:
		return Token( token_operation, op_none, line_, { good( it - 1, end ) ? *(it - 1) : '\0' } ); 
	}
}


