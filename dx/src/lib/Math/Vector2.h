#pragma once
#include "lib.h"


begin_MATH
class Region;

class Vector2
{
public:
	float x, y;

	///<summary>
	/// Returns true if this vector2 intersects the '_Area'.
	///</summary>
	bool Intersects( const __MATH Region &_Area ) const;

	///<summary>
	/// Return the dot product of this vector.
	///</summary>
	float Dot( const __MATH Vector2 &_Other ) const;

	///<summary>
	/// Return the magnitude of this vector.
	///</summary>
	float Magnitude( ) const;

public:
		// Operators

	///<summary>
	/// Increase this vector by '_Rhs'.
	///</summary>
	Vector2& operator+=( const Vector2 &_Rhs );

	///<summary>
	/// Decrease this vector by '_Rhs'.
	///</summary>
	Vector2& operator-=( const Vector2 &_Rhs );

	///<summary>
	/// assign this vector to '_Rhs'.
	///</summary>
	Vector2& operator=( const Vector2 &_Rhs );

	///<summary>
	/// Return a copy of this vector increased by '_Rhs'.
	///<summary>
	Vector2 operator+( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return a copy of this vector decreased by '_Rhs'.
	///<summary>
	Vector2 operator-( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return a copy of this vector multiplied by '_Rhs'.
	///<summary>
	Vector2 operator*( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return a copy of this vector divided by '_Rhs'.
	///<summary>
	Vector2 operator/( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return true if this is greater than '_Rhs'.
	///</summary>
	bool operator>( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return true if this is greater than or equal to '_Rhs'.
	///</summary>
	bool operator>=( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return true if this is less than '_Rhs'.
	///</summary>
	bool operator<( const Vector2 &_Rhs ) const;

	///<summary>
	/// Return true if this is less than or equal to '_Rhs'.
	///</summary>
	bool operator<=( const Vector2 &_Rhs ) const;

	///<summary>
	/// Compare this vector to '_Rhs'.
	///</summary>
	bool operator==( const Vector2 &_Rhs ) const;

	///<summary>
	/// Compare this vector to '_Rhs' and return true if they are NOT equal.
	///</summary>
	bool operator!=( const Vector2 &_Rhs ) const;
	
};

end_MATH


