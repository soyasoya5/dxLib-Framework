#include "Button.h"
#include "../Text.h"
#include "../Font.h"
#include "../Pen.h"
#include "../Painter.h"
#include <regex>

begin_UI

Button::Button()
	: Component( )
{
}


__MATH Vector2 Button::determineText(__MATH Vector2 &pos, __MATH Vector2 &text_size )
{
	__MATH Vector2 ret;
	auto allign = getAllignment( );
	auto size = getSize( );

	// Y is always gonna be in the middle for the sake of no clip
	ret.y = (size.y / 2 - text_size.y / 2) + pos.y;

	if ( allign == Allignment::Center )
		ret.x = ( size.x / 2 - text_size.x / 2 ) + pos.x;
	else if ( allign == Allignment::Left )
		ret.x = pos.x + 5;
	else
		ret.x = pos.x + size.x - (text_size.x + 5);
	return ret;
}

void Button::Paint(__GRAPHICS Window *_Sender, __GRAPHICS BasePainter * _Painter)
{
	static Pen inner, outer{ Colors::White, 1 }, pen_text{ Colors::White, 1 };
	if ( !isVisible( ) )
		return;
	
	// Raise pre paint event
	OnPrePaint( ).Invoke( this, _Painter );

	// Determine region
	auto pos = determineRegion( );

	// Get font
	auto font = getFont( );
	if ( !font ) // Use dafault font..
		font = _Painter->defaultFont( );


	// Setup text component
	Text text{ font, getText(), { } };
	auto textSize = font->calculateMetrixOf( text.getText( ) );
	text.setPosition( determineText( pos.position, textSize ) );
	
	// Setup style/colors
	auto style = getStyle( );
	auto color_inner = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto color_outer = 0xFF4B4B4B;
	pen_text.Color( style.theme( ) == Dark ? Colors::White : Colors::Black );

	// Assign colors to pen
	if ( isClicked( ) || isHovered( ) )
		outer.Color( style.style( ) );
	else
		outer.Color( color_outer );

	inner.Color( color_inner );

	// Paint
	_Painter->PaintRectOutlined( pos, inner, outer );
	_Painter->Paint( text, pen_text );

	// Raise post paint event
	OnPostPaint( ).Invoke( this, _Painter );
}


end_UI