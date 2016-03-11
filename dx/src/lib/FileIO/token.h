#pragma once
#include "lib.h"
#include "../string.h"

begin_FILEIO


enum Token_t : uint
{
	token_eof, // No more tokens, end of the file.
	token_identifier, // Any array of characters that begins on an alphabetic character and proceeds with optional alphanumeric characters.
	token_string, // an array of characters wrapped in quotes('"').
	token_bracket_left, // '{'
	token_bracket_right, // '}'
	token_parenthesis_left, // '('
	token_parenthesis_right, // ')'
	token_semicolon, // ';'
	token_comment, // '//'
	token_endl, // '\n'
	token_decimal, // decimal numbers
	token_hexadecimal, // hexadecimal numbers
	token_comma, // ','
	token_dot, // '.'
	token_arrow, // '->'
	token_colon, // ':'
	token_scope, // '::'
	token_increment, // '++'
	token_decrement, // '--'
	token_logical_and, // '&&'
	token_logical_or, // '||'
	token_address_of, // '&'
	token_left_shift, // '<<'
	token_right_shift, // '>>'
	token_less, // '<'
	token_greater, // '>'
	token_less_equal, // '<='
	token_greater_equal, // '>='
	token_plus, // '+'
	token_minus, // '-'
	token_plus_assign, // '+='
	token_minus_assign, // '-='
	token_indirect, // '*'
	token_modulus, // '%'
	token_divides, // '/'
	token_modulus_assign, // '%='
	token_divies_assign, // '/='
	token_multiplies_assign, // '*='
	token_assign, // '='
	token_subscript_left, // '['
	token_subscript_right, // ']'
	token_compare, // '=='
	token_not_compare, // '!='
	token_not, // '!'
	token_unknown, // unknown, possible error.
	keyword_if,  // "if"
	keyword_else, // "else"
	keyword_while, // "while"
	keyword_for, // "for"
	keyword_var, // "var"
	keyword_int, // "int"
	keyword_byte,  // "byte"
	keyword_bool,  // "bool"
	keyword_string,
	keyword_const, // "const"
	keyword_true,  // "true"
	keyword_false, // "false"
	keyword_sizeof, // "sizeof"
	keyword_typeof, // "typeof"
	keyword_declscope, // "declscope"
	keyword_class,
	keyword_decltype, // "decltype"
	keyword_template, // "template"
	keyword_typename, // "typename"
};

bool isKeyword( const __LIB String &_Identifier );
Token_t toKeyword( const __LIB String &_Identifier );
__LIB String TokenToString( const Token_t &_Token );

class Token
{
private:
	__FILEIO Token_t _tok;
	__LIB String _identifier;
	__DX uint _line, _char_count;
public:
	Token( const __FILEIO Token_t& tok, const __LIB String& identifier, const __DX uint& line, const __DX uint char_count );
	Token( const __FILEIO Token_t& tok, const __LIB String& identifier );
	Token( );

	__FILEIO Token_t getToken( ) const;
	void setToken( const __FILEIO Token_t& );

	__LIB String getIdentifier( ) const;
	void setIdentifier( const __LIB String& );
	
	__DX uint getLine( ) const;
	void setLine( const uint& );

	__DX uint getCharCount( ) const;
	void setCharCount( const __DX uint& );

public:
	
};

bool operator==( const __FILEIO Token &_Lhs, const __LIB String &_Rhs );
bool operator==( const __FILEIO Token &_Lhs, const __FILEIO Token_t &_Rhs );
bool operator==( const __LIB String &_Lhs, const Token &_Rhs );
bool operator==( const __FILEIO Token_t &_Lhs, const __FILEIO Token &_Rhs );
bool operator!=( const __FILEIO Token &_Lhs, const __LIB String &_Rhs );
bool operator!=( const __FILEIO Token &_Lhs, const __FILEIO Token_t &_Rhs );
bool operator!=( const __LIB String &_Lhs, const __FILEIO Token &_Rhs );
bool operator!=( const __FILEIO Token_t &_Lhs, const __FILEIO Token &_Rhs );


end_FILEIO