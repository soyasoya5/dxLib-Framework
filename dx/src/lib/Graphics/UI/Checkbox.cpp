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
	changed_ = true;
}

::dx::lib::Math::Vector2 Checkbox::determineText(::dx::lib::Math::Vector2 &pos, ::dx::lib::Math::Vector2 &text_size )
{
	auto size = getSize( );
	// Y is always gonna be in the middle for the sake of no clip
	determ_.y = (size.y / 2 - text_size.y / 2) + pos.y;
	determ_.x = pos.x + size.x + 10;
	changed_ = false;
	return determ_;
}

void Checkbox::Paint( Window* sender, BasePainter *painter )
{
	static Pen inner, outer{ Colors::White, 1 }, pen_text{ Colors::White, 1 };
	if ( !this->isVisible( ) )
		return;

	OnPrePaint( ) .Invoke( this, painter );

	// Determine region
	auto pos = determineRegion( );

	// Get font
	auto font = getFont( );
	if ( !font )
		font = painter->defaultFont( );

	// Setup Text
	Text text{ font, getText(), { } };
	auto textSize = font->calculateMetrixOf( text.getText( ) );
	text.setPosition( determineText( pos.position, textSize ) );

	// Setup Colors/Style
	auto style = getStyle( );
	inner.Color( style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8 );
	pen_text.Color( style.theme( ) == Dark ? Colors::White : Colors::Black );

	if ( isClicked( ) || isHovered( ) )
		outer.Color( style.style( ) );
	else
		outer.Color( 0xFF4B4B4B );
	

	painter->PaintRectOutlined( pos, inner, outer );
	painter->Paint( text,  pen_text );

	// Checked state
	if ( getState( ) )
	{
		Line line1, line2;
		line1.Pen( Pen( style.style( ), 2 ) );
		line2.Pen( line1.Pen( ) );

		// line1 pos
		line1.Position( { pos.position.x + 2, pos.position.y + 2 } );
		
		// Target (Center of component)
		line1.Target( pos.position + ::dx::lib::Math::Vector2{ pos.size.x / 2, pos.size.y - 2 } );

		// Line2 pos
		line2.Position( line1.Target( ) );

		// Line2 target
		line2.Target( { pos.position + ::dx::lib::Math::Vector2{ pos.size.x - 3, 5 } } );

		painter->PaintLine( line1 );
		painter->PaintLine( line2 );
	}


	OnPostPaint( ).Invoke( this, painter );
}



end_UI