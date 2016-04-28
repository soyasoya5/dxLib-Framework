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
	Line( const ::dx::lib::Math::Vector2 &position, const ::dx::lib::Math::Vector2 &target, const ::dx::lib::Graphics::Pen &pen );

	///<summary>
	///	Gets the pen of Line.
	///</sumamry>
	::dx::lib::Graphics::Pen Pen( ) const;

	///<summary>
	///	Gets the start position of this line.
	///</sumamry>
	::dx::lib::Math::Vector2 Position( ) const;

	///<summary>
	/// Gets the target position of this line.
	///</summary>
	::dx::lib::Math::Vector2 Target( ) const;

	///<summary>
	///	Sets the pen of this line.
	///</summary>
	void Pen( const ::dx::lib::Graphics::Pen &pen );

	///<summary>
	///	Sets the start position of this line.
	///</summary>
	void Position( const ::dx::lib::Math::Vector2 &position );

	///<summary>
	///	Sets the target position of this line.
	///</summary>
	void Target( const ::dx::lib::Math::Vector2 &target );

private:
	::dx::lib::Graphics::Pen pen_;
	::dx::lib::Math::Vector2 pos_, target_;
};

end_GRAPHICS