#include "Slider.h"
#include "Textbox.h"
#include "RichLabel.h"
#include "../Pen.h"

begin_UI

Slider::Slider()
	: Component( )
{
	// Textbox to change the value of the slider
	// by using a textbox instead of the wheel.
	textbox_ = std::shared_ptr<Textbox>( new Textbox( ) );
	textbox_->setUIID( String("Slider_component_textbox").hash( ) );
	textbox_->setText( "0%" );
	textbox_->setFilter( "1234567890" );
	textbox_->setRightOf( this );
	textbox_->setAlignedOf( this );
	textbox_->setSize( { 50, 30 } );
	textbox_->setLooseFocusKey( '\r' );
	textbox_->setAlignment( Alignment::Left );

	maxDelta_ = 100;
	
	// When the textbox gains focus remove the '%'
	// character, otherwise there will be parsing errors
	textbox_->OnGainFocus( ) += []( Component *sender )
	{
		auto text = sender->getText( );
		uint npos = text.find( '%' );
		if ( npos == String::bad )
			return;
 
		text.erase( npos, 1 );
		sender->setText( text );
	};

	// When we lose focus then add the '%' again 
	// and also recalculate the delta and move the wheel.
	textbox_->OnLostFocus( ) += [this]( Component *sender )
	{
		auto text = sender->getText( );
		uint npos = text.find( '%' );
		if ( npos == String::bad )
		{
			this->delta_ = { text.to<float>( ), text.to<float>( ) };
			text.push_back( '%' );
			sender->setText( text );
			if ( this->delta_.x > this->maxDelta_ || this->delta_.y > this->maxDelta_ )
			{
				text = to_string( (int)this->maxDelta_ ) + "%";
				delta_ = { maxDelta_, maxDelta_ };
				sender->setText( text );
			}

			this->moveWheelToDelta( );
			return;
		}
 
		text.erase( npos, 1 );
		this->delta_ = { text.to<float>( ), text.to<float>( ) };

		if ( this->delta_.x > this->maxDelta_ || this->delta_.y > this->maxDelta_ )
		{
			text = to_string( (int)this->maxDelta_ ) + "%";
			delta_ = { maxDelta_, maxDelta_ };
			sender->setText( text );
		}

		this->moveWheelToDelta( );
	};

	
	OnModified( ) += [this]( Component *sender )
	{
		this->changed_ = true;		
		this->textbox_->setStyle( style_ );
		this->textbox_->setFont( font_ );
	};

	changed_ = true;
}

void Slider::Paint(Window *sender, BasePainter *painter)
{
	static Pen inner, outer{ Colors::White, 1 };
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, painter );

	// Determine pos
	auto pos = determineRegion( );

	if ( changed_ )
	{
		delta_.x = (wheel_.x / (local_.size.x - wheelSize_.x)) * maxDelta_;
		delta_.y = (wheel_.x / (local_.size.y - wheelSize_.y)) * maxDelta_;

		if ( layout_ == Horizontal )
			textbox_->setText( to_string( (int)delta_.x ) + "%" );
		else
			textbox_->setText( to_string( (int)delta_.y ) + "%" );

		changed_ = false;
	}
	
	// Style
	auto style = getStyle( );
	auto color_inner = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto color_outer = 0xFF4B4B4B;
	auto color_bar = decltype(color_inner)();

	if ( dragging_ )
		color_bar = style.style( );
	else
		color_bar  = 0x909090;

	painter->PaintRectOutlined( pos, inner, outer );
	painter->PaintRect( { pos.position + wheel_, wheelSize_ }, Pen( color_bar, 1 ) );
	
	textbox_->Paint( sender, painter );

	OnPostPaint( ).Invoke( this, painter );
}

void Slider::KeyDown(Window *sender, KeyDownArgs &args)
{
	textbox_->KeyDown( sender, args );
}

void Slider::KeyUp(Window *sender, ::dx::lib::Graphics::KeyUpArgs & args)
{
	textbox_->KeyUp( sender, args );
}

void Slider::KeyDownChar(Window *sender, ::dx::lib::Graphics::KeyDownCharArgs & args)
{
	textbox_->KeyDownChar( sender, args );
}

void Slider::MouseMoved(Window *sender, ::dx::lib::Graphics::MouseMovedArgs & args)
{
	//If dragging
	if ( dragging_ && inScrollableRegion( args.position ) )
	{
		if ( moved_.x != 0 && moved_.y != 0 )
		{
			auto increment = (args.position - determined_.position) - (moved_ - determined_.position);
			
			if ( layout_ == Horizontal )
			{ 
				wheel_.x += increment.x;
				if ( wheel_.x > (local_.size.x - wheelSize_.x) )
					wheel_.x = (local_.size.x - wheelSize_.x);
				if ( wheel_.x < 0 )
					wheel_.x = 0;
			}
			else
			{ 
				wheel_.y += increment.y;
				if ( wheel_.y > (local_.size.y - wheelSize_.y) )
					wheel_.y = (local_.size.y - wheelSize_.y);
				if ( wheel_.y < 0 )
					wheel_.y = 0;
			}
		}
		moved_ = args.position;
		changed_ = true;
	}

	textbox_->MouseMoved( sender, args );
}

void Slider::MouseClicked(Window *sender, ::dx::lib::Graphics::MouseClickedArgs & args)
{
	// If collides anywhere & pressing ctrl, then directly move
	// the wheel.
	if ( Collides( args.position ) && args.ctrl )
	{
		// Get the sub offset from mouse - determined_position.
		if ( layout_ == Horizontal )
			wheel_.x = (args.position.x) - determined_.position.x;
		else // |
			wheel_.y = (args.position.y) - determined_.position.y;
		this->changed_ = true;
	}

	// Collides with the wheel
	if ( CollidesWheel( args.position ) )
		dragging_ = true;
	else
	{
		dragging_ = false;
		moved_ = { 0, 0 };
	}
	
	textbox_->MouseClicked( sender, args );
}

void Slider::MouseReleased(Window *sender, ::dx::lib::Graphics::MouseReleasedArgs & args)
{
	if ( hovering_ )
		OnMouseReleased( ).Invoke( this );
	dragging_ = false;
	clicking_ = false;
	moved_ = { 0, 0 };
	textbox_->MouseReleased( sender, args );
}

::dx::lib::Math::Vector2 Slider::getDelta() const
{
	return delta_;
}

void Slider::setMaxDelta(const float & _Delta)
{
	maxDelta_ = _Delta;
}

float Slider::getMaxDelta() const
{
	return maxDelta_;
}

void Slider::setWheel(const float & _Delta)
{
	if ( layout_ == Horizontal )
		wheel_.x = _Delta;
	else
		wheel_.y = _Delta;
}




float Slider::getWheel( ) const
{
	if ( layout_ == Horizontal )
		return wheel_.x;
	else
		return wheel_.y;
}

void Slider::setWheelSize(const ::dx::lib::Math::Vector2 & _Size)
{
	wheelSize_ = _Size;
	changed_ = true;
}

::dx::lib::Math::Vector2 Slider::getWheelSize() const
{
	return wheelSize_;
}

bool Slider::CollidesWheel(const ::dx::lib::Math::Vector2 & _Position)
{
	return _Position.Intersects( { determined_.position + wheel_, wheelSize_ } );
}

bool Slider::inScrollableRegion(const ::dx::lib::Math::Vector2 & _Cursor) const
{
	return (layout_ == Horizontal ? 
		   _Cursor.Intersects( { { determined_.position.x, 0 }, { determined_.size.x, 10000000 } } ) : 
		   _Cursor.Intersects( { { 0, determined_.position.y }, { 10000000, determined_.size.y } } ) );
}

std::shared_ptr<Textbox> Slider::getTextbox() const
{
	return textbox_;
}


void Slider::moveWheelToDelta()
{
	if ( layout_ == Horizontal )
	{
		auto wheel = (delta_.x / maxDelta_) * (local_.size.x - wheelSize_.x);
		wheel_.x = wheel;
	}
	else
	{
		auto wheel = (delta_.y / maxDelta_) * (local_.size.y - wheelSize_.y);
		wheel_.y = wheel;
	}
}

end_UI