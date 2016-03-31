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
		__DX uint _bufsz;


	private: // Internal functions
		bool __dim( const __DX uint& );
		bool __copy_ct( const char*, const __DX uint& );
		bool __shrink( const __DX uint& );
		bool __append( const char*, __DX uint );
		bool __cmp_s_o( const char*, const char*, __DX uint ) const;
		bool __mi_list( const char&, const __LIB String& ) const;
		__LIB String __concat( const __LIB String&, const __LIB String& ) const;
		void __clean( );
		bool __good_wild( const std::pair<__DX uint, __DX uint>&, const __LIB String& ) const;

	public: // Consts
		static const __DX uint bad = static_cast<__DX uint>( -1 );
		static const std::pair<__DX uint, __DX uint> bad_pair;

	public: // Ctors / Move Semantics / C++11
		String( );
		String( const __LIB String& );
		String( __LIB String&& );
		String( const char* );
		String( const char*, __DX uint len );
		String( const std::initializer_list<char> &_List );
		String( std::nullptr_t null );
		~String( );

		void swap( __LIB String& );
		__LIB String copy( );
		fwdIterator begin( ) const;
		fwdIterator end( ) const;
		cfwdIterator cbegin( ) const;
		cfwdIterator cend( ) const;
		rvrsIterator rbegin( );
		rvrsIterator rend( );
		crvrsIterator crbegin( ) const; 
		crvrsIterator crend( ) const;
		
	public: // __LIB String function
		__DX uint length( ) const;
		__DX uint capacity( ) const;
		void push_back( const char& );
		void pop_back( );

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the position of a certain __LIB String/char.

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find( '_' );

			// good_pos will be equal to '0'.
			auto good_pos = my___LIB String.find( 'H' );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find( const char &_Character ) const;
		__DX uint find( const __LIB String &_Sequence ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the position of a certain __LIB String/char.

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

			'off' <__DX uint>
				The offset of where to begin searching.

		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find( '_', 10 );

			// good_pos will be equal to 10U.
			auto good_pos = my___LIB String.find( 'O', 5 );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find( const char &_Character, __DX uint _Offset ) const;
		__DX uint find( const __LIB String &_Sequence, __DX uint _Offset ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the first position of a certain __LIB String/char.

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find_first_of( 'x' );
			
			// good_pos will be equal to 2U.
			auto good_pos = my___LIB String.find_first_of( "ll" );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find_first_of( const char &_Charcater ) const;
		__DX uint find_first_of( const __LIB String &_Sequence ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the first position of a certain __LIB String/char.

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

			

		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find_first_of( 'x', 25 );

			// good_pos will be equal to 2U.
			auto good_pos = my___LIB String.find_first_of( "ll", 1 );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find_first_of( const char &_Character, __DX uint _Offset ) const;
		__DX uint find_first_of( const __LIB String &_Sequence, __DX uint _Offset ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the last position of a certain __LIB String/char.
			(This is alot faster if the character/__LIB String to be found is at the end of the __LIB String)

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find_last_of( 'x' );

			// good_pos will be equal to 2U.
			auto good_pos = my___LIB String.find_last_of( "ll" );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find_last_of( const char &_Character ) const;
		__DX uint find_last_of( const __LIB String &_Sequence ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Finds the last position of a certain __LIB String/char.

		Arguments:
			<const char&> || <const __LIB String&>
				The __LIB String or character to find.

			'off' <__DX uint>
				The offset to begin searching.


		Return:
			Returns the position of the __LIB String/char that was found.
			If it was not found the return value is __LIB String::bad.

		Example:
			__LIB String my___LIB String = "Hello I'm Oskar";

			// bad_pos will be equal to __LIB String::bad.
			auto bad_pos = my___LIB String.find_last_of( 'x', 25 );
	
			// good_pos will be equal to 2U.
			auto good_pos = my___LIB String.find_last_of( "ll", 1 );
		---------------------------------------------------------------------------------------------------------------*/
		__DX uint find_last_of( const char &_Character, __DX uint _Offset ) const;
		__DX uint find_last_of( const __LIB String &_Sequence, __DX uint _Offset ) const;
		
		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Find the position of a certain pattern that begins at 'pat_begin_search'
			and ends at 'pat_end_search' where as find_of_type is a
			list of characters that can be found in the region between
			'pat_begin_search' & 'pat_end_search'. Not every character
			that is inside 'find_of_type' must be found. 

		Arguments:
			'pat_begin_search' <__LIB String>
				The __LIB String or character where the search shall begin.

			'pat_end_search' <__LIB String>
				The __LIB String or character where the search shall end. (From the position of 'pat_begin_search')

			'find_of_type' <__LIB String>
				The characters that are accepted to be found within the region.
				if this equals "?" then every character is accepted.

		Return:
			Returns a pair of two __DX uint's where the first one is the position of 'pat_begin_search' and the second
			is the offset from 'pat_begin_search' to 'pat_end_search'.
			If the pattern is not found the pair is equal to __LIB String::bad. (Both first & second)

		Example:
			__LIB String my___LIB String = "hello there [name] i am 20.";
			auto position = find_wild( "[", "]" ); 
			
			my___LIB String.replace( position, "Oskar" );

			std::cout << my___LIB String << std::endl;

		Output of Example:
			hello there Oskar i am 20.
		---------------------------------------------------------------------------------------------------------------*/
		std::pair<__DX uint, __DX uint> find_wild( const __LIB String &_Begin_seq, const __LIB String &_End_seq, const __LIB String &_Types = "?" ) const;

		/*-------------------------------------------------------------------------------------------------------------
			Same as first overload, except the search begins at 'offset'.
		---------------------------------------------------------------------------------------------------------------*/
		std::pair<__DX uint, __DX uint> find_wild( const __DX uint &_Offset, const __LIB String &_Begin_seq, const __LIB String &_End_seq, const __LIB String &_Types = "?" ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Returns sub __LIB String of the current __LIB String within the dimensions provided.

		Arguments:
			<const std::pair<__DX uint, __DX uint>&> : !!If bad an exception will be thrown!!
				This is the position/offset where the __LIB String should be taken from.
				The first member in the pair is the position where it should start,
				The second member in the pair is how far from the start position it should
				be. (Length)

		Returns:
			Returns a __LIB String containing the contents.
		
		Example:
			__LIB String my___LIB String = "Hello there [Name] how are you.\n".
			auto pos = my___LIB String.find_wild( "[", "]", "?" );
			
			auto contents = my___LIB String.substr( pos );
			std::cout << contents << std::endl;
			std::cout << my___LIB String;

		Output of example:
			Name
			Hello there [Name] how are you.

		Overloads:
			Other 2 overloads are wrappers for this one.
		---------------------------------------------------------------------------------------------------------------*/
		__LIB String substr( const std::pair<__DX uint, __DX uint>& _Pair ) const;
		__LIB String substr( const __DX uint &_Position ) const;
		__LIB String substr( const __DX uint &_Position, const __DX uint &_Offset ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			If the current __LIB String is empty or not.

		Arguments:

		Returns:
			Returns a boolean value wether or not the __LIB String is empty.

		Example:
			__LIB String __LIB String;
			if ( __LIB String.empty( ) )
				std::cout << "__LIB String is empty" << std::endl;
			
		Output of example:
			__LIB String is empty
		---------------------------------------------------------------------------------------------------------------*/
		bool empty( ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			If the current __LIB String contains this __LIB String.

		Arguments:
			<const __LIB String&>
				The __LIB String to be searched for inside the current __LIB String.

		Returns:
			Returns a boolean value wether or not the current __LIB String contains another
			__LIB String.

		Example:
			__LIB String __LIB String = "I like potato";
			if ( __LIB String.contains( "potato" ) )
				std::cout << "__LIB String contains potato!!" << std::endl;

		Output of example:
			__LIB String contains potato!!
		---------------------------------------------------------------------------------------------------------------*/
		bool contains( const __LIB String &_Sequence ) const;

		/**/
		bool hasCapital( ) const;

		/**/
		bool hasNumerical( ) const;


		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Returns a C null-terminated __LIB String.

		Arguments:
			
		Returns:
			The current buffer as a null-terminatd __LIB String.

		Example:
			__LIB String __LIB String = "hello";
			const char* str = __LIB String.c_str( );
			std::cout << str << std::endl;

		Output of example:
			hello
		---------------------------------------------------------------------------------------------------------------*/
		const char* c_str( ) const;

		/*-------------------------------------------------------------------------------------------------------------
		Description:
			Erases part of the current __LIB String.

		Arguments:
			<const std::pair<__DX uint, __DX uint>&>
				The part to remove, the first member
				is the start, the second member is the length 
				to remove.

		Returns:
		
		Example:
			__LIB String __LIB String = "Hello there mr [___]!";
			auto pos = __LIB String.find_wild( "[", "]", "_" );
			__LIB String.erase( pos ); 

			std::cout << __LIB String << std::endl;

		Output of example:
			Hello there mr []!

		Overloads:
			Wrapper for this erase function.
		---------------------------------------------------------------------------------------------------------------*/
		void erase( const std::pair<__DX uint, __DX uint> &_Streampos );
		void erase( const __DX uint &_Position, const __DX uint &_Length );
		void insert( const std::pair<__DX uint, __DX uint> &_Streampos, const __LIB String &_Sequence );
		void insert(const __DX uint &_Position, const __DX uint &_Length, const __LIB String &_Sequence);
		void insert( const __DX uint &_Position, const __LIB String &_Sequence );
		void append( const __LIB String &_Sequence );

		void reserve( const __DX uint &_Size );
		
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

		template<>
		void assign<String::fwdIterator>( fwdIterator it1, fwdIterator it2 )
		{
			auto myIt = begin( ), myEnd = end( );
			for ( ; it1 < it2 && myIt < myEnd; ++it1, ++myIt )
				*myIt = *it1;
		}

		std::vector<__LIB String> split( const char& _Of ) const;
		std::vector<__LIB String> split( const __LIB String &_Of_seq ) const;
		//__DX uint amount_of(  );
		//__DX uint amount_of_wild( const __LIB String &begin, const __LIB String &end, const __LIB String &type = "?" );
		__DX uint hash( ) const;


		__LIB String upper( ) const;
		__LIB String lower( ) const;

		template<typename T >
		T to( ) const
		{
			T t;
			std::stringstream ss( this->_buffer );
			if ( ::isxdigit( (unsigned char)*begin( ) ) )
				ss >> std::hex >> t;
			else
				ss >> t;
			return t;
		}

		template<typename T>
		static __LIB String from( T&& _Tx )
		{
			return __LIB to_string( _Tx );
		}

		String fill( const char &_Filler );

	public: // Operators
		const __LIB String& operator=( const __LIB String& );
		const __LIB String& operator=( __LIB String&& );

		const __LIB String& operator+=( const __LIB String& );
		const __LIB String& operator+=( const char& );

		__LIB String operator+( const __LIB String& ) const;

		bool operator==( const __LIB String& ) const;
		bool operator==( const char& ) const;
	
		bool operator!=( const __LIB String& ) const;
		bool operator!=( const char& ) const;

		friend std::ostream& operator<<(std::ostream& os, const __LIB String& dt);

	public:
		template<typename _Type>
		static __LIB String _Type_to_string( const char* _Fmt, _Type _Val )
		{
			char _Buf[21];
			auto _Len = ::sprintf_s( _Buf, _Fmt, _Val );
			return __LIB String( _Buf, _Len );
		}
	};

	
	inline __LIB String to_string(int _Val)
	{	// convert int to __LIB String
		return (__LIB String::_Type_to_string("%d", _Val));
	}

	inline __LIB String to_string(unsigned int _Val)
	{	// convert unsigned int to __LIB String
		return (__LIB String::_Type_to_string("%u", _Val));
	}

	inline __LIB String to_string(long _Val)
	{	// convert long to __LIB String
		return (__LIB String::_Type_to_string("%ld", _Val));
	}

	inline __LIB String to_string(unsigned long _Val)
	{	// convert unsigned long to __LIB String
		return (__LIB String::_Type_to_string("%lu", _Val));
	}

	inline __LIB String to_string(long long _Val)
	{	// convert long long to __LIB String
		return (__LIB String::_Type_to_string("%lld", _Val));
	}

	inline __LIB String to_string(unsigned long long _Val)
	{	// convert unsigned long long to __LIB String
		return (__LIB String::_Type_to_string("%llu", _Val));
	}

	inline __LIB String to_string(float _Val)
	{	// convert float to __LIB String
		return (__LIB String::_Type_to_string("%f", _Val));
	}

	inline __LIB String to_string(double _Val)
	{	// convert double to __LIB String
		return (__LIB String::_Type_to_string("%f", _Val));
	}

	inline __LIB String to_string(long double _Val)
	{	// convert long double to __LIB String
		return (__LIB String::_Type_to_string("%Lf", _Val));
	}

	static std::ostream& operator<<(std::ostream& stream, const __LIB String &_Rhs)
	{
		stream << _Rhs._buffer;
		return stream;
	}

	static __LIB String operator+(const char* _Lhs, const __LIB String& _Rhs)
	{
		return __LIB String(_Lhs) + _Rhs;
	}




end_LIB