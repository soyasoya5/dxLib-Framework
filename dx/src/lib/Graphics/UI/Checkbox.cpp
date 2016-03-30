#include "Checkbox.h"
#include "../Text.h"
#include "../Font.h"
#include "../Pen.h"

begin_UI


Checkbox::Checkbox()
	: Component( )
{

}

void Checkbox::Paint( Window *_Sender, BasePainter *_Painter )
{
	static Pen inner, outer{ Colors::White, 1 }, pen_text{ Colors::White, 1 };
	if ( !this->isVisible( ) )
		return;

	OnPrePaint( ) .Invoke( this );

	// Determine region
	auto pos = determineRegion( );

	// Get font
	auto font = getFont( );
	if ( !font )
		font = _Painter->defaultFont( );

	// Setup Text
	Text text{ font, getText( ), pos.position + __MATH Vector2{ pos.size.x + 15, 0 } };
	
	// Setup Colors/Style
	auto style = getStyle( );
	auto color_inner = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto color_outer = 0xFF4B4B4B;

	

	


	OnPostPaint( ).Invoke( this );
}



end_UI