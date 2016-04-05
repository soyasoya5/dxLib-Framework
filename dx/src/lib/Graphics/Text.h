#pragma once
#include "lib.h"
#include "../string.h"
#include "../Math/Vector2.h"

begin_GRAPHICS
class Font;

enum TextAllignment
{
	Left = DT_LEFT,
	Right = DT_RIGHT,
	Bottom = DT_BOTTOM,
	Top = DT_TOP,
	Center = DT_CENTER,
};

class Text
{
public:

	///<summary>
	/// Empty constructor
	///</summary>
	Text( );

	///<summary>
	/// Construct this Text component.
	///</summary>
	Text( __GRAPHICS Font *_Font, 
		  const __LIB String &_Text, 
		  const __MATH Vector2 &_Position,
		  const __MATH Vector2 &_Clip = { 500, 200 }, 
		  const __GRAPHICS TextAllignment &_Allignment = Top );

	///<summary>
	/// Get the font.
	///</summary>
	__GRAPHICS Font* getFont( ) const;

	///<summary>
	/// Set the font.
	///</summary>
	void setFont( __GRAPHICS Font *_Font );

	///<summary>
	/// Get the text allignment inside the _Clip.
	///</summary>
	__GRAPHICS TextAllignment getAllignment( ) const;

	///<summary>
	/// Set the text allignment.
	///</summary>
	void setAllignment( const __GRAPHICS TextAllignment &_Allignment );

	///<summary>
	///	Get the text.
	///</summary>
	__LIB String getText( ) const;

	///<summary>
	/// Set the text.
	///</summary>
	void setText( const __LIB String &_Text );

	///<summary>
	/// Get the position.
	///</summary>
	__MATH Vector2 getPosition( ) const;

	///<summary>
	/// Set the position.
	///</summary>
	void setPosition( const __MATH Vector2 &_Position );

	///<summary>
	/// Get the clipping.
	///</summary>
	__MATH Vector2 getMaxClip( ) const;

	///<summary>
	/// Set the clipping.
	///</summary>
	void setMaxClip( const __MATH Vector2 &_Clip );


private:
	__GRAPHICS Font* _font;
	__GRAPHICS TextAllignment _allign;
	__LIB String _text;
	__MATH Vector2 _position, _max;

};

end_GRAPHICS
