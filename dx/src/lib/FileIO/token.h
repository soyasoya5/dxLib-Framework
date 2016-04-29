#pragma once
#include "lib.h"
#include "../string.h"


begin_FILEIO

enum Keyword
{
	kw_alignas, kw_alignof, kw_and, kw_and_eq, kw_asm, kw_atomic_cancel, kw_atomic_commit,
	kw_atomic_noexcept, kw_auto, kw_bitand, kw_bitor, kw_bool, kw_break, kw_case, kw_catch, kw_char,
	kw_char16_t, kw_char32_t, kw_class, kw_compl, kw_concept, kw_const, kw_constexpr, kw_const_cast,
	kw_continue, kw_decltype, kw_default, kw_delete, kw_do, kw_double, kw_dynamic_cast, kw_else,
	kw_enum, kw_explicit, kw_export, kw_extern, kw_false, kw_float, kw_for, kw_friend, kw_goto,
	kw_if, kw_inline, kw_int, kw_import, kw_long, kw_module, kw_mutable, kw_namespace, kw_new,
	kw_noexcept, kw_not_eq, kw_nullptr, kw_operator, kw_or, kw_or_eq, kw_private, kw_protected,
	kw_public, kw_register, kw_reinterpret_cast, kw_requires, kw_return, kw_short, kw_signed,
	kw_sizeof, kw_static, kw_static_assert, kw_static_cast, kw_struct, kw_switch, kw_synchronized,
	kw_template, kw_this, kw_thread_local, kw_throw, kw_true, kw_try, kw_typedef, kw_typeid, 
	kw_typename, kw_union, kw_unsigned, kw_using, kw_virtual, kw_void, kw_volatile, kw_wchar_t,
	kw_while, kw_xor, kw_xor_eq, kw_override, kw_final, kw_transaction_safe, kw_transaction_safe_dynamic,
	kw_unknown
};

enum Operation
{
	// Presedence 1 is highest-

	/* 1 */ 
	op_scope_resolution = 96, op_colon,
	op_semicolon,

	/* 2 */
	op_postfix_increment, op_postfix_decrement,
	op_roundbracket_open, op_roundbracket_close,
	op_squarebracket_open, op_squarebracket_close,
	op_squigglybracket_open, op_squigglybracket_close,
	op_access, op_period,

	/* 3 */
	op_unary_add, op_unary_sub, 
	/* op_prefix_increment,  op_prefix_decrement, */ 
	op_logical_not, op_bitwise_not, 
	op_indirect, op_bitwise_and,

	/* 4 */
	op_ptm_access, op_ptm_period,


	/* 5 */
	op_mul, op_div,
	op_modulo,

	/* 6 */
	op_bitwise_left, op_bitwise_right,

	/* 7 */
	op_less, op_greater,
	op_less_than_equals, op_greater_than_equals,

	/* 8 */
	op_equal_to, op_not_equal_to,

	/* 9 */
	op_bitwise_xor, op_bitwise_or,
	op_logical_and, op_logical_or,
	op_ternary,

	/* 10 */
	op_assign, op_assign_add,
	op_assign_sub, op_assign_div,
	op_assign_mul, op_assign_modulu,
	op_assign_bitwise_left, op_assign_bitwise_right,
	op_assign_bitwise_and, op_assign_bitwise_or,
	op_assign_bitwise_xor,
	
	/* 11 */
	op_comma, op_preprocessor_hash,

	// None
	op_none
};


extern String get_string( const Operation &op );
extern String get_string( const Keyword &kw );
extern Keyword get_keyword( const String &str );

enum token_t
{
	token_identifier,
	token_keyword,
	token_string_literal,
	token_numerical,
	token_operation,
};


struct Token
{
	uint type, kw, line;
	String value;

	Token( )
		: type( ), kw(  ), value( ), line( )
	{}

	Token( uint type, uint kw, uint line, String value )
		: type( type ), kw( kw ), line( line ), value( value )
	{}
};

struct File 
{ 
	bool loaded;
	std::string name, contents; // Using std::string because the iterators are faster.

	File( )
		: loaded( false ), name( ), contents( )
	{}

	File( bool loaded, std::string name, std::string contents )
		: loaded( loaded ), name( std::move( name ) ), contents( std::move( contents ) )
	{}
};



end_FILEIO

