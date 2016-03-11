#include "token.h"


begin_FILEIO


Token::Token(const Token_t & tok, const __LIB String & identifier, const uint & line, const uint char_count)
	: _tok(tok), _identifier(identifier), _line(line), _char_count(char_count)
{
	if ( isKeyword( identifier ) )
		_tok = toKeyword( identifier );
}

Token::Token(const Token_t & tok, const __LIB String & identifier)
	: _tok(tok), _identifier(identifier), _line(0), _char_count(0)
{
}

Token::Token()
	: _tok(token_eof), _identifier(), _line(0), _char_count(0)
{
}

Token_t Token::getToken() const
{
	return _tok;
}

void Token::setToken(const Token_t &tok)
{
	_tok = tok;
}

__LIB String Token::getIdentifier() const
{
	return _identifier;
}

void Token::setIdentifier(const __LIB String &identifier)
{
	_identifier = identifier;
}

uint Token::getLine() const
{
	return _line;
}

void Token::setLine(const uint &line)
{
	_line = line;
}

uint Token::getCharCount() const
{
	return _char_count;
}

void Token::setCharCount(const uint &count)
{
	_char_count = count;
}

bool isKeyword(const __LIB String &id)
{
	return toKeyword( id ) != token_identifier;
}

Token_t toKeyword(const __LIB String &id)
{
	if ( id == "if" )
		return keyword_if;
	else if ( id == "else" )
		return keyword_else;
	else if ( id == "while" )
		return keyword_while;
	else if ( id == "for" )
		return keyword_for;
	else if ( id == "var" )
		return keyword_var;
	else if ( id == "int" )
		return keyword_int;
	else if ( id == "byte" )
		return keyword_byte;
	else if ( id == "bool" )
		return keyword_bool;
	else if ( id == "true" )
		return keyword_true;
	else if ( id == "false" )
		return keyword_false;
	else if ( id == "sizeof" )
		return keyword_sizeof;
	else if ( id == "typeof" )
		return keyword_typeof;
	else if ( id == "const" )
		return keyword_const;
	else if ( id == "declscope" )
		return keyword_declscope;
	else if ( id == "decltype" )
		return keyword_decltype;
	else if ( id == "template" )
		return keyword_template;
	else if ( id == "typename" )
		return keyword_typename;
	else if ( id == "class" )
		return keyword_class;
	else if ( id == "string" )
		return keyword_string;
	return token_identifier;
}

__LIB String TokenToString(const Token_t &tok)
{
#define casify(x) case x: return #x;
	switch (tok)
	{
		casify(token_eof);
		casify(token_identifier);
		casify(token_string);
		casify(token_bracket_left);
		casify(token_bracket_right);
		casify(token_parenthesis_left);
		casify(token_parenthesis_right);
		casify(token_semicolon);
		casify(token_comment);
		casify(token_endl);
		casify(token_decimal);
		casify(token_hexadecimal);
		casify(token_comma);
		casify(token_dot);
		casify(token_arrow);
		casify(token_colon);
		casify(token_scope);
		casify(token_increment);
		casify(token_decrement);
		casify(token_logical_and);
		casify(token_logical_or);
		casify(token_address_of);
		casify(token_left_shift);
		casify(token_right_shift);
		casify(token_less);
		casify(token_greater);
		casify(token_less_equal);
		casify(token_greater_equal);
		casify(token_plus);
		casify(token_minus);
		casify(token_plus_assign);
		casify(token_minus_assign);
		casify(token_indirect);
		casify(token_modulus);
		casify(token_divides);
		casify(token_modulus_assign);
		casify(token_divies_assign);
		casify(token_multiplies_assign);
		casify(token_assign);
		casify(token_subscript_left); // '['
		casify(token_subscript_right); // ']'
		casify(token_compare);
		casify(token_not_compare);
		casify(token_not);
		casify(token_unknown);
		casify(keyword_if);
		casify(keyword_else);
		casify(keyword_while);
		casify(keyword_for);
		casify(keyword_var);
		casify(keyword_int);
		casify(keyword_byte);
		casify(keyword_bool);
		casify(keyword_const);
		casify(keyword_true);
		casify(keyword_false);
		casify(keyword_sizeof);
		casify(keyword_typeof);
		casify(keyword_class);
		casify(keyword_declscope);
		casify(keyword_decltype); // "decltype"
		casify(keyword_template); // "template"
		casify(keyword_typename); // "typename"
		casify(keyword_string);
	}
	return "invalid_token";
}

bool operator==(const Token & lhs, const __LIB String & rhs)
{
	return lhs.getIdentifier( ) == rhs;
}

bool operator==(const Token & lhs, const Token_t & rhs)
{
	return lhs.getToken( ) == rhs;
}

bool operator==(const __LIB String & lhs, const Token & rhs)
{
	return rhs == lhs;
}

bool operator==(const Token_t & lhs, const Token & rhs)
{
	return rhs == lhs;
}

bool operator!=(const Token & lhs, const __LIB String & rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const Token & lhs, const Token_t & rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const __LIB String & lhs, const Token & rhs)
{
	return !(rhs == lhs);
}

bool operator!=(const Token_t & lhs, const Token & rhs)
{
	return !(rhs == lhs);
}




end_FILEIO