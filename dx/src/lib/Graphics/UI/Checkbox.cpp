#include "Checkbox.h"
#include "../Text.h"
#include "../Font.h"
#include "../Pen.h"
#include "../Line.h"
begin_UI


Checkbox::Checkbox()
	: Component( )
{
	Component::OnMouseReleased( ) += []( Component *sender ) { sender->setState( !sender->getState( ) ); }; 
}

// https://bitbucket.org/Yamiez/dxlib/src/3772a5230b86883fd890a41007e80d5502f63031/dx/main.cpp?at=master&fileviewer=file-view-default#main.cpp-42

void Checkbox::Paint( Window *_Sender, BasePainter *_Painter )
{
	static Pen inner, outer{ Colors::White, 1 }, pen_text{ Colors::White, 1 };
	if ( !this->isVisible( ) )
		return;

	OnPrePaint( ) .Invoke( this, _Painter );

	// Determine region
	auto pos = determineRegion( );

	// Get font
	auto font = getFont( );
	if ( !font )
		font = _Painter->defaultFont( );

	// Setup Text
	Text text{ font, getText( ), pos.position + __MATH Vector2{ pos.size.x + 15, 3 } };

	// Setup Colors/Style
	auto style = getStyle( );
	auto color_inner = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto color_outer = 0xFF4B4B4B;
	pen_text.Color( style.theme( ) == Dark ? Colors::White : Colors::Black );

	if ( isClicked( ) || isHovered( ) )
		outer.Color( style.style( ) );
	else
		outer.Color( color_outer );
	

	_Painter->PaintRectOutlined( pos, inner, outer );
	_Painter->Paint( text,  pen_text );

	// Checked state
	if ( getState( ) )
	{
		Line line1, line2;
		line1.Pen( Pen( style.style( ), 2 ) );
		line2.Pen( line1.Pen( ) );

		// line1 pos
		line1.Position( { pos.position.x + 2, pos.position.y + 2 } );
		
		// Target (Center of component)
		line1.Target( pos.position + __MATH Vector2{ pos.size.x / 2, pos.size.y - 2 } );

		// Line2 pos
		line2.Position( line1.Target( ) );

		// Line2 target
		line2.Target( { pos.position + __MATH Vector2{ pos.size.x - 3, 5 } } );

		_Painter->PaintLine( line1 );
		_Painter->PaintLine( line2 );
	}


	OnPostPaint( ).Invoke( this, _Painter );
}



end_UI