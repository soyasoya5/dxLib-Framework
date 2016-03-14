#pragma once
#include "lib.h"
#include "Vector2.h"

begin_MATH

class Region
{
public:
	__MATH Vector2 position, size;

	void MoveBy( const __MATH Vector2 &_Amount );
	void MoveTo( const __MATH Vector2 &_Position );
	void ResizeBy( const __MATH Vector2 &_Amount );
	void ResizeTo( const __MATH Vector2 &_Size );
	bool Intersects( const __MATH Region &_Other );
};


end_MATH


