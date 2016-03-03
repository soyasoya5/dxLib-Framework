#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "../dx.h"


namespace FileIO
{

	extern std::string ReadFile( std::string );

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
			Token(eToken tok, std::string str, std::uintptr_t count, std::uintptr_t line) : tok(tok), string(str), char_count(count), line_count(line) {}
			Token()  {}
			eToken tok;
			std::string string;
			std::uintptr_t char_count, line_count;

			bool operator==(const eToken& t) { return tok == t; }
			bool operator==(const std::string& t) { return string == t; }
			bool operator!=(const eToken& t) { return tok != t; }
			bool operator!=(const std::string& t) { return string != t; }
		};
	private:

		char c;
		std::uintptr_t _count, _line;

		std::string _file;
		std::string _orig_file;

		Token _prevToken, _currToken;

		std::vector<Token> _previousTokens;

		char getNextChar();
		Token getNewToken();
		std::vector<std::string> _operators;
	public:
		Tokenizer(const std::string& file) : _file(file), _orig_file(file), c(' '), _count(0), _line(1) {}
		void Re_Construct(std::string str) { Release(); _file = str; c = ' '; }

		std::vector<Token>::iterator begin() { return _previousTokens.begin(); }
		std::vector<Token>::iterator end() { return _previousTokens.end(); }

		bool isop(const char& c) const noexcept;


		Token getNextToken(); // Returns new token, and sets the new token to _currToken (and _prevToken to _currToken)
		Token getCurrToken(); // Returns the current token
		Token getPrevToken(); // Returns the previous token
		Token getTokenAt(size_t index);
		size_t getCurrTokenIndex();
		size_t getPrevTokenIndex();
		std::string getFullFile() { return _orig_file; }
		std::string getCurrentFile() { return _file; } // Returns a substr of _orig_file from the current count (to end).
		std::uintptr_t getCharCount();

		static std::string TokToString(eToken tok);

		void Tokenize();
		void Release();
	};

	class ConfigElement
	{
	private:
		std::string _element;
		std::vector<std::vector<std::string>> _values;

		bool __dim( const uint& );
		bool __dim( const uint&, const uint& );
	public:
		ConfigElement( ) = default;

		std::string& Name( ) { return _element; }
		std::string  Value( const uint& val_idx, const uint& val_idx_arr );
		bool setValue( const uint& val_idx, const uint& val_idx_arr, const std::string& value );

		std::vector<std::vector<std::string>>& Array( ) { return _values; };
	};

	class Config : public Object
	{
	public:
		typedef std::vector<ConfigElement> List;
		typedef std::vector<Tokenizer::Token>::iterator iterator;
		Config( ) = default;
		Config( const std::string& file ) : _file(file) { }

		void setFile( const std::string& file ) { _file = file; }
		bool Parse( );

		ConfigElement& Element( const std::string& name );
		ConfigElement& Element( const uint& idx );

		bool Exists( const std::string& );
		List getElements() { return _elems; }
	private:
		std::string _file;
		List _elems;

		bool IsComment( iterator iter );
		void EatComment( iterator& iter );
		ConfigElement ParseElement( iterator& iter );
		std::vector<std::vector<std::string>> ParseBrackets( iterator& iter );


		void ReplaceVector( std::vector<std::string>& vec, std::vector<std::string> vec2 );
	};


}