#include "TabControl.h"
#include "Tab.h"
#include "../Pen.h"
#include "../Text.h"
#include "../Font.h"

begin_UI

TabControl::TabControl()
	: Component(), cache_( ), changed_( true ), selected_( nullptr )
{
	OnModified( ) += [this]( Component *component )
	{
		changed_ = true;
	};
}

void TabControl::Paint(::dx::lib::Graphics::Window * sender, ::dx::lib::Graphics::BasePainter * painter)
{
	auto style = this->getStyle( );
	auto color = style.theme( ) == Dark ? 0xFF2C2C2C : 0xFFC8C8C8;
	auto pen_color = style.theme( ) == Dark ? Colors::White : Colors::Black;

	auto index = 0u;
	Math::Vector2 size{ 0, 400 };
	auto pos_current = determineRegion( ); 
	for ( auto &x : children_ )
	{
		auto text = x->getText( );
		auto pos = decltype(pos_current)();
		pos.size = x->getSize( );
		pos.position = pos_current.position + Math::Vector2{ pos.size.x * index, 0 };
		x->setLocalRegion( pos );
		auto font = x->getFont( );

		if ( !font )
			font = painter->defaultFont( );

		auto text_pos = determineText( pos.position, pos.size, text, font, index );
		auto text_size = sizecache_[index];

		Text text_r{ font, text, text_pos, text_size };
		
		painter->Paint( text_r, Pen( pen_color ) );
		painter->PaintRect( { { pos.position.x, pos.position.y + pos.size.y }, { pos.size.x, 5 } }, Pen( x == selected_ ? style.style( ) : 0xFF4B4B4B ) );
		++index;
		size.x += pos.size.x;
	}
	size_ = size;

	if ( size.x > 600 )
		size_.x = size.x;
	else
		size_.x = 600;

	if ( selected_ )
		selected_->Paint( sender, painter );
	else
		selected_ = reinterpret_cast<Tab*>( children_.empty( ) ? nullptr : children_.front( ) );
}

Math::Vector2 TabControl::get_tab_size( )
{
	return size_;
}

Tab * TabControl::selected()
{
	return selected_;
}

void TabControl::KeyDown(Window * sender, KeyDownArgs & args)
{
	if ( selected_ )
		selected_->KeyDown( sender, args );
}

void TabControl::KeyUp(Window * sender, KeyUpArgs & args)
{
	if ( selected_ )
		selected_->KeyUp( sender, args );
}

void TabControl::KeyDownChar(Window * sender, KeyDownCharArgs & args)
{
	if ( selected_ )
		selected_->KeyDownChar( sender, args );
}

void TabControl::MouseMoved(Window * sender, MouseMovedArgs & args)
{
	for ( auto &x : children_ )
		if ( x->Collides( args.position ) )
		{
			x->setHovered( true );
			args.handled = true;
		}
		else
			x->setHovered( false );

	if ( selected_ )
		selected_->MouseMoved( sender, args );
}

void TabControl::MouseClicked(Window * sender, MouseClickedArgs & args)
{
	for ( auto &x : children_ )
		if ( x->isHovered( ) )
		{
			x->setClicked( true );
			args.handled = true;
		}
		else
			x->setClicked( false );

	if ( selected_ )
		selected_->MouseClicked( sender, args );
}

void TabControl::MouseReleased(Window * sender, MouseReleasedArgs & args)
{
	for ( auto &x : children_ )
	{
		if ( x->isClicked( ) )
		{
			x->setClicked( false );
			select( (Tab*)x );
			args.handled = true;
			break;
		}
	}

	if ( selected_ )
		selected_->MouseReleased( sender, args );
}

void TabControl::MouseScrolled(Window * sender, ScrollArgs & args)
{
	if ( selected_ )
		selected_->MouseScrolled( sender, args );
}

void TabControl::MouseDoubleClicked(Window * sender, MouseClickedArgs & args)
{
	if ( selected_ )
		selected_->MouseDoubleClicked( sender, args );
}

void TabControl::remove_child(Component * child)
{
	__super::remove_child( child );
	if ( children_.empty( ) )
		selected_ = nullptr;
	else
		selected_ = (Tab*)children_.front( );
}

void TabControl::addTab(Tab * tab)
{
	if ( children_.empty( ) )
		select( tab );

	cache_.emplace_back( true );
	cachedet_.emplace_back( );
	sizecache_.emplace_back( );
	children_.emplace_back( tab );
	tab->setParent( this );
}

void TabControl::select(Tab * tab)
{
	if ( selected_ )
		selected_->setVisible( false );
	selected_ = tab;
	selected_->setVisible( true );
}

::dx::lib::Math::Vector2 TabControl::determineText(::dx::lib::Math::Vector2 & pos, ::dx::lib::Math::Vector2 &size, String text, std::shared_ptr<Font> font, ::dx::uint index)
{
	auto &determ = cachedet_[index];
	auto &changed = cache_[index];
	auto textSize = font->calculateMetrixOf( text );
	sizecache_[index] = textSize;

	auto align = getAlignment( );
	// Y is always gonna be in the middle for the sake of no clip
	determ.y = (size.y / 2 - textSize.y / 2) + pos.y;

	if ( align == Alignment::Center )
		determ.x = ( size.x / 2 - textSize.x / 2 ) + pos.x;
	else if ( align == Alignment::Left )
		determ.x = pos.x + 5;
	else
		determ.x = pos.x + size.x - (textSize.x + 5);
	return determ;
}





end_UI