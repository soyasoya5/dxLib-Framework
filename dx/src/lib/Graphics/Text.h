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
	Text( );
	Text( __GRAPHICS Font *_Font, 
		  const __LIB String &_Text, 
		  const __MATH Vector2 &_Position,
		  const __MATH Vector2 &_Clip = { 500, 200 }, 
		  const __GRAPHICS TextAllignment &_Allignment = Top );

	__GRAPHICS Font* getFont( ) const;
	void setFont( __GRAPHICS Font *_Font );

	__GRAPHICS TextAllignment getAllignment( ) const;
	void setAllignment( const __GRAPHICS TextAllignment &_Allignment );

	__LIB String getText( ) const;
	void setText( const __LIB String &_Text );

	__MATH Vector2 getPosition( ) const;
	void setPosition( const __MATH Vector2 &_Position );

	__MATH Vector2 getMaxClip( ) const;
	void setMaxClip( const __MATH Vector2 &_Clip );


private:
	__GRAPHICS Font* _font;
	__GRAPHICS TextAllignment _allign;
	__LIB String _text;
	__MATH Vector2 _position, _max;

};

end_GRAPHICS
