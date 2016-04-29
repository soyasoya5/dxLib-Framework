#pragma once
#include "lib.h"



begin_LIB
// INDEXED ITERATORS
// These iterators are indexed, meaning that they are slower than 
// the normal iterators, but provide more functionality.

template<typename Px>
class Iterator
	: std::iterator<std::random_access_iterator_tag, Px>
{
private:
	template<typename Px>
	friend Iterator<Px> CreateIterator(Px*, size_t, size_t);
	Px* _arr;
	size_t _len;
	size_t _count;
	using _MyT = Iterator<Px>;

public:
	Iterator( ) : _arr( nullptr ), _count( 0 ), _len( 0 ) {}

	///<summary>
	/// Returns a pointer to the element.
	///</summary>
	pointer get( )
	{
		return reinterpret_cast<Px*>( _arr + _count );
	}

	///<summary>
	/// Return the lenth of the internal array.
	///</summary>
	const difference_type& length( ) const
	{
		return _len;
	}

	///<summary>
	/// Return the index of this iterator.
	///</summary>
	const difference_type& index( ) const
	{
		return _count;
	}
public: // Operators

	///<summary>
	/// Return a copy of this iterator that has its index decreased by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT operator-( const off_t& _Offset )
	{
		return (CreateIterator( _arr, _len, _count - _Offset ));
	}

	///<summary>
	/// Return a copy of this iterator that has its index increased by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT operator+( const off_t& _Offset )
	{
		return (CreateIterator( _arr, _len, _count + _Offset ));
	}

	///<summary>
	/// Increase index by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT& operator+=( const off_t& _Offset )
	{
		_count += _Offset;
		return (*this);
	}

	///<summary>
	/// Decrease index by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT& operator-=( const off_t& _Offset )
	{
		_count -= _Offset;
		return (*this);
	}

	///<summary>
	/// Dereference the element.
	///</summary>
	reference operator*( )
	{
		return (_arr[_count]);
	};

	///<summary>
	/// Return a pointer to the element.
	///</summary>
	pointer operator->( )
	{
		return get( );
	}

	///<summary>
	///	Pre Increment the index by one.
	///</summary>
	_MyT& operator++( )
	{
		if ( _count >= _len )
			return (*this);
		++_count;
		return (*this);
	}

	///<summary>
	///	Pre Decrement the index by one.
	///</summary>
	_MyT& operator--( )
	{
		if ( _count <= 0 )
			return (*this);
		--_count;
		return (*this);
	}

	///<summary>
	///	Post Increment the index by one.
	///</summary>
	_MyT operator++( int )
	{
		_MyT tmp = *this;
		operator++( );
		return tmp;
	}

	///<summary>
	///	Post Decrement the index by one.
	///</summary>
	_MyT operator--( int )
	{
		_MyT tmp = *this;
		operator--( );
		return tmp;
	}

	///<summary>
	/// Compare this iterator to '_Rhs'.
	///</summary>
	bool operator==( const Iterator<Px> &_Rhs ) const
	{
		return (this->_arr + _count) == (_Rhs._arr + _Rhs._count);
	}

	///<summary>
	/// Compare this iterator to '_Rhs' and return true if they are not equal.
	///</summary>
	bool operator!=( const Iterator<Px> &_Rhs ) const
	{
		return !( *this == _Rhs );
	}

	///<summary>
	/// Return wether or not the index of this is greater than '_Rhs'.
	///</summary>
	bool operator>( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count > _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is greater than equal to '_Rhs'.
	///</summary>
	bool operator>=( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count >= _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is less than '_Rhs'.
	///</summary>
	bool operator<( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count < _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is less than equal to '_Rhs'.
	///</summary>
	bool operator<=( const Iterator<Px> &_Rhs) const
	{
		return (this->_count <= _Rhs._count);
	}
};

template<typename Px>
class ReverseIterator
	: std::iterator<std::random_access_iterator_tag, Px>
{
	template<typename Px>
	friend ReverseIterator<Px> CreateReverseIterator(Px*, size_t, size_t);
	Px* _arr;
	size_t _len;
	size_t _count;
	using _MyT = ReverseIterator<Px>;

public:
	ReverseIterator() : _arr(nullptr), _count(0), _len(0) {}

	///<summary>
	/// Returns a pointer to the element.
	///</summary>
	pointer get( )
	{
		return reinterpret_cast<pointer>( _arr + (_len - 1) - _count );
	}

	///<summary>
	/// Return the lenth of the internal array.
	///</summary>
	const difference_type& length( ) const
	{
		return _len;
	}

	///<summary>
	/// Return the index of this iterator.
	///</summary>
	const difference_type& index( ) const
	{
		return _count;
	}
public: // Operators
	///<summary>
	/// Return a copy of this iterator that has its index decreased by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT operator-( const off_t& _Offset )
	{
		return (CreateIterator( _arr, _len, _count - _Offset ));
	}

	///<summary>
	/// Return a copy of this iterator that has its index increased by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT operator+( const off_t& _Offset )
	{
		return (CreateIterator( _arr, _len, _count + _Offset ));
	}

	///<summary>
	/// Increase index by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT& operator+=( const off_t& _Offset )
	{
		_count += _Offset;
		return (*this);
	}

	///<summary>
	/// Decrease index by '_Offset'.
	///</summary>
	template<typename off_t>
	_MyT& operator-=( const off_t& _Offset )
	{
		_count -= _Offset;
		return (*this);
	}

	///<summary>
	/// Dereference the element.
	///</summary>
	reference operator*( )
	{
		return (_arr[_count]);
	};

	///<summary>
	/// Return a pointer to the element.
	///</summary>
	pointer operator->( )
	{
		return get( );
	}

	///<summary>
	///	Pre Increment the index by one.
	///</summary>
	_MyT& operator++( )
	{
		if ( _count >= _len )
			return (*this);
		++_count;
		return (*this);
	}

	///<summary>
	///	Pre Decrement the index by one.
	///</summary>
	_MyT& operator--( )
	{
		if ( _count <= 0 )
			return (*this);
		--_count;
		return (*this);
	}

	///<summary>
	///	Post Increment the index by one.
	///</summary>
	_MyT operator++( int )
	{
		_MyT tmp = *this;
		operator++( );
		return tmp;
	}

	///<summary>
	///	Post Decrement the index by one.
	///</summary>
	_MyT operator--( int )
	{
		_MyT tmp = *this;
		operator--( );
		return tmp;
	}

	///<summary>
	/// Compare this iterator to '_Rhs'.
	///</summary>
	bool operator==( const ReverseIterator<Px> &_Rhs ) const
	{
		return (this->_arr + _len - _count) == (_Rhs._arr + _Rhs._len - _Rhs._count);
	}

	///<summary>
	/// Compare this iterator to '_Rhs' and return true if they are not equal.
	///</summary>
	bool operator!=( const ReverseIterator<Px> &_Rhs ) const
	{
		return !(*this == _Rhs);
	}

	///<summary>
	/// Return wether or not the index of this is greater than '_Rhs'.
	///</summary>
	bool operator>( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count > _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is greater than equal to '_Rhs'.
	///</summary>
	bool operator>=( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count >= _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is less than '_Rhs'.
	///</summary>
	bool operator<( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count < _Rhs._count);
	}

	///<summary>
	///	Return wether or not the index of this is less than equal to '_Rhs'.
	///</summary>
	bool operator<=( const Iterator<Px> &_Rhs ) const
	{
		return (this->_count <= _Rhs._count);
	}
};


///<summary>
///	Create a forward iterator
///</summary>
template<typename Px>
static Iterator<Px> CreateIterator(Px* array = nullptr, size_t length = 0, size_t offset = 0)
{
	Iterator<Px> iter;
	iter._arr = array;
	iter._len = length;
	iter._count = offset;
	return (iter);
}

///<summary>
///	Create a reverse iterator
///</summary>
template<typename Px>
static ReverseIterator<Px> CreateReverseIterator(Px* array = nullptr, size_t length = 0, size_t offset = 0)
{
	ReverseIterator<Px> iter;
	iter._arr = array;
	iter._len = length;
	iter._count = offset;
	return (iter);
}

end_LIB