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

		if ( this->_layout == Horizontal ) 
		{
			this->_wheelSize.y = this->_local.size.y;
			this->_wheelSize.x = 15;
		}
		else
		{
			this->_wheelSize.x = this->_local.size.x;
			this->_wheelSize.y = 15;
		}
		
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

	// First lets do some nasty calculations
	if ( _changed )
	{
		// _barPos.x / (getSize().x - _barSize.x)) * getMax();
		// Lets calcualte the delta of X
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
	if ( _dragging )
	{
		// __
		if ( _layout == Horizontal )
		{
			auto delta = (_Args.position.x) - _determined.position.x;
			if ( delta > 0 && delta <= (_local.size.x - _wheelSize.x) )
				_wheel.x = delta;
			this->_changed = true;
		}
		else // |
		{
			auto delta = (_Args.position.y) - _determined.position.y;
			if ( delta > 0 && delta <= (_local.size.y - _wheelSize.y) )
				_wheel.y = delta;
			this->_changed = true;
		}
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
		{
			_wheel.x = (_Args.position.x) - _determined.position.x;
			this->_changed = true;
		}
		else // |
		{
			_wheel.y = (_Args.position.y) - _determined.position.y;
			this->_changed = true;
		}
		this->_changed = true;
		this->_hovering = true;
	}


	// If hovering
	if ( _hovering )
	{
		// Do stuff
		
		// If was not already clicking then raise mousepressed event.
		if ( !_clicking )
			OnMousePressed( ).Invoke( this );
		// Set
		this->_clicking = true;
		this->_moved = { 0, 0 };
	}
	else
	{
		// set
		this->_clicking = false;
		this->_moved = { 0, 0 };
	}

	// Collides with the wheel
	if ( CollidesWheel( _Args.position ) )
		_dragging = true;
	else
		_dragging = false;
	
	_textbox->MouseClicked( _Sender, _Args );
}

void Slider::MouseReleased(__GRAPHICS Window * _Sender, __GRAPHICS MouseReleasedArgs & _Args)
{
	if ( _hovering )
		OnMouseReleased( ).Invoke( this );
	_dragging = false;
	_clicking = false;
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

bool Slider::CollidesWheel(const __MATH Vector2 & _Position)
{
	return _Position.Intersects( { _determined.position + _wheel, _wheelSize } );
}


const Textbox * Slider::getTextbox() const
{
	return _textbox;
}

void Slider::moveWheelToDelta()
{

	// return ((float)getState() / getMax()) * (getSize().x - _barSize.x);
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