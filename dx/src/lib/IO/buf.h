#pragma once
#include "lib.h"
#include "../../dx.h"
#include "../event.h"

begin_IO


template<typename _Tx>
class _Streambuf
{
public:
	using _MyTx = typename __DX remove_all<_Tx>::type;
	using _Base = _Streambuf<_MyTx>;
	using _FwdIter = _MyTx*;


public:
	static const __DX uint bad = static_cast<__DX uint>( -1 );

public:
	_Streambuf( );
	_Streambuf( _MyTx *_Buffer, __DX uint _Length );
	_Streambuf( const _Base &_Other );
	_Streambuf( _Base &&_Rvalue );
	_Streambuf( const std::initializer_list<_MyTx> &_List );
	~_Streambuf( );
	
	///<summary>
	/// Cleans current buffer (if needed)
	/// and resizes the current buffer.
	///</summary>
	void reserve( const __DX uint &_Length );
	template<typename _Iterator>

	///<summary>
	/// assigns the current bufefr to the values of _I1 to _I2
	/// starts at begin( ), ends when _I2 == _I1 || current == end( )
	///</summary>
	void assign( _Iterator _I1, _Iterator _I2 );

	///<summary>
	/// assigns the current bufefr to the values of _I1 to _I2
	/// starts at begin( ) + _Offset, ends when _I2 == _I1 || current == end( )
	///</summary>
	template<typename _Iterator>
	void assign( const __DX uint &_Offset, _Iterator _I1, _Iterator _I2 );

	///<summary>
	/// appends to the current buffer
	///</summary>
	template<typename _Iterator>
	void append( _Iterator _I1, _Iterator _I2 );


	///<sumamry>
	/// Like reserve but keeps the values of _Buf
	/// returns the old length
	///</summary>
	__DX uint resize( const __DX uint &_Length );

	///<summary>
	///deletes the buffer
	///</summary>
	void clean( );

	///<summary>
	/// grabs the length of the buffer
	///</summary>
	__DX uint length( );

	///<summary>
	/// returns wether or not the buffer is good to use
	///</summary>
	bool good( );

	_Base operator=( const _Base &_Other );

public: // Semantics
	void swap( _Base &_Other );
	_Base copy( ) const;
	_FwdIter begin( );
	_FwdIter end( );
private:
	_MyTx		*_Buf;
	__DX uint	 _Length;
};

end_IO

#include "buf.inl"
