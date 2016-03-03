#include "Config.h"



namespace FileIO
{

	char Tokenizer::getNextChar()
	{
		if ( _file.empty( ) )
			return '\0'; // eof
		char c = *_file.begin( );
		_file.erase( _file.begin() );
		++_count;


		if ( c == '\n' ) 
			++_line;
		return c;
	}

	Tokenizer::Token Tokenizer::getNewToken()
	{
		while (c == ' ') {
			c = getNextChar();
			if (c == '\0')
				return Token( eToken_eof, "\0", _count, _line);
			if (c == '\n')
				return Token( eToken_endl, "\n", _count, _line );
		}
		if (isalpha((unsigned char)c))
		{
			std::string id = "";
			while (isalnum((unsigned char)c) || c == '_')
			{
				id += c;
				c = getNextChar();
			}
			if (id == "if")
				return Token(eToken_if, id, _count, _line);
			else if (id == "class")
				return Token(eToken_class, id, _count, _line);
			else if (id == "else")
				return Token(eToken_else, id, _count, _line);
			else if (id == "while")
				return Token(eToken_while, id, _count, _line);
			else if (id == "for")
				return Token(eToken_for, id, _count, _line);
			else if (id == "foreach")
				return Token(eToken_foreach, id, _count, _line);
			else if (id == "int")
				return Token(eToken_int, id, _count, _line);
			else if (id == "float")
				return Token(eToken_float, id, _count, _line);
			else if (id == "double")
				return Token(eToken_double, id, _count, _line);
			else if (id == "long")
				return Token(eToken_long, id, _count, _line);
			else if (id == "char")
				return Token(eToken_char, id, _count, _line);
			else if (id == "string")
				return Token(eToken_string, id, _count, _line);
			else if (id == "void")
				return Token(eToken_void, id, _count, _line);
			else if (id == "extern")
				return Token(eToken_extern, id, _count, _line);
			else if (id == "pointer")
				return Token(eToken_pointer, id, _count, _line);
			else if (id == "macro")
				return Token(eToken_macro, id, _count, _line);
			else
				return Token(eToken_identifier, id, _count, _line);
		}
		else if (isdigit((unsigned char)c))
		{
			std::string dig = "";
			while (isdigit((unsigned char)c))
			{
				dig.push_back(c);
				c = getNextChar();
				if (c == '.') {
					dig.push_back(c);
					c = getNextChar();
				}
			}
			return Token(eToken_numerical, dig, _count, _line);
		}
		else if (isop(c))
		{
			std::string id;
			id += c;
			c = getNextChar();
			if (isop(c))
			{
				id += c;
				c = getNextChar( );
				if (id == "==")
					return Token(eToken_equalsEquals, id, _count, _line);
				else if (id == "!=")
					return Token(eToken_notEquals, id, _count, _line);
				else if (id == "+=")
					return Token(eToken_plusEquals, id, _count, _line);
				else if (id == "-=")
					return Token(eToken_minusEquals, id, _count, _line);
				else if (id == "*=")
					return Token(eToken_timesEquals, id, _count, _line);
				else if (id == "/=")
					return Token(eToken_slashEquals, id, _count, _line);
				else if (id == "->")
					return Token(eToken_operatorAccess, id, _count, _line);
				else if (id == "//")
					return Token(eToken_comment, id, _count, _line);
			}

			if (id == "=")
				return Token(eToken_equals, id, _count, _line);
			else if (id == "!")
				return Token(eToken_not, id, _count, _line);
			else if (id == "+")
				return Token(eToken_plus, id, _count, _line);
			else if (id == "-")
				return Token(eToken_minus, id, _count, _line);
			else if (id == "*")
				return Token(eToken_times, id, _count, _line);
			else if (id == "/")
				return Token(eToken_slash, id, _count, _line);
			return Token(eToken_eof, id, _count, _line);
		}
		std::string id;
		id.push_back(c);
		switch (c)
		{
		case '"':
		{
			c = getNextChar();
			while ( c != '\0' )
			{
				id.push_back( c );
				c = getNextChar( );
				if ( c == '"' ) {
					id.push_back( c );
					c = getNextChar( );
					break;
				}
			}
			return Token(eToken_string, id, _count, _line);
		}
		case ';':
			c = getNextChar();
			return Token(eToken_semicolon, id, _count, _line);
		case ')':
			c = getNextChar();
			return Token(eToken_RightParanthesis, id, _count, _line);
		case '(':
			c = getNextChar();
			return Token(eToken_leftParanthesis, id, _count, _line);
		case '&':
		{
			auto x = getNextChar();
			if (x != '&')
			{
				c = x;
				return Token(eToken_unknown, id, _count, _line);
			}
			id.push_back(x);
			c = getNextChar();
			return Token(eToken_operator_and, id, _count, _line);
		}
		case '|':
		{
			auto x = getNextChar();
			if (x != '|')
			{
				c = x;
				return Token(eToken_unknown, id, _count, _line);
			}
			id.push_back(x);
			c = getNextChar();
			return Token(eToken_operator_and, id, _count, _line);
		}
		}
		c = getNextChar();
		if (c == '\0')
			return Token(eToken_eof, "eof", _count, _line);
		return Token(eToken_unknown, id, _count, _line); // Unknown (user defined operators or similiar)
	}

	bool Tokenizer::isop(const char& c) const noexcept
	{
		return c == '=' || c == '!' || c == '&' || c == '|' || c == '/' || c == '*'
			|| c == '-' || c == '+' || c == '%' || c == '>' || c == '<';
	}

	Tokenizer::Token Tokenizer::getNextToken()
	{
		Token tok = getNewToken();
		_prevToken = _currToken;
		_currToken = tok;
		_previousTokens.push_back(_currToken);
		return _currToken;
	}

	Tokenizer::Token Tokenizer::getCurrToken()
	{
		return _currToken;
	}

	Tokenizer::Token Tokenizer::getPrevToken()
	{
		return _prevToken;
	}

	Tokenizer::Token Tokenizer::getTokenAt(size_t index)
	{
		return _previousTokens[index];
	}

	::size_t Tokenizer::getCurrTokenIndex()
	{
		return _previousTokens.size();
	}

	::size_t Tokenizer::getPrevTokenIndex()
	{
		return getCurrTokenIndex() - 1;
	}

	std::uintptr_t Tokenizer::getCharCount()
	{
		return _count;
	}

	std::string Tokenizer::TokToString(eToken tok)
	{
#define CASIFY(x) case x: return #x;
		switch (tok)
		{
			CASIFY(eToken_eof);
			CASIFY(eToken_import);
			CASIFY(eToken_leftParanthesis);
			CASIFY(eToken_RightParanthesis);
			CASIFY(eToken_operatorAccess);
			CASIFY(etoken_quote);
			CASIFY(eToken_plus);
			CASIFY(eToken_minus);
			CASIFY(eToken_times);
			CASIFY(eToken_slash);
			CASIFY(eToken_equals);
			CASIFY(eToken_not);
			CASIFY(eToken_plusEquals);
			CASIFY(eToken_equalsEquals);
			CASIFY(eToken_notEquals);
			CASIFY(eToken_minusEquals);
			CASIFY(eToken_slashEquals);
			CASIFY(eToken_timesEquals);
			CASIFY(eToken_semicolon);
			CASIFY(eToken_numerical);
			CASIFY(eToken_identifier);
			CASIFY(eToken_if);
			CASIFY(eToken_else);
			CASIFY(eToken_while);
			CASIFY(eToken_for);
			CASIFY(eToken_foreach);
			CASIFY(eToken_int);
			CASIFY(eToken_float);
			CASIFY(eToken_double);
			CASIFY(eToken_long);
			CASIFY(eToken_char);
			CASIFY(eToken_string);
			CASIFY(eToken_void);
			CASIFY(eToken_unknown);
		}


	}

	void Tokenizer::Tokenize()
	{
		_previousTokens.clear();
		getNextToken();
		while (getCurrToken() != eToken_eof)
			getNextToken();
	}

	void Tokenizer::Release()
	{
		_file = "";
		c = EOF;
		_previousTokens.clear();
		_currToken.string = "";
		_currToken.tok = eToken_eof;
		_prevToken.string = "";
		_prevToken.tok = eToken_eof;
	}

	std::string ReadFile(std::string file)
	{
		std::ifstream t(file);
		std::string str;

		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);
		str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		return str;
	}

	bool ConfigElement::__dim(const uint &idx)
	{
		if (idx <= _values.size())
			return true;
		return false;
	}

	bool ConfigElement::__dim(const uint &pos, const uint &pos2)
	{
		return __dim( pos ) && pos2 < _values[pos].size( );
	}


	std::string ConfigElement::Value(const uint & val_idx, const uint & val_idx_arr)
	{
		if ( !__dim( val_idx, val_idx_arr ) )
			return "";
		return _values[val_idx][val_idx_arr];
	}

	bool ConfigElement::setValue(const uint & val_idx, const uint & val_idx_arr, const std::string & value)
	{
		if ( !__dim( val_idx, val_idx_arr ) )
			return false;
		_values[val_idx][val_idx_arr] = value;
		return true;
	}

	bool Config::Parse()
	{
		if ( _file.empty( ) )
			return false;
		Tokenizer tokenizer{ ReadFile( _file ) };
		tokenizer.Tokenize( );
		for (auto it = tokenizer.begin( ); it != tokenizer.end( ); ++it)
		{
			if ( IsComment( it ) )
			{
				EatComment( it );
				continue;
			}

			auto element = ParseElement( it );
			if ( element.Array( ).empty( ) || element.Name( ).empty( ) )
				continue;
			if ( Exists( element.Name( ) ) )
			{
				auto el = Element( element.Name( ) );
				el.Array() = element.Array( );
			}
			else 
				_elems.push_back( element );
		}
		
		return true;
	}

	ConfigElement& Config::Element(const std::string & name)
	{
		for (auto&x : _elems)
			if (x.Name() == name)
				return x;
		ConfigElement{};
	}

	ConfigElement& Config::Element(const uint & idx)
	{
		return _elems[idx];
	}

	bool Config::Exists(const std::string &name)
	{
		for (auto&x : _elems)
			if (x.Name() == name)
				return true;
		return false;
	}

	bool Config::IsComment(iterator iter)
	{
		return *iter == "//";
	}

	void Config::EatComment(iterator &iter)
	{
		while (*iter != FileIO::Tokenizer::eToken_eof && *iter != "\n")
			++iter;
	}

	ConfigElement Config::ParseElement(iterator &iter)
	{
		if (*iter != Tokenizer::eToken_identifier)
			return{};
		ConfigElement element;
		element.Name() = iter->string;
		
		if (*(++iter) != Tokenizer::eToken_equals)
			return element;
		++iter;

		if (*iter == "[")
		{
			auto vec =  ParseBrackets(iter);
			//ReplaceVector( element.Array(), vec );
			element.Array( ) = vec;
		}
		return element;
	}

	std::vector<std::vector<std::string>> Config::ParseBrackets(iterator &iter)
	{
		std::vector<std::vector<std::string>> ret;
		if (*iter != "[")
			return ret;
		++iter;

		while (*iter != "]" && *iter != Tokenizer::eToken_eof)
		{
			std::vector<std::string> _vals;
			if ( *iter == "," ) {
				++iter;
				continue;
			}

			if ( *iter == "{" && *iter != Tokenizer::eToken_eof)
			{
				++iter;
				while ( *iter != "}" && *iter != Tokenizer::eToken_eof)
				{
					if (*iter == ",") {
						++iter;
						continue;
					}
					_vals.push_back(iter->string);
					++iter;
				}
			}

			ret.push_back( _vals );
			++iter;
		}

		return ret;
	}

	void Config::ReplaceVector(std::vector<std::string>& vec, std::vector<std::string> vec2)
	{
		vec.clear();
		for (auto&x : vec2)
			vec.push_back(x);
	}

}


