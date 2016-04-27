#include "Component.h"
#include "../Font.h"

begin_UI

Component::Component()
	: local_( ), global_( ), style_( Dark, Blue ), leftOf_( nullptr ),
	  rightOf_( nullptr ), bottomOf_( nullptr ), topOf_( nullptr ),
	  parent_( nullptr ), allignment_( Center ), layout_( Horizontal ),
	  state_( 0 ), hovering_( false ), focusing_( false ), clicking_( false ),
	  enabled_( true ), visible_( true ), userdata_( nullptr ), region_changed_( true )
{

}

Component::~Component()
{
	Release( );
}

__MATH Region Component::getLocalRegion() const
{
	return local_;
}

__MATH Vector2 Component::getLocalPosition() const
{
	return local_.position;
}

__MATH Region Component::getGlobalRegion() const
{
	return global_;
}

__MATH Region Component::determineRegion()
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
		
		if ( allignedOf_ && ( determined_.position.x == 0 || determined_.position.y == 0 ) )
		{
			auto detAllign = allignedOf_->determineRegion( );
			if ( determined_.position.y == 0 )
				determined_.position.y = detAllign.position.y;
			if ( determined_.position.x == 0 )
				determined_.position.x = detAllign.position.x;
		}
		region_changed_ = false;
	}

	return determined_;
}

__MATH Vector2 Component::getGlobalPosition() const
{
	return global_.position;
}

__MATH Vector2 Component::getSize() const
{
	return local_.size;
}

__UI StyleManager Component::getStyle() const
{
	return style_;
}

__UI Component * Component::getLeftOf() const
{
	return leftOf_;
}

__UI Component * Component::getRightOf() const
{
	return rightOf_;
}

__UI Component * Component::getBottomOf() const
{
	return bottomOf_;
}

__UI Component * Component::getTopOf() const
{
	return topOf_;
}

__UI Component * Component::getAllignedOf() const
{
	return allignedOf_;
}

__UI Component * Component::getParent() const
{
	return parent_;
}

__UI Allignment Component::getAllignment() const
{
	return allignment_;
}

__UI Layout Component::getLayout() const
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

__LIB String Component::getText() const
{
	return text_;
}

void Component::setLocalRegion(const __MATH Region & region)
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

	if ( allignedOf_ )
		allignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setLocalPosition(const __MATH Vector2 & position)
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

	if ( allignedOf_ )
		allignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setGlobalRegion(const __MATH Region & region)
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

	if ( allignedOf_ )
		allignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setGlobalPosition(const __MATH Vector2 & position)
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

	if ( allignedOf_ )
		allignedOf_->region_changed_ = true;

	OnModified( ).Invoke( this );
}

void Component::setSize(const __MATH Vector2 & size)
{
	local_.size = size;
	global_.size = size;
	region_changed_ = true;
	OnModified( ).Invoke( this );
}

void Component::setStyle(const __UI StyleManager & style)
{
	style_ = style;
	OnModified( ).Invoke( this );
}

void Component::setLeftOf(__UI Component * component)
{
	if ( leftOf_ )
		leftOf_->OnModified( ).remove_handler( __LIB to_string( this->getUIID( ) ) + "_leftof" );

	leftOf_ = component;
	
	if ( leftOf_ )
		leftOf_->OnModified( ) += __LIB EventHandler<void(Component*)>( __LIB to_string( this->getUIID( ) ) + "_leftof", 
								  [this]( Component* sender )
								  {
									  region_changed_ = true;
								  	  this->OnModified( ).Invoke( this );
								  });
	OnModified( ).Invoke( this );
}

void Component::setRightOf(__UI Component * component)
{
	if ( rightOf_ )
		rightOf_->OnModified( ).remove_handler( __LIB to_string( this->getUIID( ) ) + "_rightof" );

	rightOf_ = component;
	
	if ( rightOf_ )
		rightOf_->OnModified( ) += __LIB EventHandler<void(Component*)>( __LIB to_string( this->getUIID( ) ) + "_rightof", 
								  [this]( Component* sender )
								  {
									  region_changed_ = true;
								  	  this->OnModified( ).Invoke( this );
								  });
	OnModified( ).Invoke( this );
}

void Component::setBottomOf(__UI Component * component)
{
	if ( bottomOf_ )
		bottomOf_->OnModified( ).remove_handler( __LIB to_string( this->getUIID( ) ) + "_bottomof" );

	bottomOf_ = component;
	
	if ( bottomOf_ )
		bottomOf_->OnModified( ) += __LIB EventHandler<void(Component*)>( __LIB to_string( this->getUIID( ) ) + "_bottomof", 
								  [this]( Component* sender )
								  {
									  region_changed_ = true;
								  	  this->OnModified( ).Invoke( this );
								  });
	OnModified( ).Invoke( this );
}

void Component::setTopOf(__UI Component * component)
{
	if ( topOf_ )
		topOf_->OnModified( ).remove_handler( __LIB to_string( this->getUIID( ) ) + "_topof" );

	topOf_ = component;
	
	if ( topOf_ )
		topOf_->OnModified( ) += __LIB EventHandler<void(Component*)>( __LIB to_string( this->getUIID( ) ) + "_topof",
								  [this]( Component* sender )
								  {
									  region_changed_ = true;
								  	  this->OnModified( ).Invoke( this );
								  });
	OnModified( ).Invoke( this );
}

void Component::setAllignedOf(__UI Component * component)
{
	if ( allignedOf_ )
		allignedOf_->OnModified( ).remove_handler( __LIB to_string( this->getUIID( ) ) + "_allignedof" );

	allignedOf_ = component;
	
	if ( allignedOf_ )
		allignedOf_->OnModified( ) += __LIB EventHandler<void(Component*)>( __LIB to_string( this->getUIID( ) ) + "_allignedof",
										[this]( Component* sender )
										{
											  region_changed_ = true;
											  this->OnModified( ).Invoke( this );
										});
	OnModified( ).Invoke( this );
}

void Component::setParent(__UI Component * parent)
{
	parent_ = parent;
	OnModified( ).Invoke( this );
}

void Component::setAllignment(const __UI Allignment & allignment)
{
	allignment_ = allignment;
	OnModified( ).Invoke( this );
}

void Component::setLayout(const __UI Layout & layout)
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

void Component::setText(const __LIB String & text)
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

bool Component::Collides(const __MATH Vector2 & with)
{
	auto region = determineRegion( );
	return with.Intersects( region );
}

bool Component::Collides(const __UI Component * with)
{
	return Collides( with->getLocalPosition( ) + with->getGlobalPosition( ) );
}

__LIB Event<void(Component*)>& Component::OnModified( )
{
	return _OnModified;
}

__LIB Event<void(Component*)>& Component::OnMouseEnter()
{
	return _OnMouseEnter;
}

__LIB Event<void(Component*)>& Component::OnMouseLeave()
{
	return _OnMouseLeave;
}

__LIB Event<void(Component*)>& Component::OnMousePressed()
{
	return _OnMousePressed;
}

__LIB Event<void(Component*)>& Component::OnMouseReleased()
{
	return _OnMouseReleased;
}

__LIB Event<void(Component*, __GRAPHICS BasePainter*)>& Component::OnPrePaint()
{
	return _OnPrePaint;
}

__LIB Event<void(Component*, __GRAPHICS BasePainter*)>& Component::OnPostPaint()
{
	return _OnPostPaint;
}

__LIB Event<void(Component*)>& Component::OnRelease()
{
	return _OnRelease;
}



end_UI