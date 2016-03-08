#pragma once
#include "Utils.h"
#include "Iter.h"



namespace Utils {


	
	class String
	{
	private:
		typedef Iterator<char> fwdIterator;
		typedef ReverseIterator<char> rvrsIterator;
		typedef Iterator<const char> cfwdIterator;
		typedef ReverseIterator<const char> crvrsIterator;
		char* _buffer;
		uint _bufsz;


	private: // Internal functions
		bool __dim( const uint& );
		bool __copy_ct( const char*, const uint& );
		bool __shrink( const uint& );
		bool __append( const char*, uint );
		bool __cmp_s_o( const char*, const char*, uint ) const;
		bool __mi_list( const char&, const String& ) const;
		String __concat( const String&, const String& ) const;
		void __clean( );
		bool __good_wild( const std::pair<uint, uint>&, const String& ) const;

	public: // Consts
		static const uint bad = static_cast<uint>( -1 );
		static const std::pair<uint, uint> bad_pair;

	public: // Ctors / Move Semantics / C++11
		String( );
		String( const String& );
		String( String&& );
		String( const char* );
		String( const char*, uint len );
		~String( );

		void swap( String& );
		String copy( );
		fwdIterator begin( ) const;
		fwdIterator end( ) const;
		cfwdIterator cbegin( ) const;
		cfwdIterator cend( ) const;
		rvrsIterator rbegin( );
		rvrsIterator rend( );
		crvrsIterator crbegin( ) const; 
		crvrsIterator crend( ) const;
		
	public: // String function
		uint length( ) const;
		uint capacity( ) const;
		void push_back( const char& );
		void pop_back( );

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the position of a certain string/char.

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find( '_' );

			// good_pos will be equal to '0'.
			auto good_pos = my_string.find( 'H' );
		---------------------------------------------------------------------------------------------------------------*/
		uint find( const char& ) const;
		uint find( const String& ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the position of a certain string/char.

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

			'off' <uint>
				The offset of where to begin searching.

		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find( '_', 10 );

			// good_pos will be equal to 10U.
			auto good_pos = my_string.find( 'O', 5 );
		---------------------------------------------------------------------------------------------------------------*/
		uint find( const char&, uint off ) const;
		uint find( const String&, uint off ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the first position of a certain string/char.

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find_first_of( 'x' );
			
			// good_pos will be equal to 2U.
			auto good_pos = my_string.find_first_of( "ll" );
		---------------------------------------------------------------------------------------------------------------*/
		uint find_first_of( const char& ) const;
		uint find_first_of( const String& ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the first position of a certain string/char.

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

			

		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find_first_of( 'x', 25 );

			// good_pos will be equal to 2U.
			auto good_pos = my_string.find_first_of( "ll", 1 );
		---------------------------------------------------------------------------------------------------------------*/
		uint find_first_of( const char&, uint off ) const;
		uint find_first_of( const String&, uint off ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the last position of a certain string/char.
			(This is alot faster if the character/string to be found is at the end of the string)

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find_last_of( 'x' );

			// good_pos will be equal to 2U.
			auto good_pos = my_string.find_last_of( "ll" );
		---------------------------------------------------------------------------------------------------------------*/
		uint find_last_of( const char& ) const;
		uint find_last_of( const String& ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the last position of a certain string/char.

		Arguments:
			<const char&> || <const String&>
				The string or character to find.

			'off' <uint>
				The offset to begin searching.


		Return:
			Returns the position of the string/char that was found.
			If it was not found the return value is String::bad.

		Example:
			String my_string = "Hello I'm Oskar";

			// bad_pos will be equal to String::bad.
			auto bad_pos = my_string.find_last_of( 'x', 25 );
	
			// good_pos will be equal to 2U.
			auto good_pos = my_string.find_last_of( "ll", 1 );
		---------------------------------------------------------------------------------------------------------------*/
		uint find_last_of( const char&, uint off ) const;
		uint find_last_of( const String&, uint off ) const;
		
		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Find the position of a certain pattern that begins at 'pat_begin_search'
			and ends at 'pat_end_search' where as find_of_type is a
			list of characters that can be found in the region between
			'pat_begin_search' & 'pat_end_search'. Not every character
			that is inside 'find_of_type' must be found. 

		Arguments:
			'pat_begin_search' <String>
				The string or character where the search shall begin.

			'pat_end_search' <String>
				The string or character where the search shall end. (From the position of 'pat_begin_search')

			'find_of_type' <String>
				The characters that are accepted to be found within the region.
				if this equals "?" then every character is accepted.

		Return:
			Returns a pair of two uint's where the first one is the position of 'pat_begin_search' and the second
			is the offset from 'pat_begin_search' to 'pat_end_search'.
			If the pattern is not found the pair is equal to String::bad. (Both first & second)

		Example:
			String my_string = "hello there [name] i am 20.";
			auto position = find_wild( "[", "]" ); 
			
			my_string.replace( position, "Oskar" );

			std::cout << my_string << std::endl;

		Output of Example:
			hello there Oskar i am 20.
		---------------------------------------------------------------------------------------------------------------*/
		std::pair<uint, uint> find_wild( const String& pat_begin_search, const String& pat_end_search, const String& find_of_type = "?" ) const;

		/*-------------------------------------------------------------------------------------------------------------
			Same as first overload, except the search begins at 'offset'.
		---------------------------------------------------------------------------------------------------------------*/
		std::pair<uint, uint> find_wild( const uint& offset, const String& pat_begin_search, const String& pat_end_search, const String& find_of_type = "?" ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Returns sub string of the current string within the dimensions provided.

		Arguments:
			<const std::pair<uint, uint>&> : !!If bad an exception will be thrown!!
				This is the position/offset where the string should be taken from.
				The first member in the pair is the position where it should start,
				The second member in the pair is how far from the start position it should
				be. (Length)

		Returns:
			Returns a String containing the contents.
		
		Example:
			String my_string = "Hello there [Name] how are you.\n".
			auto pos = my_string.find_wild( "[", "]", "?" );
			
			auto contents = my_string.substr( pos );
			std::cout << contents << std::endl;
			std::cout << my_string;

		Output of example:
			Name
			Hello there [Name] how are you.

		Overloads:
			Other 2 overloads are wrappers for this one.
		---------------------------------------------------------------------------------------------------------------*/
		String substr( const std::pair<uint, uint>& ) const;
		String substr( const uint& pos ) const;
		String substr( const uint& pos, const uint& off ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			If the current string is empty or not.

		Arguments:

		Returns:
			Returns a boolean value wether or not the string is empty.

		Example:
			String string;
			if ( string.empty( ) )
				std::cout << "String is empty" << std::endl;
			
		Output of example:
			String is empty
		---------------------------------------------------------------------------------------------------------------*/
		bool empty( ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			If the current string contains this string.

		Arguments:
			<const String&>
				The string to be searched for inside the current string.

		Returns:
			Returns a boolean value wether or not the current string contains another
			string.

		Example:
			String string = "I like potato";
			if ( string.contains( "potato" ) )
				std::cout << "String contains potato!!" << std::endl;

		Output of example:
			String contains potato!!
		---------------------------------------------------------------------------------------------------------------*/
		bool contains( const String& ) const;

		/**/
		bool hasCapital( ) const;

		/**/
		bool hasNumerical( ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Returns a C null-terminated string.

		Arguments:
			
		Returns:
			The current buffer as a null-terminatd string.

		Example:
			String string = "hello";
			const char* str = string.c_str( );
			std::cout << str << std::endl;

		Output of example:
			hello
		---------------------------------------------------------------------------------------------------------------*/
		const char* c_str( ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Erases part of the current string.

		Arguments:
			<const std::pair<uint, uint>&>
				The part to remove, the first member
				is the start, the second member is the length 
				to remove.

		Returns:
		
		Example:
			String string = "Hello there mr [___]!";
			auto pos = string.find_wild( "[", "]", "_" );
			string.erase( pos ); 

			std::cout << string << std::endl;

		Output of example:
			Hello there mr []!

		Overloads:
			Wrapper for this erase function.
		---------------------------------------------------------------------------------------------------------------*/
		void erase( const std::pair<uint, uint>& );
		void erase( const uint& pos, const uint& off );
		void insert( const std::pair<uint, uint>& pos, const String& strs );
		void insert(const uint& pos, const uint& off, const String& str);
		void insert( const uint& pos, const String& str );
		void append( const String &_Str );

		std::vector<Utils::String> split( const char& splitter ) const;
		std::vector<Utils::String> split( const String& splitter ) const;
		uint amount_of(  );
		uint amount_of_wild( const String &begin, const String &end, const String &type = "?" );
		uint hash( ) const;


		String upper( ) const;
		String lower( ) const;

		template<typename T >
		T to( )
		{
			T t;
			std::stringstream ss( this->_buffer );
			if ( ::isxdigit( (unsigned char)*begin( ) ) )
				ss >> std::hex >> t;
			else
				ss >> t;
			return t;
		}

	public: // Operators
		const String& operator=( const String& );
		const String& operator=( String&& );

		const String& operator+=( const String& );
		const String& operator+=( const char& );

		String operator+( const String& ) const;

		bool operator==( const String& ) const;
		bool operator==( const char& ) const;
	
		bool operator!=( const String& ) const;
		bool operator!=( const char& ) const;

		friend std::ostream& operator<<(std::ostream& os, const String& dt);

	public:
		template<typename _Type>
		static String _Type_to_string( const char* _Fmt, _Type _Val )
		{
			char _Buf[21];
			auto _Len = ::sprintf_s( _Buf, _Fmt, _Val );
			return String( _Buf, _Len );
		}
	};

	
	inline String to_string(int _Val)
	{	// convert int to string
		return (String::_Type_to_string("%d", _Val));
	}

	inline String to_string(unsigned int _Val)
	{	// convert unsigned int to string
		return (String::_Type_to_string("%u", _Val));
	}

	inline String to_string(long _Val)
	{	// convert long to string
		return (String::_Type_to_string("%ld", _Val));
	}

	inline String to_string(unsigned long _Val)
	{	// convert unsigned long to string
		return (String::_Type_to_string("%lu", _Val));
	}

	inline String to_string(long long _Val)
	{	// convert long long to string
		return (String::_Type_to_string("%lld", _Val));
	}

	inline String to_string(unsigned long long _Val)
	{	// convert unsigned long long to string
		return (String::_Type_to_string("%llu", _Val));
	}

	inline String to_string(float _Val)
	{	// convert float to string
		return (String::_Type_to_string("%f", _Val));
	}

	inline String to_string(double _Val)
	{	// convert double to string
		return (String::_Type_to_string("%f", _Val));
	}

	inline String to_string(long double _Val)
	{	// convert long double to string
		return (String::_Type_to_string("%Lf", _Val));
	}

	static std::ostream& operator<<(std::ostream& stream, const String& string)
	{
		stream << string._buffer;
		return stream;
	}

	static Utils::String operator+(const char* lhs, const Utils::String& rhs)
	{
		return Utils::String(lhs) + rhs;
	}


}