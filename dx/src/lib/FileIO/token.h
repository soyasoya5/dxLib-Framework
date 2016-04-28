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

///<summary>
/// Returns true if '_Identifier' is a keyword.
///</summary>
bool isKeyword( const ::dx::lib::String &_Identifier );

///<summary>
/// Convert '_Identifier' to a keyword.
///</summary>
Token_t toKeyword( const ::dx::lib::String &_Identifier );

///<summary>
/// Convert token to string.
///</summary>
::dx::lib::String TokenToString( const Token_t &_Token );


class Token
{
private:
	::dx::lib::FileIO::Token_t _tok;
	::dx::lib::String _identifier;
	::dx::uint _line, _char_count;
public:

	///<summary>
	/// Construct this tokenizer optional more parameters.
	///</summary>
	Token( const ::dx::lib::FileIO::Token_t& tok, const ::dx::lib::String& identifier, const ::dx::uint& line, const ::dx::uint char_count );

	///<summary>
	/// Construct this tokenizer.
	///</summary>
	Token( const ::dx::lib::FileIO::Token_t& tok, const ::dx::lib::String& identifier );

	///<summary>
	/// Empty constructor
	///</summary>
	Token( );

	///<summary>
	/// Return the token type.
	///</summary>
	::dx::lib::FileIO::Token_t getToken( ) const;

	///<summary>
	/// Set the token type.
	///</summary>
	void setToken( const ::dx::lib::FileIO::Token_t& );

	///<summary>
	/// Get the identifier of this token.
	///</summary>
	::dx::lib::String getIdentifier( ) const;

	///<summary>
	/// Set the identifier of this token.
	///</summary>
	void setIdentifier( const ::dx::lib::String& );
	
	///<summary>
	/// Get the line of this token.
	///</summary>
	::dx::uint getLine( ) const;
	
	///<summary>
	/// Set the line of this token.
	///</summary>
	void setLine( const uint& );

	///<summary>
	///	Get the char count of this token.
	///</summary>
	::dx::uint getCharCount( ) const;

	///<summary>
	///	Set the char count of this token.
	///</summary>
	void setCharCount( const ::dx::uint& );

public:
	
};


///<summary>
/// Return true if '_Lhs''s  identifier is equal to _Rhs.
///</summary>
bool operator==( const ::dx::lib::FileIO::Token &_Lhs, const ::dx::lib::String &_Rhs );

///<summary>
/// Return true if '_Lhs''s token is equal to _Rhs.
///</summary>
bool operator==( const ::dx::lib::FileIO::Token &_Lhs, const ::dx::lib::FileIO::Token_t &_Rhs );

///<summary>
/// Return true if '_Lhs''s  identifier is equal to _Rhs. (Reversed)
///</summary>
bool operator==( const ::dx::lib::String &_Lhs, const Token &_Rhs );

///<summary>
/// Return true if '_Lhs''s token is equal to _Rhs. (Reversed)
///</summary>
bool operator==( const ::dx::lib::FileIO::Token_t &_Lhs, const ::dx::lib::FileIO::Token &_Rhs );

///<summary>
/// Return false if '_Lhs''s  identifier is equal to _Rhs.
///</summary>
bool operator!=( const ::dx::lib::FileIO::Token &_Lhs, const ::dx::lib::String &_Rhs );

///<summary>
/// Return true if '_Lhs''s token is equal to _Rhs.
///</summary>
bool operator!=( const ::dx::lib::FileIO::Token &_Lhs, const ::dx::lib::FileIO::Token_t &_Rhs );

///<summary>
/// Return true if '_Lhs''s  identifier is equal to _Rhs. (Reversed)
///</summary>
bool operator!=( const ::dx::lib::String &_Lhs, const ::dx::lib::FileIO::Token &_Rhs );

///<summary>
/// Return true if '_Lhs''s token is equal to _Rhs. (Reversed)
///</summary>
bool operator!=( const ::dx::lib::FileIO::Token_t &_Lhs, const ::dx::lib::FileIO::Token &_Rhs );


end_FILEIO