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

void Textbox::Paint(__GRAPHICS Window * _Sender, __GRAPHICS BasePainter * _Painter)
{
	static Pen outer{ Colors::White, 2 }, pen_text{ Colors::White, 2 };
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, _Painter );

	// pos
	auto pos = determineRegion( );
	
	// Font
	auto font = getFont( );
	if ( !font )
		font = _Painter->defaultFont( );
	

	// Setup text
	auto myText = getText( );
	if ( myText.empty( ) )
		myText = _prompt;
	else if ( _usePasswordChar )
		myText = myText.fill( _passwordChar );
	
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

	_Painter->PaintLine( line );
	_Painter->Paint( text, pen_text );

	if ( _canwrite  )
	{
		if ( GetTickCount( ) > _lblink )
		{
			_lblink = GetTickCount( ) + 500;
			_blink = !_blink;
		}

		if ( _blink ) {
			__MATH Vector2 lpos = text.getPosition( );
			lpos.x += textsize.x + 2;
			lpos.y = pos.position.y + 2;
			auto tlpos = lpos;
			tlpos.y = pos.position.y + pos.size.y - 2;
			Line line{ lpos, tlpos, Pen( Colors::White, 1 ) };
			_Painter->PaintLine( line );
		}
	}

	OnPostPaint( ).Invoke( this, _Painter );
}



void Textbox::KeyDownChar(__GRAPHICS Window * _Sender, __GRAPHICS KeyDownCharArgs & _Args)
{
	if ( _Args.handled )
		return;

	if ( _canwrite )
	{
		auto text = getText( );
		auto font = getFont();
		if ( !font )
			font = _Sender->getPainter( )->defaultFont( );

		auto key = _Args.key_char;
		if ( key == _loose )
		{
			_canwrite = false;
			OnLostFocus( ).Invoke( this );
			return;
		}

		if ( key == '\n' && !isMultiline( ) )
			return;
		
		if ( key == '\b' && !text.empty( ) )
			text.pop_back( );
		else if ( key != '\b' && isInFilter( key ) )
			text.push_back( key );
		setText( text );
		OnCharacterAdded( ).Invoke( this, key );

		_Sender->ForcePaint( );
		_Args.handled = true;
	}
}

void Textbox::MouseClicked(__GRAPHICS Window * _Sender, __GRAPHICS MouseClickedArgs & _Args)
{
	__super::MouseClicked( _Sender, _Args );
	if ( !isClicked( ) ) 
	{
		_canwrite = false;
		OnLostFocus( ).Invoke( this );
	}
}

void Textbox::MouseReleased(__GRAPHICS Window * _Sender, __GRAPHICS MouseReleasedArgs & _Args)
{
	if ( Collides( _Args.position ) )
	{
		if ( isClicked( ) )
		{
			_canwrite = true;
			setClicked( false );
			OnMousePressed( ).Invoke( this );
			OnGainFocus( ).Invoke( this );
		}
	}
}

bool Textbox::getCanWrite() const
{
	return _canwrite;
}

bool Textbox::isMultiline() const
{
	return _multiline;
}

__LIB String Textbox::getPromptText() const
{
	return _prompt;
}

__LIB String Textbox::getFilter() const
{
	return _filter;
}

char Textbox::getPasswordChar() const
{
	return _passwordChar;
}

bool Textbox::getUsePasswordChar() const
{
	return _usePasswordChar;
}

char Textbox::getLooseFocusKey() const
{
	return _loose;
}

bool Textbox::isInFilter(const char & _Key) const
{
	if ( _filter.empty( ) )
		return true;
	for ( auto x : _filter )
		if ( x == _Key )
			return true;
	return false;
}

bool Textbox::isWriting() const
{
	return _canwrite;
}

void Textbox::setLooseFocusKey(const char & _Key)
{
	_loose = _Key;
}

void Textbox::setCanWrite(const bool & _Can)
{
	_canwrite = _Can;
	OnModified( ).Invoke( this );
}

void Textbox::setPromptText(const __LIB String & _Text)
{
	_prompt = _Text;
	OnModified( ).Invoke( this );
}

void Textbox::setPasswordChar( const char &_Char )
{
	_passwordChar = _Char;
	OnModified( ).Invoke( this );
}

void Textbox::setUsePasswordChar(const bool & _Use)
{
	_usePasswordChar = _Use;
	OnModified( ).Invoke( this );
}

void Textbox::setMultiline(const bool & _Can)
{
	_multiline = _Can;
	OnModified( ).Invoke( this );
}

void Textbox::setFilter(const __LIB String & _Filter)
{
	this->_filter = _Filter;
	OnModified( ).Invoke( this );
}

void Textbox::addFilterCharacter(const char & _Character)
{
	this->_filter.push_back( _Character );
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

