#include "Slider.h"
#include "Textbox.h"
#include "RichLabel.h"
#include "../Pen.h"

begin_UI

Slider::Slider()
	: Component( )
{
	_textbox = new Textbox( );
	_textbox->setUIID( String("Slider_component_textbox").hash( ) );
	_textbox->setText( "0%" );
	_textbox->setFilter( "1234567890" );
	_textbox->setRightOf( this );
	_textbox->setAllignedOf( this );
	_textbox->setSize( { 50, 30 } );
	_textbox->setLooseFocusKey( '\r' );

	_maxDelta = 100;
	
	_textbox->OnGainFocus( ) += []( Component *sender )
	{
		auto text = sender->getText( );
		uint npos = text.find( '%' );
		if ( npos == String::bad )
			return;
 
		text.erase( npos, 1 );
		sender->setText( text );
	};

	_textbox->OnLostFocus( ) += [this]( Component *sender )
	{
		auto text = sender->getText( );
		uint npos = text.find( '%' );
		if ( npos == String::bad )
		{
			this->_delta = { text.to<float>( ), text.to<float>( ) };
			text.push_back( '%' );
			sender->setText( text );
			if ( this->_delta.x > this->_maxDelta || this->_delta.y > this->_maxDelta )
			{
				text = to_string( (int)this->_maxDelta ) + "%";
				_delta = { _maxDelta, _maxDelta };
				sender->setText( text );
			}

			this->moveWheelToDelta( );
			return;
		}
 
		text.erase( npos, 1 );
		this->_delta = { text.to<float>( ), text.to<float>( ) };

		if ( this->_delta.x > this->_maxDelta || this->_delta.y > this->_maxDelta )
		{
			text = to_string( (int)this->_maxDelta ) + "%";
			_delta = { _maxDelta, _maxDelta };
			sender->setText( text );
		}

		this->moveWheelToDelta( );
	};

	
	OnModified( ) += [this]( Component *sender )
	{
		this->_changed = true;		
		this->_textbox->setStyle( this->_style );
		this->_textbox->setFont( this->_font );
	};

	_changed = true;
}

Slider::~Slider()
{
	_textbox->Release( );
	delete _textbox;
}

void Slider::Paint(__GRAPHICS Window * _Sender, __GRAPHICS BasePainter * _Painter)
{
	static Pen inner, outer{ Colors::White, 1 };
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, _Painter );

	// Determine pos
	auto pos = determineRegion( );

	if ( _changed )
	{
		_delta.x = (_wheel.x / (_local.size.x - _wheelSize.x)) * _maxDelta;
		_delta.y = (_wheel.x / (_local.size.y - _wheelSize.y)) * _maxDelta;

		if ( _layout == Horizontal )
			_textbox->setText( __LIB to_string( (int)_delta.x ) + "%" );
		else
			_textbox->setText( __LIB to_string( (int)_delta.y ) + "%" );

		_changed = false;
	}
	
	// Style
	auto style = getStyle( );
	auto color_inner = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto color_outer = 0xFF4B4B4B;
	auto color_bar = decltype(color_inner)();

	if ( _dragging )
		color_bar = style.style( );
	else
		color_bar  = 0x909090;

	_Painter->PaintRectOutlined( pos, inner, outer );
	_Painter->PaintRect( { pos.position + _wheel, _wheelSize }, Pen( color_bar, 1 ) );
	
	_textbox->Paint( _Sender, _Painter );

	OnPostPaint( ).Invoke( this, _Painter );
}

void Slider::KeyDown(__GRAPHICS Window * _Sender, __GRAPHICS KeyDownArgs & _Args)
{
	__super::KeyDown( _Sender, _Args );
	_textbox->KeyDown( _Sender, _Args );
}

void Slider::KeyUp(__GRAPHICS Window * _Sender, __GRAPHICS KeyUpArgs & _Args)
{
	__super::KeyUp( _Sender, _Args );
	_textbox->KeyUp( _Sender, _Args );
}

void Slider::KeyDownChar(__GRAPHICS Window * _Sender, __GRAPHICS KeyDownCharArgs & _Args)
{
	__super::KeyDownChar( _Sender, _Args );
	_textbox->KeyDownChar( _Sender, _Args );
}

void Slider::MouseMoved(__GRAPHICS Window * _Sender, __GRAPHICS MouseMovedArgs & _Args)
{
	//If dragging
	if ( _dragging && inScrollableRegion( _Args.position ) )
	{
		if ( _moved.x != 0 && _moved.y != 0 )
		{
			auto increment = (_Args.position - _determined.position) - (_moved - _determined.position);
			
			if ( _layout == Horizontal )
			{ 
				_wheel.x += increment.x;
				if ( _wheel.x > (_local.size.x - _wheelSize.x) )
					_wheel.x = (_local.size.x - _wheelSize.x);
				if ( _wheel.x < 0 )
					_wheel.x = 0;
			}
			else
			{ 
				_wheel.y += increment.y;
				if ( _wheel.y > (_local.size.y - _wheelSize.y) )
					_wheel.y = (_local.size.y - _wheelSize.y);
				if ( _wheel.y < 0 )
					_wheel.y = 0;
			}
		}
		_moved = _Args.position;
		_changed = true;
	}

	_textbox->MouseMoved( _Sender, _Args );
}

void Slider::MouseClicked(__GRAPHICS Window * _Sender, __GRAPHICS MouseClickedArgs & _Args)
{
	// If collides anywhere & pressing ctrl, then directly move
	// the wheel.
	if ( Collides( _Args.position ) && _Args.ctrl )
	{
		// Get the sub offset from mouse - determined_position.
		if ( _layout == Horizontal )
			_wheel.x = (_Args.position.x) - _determined.position.x;
		else // |
			_wheel.y = (_Args.position.y) - _determined.position.y;
		this->_changed = true;
	}

	// Collides with the wheel
	if ( CollidesWheel( _Args.position ) )
		_dragging = true;
	else
	{
		_dragging = false;
		_moved = { 0, 0 };
	}
	
	_textbox->MouseClicked( _Sender, _Args );
}

void Slider::MouseReleased(__GRAPHICS Window * _Sender, __GRAPHICS MouseReleasedArgs & _Args)
{
	if ( _hovering )
		OnMouseReleased( ).Invoke( this );
	_dragging = false;
	_clicking = false;
	_moved = { 0, 0 };
	_textbox->MouseReleased( _Sender, _Args );
}

__MATH Vector2 Slider::getDelta() const
{
	return _delta;
}

void Slider::setMaxDelta(const float & _Delta)
{
	_maxDelta = _Delta;
}

float Slider::getMaxDelta() const
{
	return _maxDelta;
}

void Slider::setWheel(const float & _Delta)
{
	if ( _layout == Horizontal )
		_wheel.x = _Delta;
	else
		_wheel.y == _Delta;
}




float Slider::getWheel( ) const
{
	if ( _layout == Horizontal )
		return _wheel.x;
	else
		return _wheel.y;
}

void Slider::setWheelSize(const __MATH Vector2 & _Size)
{
	_wheelSize = _Size;
	_changed = true;
}

__MATH Vector2 Slider::getWheelSize() const
{
	return _wheelSize;
}

bool Slider::CollidesWheel(const __MATH Vector2 & _Position)
{
	return _Position.Intersects( { _determined.position + _wheel, _wheelSize } );
}

bool Slider::inScrollableRegion(const __MATH Vector2 & _Cursor) const
{
	return (_layout == Horizontal ? 
		   _Cursor.Intersects( { { _determined.position.x, 0 }, { _determined.size.x, 100000 } } ) : 
		   _Cursor.Intersects( { { 0, _determined.position.y }, { 100000, _determined.size.y } } ) );
}

const Textbox * Slider::getTextbox() const
{
	return _textbox;
}


void Slider::moveWheelToDelta()
{
	if ( _layout == Horizontal )
	{
		auto wheel = (_delta.x / _maxDelta) * (_local.size.x - _wheelSize.x);
		_wheel.x = wheel;
	}
	else
	{
		auto wheel = (_delta.y / _maxDelta) * (_local.size.y - _wheelSize.y);
		_wheel.y = wheel;
	}
}

end_UI