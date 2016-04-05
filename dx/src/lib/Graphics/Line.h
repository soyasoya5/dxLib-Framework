#pragma once
#include "lib.h"
#include "Pen.h"
#include "../Math/Vector2.h"


begin_GRAPHICS

class Line
{
public:

	///<summary>
	///	Empty constructor
	///</summary>
	Line( );

	///<summary>
	///	Construct line.
	///</summary>
	Line( const __MATH Vector2 &_Position, const __MATH Vector2 &_Target, const __GRAPHICS Pen &_Pen );

	///<summary>
	///	Gets the pen of Line.
	///</sumamry>
	__GRAPHICS Pen Pen( ) const;

	///<summary>
	///	Gets the start position of this line.
	///</sumamry>
	__MATH Vector2 Position( ) const;

	///<summary>
	/// Gets the target position of this line.
	///</summary>
	__MATH Vector2 Target( ) const;

	///<summary>
	///	Sets the pen of this line.
	///</summary>
	void Pen( const __GRAPHICS Pen &_Pen );

	///<summary>
	///	Sets the start position of this line.
	///</summary>
	void Position( const __MATH Vector2 &_Position );

	///<summary>
	///	Sets the target position of this line.
	///</summary>
	void Target( const __MATH Vector2 &_Target );

private:
	__GRAPHICS Pen _pen;
	__MATH Vector2 _pos, _target;
};

end_GRAPHICS