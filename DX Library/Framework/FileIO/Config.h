#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "../dx.h"
#include "../Utils/string.h"


namespace FileIO
{

	extern Utils::String ReadFile( Utils::String );

	class Tokenizer
	{
	public:
		enum eToken
		{
			eToken_eof, // End of file
			eToken_comment,
			eToken_endl,
			eToken_class,
			eToken_import, // Basically include, but for OSharp
			eToken_leftParanthesis,
			eToken_RightParanthesis,
			eToken_operatorAccess, // ->
			etoken_quote, // dafuq is a ' called?
			eToken_plus,
			eToken_minus,
			eToken_times,
			eToken_slash,
			eToken_equals,
			eToken_not,
			eToken_plusEquals, // "+="
			eToken_equalsEquals,
			eToken_notEquals,
			eToken_minusEquals,
			eToken_slashEquals,
			eToken_timesEquals,
			eToken_semicolon,
			eToken_numerical,
			eToken_identifier,
			eToken_operator_and,
			eToken_operaotr_or,
			eToken_if,
			eToken_else,
			eToken_while,
			eToken_for,
			eToken_foreach,
			eToken_extern,
			eToken_macro,

			// Standard types..
			eToken_int,
			eToken_float,
			eToken_double,
			eToken_long,
			eToken_char,
			eToken_string,
			eToken_void,
			eToken_pointer,
			eToken_unknown
		};
		struct Token
		{
			Token(eToken tok, Utils::String str, std::uintptr_t count, std::uintptr_t line) : tok(tok), string(str), char_count(count), line_count(line) {}
			Token()  {}
			eToken tok;
			Utils::String string;
			std::uintptr_t char_count, line_count;

			bool operator==(const eToken& t) { return tok == t; }
			bool operator==(const Utils::String& t) { return string == t; }
			bool operator!=(const eToken& t) { return tok != t; }
			bool operator!=(const Utils::String& t) { return string != t; }
		};
	private:

		char c;
		std::uintptr_t _count, _line;

		Utils::String _file;
		Utils::String _orig_file;

		Token _prevToken, _currToken;

		std::vector<Token> _previousTokens;

		char getNextChar();
		Token getNewToken();
		std::vector<Utils::String> _operators;
	public:
		Tokenizer(const Utils::String& file) : _file(file), _orig_file(file), c(' '), _count(0), _line(1) {}
		void Re_Construct(Utils::String str) { Release(); _file = str; c = ' '; }

		std::vector<Token>::iterator begin() { return _previousTokens.begin(); }
		std::vector<Token>::iterator end() { return _previousTokens.end(); }

		bool isop(const char& c) const noexcept;


		Token getNextToken(); // Returns new token, and sets the new token to _currToken (and _prevToken to _currToken)
		Token getCurrToken(); // Returns the current token
		Token getPrevToken(); // Returns the previous token
		Token getTokenAt(size_t index);
		size_t getCurrTokenIndex();
		size_t getPrevTokenIndex();
		Utils::String getFullFile() { return _orig_file; }
		Utils::String getCurrentFile() { return _file; } // Returns a substr of _orig_file from the current count (to end).
		std::uintptr_t getCharCount();

		static Utils::String TokToString(eToken tok);

		void Tokenize();
		void Release();
	};

	class ConfigElement
	{
	private:
		Utils::String _element;
		std::vector<std::vector<Utils::String>> _values;

		bool __dim( const uint& );
		bool __dim( const uint&, const uint& );
	public:
		ConfigElement( ) = default;

		Utils::String& Name( ) { return _element; }
		Utils::String  Value( const uint& val_idx, const uint& val_idx_arr );
		bool setValue( const uint& val_idx, const uint& val_idx_arr, const Utils::String& value );

		std::vector<std::vector<Utils::String>>& Array( ) { return _values; };
	};

	class Config : public Object
	{
	public:
		typedef std::vector<ConfigElement> List;
		typedef std::vector<Tokenizer::Token>::iterator iterator;
		Config( ) = default;
		Config( const Utils::String& file ) : _file(file) { }

		void setFile( const Utils::String& file ) { _file = file; }
		bool Parse( );

		ConfigElement& Element( const Utils::String& name );
		ConfigElement& Element( const uint& idx );

		bool Exists( const Utils::String& );
		List getElements() { return _elems; }
	private:
		Utils::String _file;
		List _elems;

		bool IsComment( iterator iter );
		void EatComment( iterator& iter );
		ConfigElement ParseElement( iterator& iter );
		std::vector<std::vector<Utils::String>> ParseBrackets( iterator& iter );


		void ReplaceVector( std::vector<Utils::String>& vec, std::vector<Utils::String> vec2 );
	};


}