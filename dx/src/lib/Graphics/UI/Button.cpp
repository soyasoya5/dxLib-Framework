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
	OnModified( ) += [this]( Component* ) { this->_changed = true; };
}


__MATH Vector2 Button::determineText(__MATH Vector2 &pos, __MATH Vector2 &text_size )
{
	if ( _changed ) {
		auto align = getAlignment( );
		auto size = getSize( );
		// Y is always gonna be in the middle for the sake of no clip
		_determ.y = (size.y / 2 - text_size.y / 2) + pos.y;

		if ( align == Alignment::Center )
			_determ.x = ( size.x / 2 - text_size.x / 2 ) + pos.x;
		else if ( align == Alignment::Left )
			_determ.x = pos.x + 5;
		else
			_determ.x = pos.x + size.x - (text_size.x + 5);
		_changed = false;
	}
	return _determ;
}

void Button::Paint(Window *sender, BasePainter * painter)
{
	static Pen inner, outer{ Colors::White, 1 }, pen_text{ Colors::White, 1 };
	if ( !isVisible( ) )
		return;
	
	// Raise pre paint event
	OnPrePaint( ).Invoke( this, painter );

	// Determine region
	auto pos = determineRegion( );

	// Get font
	auto font = getFont( );
	if ( !font ) // Use dafault font..
		font = painter->defaultFont( );


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
	painter->PaintRectOutlined( pos, inner, outer );
	painter->Paint( text, pen_text );

	// Raise post paint event
	OnPostPaint( ).Invoke( this, painter );
}


end_UI