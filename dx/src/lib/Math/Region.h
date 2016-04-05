#pragma once
#include "lib.h"
#include "Vector2.h"

begin_MATH

class Region
{
public:
	__MATH Vector2 position, size;

	///<summary>
	/// Moves the position by '_Amount' amount.
	///</summary>
	void MoveBy( const __MATH Vector2 &_Amount );
	
	///<summary>
	/// Moves the position to '_Position'.
	///</summary>
	void MoveTo( const __MATH Vector2 &_Position );

	///<summary>
	/// Resizes the size by '_Amount' amount.
	///</summary>
	void ResizeBy( const __MATH Vector2 &_Amount );

	///<summary>
	/// Resizes the size to '_Size'.
	///</summary>
	void ResizeTo( const __MATH Vector2 &_Size );

	///</summary>
	/// Returns wether '_Other' positon intersects with this Region.
	///</summary>
	bool Intersects( const __MATH Region &_Other );
};


end_MATH


