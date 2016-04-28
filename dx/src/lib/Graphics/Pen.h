#pragma once
#include "lib.h"
#include "../../dx.h"


begin_GRAPHICS


class Pen
{
public:

	///<summary>
	///	Empty constructor
	///</summary>
	Pen( );

	///<summary>
	///	Construct with Color and Thickness.
	///</summary>
	Pen( const ::dx::uint &color, const ::dx::uint &thickness = 1 );

	///<summary>
	///	Gets the color of this pen.
	///</summary>
	::dx::uint Color( ) const;
	
	///<summary>
	///	Gets the thickness of this pen.
	///</summary>
	::dx::uint Thickness( ) const;
	
	///<summary>
	///	Sets the color of this pen.
	///</summary>
	void Color( const ::dx::uint &color );
	
	///<summary>
	///	Sets the thickness of this pen.
	///</summary>
	void Thickness( const ::dx::uint &thickness );

private:
	::dx::uint color_, thickness_;
};

end_GRAPHICS