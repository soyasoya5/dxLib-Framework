#include "string.h"



begin_LIB


const std::pair<uint, uint> String::bad_pair = std::pair<uint, uint>{ static_cast<uint>( -1 ), static_cast<uint>( -1 ) };

bool String::__dim(const uint &sz)
{
	if (sz < _bufsz)
		return true;

	uint newsz = sz + 5;
	char* newbuf = new char[ newsz ];
	if ( !::memset( (byte*)( newbuf ), 0, newsz ) ) {
		delete[newsz] newbuf;
		return false;
	}

	::memcpy( (byte*)( newbuf ), (byte*)( _buffer ), _bufsz );
	__clean( );
	_buffer = newbuf;
	_bufsz = newsz;
	return true;
}

void String::__clean()
{
	delete[_bufsz] _buffer;
	_buffer = nullptr;
}

bool String::__good_wild(const std::pair<uint, uint>& pos, const String& pat ) const
{
	if ( pos.first == bad || pos.second == bad )
		return false;

	if ( pat == "?" )
		return true;
	for ( auto it = begin( ) + pos.first, end = begin( ) + pos.first + pos.second; it < end; ++it )
	{
		if ( !__mi_list( *it, pat ) )
			return false;
	}
	return true;
}

bool String::__copy_ct(const char *str, const uint &sz)
{
	if ( !__dim( sz ) )
		return false;
	return ::memcpy( (byte*)( _buffer ), (byte*)( str ), sz );
}

bool String::__shrink(const uint& newsz)
{
	if (newsz >= _bufsz) // Cant shrink to a greater value...
		return false;
	uint onewsz = newsz;

	onewsz += 5;
	char* newbuf = new char[ onewsz ];
	if ( !::memset( (byte*)( newbuf ), 0, newsz ) ) {
		delete[newsz] newbuf;
		return false;
	}

	::memcpy( (byte*)( newbuf ), (byte*)( _buffer ), newsz );
	__clean( );
	_buffer = newbuf;
	_bufsz = onewsz;
	return true;
}

bool String::__append(const char *str, uint sz)
{
	uint len = length( );
	if ( !__dim( len + sz ) )
		return false;;

	while( sz )
	{
		_buffer[len] = *str;
		++len, ++str;
		--sz;
	}
	return true;
}

bool String::__cmp_s_o(const char *str, const char* str2, uint len) const
{
	while( len ) {
		if ( *str != *str2)
			return false;
		++str, ++str2;
		--len;
	}
	return true;
}

bool String::__mi_list(const char &c, const String &str) const
{
	if ( c == '?' )
		return true;
	for ( auto& x : str )
		if ( x == c )
			return true;
	return false;
}

String String::__concat(const String &s1, const String &s2) const
{
	return s1 + s2;
}

String::String()
	: _buffer(nullptr), _bufsz(0)
{
	_buffer = new char[20];
	_bufsz = 20;
	::memset( (byte*)( _buffer ), 0, _bufsz );
}

String::String(const String &str)
	: String( )
{
	if ( !__copy_ct( str._buffer, str._bufsz ) )
		throw;
}

String::String(String &&str)
	: String( )
{
	swap(str);
}

String::String(const char *str)
	: String( )
{
	__copy_ct( str, strlen(str) );
	
}

String::String(const char *str, uint len)
	: String( )
{
	__copy_ct( str, len );
}

String::String(const std::initializer_list<char>& _List)
{
	for ( auto it = _List.begin( ); it < _List.end( ); ++it )
		push_back( *it );
}

String::~String()
{
	__clean( );
}

void String::swap(String &str)
{
	std::swap( _buffer, str._buffer );
	std::swap( _bufsz, str._bufsz );
}

String String::copy()
{
	return String( *this );
}

String::fwdIterator String::begin() const
{
	return CreateIterator( _buffer, length( ) );
}

String::fwdIterator String::end() const
{
	return CreateIterator( _buffer, length( ), length( ) );
}

String::cfwdIterator String::cbegin() const
{
	return CreateIterator<const char>( _buffer, length( ) );
}

String::cfwdIterator String::cend() const
{
	return CreateIterator<const char>(_buffer, length( ), length( ) );
}

String::rvrsIterator String::rbegin()
{
	return CreateReverseIterator( _buffer, length( ) );
}

String::rvrsIterator String::rend()
{
	return CreateReverseIterator( _buffer, length( ), length( ) );
}

String::crvrsIterator String::crbegin() const
{
	return CreateReverseIterator<const char>( _buffer, length( ) );
}

String::crvrsIterator String::crend() const
{
	return CreateReverseIterator<const char>( _buffer, length( ), length( ) );
}

uint String::length() const
{
	return ::strlen( _buffer );
}

uint String::capacity() const
{
	return _bufsz;
}

void String::push_back(const char &c)
{
	if ( !__dim( strlen( _buffer ) + 1 ) )
		throw;
	_buffer[ strlen( _buffer ) ] = c;
}

void String::pop_back()
{
	_buffer[ strlen( _buffer ) - 1 ] = 0;
}

uint String::find(const char &c) const
{
	return find( c, 0 );
}

uint String::find(const String &str) const
{
	return find( str, 0 );
}

uint String::find(const char &c, uint off) const
{
	if ( off >= length( ) )
		return bad;
	for ( auto it = begin( ) + off; it < end( ); ++it )
		if ( *it == c )
			return it.index( );
	return bad;
}

uint String::find(const String &str, uint off) const
{
	auto len = length( ), slen = str.length( );
	if ( off > len )
		return bad;
	for ( auto it = begin( ) + off; it < end( ); ++it)
	{
		if ( it.index( ) + slen > len)
			break;
		if ( __cmp_s_o( str._buffer, it.get( ), slen ) )
			return it.index( );
	}
	return bad;
}

uint String::find_first_of(const char &c) const
{
	return find( c, 0 );
}

uint String::find_first_of(const String &str) const
{
	return find( str, 0 );
}

uint String::find_first_of(const char &c, uint off) const
{
	return find(c, off);
}

uint String::find_first_of(const String &str, uint off) const
{
	return find(str, off);
}

uint String::find_last_of(const char &c) const
{
	 return find_last_of( c, 0 );
}

uint String::find_last_of(const String &str) const
{ 
	return find_last_of( str, 0 );
}

uint String::find_last_of(const char &c, uint off) const
{
	if ( off > length( ) )
		return bad;
	uint last = bad;
	for ( auto it = begin( ) + off; it < end( ); ++it )
		if ( *it == c )
			last = it.index( );
	return last;
}

uint String::find_last_of(const String &str, uint off) const
{
	if ( off > length( ) )
		return bad;
	uint last = bad;
	auto slen = str.length( ), len = length( );
	for ( auto it = begin( ) + off; it < end( ); ++it )
	{
		if ( it.index( ) + slen > len )
			return last;
		if ( __cmp_s_o( str._buffer, it.get( ), slen ) )
			last = it.index( );
	}
	return last;
}

std::pair<uint, uint> String::find_wild(const String & pat_begin_search, const String & pat_end_search, const String & find_of_type) const
{
	return find_wild( 0, pat_begin_search, pat_end_search, find_of_type );
}

std::pair<uint, uint> String::find_wild(const uint & offset, const String & pat_begin_search, const String & pat_end_search, const String & find_of_type) const
{
	auto pat_begin = find( pat_begin_search, offset );
	if ( pat_begin == bad )
		return bad_pair;
	++pat_begin;

	auto pat_end = find( pat_end_search, pat_begin );
	if ( pat_end == bad )
		return bad_pair;


	if ( __good_wild( { pat_begin, pat_end - pat_begin }, find_of_type ) )
		return { pat_begin, pat_end - pat_begin };

	while( pat_begin != bad && pat_end != bad )
	{
		pat_begin = find( pat_begin_search, pat_begin + 1 );
		if ( pat_begin == bad )
			return bad_pair;
		++pat_begin;

		pat_end = find( pat_end_search, pat_begin );
		if ( pat_end == bad )
			return bad_pair;

		if ( __good_wild( { pat_begin, pat_end - pat_begin }, find_of_type ) )
			return { pat_begin, pat_end - pat_begin };
	}
	return bad_pair;
}

String String::substr(const std::pair<uint, uint> &pos) const 
{
	if ( pos.second == bad )
		return "";

	char* buffer = new char[ pos.second + 1 ];
	if ( !::memcpy( (byte*)( buffer ), (byte*)( &_buffer[pos.first] ), pos.second ) )
		return "";
	buffer[pos.second] = '\0';
	return buffer;
}

String String::substr(const uint &pos) const
{
	return substr( { pos, length( ) - pos } );
}

String String::substr(const uint &pos, const uint &off) const
{
	return substr( { pos, off } );
}
 
bool String::empty() const
{
	return length( ) == 0;
}

bool String::contains(const String &str) const
{
	return find( str ) != bad;
}

bool String::hasCapital() const
{
	for ( auto&x : *this )
		if ( x > 'A' && x < 'Z' )
			return true;
	return false;
}

bool String::hasNumerical() const
{
	for ( auto&x : *this )
		if ( x > '0' && x < '9' )
			return true;
	return false;
}

const char * String::c_str() const
{
	return _buffer;
}

void String::erase(const uint & pos, const uint & off)
{
	return erase( { pos, off } );
}

void String::erase(const std::pair<uint, uint>& pos)
{
	auto str = __concat( substr( 0, pos.first ), substr( pos.first + pos.second ) );
	__copy_ct( str._buffer, str.length( ) + 1 );
}

void String::reserve(const __DX uint & _Size)
{
	__clean( );
	this->_buffer = new char[_Size];
	this->_bufsz = _Size;
	*_buffer = '\0';
}

void String::insert(const std::pair<uint, uint>& pos, const String & str)
{
	auto len = str.length( );
	__dim( length( ) + len );
	
	auto str_in = __concat( substr( 0, pos.first ), str );
	*this = __concat( str_in, substr( pos.first, pos.second ) );
}

void String::insert(const uint & pos, const uint & off, const String & str)
{
	return insert( { pos, off }, str );
}

void String::insert(const uint &pos, const String &str)
{
	return insert( { pos, str.length( ) } , str );
}

void String::append(const String & _Str)
{
	__append( _Str.c_str( ), _Str.length( ) );
}

std::vector<String> String::split(const char & splitter) const
{
	std::vector<String> ret;
	uint pos = 0;
	auto copy = *this;
	while( true )
	{
		pos = copy.find( splitter, pos );
		if ( pos != bad )
		{
			ret.push_back( copy.substr( 0, pos ) );
			copy.erase( 0, pos + 1 );
		}
		else
		{
			if ( !copy.empty( ) )
				ret.push_back( copy );
			break;
		}
	}
	return ret;
}

std::vector<String> String::split(const String& splitter) const
{
	std::vector<String> ret;
	uint pos = 0;
	auto copy = *this;
	while( true )
	{
		pos = copy.find( splitter );
		if ( pos != bad )
		{
			ret.push_back( copy.substr( 0, pos ) );
			copy.erase( 0, pos + 1 );
		}
		else
		{
			if ( !copy.empty( ) )
				ret.push_back( copy );
			break;
		}
	}
	return ret;
}

uint String::hash() const
{
	uint hash = 0x0;
	for ( const auto&x : *this )
		hash += x ^ ( rand( ) % 255 + 1 );
	return hash;
}



String String::upper() const
{
	String ret = *this;
	for ( auto& x : ret )
		x = ::toupper( x );
	return std::move( ret );
}

String String::lower() const
{
	String ret = *this;
	for ( auto& x : ret )
		x = ::tolower( x );
	return std::move( ret );
}

const String & String::operator=(const String &str)
{
	__copy_ct( str._buffer, str._bufsz );
	return *this;
}

const String & String::operator=(String &&str)
{
	swap( str );
	return *this;
}


const String & String::operator+=(const String &str)
{
	__append( str._buffer, strlen( str._buffer ) );
	return *this;
}


const String & String::operator+=(const char &c)
{
	push_back( c );
	return *this;
}

String String::operator+(const String &str) const
{
	String string = *this;
	string.__append( str._buffer, str.length( ) );
	return std::move( string );
}


bool String::operator==(const String &str) const
{
	return ::strcmp( str._buffer, _buffer ) == 0;
}

bool String::operator==(const char &c) const
{
	return *_buffer == c;
}

bool String::operator!=(const String &str) const
{
	return !operator==( str );
}


bool String::operator!=(const char &c) const
{
	return !operator==( c );
}

end_LIB