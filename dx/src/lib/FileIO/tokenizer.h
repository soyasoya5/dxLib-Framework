#include "lib.h"
#include "token.h"
#include <vector>

begin_FILEIO


class Tokenizer
{
private:
	std::vector<Token> tokens_;
	File file_;
	uint line_;

public:
	using iterator = std::vector<Token>::const_iterator;

public:
	Tokenizer( File file );

	void tokenize( );

	void setFile( File file );

	std::vector<Token>::const_iterator begin( ) const;
	
	std::vector<Token>::const_iterator end( ) const;

private:
	Token get_identifier( std::string::iterator &it, const std::string::iterator &end );
	Token get_literal_string( std::string::iterator &it, const std::string::iterator &end );
	Token get_literal_decimal( std::string::iterator &it, const std::string::iterator &end );
	Token get_literal_hexadecimal( std::string::iterator &it, const std::string::iterator &end );
	Token get_operation( std::string::iterator &it, const std::string::iterator &end );
	
	template<typename Iter>
	bool good( Iter it, Iter end ) { return it < end; }
};


end_FILEIO
