#include "tokenizer.h"
#include "token.h"

begin_FILEIO


Tokenizer::Tokenizer()
	: _filename(), _tokens(), _filecontent()
{
}

bool Tokenizer::Tokenize()
{

	if (_filecontent.empty() && !_filename.empty()) {
		std::ifstream fstream( _filename.c_str( ) );

		if (!fstream.is_open())
			return SendMessage({ TokenizerMessage::Error, "File not found", 1002 });


		fstream.seekg(0, std::ios::end);
		auto size = (fstream.tellg());
		fstream.seekg(0, std::ios::beg);

		for ( auto it = std::istreambuf_iterator<char>( fstream ); it != std::istreambuf_iterator<char>( ); ++it )
		{
			_filecontent.push_back( *it );
		}

		//_filecontent.assign((std::istreambuf_iterator<char>(fstream)),
		//	std::istreambuf_iterator<char>());
	}

	SendMessage({ TokenizerMessage::Info, "Read file contents", 0 });

	uint line = 1, char_c = 0;
	_tokens.clear();
	for (auto it = _filecontent.begin(); it < _filecontent.end(); ++it)
	{
		/*

		TODO:
		Implement boolean operators. // DONE //
		Implement scope operators (::). // DONE //
		Implement general characters. // was drunk, dont know what this means tbh
		Implement ++/-- operators. // DONE //
		Implement shifting operators.  // DONE //
		Implement more delimiters (<>, [], '')
		Add keywords (continue, break, switch, case, static, extern, return, class, struct, private, public, const, namespace etc)
		Doing -1 ends up as - (instead of 2 tokens - and 1) (Same with the other operators)
		Implement not operators. (!, !=)
		Implement references.


		*/


		if (*it == '\n')
		{
			_tokens.push_back(Token(token_endl, "endl", line, char_c));
			++line;
		}

		// Parse comment
		else if (*it == '/')
		{
			// Oneline comment
			if (*(++it) == '/')
			{
				while (it < _filecontent.end())
				{
					if (*it == '\n')
						break;
					++it;
				}
			}
			/* Multiline comment */
			else if (*it == '*')
			{
				while (it < _filecontent.end())
				{
					if (*it == '*' && *(it + 1) == '/')
						break;
					++it;
				}
			}
			continue;
		}

		else if (*it == '<')
		{
			if (*(++it) == '<')
				_tokens.push_back(Token(token_left_shift, "<<", line, char_c));
			else if (*it == '=')
				_tokens.push_back(Token(token_less_equal, "<=", line, char_c));
			else
				_tokens.push_back(Token(token_less, "<", line, char_c));
			continue;
		}

		else if (*it == '>')
		{
			if (*(++it) == '>')
				_tokens.push_back(Token(token_right_shift, ">>", line, char_c));
			else if (*it == '=')
				_tokens.push_back(Token(token_greater_equal, ">=", line, char_c));
			else
				_tokens.push_back(Token(token_greater, ">", line, char_c));
			continue;
		}

		else if (*it == '&')
		{
			if (*(++it) == '&')
				_tokens.push_back(Token(token_logical_and, "&&", line, char_c));
			else
				_tokens.push_back(Token(token_address_of, "&", line, char_c));
			continue;
		}

		else if (*it == '|')
		{
			if (*(++it) == '|')
				_tokens.push_back(Token(token_logical_or, "||", line, char_c));
			else
				SendMessage({ TokenizerMessage::Error, "Bitwise operator '|'(or) is not implemented.", line });
			continue;
		}

		else if (*it == ':')
		{
			if (*(++it) == ':')
				_tokens.push_back(Token(token_scope, "::", line, char_c));
			else
				_tokens.push_back(Token(token_colon, ":", line, char_c));
			continue;
		}

		// Parse + or +=
		else if (*it == '+')
		{
			// operator+=
			if (*(++it) == '=')
				_tokens.push_back(Token(token_plus_assign, "+=", line, char_c));
			else if (*it == '+')
				_tokens.push_back(Token(token_increment, "++", line, char_c));
			else // operator+
				_tokens.push_back(Token(token_plus, "+", line, char_c));
			continue;
		}

		// Parse - or -=
		else if (*it == '-')
		{
			if (*(++it) == '=')
				_tokens.push_back(Token(token_minus_assign, "-=", line, char_c));
			else if (*it == '>') // Already forwarded past '-', no need for ++
				_tokens.push_back(Token(token_arrow, "->", line, char_c));
			else if (*it == '-')
				_tokens.push_back(Token(token_decrement, "--", line, char_c));
			else
				_tokens.push_back(Token(token_minus, "-", line, char_c));
			continue;
		}

		// Parse * or *=
		else if (*it == '*')
		{
			if (*(++it) == '=')
				_tokens.push_back(Token(token_multiplies_assign, "*=", line, char_c));
			else
				_tokens.push_back(Token(token_indirect, "*", line, char_c));
			continue;
		}

		// Parse / or /=
		else if (*it == '/')
		{
			if (*(++it) == '=')
				_tokens.push_back(Token(token_divies_assign, "/=", line, char_c));
			else
				_tokens.push_back(Token(token_divides, "/", line, char_c));
			continue;
		}

		// Parse = or ==
		else if (*it == '=')
		{
			if (*(++it) == '=')
				_tokens.push_back(Token(token_compare, "==", line, char_c));
			else
				_tokens.push_back(Token(token_assign, "=", line, char_c));
			continue;
		}

		else if (*it == '!')
		{
			if (*(++it) == '=')
				_tokens.push_back(Token(token_not_compare, "!=", line, char_c));
			else
				_tokens.push_back(Token(token_not, "!", line, char_c));
			continue;
		}

		else if (*it == ' ' || *it == '\t' || *it == '\r' || *it == '\b') // Whitespace
		{
		}

		else if (*it == '{')
			_tokens.push_back(Token(token_bracket_left, "{", line, char_c));

		else if (*it == '}')
			_tokens.push_back(Token(token_bracket_right, "}", line, char_c));

		else if (*it == '(')
			_tokens.push_back(Token(token_parenthesis_left, "(", line, char_c));

		else if (*it == ')')
			_tokens.push_back(Token(token_parenthesis_right, ")", line, char_c));

		else if (*it == '[')
			_tokens.push_back(Token(token_subscript_left, "[", line, char_c));

		else if (*it == ']')
			_tokens.push_back(Token(token_subscript_right, "]", line, char_c));

		else if (*it == ';')
			_tokens.push_back(Token(token_semicolon, ";", line, char_c));

		else if (*it == ',')
			_tokens.push_back(Token(token_comma, ",", line, char_c));

		else if (*it == '.')
			_tokens.push_back(Token(token_dot, ".", line, char_c));

		// Parse a literal string e.g "hello lol"
		else if (*it == '"')
		{
			// Identifier
			__LIB String id = "";
			++it;
			while (it < _filecontent.end())
			{
				if (*it == '"')
					break;
				if (*it == '\n') // String did not end on current line
					return SendMessage({ TokenizerMessage::Error, "String did not end on current line", line });
				// Push back the current character
				id.push_back(*(it++));
			}
			_tokens.push_back({ token_string, id, line, char_c });
		}

		else if (::isdigit((unsigned char)*it))
		{
			// Hexadecimal e.g 0xDE4DBEEF
			if (*it == '0' && *(it + 1) == 'x' || *(it + 1) == 'X')
			{
				__LIB String id = "";
				id.push_back(*(it++)); // 0
				id.push_back(*(it++)); // x
				while (it < _filecontent.end())
				{
					if (!::isxdigit((unsigned char)*it))
						break;
					id.push_back(*(it++));
				}
				_tokens.push_back({ token_hexadecimal, id, line, char_c });
				continue;
			}
			// Decimal e.g 1337
			else
			{
				__LIB String id = "";
				id.push_back(*(it++)); // numerical
				while (it < _filecontent.end())
				{
					if (!::isdigit((unsigned char)*it))
						break;
					id.push_back(*(it++));
				}
				_tokens.push_back({ token_decimal, id, line, char_c });
				continue;
			}
		}

		// Any identifer (e.g a keyword etc etc etc)
		else if (isalpha((unsigned char)*it) || *it == '_')
		{
			__LIB String id = "";
			id.push_back(*(it++)); // Alphameric
			while (it < _filecontent.end())
			{
				if (!::isalnum((unsigned char)*it) && *it != '_')
					break;
				id.push_back(*(it++));
			}
			_tokens.push_back({ token_identifier, id, line, char_c });
			continue;
		}
		else
			_tokens.push_back( { token_unknown, { *it }, line, char_c });
	}
	_tokens.push_back(Token(token_eof, "eof", line, char_c));
	SendMessage({ TokenizerMessage::Info, "End of string reached", line });
	return true;
}

Tokenizer::iterator Tokenizer::begin()
{
	return _tokens.begin();
}

Tokenizer::iterator Tokenizer::end()
{
	return _tokens.end();
}

bool Tokenizer::SendMessage(const TokenizerMessage &msg)
{
	OnMessage( ).Invoke( msg );
	return msg.type != TokenizerMessage::Error;
}

__LIB String Tokenizer::ContentsFile()
{
	return _filecontent;
}

void Tokenizer::Clear()
{
	_msgs.clear();
	_tokens.clear();
	_filename = "";
	_filecontent = "";
}

Event<void, TokenizerMessage>& Tokenizer::OnMessage()
{
	return _OnMessage;
}

Tokenizer * Tokenizer::CreateFromHeader(const __LIB String & contents)
{
	auto token = new Tokenizer();
	token->_filecontent = contents;
	return token;
}

Tokenizer * Tokenizer::CreateFromFile(const __LIB String & file)
{
	auto token = new Tokenizer();
	token->_filename = file;
	return token;
}



TokenizerMessage::TokenizerMessage(const Message_t &type, const __LIB String &msg, const uint &line)
	: type(type), message(msg), line(line)
{
	formated_mesasge = TypeToString(type) + " " + msg + ": " + __LIB to_string(line) + "\n";
}

__LIB String TokenizerMessage::TypeToString(const Message_t & type)
{
	if (type == Error)
		return "[Error]";
	else if (type == Warning)
		return "[Warning]";
	return "[Info]";
}

end_FILEIO