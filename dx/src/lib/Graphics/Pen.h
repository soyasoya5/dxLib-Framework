#pragma once
#include "lib.h"
#include "../../dx.h"


begin_GRAPHICS


class Pen
{
public:
	Pen( );
	Pen( const __DX uint &_Color, const __DX uint &_Thickness = 1 );

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
	void Color( const __DX uint &_Color );
	
	///<summary>
	///	Sets the thickness of this pen.
	///</summary>
	void Thickness( const __DX uint &_Thickness );

private:
	__DX uint _color, _thickness;
};

end_GRAPHICS