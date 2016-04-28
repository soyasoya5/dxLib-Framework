#pragma once
#include "lib.h"
#include "../string.h"
#include "../Math/Vector2.h"

begin_GRAPHICS
class Font;

enum TextAlignment
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
	Text( std::shared_ptr<Font> font, 
		  const String &text, 
		  const __MATH Vector2 &position,
		  const __MATH Vector2 &clip = { 500, 200 }, 
		  const TextAlignment &allignment = Top );

	///<summary>
	/// Get the font.
	///</summary>
	std::shared_ptr<Font> getFont( ) const;

	///<summary>
	/// Set the font.
	///</summary>
	void setFont( std::shared_ptr<Font> font );

	///<summary>
	/// Get the text allignment inside the _Clip.
	///</summary>
	__GRAPHICS TextAlignment getAlignment( ) const;

	///<summary>
	/// Set the text allignment.
	///</summary>
	void setAlignment( const __GRAPHICS TextAlignment &_Alignment );

	///<summary>
	///	Get the text.
	///</summary>
	const __LIB String &getText( ) const;

	///<summary>
	/// Set the text.
	///</summary>
	void setText( const __LIB String &_Text );

	///<summary>
	/// Get the position.
	///</summary>
	const __MATH Vector2 &getPosition( ) const;

	///<summary>
	/// Set the position.
	///</summary>
	void setPosition( const __MATH Vector2 &_Position );

	///<summary>
	/// Get the clipping.
	///</summary>
	const __MATH Vector2 &getMaxClip( ) const;

	///<summary>
	/// Set the clipping.
	///</summary>
	void setMaxClip( const __MATH Vector2 &_Clip );


private:
	std::shared_ptr<Font> font_;
	TextAlignment allign_;
	String text_;
	__MATH Vector2 position_, max_;

};

end_GRAPHICS
