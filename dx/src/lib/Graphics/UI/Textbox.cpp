#include "Textbox.h"
#include "../Text.h"
#include "../Line.h"
#include "../Font.h"
#include "../Pen.h"

begin_UI

Textbox::Textbox()
	: Component( )
{
}

void Textbox::Paint(Window *sender, BasePainter *painter)
{
	static Pen outer{ Colors::White, 2 }, pen_text{ Colors::White, 2 };
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, painter );

	// pos
	auto pos = determineRegion( );
	
	// Font
	auto font = getFont( );
	if ( !font )
		font = painter->defaultFont( );
	

	// Setup text
	auto myText = getText( );
	if ( myText.empty( ) )
		myText = prompt_;
	else if ( usePasswordChar_ )
		myText = myText.fill( passwordChar_ );
	
	auto textsize = font->calculateMetrixOf( myText );
	Text text{ font, myText, determineText( pos.position, textsize ) };


	// Style/Colors
	auto style = getStyle( );
	pen_text.Color( style.theme( ) == Dark ? Colors::White : Colors::Black );

	if ( isHovered( ) )
		outer.Color( style.style( ) );
	else
		outer.Color( 0xFF4B4B4B );

	// ________ line
	Line line;
	line.Pen( outer );
	line.Position( pos.position + __MATH Vector2{ 0, pos.size.y } );
	line.Target( pos.position + __MATH Vector2{ pos.size.x, pos.size.y } );

	painter->PaintLine( line );
	painter->Paint( text, pen_text );

	if ( canwrite_  )
	{
		if ( GetTickCount( ) > lblink_ )
		{
			lblink_ = GetTickCount( ) + 500;
			blink_ = !blink_;
		}

		if ( blink_ ) 
		{
			__MATH Vector2 lpos = text.getPosition( );
			lpos.x += textsize.x + 2;
			lpos.y = pos.position.y + 2;
			auto tlpos = lpos;
			tlpos.y = pos.position.y + pos.size.y - 2;
			Line line{ lpos, tlpos, Pen( Colors::White, 1 ) };
			painter->PaintLine( line );
		}
	}

	OnPostPaint( ).Invoke( this, painter);
}



void Textbox::KeyDownChar(Window *sender, KeyDownCharArgs & args)
{
	if ( args.handled )
		return;

	if ( canwrite_ )
	{
		auto font = getFont();
		if ( !font )
			font = sender->getPainter( )->defaultFont( );

		auto key = args.key_char;
		if ( key == loose_ )
		{
			canwrite_ = false;
			OnLostFocus( ).Invoke( this );
			return;
		}

		if ( key == '\n' && !isMultiline( ) )
			return;
		
		if ( key == '\b' && !text_.empty( ) )
			text_.pop_back( );
		else if ( key != '\b' && isInFilter( key ) )
			text_.push_back( key );
		OnCharacterAdded( ).Invoke( this, key );

		sender->ForcePaint( );
		args.handled = true;
	}
}

void Textbox::MouseClicked(Window *sender, MouseClickedArgs & args)
{
	__super::MouseClicked( sender, args );
	if ( !isClicked( ) ) 
	{
		canwrite_ = false;
		OnLostFocus( ).Invoke( this );
	}
}

void Textbox::MouseReleased(Window *sender, MouseReleasedArgs & args)
{
	if ( Collides( args.position ) )
	{
		if ( isClicked( ) )
		{
			canwrite_ = true;
			setClicked( false );
			OnMousePressed( ).Invoke( this );
			OnGainFocus( ).Invoke( this );
		}
	}
}

bool Textbox::getCanWrite() const
{
	return canwrite_;
}

bool Textbox::isMultiline() const
{
	return multiline_;
}

__LIB String Textbox::getPromptText() const
{
	return prompt_;
}

__LIB String Textbox::getFilter() const
{
	return filter_;
}

char Textbox::getPasswordChar() const
{
	return passwordChar_;
}

bool Textbox::getUsePasswordChar() const
{
	return usePasswordChar_;
}

char Textbox::getLooseFocusKey() const
{
	return loose_;
}

bool Textbox::isInFilter(const char & _Key) const
{
	if ( filter_.empty( ) )
		return true;
	for ( auto x : filter_ )
		if ( x == _Key )
			return true;
	return false;
}

bool Textbox::isWriting() const
{
	return canwrite_;
}

void Textbox::setLooseFocusKey( char key )
{
	loose_ = key;
}

void Textbox::setCanWrite( bool can )
{
	canwrite_ = can;
	OnModified( ).Invoke( this );
}

void Textbox::setPromptText( String text )
{
	prompt_ = std::move( text );
	OnModified( ).Invoke( this );
}

void Textbox::setPasswordChar( char character )
{
	passwordChar_ = character;
	OnModified( ).Invoke( this );
}

void Textbox::setUsePasswordChar(bool use)
{
	usePasswordChar_ = use;
	OnModified( ).Invoke( this );
}

void Textbox::setMultiline(bool can)
{
	multiline_ = can;
	OnModified( ).Invoke( this );
}

void Textbox::setFilter( String filter )
{
	this->filter_ = filter;
	OnModified( ).Invoke( this );
}

void Textbox::addFilterCharacter(char character)
{
	this->filter_.push_back( character );
	OnModified( ).Invoke( this );
}

__LIB Event<void(Component*)>& Textbox::OnLostFocus()
{
	return _OnLostFocus;
}

__LIB Event<void(Component*)>& Textbox::OnGainFocus()
{
	return _OnGainFocus;
}
__LIB Event<void(Component*, const char&)> &Textbox::OnCharacterAdded( )
{
	return _OnCharacterAdded;
}


__MATH Vector2 Textbox::determineText(__MATH Vector2 & pos, __MATH Vector2 & text_size)
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


end_UI

