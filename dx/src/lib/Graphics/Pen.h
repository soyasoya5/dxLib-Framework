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
	Pen( const __DX uint &color, const __DX uint &thickness = 1 );

	///<summary>
	///	Gets the color of this pen.
	///</summary>
	__DX uint Color( ) const;
	
	///<summary>
	///	Gets the thickness of this pen.
	///</summary>
	__DX uint Thickness( ) const;
	
	///<summary>
	///	Sets the color of this pen.
	///</summary>
	void Color( const __DX uint &color );
	
	///<summary>
	///	Sets the thickness of this pen.
	///</summary>
	void Thickness( const __DX uint &thickness );

private:
	__DX uint color_, thickness_;
};

end_GRAPHICS