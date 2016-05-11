#include "Component.h"
#include "../Font.h"

begin_UI

Component::Component()
	: local_( ), global_( ), style_( Dark, Blue ), leftOf_( nullptr ),
	  rightOf_( nullptr ), bottomOf_( nullptr ), topOf_( nullptr ),
	  parent_( nullptr ), alignment_( Center ), layout_( Horizontal ),
	  state_( 0 ), hovering_( false ), focusing_( false ), clicking_( false ),
	  enabled_( true ), visible_( true ), userdata_( nullptr ), region_changed_( true )
{

}

Component::~Component()
{
	Release( );
}

bool Component::empty() const
{
	return children_.empty( );
}

::dx::lib::Math::Region Component::getLocalRegion() const
{
	return local_;
}

::dx::lib::Math::Vector2 Component::getLocalPosition() const
{
	return local_.position;
}

::dx::lib::Math::Region Component::getGlobalRegion() const
{
	return global_;
}

::dx::lib::Math::Region Component::determineRegion()
{
	if ( region_changed_ ) 
	{
		determined_.position = local_.position + global_.position;
		determined_.size = local_.size;
		
		// Determine X axis
		if ( leftOf_ )
		{
			auto detLeft = leftOf_->determineRegion( );
			determined_.position.x = detLeft.position.x - local_.size.x - 15;
		}
		else if ( rightOf_ )
		{
			auto detRight = rightOf_->determineRegion( );
			determined_.position.x = detRight.position.x + detRight.size.x + 15;
		}
		
		if ( bottomOf_ )
		{
			auto detBottom = bottomOf_->determineRegion( );
			determined_.position.y = detBottom.position.y + bottomOf_->local_.size.y + 15;
		}
		else if ( topOf_ )
		{
			auto detTop = topOf_->determineRegion( );
			determined_.position.y = detTop.position.y - 15;
		}
		
		if ( alignedOf_ && ( determined_.position.x == 0 || determined_.position.y == 0 ) )
		{
			auto detAlign = alignedOf_->determineRegion( );
			if ( determined_.position.y == 0 )
				determined_.position.y = detAlign.position.y;
			if ( determined_.position.x == 0 )
				determined_.position.x = detAlign.position.x;
		}
		region_changed_ = false;
	}

	return determined_;
}

::dx::lib::Math::Vector2 Component::getGlobalPosition() const
{
	return global_.position;
}

::dx::lib::Math::Vector2 Component::getSize() const
{
	return local_.size;
}

::dx::lib::Graphics::UI::StyleManager Component::getStyle() const
{
	return style_;
}

::dx::lib::Graphics::UI::Component * Component::getLeftOf() const
{
	return leftOf_;
}

::dx::lib::Graphics::UI::Component * Component::getRightOf() const
{
	return rightOf_;
}

::dx::lib::Graphics::UI::Component * Component::getBottomOf() const
{
	return bottomOf_;
}

::dx::lib::Graphics::UI::Component * Component::getTopOf() const
{
	return topOf_;
}

::dx::lib::Graphics::UI::Component * Component::getAlignedOf() const
{
	return alignedOf_;
}

::dx::lib::Graphics::UI::Component * Component::getParent() const
{
	return parent_;
}

std::vector<Component*> Component::getChildren() const
{
	return children_;
}

::dx::lib::Graphics::UI::Alignment Component::getAlignment() const
{
	return alignment_;
}

::dx::lib::Graphics::UI::Layout Component::getLayout() const
{
	return layout_;
}

int Component::getState() const
{
	return state_;
}

bool Component::isHovered() const
{
	return hovering_;
}

bool Component::isFocused() const
{
	return focusing_;
}

bool Component::isClicked() const
{
	return clicking_;
}

bool Component::isEnabled() const
{
	return enabled_;
}

bool Component::isVisible() const
{
	return visible_;
}

void * Component::getUserdata() const
{
	return userdata_;
}

std::shared_ptr<Font> Component::getFont() const
{
	return font_;
}

int Component::getUIID() const
{
	return uiid_;
}

::dx::lib::String Component::getText() const
{
	return text_;
}

void Component::clear()
{
	this->children_.clear( );
}

void Component::setLocalRegion(const ::dx::lib::Math::Region & region)
{
	local_ = region;
	global_.size = local_.size;
	region_changed_ = true;

	if ( leftOf_ )
		leftOf_->region_changed_ = true;
	else if ( rightOf_ )
		rightOf_->region_changed_ = true;
	
	if ( bottomOf_ )
		bottomOf_->region_changed_ = true;
	else if ( topOf_ )
		topOf_->region_changed_ = true;

	if ( alignedOf_ )
		alignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setLocalPosition(const ::dx::lib::Math::Vector2 & position)
{
	local_.position = position;
	region_changed_ = true;

	if ( leftOf_ )
		leftOf_->region_changed_ = true;
	else if ( rightOf_ )
		rightOf_->region_changed_ = true;
	
	if ( bottomOf_ )
		bottomOf_->region_changed_ = true;
	else if ( topOf_ )
		topOf_->region_changed_ = true;

	if ( alignedOf_ )
		alignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setGlobalRegion(const ::dx::lib::Math::Region & region)
{
	global_ = region;
	local_.size = global_.size;
	region_changed_ = true;

	if ( leftOf_ )
		leftOf_->region_changed_ = true;
	else if ( rightOf_ )
		rightOf_->region_changed_ = true;
	
	if ( bottomOf_ )
		bottomOf_->region_changed_ = true;
	else if ( topOf_ )
		topOf_->region_changed_ = true;

	if ( alignedOf_ )
		alignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setGlobalPosition(const ::dx::lib::Math::Vector2 & position)
{
	global_.position = position;
	region_changed_ = true;

	if ( leftOf_ )
		leftOf_->region_changed_ = true;
	else if ( rightOf_ )
		rightOf_->region_changed_ = true;
	
	if ( bottomOf_ )
		bottomOf_->region_changed_ = true;
	else if ( topOf_ )
		topOf_->region_changed_ = true;

	if ( alignedOf_ )
		alignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setSize(const ::dx::lib::Math::Vector2 & size)
{
	local_.size = size;
	global_.size = size;
	region_changed_ = true;

	if ( leftOf_ )
		leftOf_->region_changed_ = true;
	else if ( rightOf_ )
		rightOf_->region_changed_ = true;
	
	if ( bottomOf_ )
		bottomOf_->region_changed_ = true;
	else if ( topOf_ )
		topOf_->region_changed_ = true;

	if ( alignedOf_ )
		alignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setStyle(const ::dx::lib::Graphics::UI::StyleManager & style)
{
	style_ = style;
	OnModified( ).Invoke( this );
}

void Component::setLeftOf(::dx::lib::Graphics::UI::Component * component)
{
	if ( leftOf_ )
		leftOf_->OnModified( ) -= "leftof_modified";

	leftOf_ = component;

	if ( leftOf_ )
		leftOf_->OnModified( ) += EventHandler<void(Component*)>( "leftof_modified", [this]( Component *component ) { this->region_changed_ = true; } );

	OnModified( ).Invoke( this );
}

void Component::setRightOf(::dx::lib::Graphics::UI::Component * component)
{
	if ( rightOf_ )
		rightOf_->OnModified( ) -= "rightof_modified";

	rightOf_ = component;

	if ( rightOf_ )
		rightOf_->OnModified( ) += EventHandler<void(Component*)>( "rightof_modified", [this]( Component *component ) { this->region_changed_ = true; } );

	OnModified( ).Invoke( this );
}

void Component::setBottomOf(::dx::lib::Graphics::UI::Component * component)
{
	if ( bottomOf_ )
		bottomOf_->OnModified( ) -= "bottomof_modified";

	bottomOf_ = component;

	if ( bottomOf_ )
		bottomOf_->OnModified( ) += EventHandler<void(Component*)>( "bottomof_modified", [this]( Component *component ) { this->region_changed_ = true; } );

	OnModified( ).Invoke( this );
}

void Component::setTopOf(::dx::lib::Graphics::UI::Component * component)
{
	if ( alignedOf_ )
		alignedOf_->OnModified( ) -= "topof_modified";

	topOf_ = component;

	if ( topOf_ )
		topOf_->OnModified( ) += EventHandler<void(Component*)>( "topof_modified", [this]( Component *component ) { this->region_changed_ = true; } );

	OnModified( ).Invoke( this );
}

void Component::setAlignedOf(::dx::lib::Graphics::UI::Component * component)
{
	if ( alignedOf_ )
		alignedOf_->OnModified( ) -= "alignedof_modified";

	alignedOf_ = component;

	if ( leftOf_ != alignedOf_ && rightOf_ != alignedOf_ && 
		 bottomOf_ != alignedOf_ && topOf_ != alignedOf_ && leftOf_ )
		alignedOf_->OnModified( ) += EventHandler<void(Component*)>( "alignedof_modified", [this]( Component *component ) { this->region_changed_ = true; } );

	OnModified( ).Invoke( this );
}

void Component::setParent(::dx::lib::Graphics::UI::Component * parent)
{
	parent_ = parent;
	OnModified( ).Invoke( this );
}

void Component::setAlignment(const ::dx::lib::Graphics::UI::Alignment & allignment)
{
	alignment_ = allignment;
	OnModified( ).Invoke( this );
}

void Component::setLayout(const ::dx::lib::Graphics::UI::Layout & layout)
{
	layout_ = layout;
	OnModified( ).Invoke( this );
}

void Component::setState( const int &state )
{
	state_ = state;
	OnModified( ).Invoke( this );
}

void Component::setHovered(const bool & hovered)
{
	hovering_ = hovered;
	OnModified( ).Invoke( this );
}

void Component::setFocused(const bool & focused)
{
	focusing_ = focused;
	OnModified( ).Invoke( this );
}

void Component::setClicked(const bool & clicked)
{
	clicking_ = clicked;
	OnModified( ).Invoke( this );
}

void Component::setEnabled(const bool & enabled)
{
	enabled_ = enabled;
	OnModified( ).Invoke( this );
}

void Component::setVisible(const bool & visible)
{
	visible_ = visible;
	OnModified( ).Invoke( this );
}

void Component::setUserdata(void * data)
{
	userdata_ = data;
	OnModified( ).Invoke( this );
}

void Component::setFont(std::shared_ptr<Font> font)
{
	font_ = font;
	OnModified( ).Invoke( this );
}

void Component::setUIID(const int & id)
{
	uiid_ = id;
	OnModified( ).Invoke( this );
}

void Component::setText(const ::dx::lib::String & text)
{
	text_ = text;
	OnModified( ).Invoke( this );
}

void Component::flipLayout()
{
	if ( layout_ == Horizontal )
		setLayout( Vertical );
	else
		setLayout( Horizontal );
}

void Component::remove_child(Component * child)
{
	for ( auto it = children_.begin( ), end = children_.end( ); it < end; ++it )
	{
		auto x = *it;
		if ( x == child )
		{
			children_.erase( it );
			break;
		}
	}
}

void Component::KeyDown(Window* sender, KeyDownArgs &args)
{
}

void Component::KeyUp(Window* sender, KeyUpArgs &args)
{
}

void Component::KeyDownChar(Window* _Sender, KeyDownCharArgs &args)
{
}

void Component::MouseMoved(Window* _Sender, MouseMovedArgs &args)
{
	if ( Collides( args.position ) && !args.handled )
	{
		if ( !this->hovering_ )
		{
			this->hovering_ = true;
			OnMouseEnter( ).Invoke( this );
		}
		args.handled = true;
	}
	else if ( this->hovering_ )
	{
		this->hovering_ = false;
		OnMouseLeave( ).Invoke( this );
		args.handled = true;
	}
}

void Component::MouseClicked(Window* sender, MouseClickedArgs &args)
{
	if ( args.handled )
		return;

	if ( this->hovering_ && !this->clicking_ )
	{
		OnMousePressed( ).Invoke( this );
		this->clicking_ = true;
		args.handled = true;
	}
	else
		this->clicking_ = false;
}

void Component::MouseReleased(Window* sender, MouseReleasedArgs &args)
{
	if ( this->hovering_ && this->clicking_ ) {
		OnMouseReleased( ).Invoke( this );
		args.handled = true;
	}
	this->clicking_ = false;
}

void Component::MouseScrolled(Window* sender, ScrollArgs &args)
{
}

void Component::MouseDoubleClicked(Window* sender, MouseClickedArgs &args)
{
}

void Component::Release(const bool & releaseChildren)
{
	OnRelease( ).Invoke( this );
	if ( releaseChildren )
	{
		for ( auto &x : children_ )
			x->Release( true );
	}
}

bool Component::Collides(const ::dx::lib::Math::Vector2 & with)
{
	auto region = determineRegion( );
	auto size = local_.size;
	return with.Intersects( { region.position, size } );
}

bool Component::Collides(const ::dx::lib::Graphics::UI::Component * with)
{
	return Collides( with->getLocalPosition( ) + with->getGlobalPosition( ) );
}

::dx::lib::Event<void(Component*)>& Component::OnModified( )
{
	return _OnModified;
}

::dx::lib::Event<void(Component*)>& Component::OnMouseEnter()
{
	return _OnMouseEnter;
}

::dx::lib::Event<void(Component*)>& Component::OnMouseLeave()
{
	return _OnMouseLeave;
}

::dx::lib::Event<void(Component*)>& Component::OnMousePressed()
{
	return _OnMousePressed;
}

::dx::lib::Event<void(Component*)>& Component::OnMouseReleased()
{
	return _OnMouseReleased;
}

::dx::lib::Event<void(Component*, ::dx::lib::Graphics::BasePainter*)>& Component::OnPrePaint()
{
	return _OnPrePaint;
}

::dx::lib::Event<void(Component*, ::dx::lib::Graphics::BasePainter*)>& Component::OnPostPaint()
{
	return _OnPostPaint;
}

::dx::lib::Event<void(Component*)>& Component::OnRelease()
{
	return _OnRelease;
}



end_UI