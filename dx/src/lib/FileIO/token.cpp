#include "token.h"

begin_FILEIO

String get_string(const Operation & op)
{
	switch( op )
	{
	case op_scope_resolution:
		return "::";
	case op_postfix_increment:
		return "++";
	case op_postfix_decrement:
		return "--";
	case op_roundbracket_open:
		return "(";
	case op_roundbracket_close:
		return ")";
	case op_squarebracket_open:
		return "[";
	case op_squarebracket_close:
		return "]";
	case op_squigglybracket_open:
		return "{";
	case op_squigglybracket_close:
		return "}";
	case op_access:
		return "->";
	case op_period:
		return ".";
	case op_unary_add:
		return "+";
	case op_unary_sub:
		return "-";
	case op_logical_not:
		return "!";
	case op_bitwise_not:
		return "~";
	case op_indirect:
		return "*";
	case op_bitwise_and:
		return "&";
	case op_ptm_access:
		return "->*";
	case op_ptm_period:
		return ".*";
	case op_mul:
		return "*";
	case op_div:
		return "/";
	case op_modulo:
		return "%";
	case op_bitwise_left:
		return "<<";
	case op_bitwise_right:
		return ">>";
	case op_less:
		return "<";
	case op_greater:
		return ">";
	case op_less_than_equals:
		return "<=";
	case op_greater_than_equals:
		return ">=";
	case op_equal_to:
		return "==";
	case op_not_equal_to:
		return "!=";
	case op_bitwise_xor:
		return "^";
	case op_bitwise_or:
		return "|";
	case op_logical_and:
		return "&&";
	case op_logical_or:
		return "||";
	case op_ternary:
		return "?";
	case op_assign:
		return "=";
	case op_assign_add:
		return "+=";
	case op_assign_sub:
		return "-=";
	case op_assign_div:
		return "/=";
	case op_assign_mul:
		return "*=";
	case op_assign_modulu:
		return "%=";
	case op_assign_bitwise_left:
		return "<<=";
	case op_assign_bitwise_right:
		return ">>=";
	case op_assign_bitwise_and:
		return "&=";
	case op_assign_bitwise_or:
		return "|=";
	case op_comma:
		return ",";
	default:
		return "none";
	}
}

String get_string(const Keyword & kw)
{
	switch( kw )
	{
	case kw_alignas:
		return "alignas";
	case kw_alignof:
		return "alignof";
	case kw_and:
		return "and";
	case kw_and_eq:
		return "and_eq";
	case kw_asm:
		return "__asm";
	case kw_atomic_cancel:
		return "atomic_cancel";
	case kw_atomic_commit:
		return "atomic_commit";
	case kw_atomic_noexcept:
		return "atomic_noexcept";
	case kw_auto:
		return "auto";
	case kw_bitand:
		return "bitand";
	case kw_bitor:
		return "bitor";
	case kw_bool:
		return "bool";
	case kw_break:
		return "break";
	case kw_case:
		return "case";
	case kw_catch:
		return "catch";
	case kw_char:
		return "char";
	case kw_char16_t:
		return "char16_t";
	case kw_class:
		return "class";
	case kw_compl:
		return "compl";
	case kw_concept:
		return "concept";
	case kw_const:
		return "const";
	case kw_constexpr:
		return "constexpr";
	case kw_const_cast:
		return "const_cast";
	case kw_continue:
		return "continue";
	case kw_decltype:
		return "decltype";
	case kw_default:
		return "default";
	case kw_delete:
		return "delete";
	case kw_do:
		return "do";
	case kw_double:
		return "double";
	case kw_dynamic_cast:
		return "dynamic_cast";
	case kw_else:
		return "else";
	case kw_enum:
		return "enum";
	case kw_explicit:
		return "explicit";
	case kw_export:
		return "export";
	case kw_extern:
		return "extern";
	case kw_false:
		return "false";
	case kw_float:
		return "float";
	case kw_for:
		return "for";
	case kw_friend:
		return "friend";
	case kw_goto:
		return "goto";
	case kw_if:
		return "if";
	case kw_inline:
		return "inline";
	case kw_int:
		return "int";
	case kw_import:
		return "import";
	case kw_long:
		return "long";
	case kw_module:
		return "module";
	case kw_mutable:
		return "mutable";
	case kw_namespace:
		return "namespace";
	case kw_new:
		return "new";
	case kw_noexcept:
		return "noexcept";
	case kw_not_eq:
		return "not_eq";
	case kw_nullptr:
		return "nullptr";
	case kw_operator:
		return "operator";
	case kw_or:
		return "or";
	case kw_or_eq:
		return "or_eq";
	case kw_private:
		return "private";
	case kw_protected:
		return "proected";
	case kw_public:
		return "public";
	case kw_register:
		return "register";
	case kw_reinterpret_cast:
		return "reinterpret_cast";
	case kw_requires:
		return "requires";
	case kw_return:
		return "return";
	case kw_short:
		return "short";
	case kw_signed:
		return "signed";
	case kw_sizeof:
		return "sizeof";
	case kw_static:
		return "static";
	case kw_static_assert:
		return "static_assert";
	case kw_static_cast:
		return "static_cast";
	case kw_struct:
		return "struct";
	case kw_switch:
		return "switch";
	case kw_synchronized:
		return "synchronized";
	case kw_template:
		return "template";
	case kw_this:
		return "this";
	case kw_thread_local:
		return "thread_local";
	case kw_throw:
		return "throw";
	case kw_true:
		return "true";
	case kw_try:
		return "try";
	case kw_typedef:
		return "typedef";
	case kw_typeid:
		return "typeid";
	case kw_typename:
		return "typename";
	case kw_union:
		return "union";
	case kw_unsigned:
		return "unsigned";
	case kw_using:
		return "using";
	case kw_virtual:
		return "virtual";
	case kw_void:
		return "void";
	case kw_volatile:
		return "volatile";
	case kw_wchar_t:
		return "wchar_t";
	case kw_while:
		return "while";
	case kw_xor:
		return "xor";
	case kw_xor_eq:
		return "xor_eq";
	case kw_override:
		return "override";
	case kw_final:
		return "final";
	case kw_transaction_safe:
		return "transaction_safe";
	case kw_transaction_safe_dynamic:
		return "transaction_safe_dynamic";
	default:
		return "unknown";
	}
}

Keyword get_keyword(const String &str)
{
	if ( str == "alignas" )
		return kw_alignas;
	else if ( str == "alignof" || str == "__alignof" )
		return kw_alignof;
	else if ( str == "and" )
		return kw_and;
	else if ( str == "and_eq" )
		return kw_and_eq;
	else if ( str == "__asm" )
		return kw_asm;
	else if ( str == "atomic_cancel" )
		return kw_atomic_cancel;
	else if ( str == "atomic_commit" )
		return kw_atomic_commit;
	else if ( str == "atomic_noexcept" )
		return kw_atomic_noexcept;
	else if ( str == "auto" )
		return kw_auto;
	else if ( str == "bitand" )
		return kw_bitand;
	else if ( str == "bitor" )
		return kw_bitor;
	else if ( str == "bool" )
		return kw_bool;
	else if ( str == "break" )
		return kw_break;
	else if ( str == "case" )
		return kw_case;
	else if ( str == "catch" )
		return kw_catch;
	else if ( str == "char" )
		return kw_char;
	else if ( str == "char16_t" )
		return kw_char16_t;
	else if ( str == "char32_t" )
		return kw_char32_t;
	else if ( str == "class" )
		return kw_class;
	else if ( str == "compl" )
		return kw_compl;
	else if ( str == "concept" )
		return kw_concept;
	else if ( str == "const" )
		return kw_const;
	else if ( str == "constexpr" )
		return kw_constexpr;
	else if ( str == "const_cast" )
		return kw_const_cast;
	else if ( str == "continue" )
		return kw_continue;
	else if ( str == "decltype" )
		return kw_decltype;
	else if ( str == "default" )
		return kw_default;
	else if ( str == "delete" )
		return kw_delete;
	else if ( str == "do" )
		return kw_do;
	else if ( str == "double" )
		return kw_double;
	else if ( str == "dynamic_cast" )
		return kw_dynamic_cast;
	else if ( str == "else" )
		return kw_else;
	else if ( str == "enum" )
		return kw_enum;
	else if ( str == "explicit" )
		return kw_explicit;
	else if ( str == "export" )
		return kw_export;
	else if ( str == "extern" )
		return kw_extern;
	else if ( str == "false" )
		return kw_false;
	else if ( str == "float" )
		return kw_float;
	else if ( str == "for" )
		return kw_for;
	else if ( str == "friend" )
		return kw_friend;
	else if ( str == "goto" )
		return kw_goto;
	else if ( str == "if" )
		return kw_if;
	else if ( str == "inline" || str == "__forceinline" )
		return kw_inline;
	else if ( str == "int" )
		return kw_int;
	else if ( str == "import" )
		return kw_import;
	else if ( str == "long" )
		return kw_long;
	else if ( str == "module" )
		return kw_module;
	else if ( str == "mutable" )
		return kw_mutable;
	else if ( str == "namespace" )
		return kw_namespace;
	else if ( str == "new" )
		return kw_new;
	else if ( str == "noexcept" )
		return kw_noexcept;
	else if ( str == "not_eq" )
		return kw_not_eq;
	else if ( str == "nullptr" )
		return kw_nullptr;
	else if ( str == "operator" )
		return kw_operator;
	else if ( str == "or" )
		return kw_or;
	else if ( str == "or_eq" )
		return kw_or_eq;
	else if ( str == "private" )
		return kw_private;
	else if ( str == "protected" )
		return kw_protected;
	else if ( str == "public" )
		return kw_public;
	else if ( str == "register" )
		return kw_register;
	else if ( str == "reinterpret_cast" )
		return kw_reinterpret_cast;
	else if ( str == "requires" )
		return kw_requires;
	else if ( str == "return" )
		return kw_return;
	else if ( str == "short" )
		return kw_short;
	else if ( str == "signed" )
		return kw_signed;
	else if ( str == "sizeof" )
		return kw_sizeof;
	else if ( str == "static" )
		return kw_static;
	else if ( str == "static_assert" )
		return kw_static_assert;
	else if ( str == "static_cast" )
		return kw_static_cast;
	else if ( str == "struct" )
		return kw_struct;
	else if ( str == "switch" )
		return kw_switch;
	else if ( str == "synchronized" )
		return kw_synchronized;
	else if ( str == "template" )
		return kw_template;
	else if ( str == "this" )
		return kw_this;
	else if ( str == "thread_local" )
		return kw_thread_local;
	else if ( str == "throw" )
		return kw_throw;
	else if ( str == "try" )
		return kw_try;
	else if ( str == "typedef" )
		return kw_typedef;
	else if ( str == "typeid" )
		return kw_typeid;
	else if ( str == "typename" )
		return kw_typename;
	else if ( str == "union" )
		return kw_union;
	else if ( str == "unsigned" )
		return kw_unsigned;
	else if ( str == "using" )
		return kw_using;
	else if ( str == "virtual" )
		return kw_virtual;
	else if ( str == "void" )
		return kw_void;
	else if ( str == "volatile" )
		return kw_volatile;
	else if ( str == "wchar_t" )
		return kw_wchar_t;
	else if ( str == "while" )
		return kw_while;
	else if ( str == "xor" )
		return kw_xor;
	else if ( str == "xor_eq" )
		return kw_xor_eq; // kw_override, kw_final, kw_transaction_safe, kw_transaction_safe_dynamic
	else if ( str == "override" )
		return kw_override;
	else if ( str == "final" )
		return kw_final;
	else if ( str == "transaction_safe" )
		return kw_transaction_safe;
	else if ( str == "transaction_safe_dynamic" )
		return kw_transaction_safe_dynamic;


	return kw_unknown;
}

end_FILEIO