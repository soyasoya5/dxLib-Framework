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
	Line( const __MATH Vector2 &position, const __MATH Vector2 &target, const __GRAPHICS Pen &pen );

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
	void Pen( const __GRAPHICS Pen &pen );

	///<summary>
	///	Sets the start position of this line.
	///</summary>
	void Position( const __MATH Vector2 &position );

	///<summary>
	///	Sets the target position of this line.
	///</summary>
	void Target( const __MATH Vector2 &target );

private:
	__GRAPHICS Pen pen_;
	__MATH Vector2 pos_, target_;
};

end_GRAPHICS