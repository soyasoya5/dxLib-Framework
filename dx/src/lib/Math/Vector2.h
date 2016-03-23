#pragma once
#include "lib.h"


begin_MATH
class Region;

class Vector2
{
public:
	float x, y;


	bool Intersects( const __MATH Region &_Area ) const;
	float Dot( const __MATH Vector2 &_Other ) const;
	float Magnitude( ) const;

public:
		// Operators
	Vector2& operator+=( const Vector2 &_Other );
	Vector2& operator-=( const Vector2 &_Other );
	Vector2& operator=( const Vector2 &_Other );

	Vector2 operator+( const Vector2 &_Other ) const;
	Vector2 operator-( const Vector2 &_Other ) const;
	Vector2 operator*( const Vector2 &_Other ) const;
	Vector2 operator/( const Vector2 &_Other ) const;
};

end_MATH


