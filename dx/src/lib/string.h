#pragma once
#include "lib.h"
#include "../dx.h"
#include "iter.h"


begin_LIB

class String
{
private:
	typedef Iterator<char> fwdIterator;
	typedef ReverseIterator<char> rvrsIterator;
	typedef Iterator<const char> cfwdIterator;
	typedef ReverseIterator<const char> crvrsIterator;
	char* _buffer;
	::dx::uint _bufsz;


private: // Internal functions (No documentation)
	bool __dim( const ::dx::uint& );
	bool __copy_ct( const char*, const ::dx::uint& );
	bool __shrink( const ::dx::uint& );
	bool __append( const char*, ::dx::uint );
	bool __cmp_s_o( const char*, const char*, ::dx::uint ) const;
	bool __mi_list( const char&, const ::dx::lib::String& ) const;
	::dx::lib::String __concat( const ::dx::lib::String&, const ::dx::lib::String& ) const;
	void __clean( );
	bool __good_wild( const std::pair<::dx::uint, ::dx::uint>&, const ::dx::lib::String& ) const;

public: // Consts
	static const ::dx::uint bad = static_cast<::dx::uint>( -1 );
	static const std::pair<::dx::uint, ::dx::uint> bad_pair;

public: // Ctors / Move Semantics / C++11
	String( );
	String( const ::dx::lib::String& );
	String( ::dx::lib::String&& );
	String( const char* );
	String( const char*, ::dx::uint len );
	String( const std::initializer_list<char> &_List );
	String( std::nullptr_t null );
	template<class _Iter,
			class = typename std::enable_if<std::_Is_iterator<_Iter>::value,void>::type>
	String( _Iter i1, _Iter i2 )
	{
		for ( ; i1 != i2; ++i1 )
			push_back( *i1 );
	}
	
	~String( );

	///<summary>
	///	Swap the contents of the two strings
	///</summary>
	void swap( ::dx::lib::String &_String );

	///<summary>
	/// Return a copy of this string.
	///</summary>
	::dx::lib::String copy( ) const;

	// Iterators
	fwdIterator begin( ) const;
	fwdIterator end( ) const;
	cfwdIterator cbegin( ) const;
	cfwdIterator cend( ) const;
	rvrsIterator rbegin( );
	rvrsIterator rend( );
	crvrsIterator crbegin( ) const; 
	crvrsIterator crend( ) const;
	
public: // ::dx::lib::String function

	///<summary>
	///	Returns the length of the string.
	///</summary>
	::dx::uint length( ) const;

	///<summary>
	/// Returns the current capacity of this string.
	///</summary>
	::dx::uint capacity( ) const noexcept;

	///<summary>
	/// Pushes a character to the back of the string.
	///</summary>
	void push_back( const char& );

	///<summary>
	///	Removes the last character of the string.
	///</summary>
	void pop_back( );

	///<summary>
	///	Finds the position of a character within this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find( const char &_Character ) const;

	///<summary>
	///	Finds the start position of a sequence within this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find( const ::dx::lib::String &_Sequence ) const;

	///<summary>
	///	Finds the position of a character within this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find( const char &_Character, ::dx::uint _Offset ) const;

	///<summary>
	///	Finds the start position of a sequence within this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find( const ::dx::lib::String &_Sequence, ::dx::uint _Offset ) const;

	///<summay>
	/// Find the first reference of '_Character' in this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_first_of( const char &_Character ) const;

	///<summary>
	/// Find the first reference of '_Sequence' in this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_first_of( const ::dx::lib::String &_Sequence ) const;

	///<summary>
	/// Find the first reference of '_Character' in this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_first_of( const char &_Character, ::dx::uint _Offset ) const;

	///<summary>
	/// Find the first reference of '_Sequence' in this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_first_of( const ::dx::lib::String &_Sequence, ::dx::uint _Offset ) const;

	///<summary>
	/// Find the last reference of '_Character' in this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_last_of( const char &_Character ) const;

	///<summary>
	/// Find the last reference of '_Sequence' in this string.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_last_of( const ::dx::lib::String &_Sequence ) const;

	///<summary>
	/// Find the last reference of '_Character' in this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_last_of( const char &_Character, ::dx::uint _Offset ) const;

	///<summary>
	/// Find the last reference of '_Sequence' in this string, the search starts at '_Offset'.
	/// If it fails to find it returns String::bad
	///</summary>
	::dx::uint find_last_of( const ::dx::lib::String &_Sequence, ::dx::uint _Offset ) const;
	
	///<summary>
	/// Find the position of a certain pattern that begins at 'pat_begin_search'
	///	and ends at 'pat_end_search' where as find_of_type is a
	///	list of characters that can be found in the region between
	///	'pat_begin_search' & 'pat_end_search'.Not every character
	///	that is inside 'find_of_type' must be found.
	/// If the pattern is not found it returns String::bad_pair
	///</summary>
	std::pair<::dx::uint, ::dx::uint> find_wild( const ::dx::lib::String &_Begin_seq, const ::dx::lib::String &_End_seq, const ::dx::lib::String &_Types = "?" ) const;

	///<summary>
	/// Find the position of a certain pattern that begins at 'pat_begin_search'
	///	and ends at 'pat_end_search' where as find_of_type is a
	///	list of characters that can be found in the region between
	///	'pat_begin_search' & 'pat_end_search'.Not every character
	///	that is inside 'find_of_type' must be found.
	/// Search starts at '_Offset'
	/// If the pattern is not found it returns String::bad_pair
	///</summary>
	std::pair<::dx::uint, ::dx::uint> find_wild( const ::dx::uint &_Offset, const ::dx::lib::String &_Begin_seq, const ::dx::lib::String &_End_seq, const ::dx::lib::String &_Types = "?" ) const;

	///<summary>
	/// Returns a a sub-string of the characters within the dimension provided. 
	///</summary>
	::dx::lib::String substr( const std::pair<::dx::uint, ::dx::uint>& _Pair ) const;

	///<summary>
	/// Returns a a sub-string of the characters from _Position to the end.
	///</summary>
	::dx::lib::String substr( const ::dx::uint &_Position ) const;

	///<summary>
	/// Returns a a sub-string of the characters within the dimension provided. 
	///</summary>
	::dx::lib::String substr( const ::dx::uint &_Position, const ::dx::uint &_Offset ) const;

	///<summary>
	///	Wether or not this string is empty.
	///</summary>
	bool empty( ) const;

	///<summary>
	/// Returns wether or not this string contains a sequence of characters that matches '_Sequence'
	///</summary>
	bool contains( const ::dx::lib::String &_Sequence ) const;

	///<summary>
	///	Returns wether or not this string contains a capital character.
	///</summary>
	bool hasCapital( ) const;

	///<summary>
	///	Returns wether or not this string contains a numerical character.
	///</summary>
	bool hasNumerical( ) const;


	///<summary>
	/// Returns a C null terminated string.
	///</summary>
	const char* c_str( ) const;

	///<summary>
	///	Erases the sequence of characters within the dimension provided.
	/// NOTE: This does not do valid checks.
	///</summary>
	void erase( const std::pair<::dx::uint, ::dx::uint> &_Streampos );

	///<summary>
	/// Erases the sequence of characters within the dimension provided.
	/// NOTE: This does not do valid checks.
	///</summary>
	void erase( const ::dx::uint &_Position, const ::dx::uint &_Length );

	///<summary>
	/// Inserts '_Sequence' within the dimensions provided.
	/// NOTE: This does not do valid checks.
	///</summary>
	void insert( const std::pair<::dx::uint, ::dx::uint> &_Streampos, const ::dx::lib::String &_Sequence );

	///<summary>
	/// Inserts '_Sequence' within the dimensions provided.
	/// NOTE: This does not do valid checks.
	///</summary>
	void insert(const ::dx::uint &_Position, const ::dx::uint &_Length, const ::dx::lib::String &_Sequence);

	///<summary>
	/// Inserts '_Sequence' at _Position untill end, meaning even if _Sequence is less than 
	/// (Length - _Positon) everything from _Position and forward will be erased.
	/// NOTE: This does not do valid checks.
	///</summary>
	void insert( const ::dx::uint &_Position, const ::dx::lib::String &_Sequence );

	///<summary>
	/// Appends '_Sequence' to the back of the string.
	///</summary>
	void append( const ::dx::lib::String &_Sequence );

	///<summary>
	/// Sets the capacity of this string to _Size, this is independant from the length of the string.
	/// NOTE: This erases all the contents of this string.
	///</summary>
	void reserve( const ::dx::uint &_Size );
	
	///<summary>
	/// Replaces each character with the range of characters from it1 and it2.
	/// This does not resize the buffer and can only assign as far as the current
	/// capacity of the string.
	///</summary>
	template<typename Iter>
	void assign( Iter it1, Iter it2 )
	{	// Assign
		auto myIt = CreateIterator<char>( _buffer, _bufsz ), myEnd = CreateIterator<char>( _buffer, _bufsz, _bufsz );
		while( myIt < myEnd && it1 != it2 )
		{
			*myIt = *it1;
			++it1;
			++myIt;
			continue;
		}
		*myIt = '\0';
	}

	///<summary>
	/// Replaces each character with the range of characters from it1 and it2.
	/// This does not resize the buffer and can only assign as far as the current
	/// capacity of the string.
	/// Specialization for String::fwdIterator.
	///</summary>
	template<>
	void assign<String::fwdIterator>( fwdIterator it1, fwdIterator it2 )
	{
		auto myIt = begin( ), myEnd = end( );
		for ( ; it1 < it2 && myIt < myEnd; ++it1, ++myIt )
			*myIt = *it1;
	}

	///<summary>
	/// Splits the string into a vector of strings.
	///</summary>
	std::vector<::dx::lib::String> split( const char& _Splitter ) const;

	///<summary>
	/// Splits the string into a vector of strings.
	///</summary>
	std::vector<::dx::lib::String> split( const ::dx::lib::String &_Splitter ) const;

	///<summary>
	/// A simple hash algorithm.
	///</summary>
	::dx::uint hash( ) const;

	///<summary>
	/// Returns a copy of this string in all capital letters.
	///</summary>
	::dx::lib::String upper( ) const;

	///<summary>
	/// Returns a copy of this string in all lower letters.
	///</summary>
	::dx::lib::String lower( ) const;

	///<summary>
	/// Convert this string to T using std::stringstream.
	///</summary>
	template<typename T >
	T to( ) const
	{
		T t = T();
		std::stringstream ss( this->_buffer );
		if ( ::isdigit( *begin( ) ) )
			ss >> t;
		else if ( ::isxdigit( (unsigned char)*begin( ) ) )
			ss >> std::hex >> t;
		return t;
	}

	///<summary>
	/// Static function for initialzing this string from T.
	///</summary>
	template<typename T>
	static ::dx::lib::String from( T&& _Tx )
	{
		return ::dx::lib::to_string( _Tx );
	}

	///<summary>
	/// Returns a copy of this string that is filled with '_Filler'.
	///</summary>
	String fill( const char &_Filler ) const;

	///<summary>
	/// Counts the amount of references of character
	///</summary>
	uint count( const char &_Character ) const;

public: 
	///<summary>
	/// Assigns this string to '_Rhs'.
	///</summary>
	const ::dx::lib::String& operator=( const ::dx::lib::String &_Rhs );

	///<summary>
	/// Swaps this string with '_Rhs'.
	///</summary>
	const ::dx::lib::String& operator=( ::dx::lib::String &&_Rhs );

	///<summary>
	/// Appends this string with '_Rhs'.
	///</summary>
	const ::dx::lib::String& operator+=( const ::dx::lib::String &_Rhs );

	///<summary>
	/// Appends this string with '_Rhs'.
	///</summary>
	const ::dx::lib::String& operator+=( const char &_Rhs );

	///<summary>
	/// Returns this string concatinated with '_Rhs'.
	///</summary>
	::dx::lib::String operator+( const ::dx::lib::String &_Rhs ) const;

	///<summary>
	/// Compares this string with '_Rhs'.
	///</summary>
	bool operator==( const ::dx::lib::String &_Rhs ) const;

	///<summary>
	/// Compares this string with '_Rhs'.
	///</summary>
	bool operator==( const char &_Rhs ) const;

	///<summary>
	/// Compares this string with '_Rhs' and returns true if they are NOT equal.
	///</summary>
	bool operator!=( const ::dx::lib::String &_Rhs ) const;

	///<summary>
	/// Compares this string with '_Rhs' and returns true if they are NOT equal.
	///</summary>
	bool operator!=( const char &_Rhs ) const;

	///<summary>
	/// Adds support for using std::ostream.
	///</summary>
	friend std::ostream& operator<<(std::ostream& os, const ::dx::lib::String& dt);

public:

	///<summary>
	/// Performs a sprintf_s operator to create a string from a numerical value.
	///</summary>
	template<typename _Type>
	static ::dx::lib::String _Type_to_string( const char* _Fmt, _Type _Val )
	{
		char _Buf[21];
		auto _Len = ::sprintf_s( _Buf, _Fmt, _Val );
		return ::dx::lib::String( _Buf, _Len );
	}
};


inline ::dx::lib::String to_string(int _Val)
{	// convert int to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%d", _Val));
}

inline ::dx::lib::String to_string(unsigned int _Val)
{	// convert unsigned int to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%u", _Val));
}

inline ::dx::lib::String to_string(long _Val)
{	// convert long to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%ld", _Val));
}

inline ::dx::lib::String to_string(unsigned long _Val)
{	// convert unsigned long to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%lu", _Val));
}

inline ::dx::lib::String to_string(long long _Val)
{	// convert long long to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%lld", _Val));
}

inline ::dx::lib::String to_string(unsigned long long _Val)
{	// convert unsigned long long to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%llu", _Val));
}

inline ::dx::lib::String to_string(float _Val)
{	// convert float to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%f", _Val));
}

inline ::dx::lib::String to_string(double _Val)
{	// convert double to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%f", _Val));
}

inline ::dx::lib::String to_string(long double _Val)
{	// convert long double to ::dx::lib::String
	return (::dx::lib::String::_Type_to_string("%Lf", _Val));
}

static std::ostream& operator<<(std::ostream& stream, const ::dx::lib::String &_Rhs)
{
	stream << _Rhs._buffer;
	return stream;
}

static ::dx::lib::String operator+(const char* _Lhs, const ::dx::lib::String& _Rhs)
{
	return ::dx::lib::String(_Lhs) + _Rhs;
}




end_LIB