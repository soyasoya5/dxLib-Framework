#include "Component.h"
#include "../Font.h"

begin_UI

Component::Component()
	: _local( ), _global( ), _style( Dark, Blue ), _leftOf( nullptr ),
	  _rightOf( nullptr ), _bottomOf( nullptr ), _topOf( nullptr ),
	  _parent( nullptr ), _allignment( Center ), _layout( Horizontal ),
	  _state( 0 ), _hovering( false ), _focusing( false ), _clicking( false ),
	  _enabled( true ), _visible( true ), _userdata( nullptr ), _region_changed( true )
{

}

Component::~Component()
{
	Release( );
}

__MATH Region Component::getLocalRegion() const
{
	return _local;
}

__MATH Vector2 Component::getLocalPosition() const
{
	return _local.position;
}

__MATH Region Component::getGlobalRegion() const
{
	return _global;
}

__MATH Region Component::determineRegion()
{
	if ( _region_changed ) {
		_determined.position = _local.position + _global.position;
		_determined.size = _local.size;
		
		// Determine X axis
		if ( _leftOf )
		{
			auto detLeft = _leftOf->determineRegion( );
			_determined.position.x = detLeft.position.x - _local.size.x - 15;
		}
		else if ( _rightOf )
		{
			auto detRight = _rightOf->determineRegion( );
			_determined.position.x = detRight.position.x + detRight.size.x + 15;
		}
		
		if ( _bottomOf )
		{
			auto detBottom = _bottomOf->determineRegion( );
			_determined.position.y = detBottom.position.y + _bottomOf->_local.size.y + 15;
		}
		else if ( _topOf )
		{
			auto detTop = _topOf->determineRegion( );
			_determined.position.y = detTop.position.y - 15;
		}
		
		if ( _allignedOf && ( _determined.position.x == 0 || _determined.position.y == 0 ) )
		{
			auto detAllign = _allignedOf->determineRegion( );
			if ( _determined.position.y == 0 )
				_determined.position.y = detAllign.position.y;
			if ( _determined.position.x == 0 )
				_determined.position.x = detAllign.position.x;
		}
		_region_changed = false;
	}

	return _determined;
}

__MATH Vector2 Component::getGlobalPosition() const
{
	return _global.position;
}

__MATH Vector2 Component::getSize() const
{
	return _local.size;
}

__UI StyleManager Component::getStyle() const
{
	return _style;
}

__UI Component * Component::getLeftOf() const
{
	return _leftOf;
}

__UI Component * Component::getRightOf() const
{
	return _rightOf;
}

__UI Component * Component::getBottomOf() const
{
	return _bottomOf;
}

__UI Component * Component::getTopOf() const
{
	return _topOf;
}

__UI Component * Component::getAllignedOf() const
{
	return _allignedOf;
}

__UI Component * Component::getParent() const
{
	return _parent;
}

__UI Allignment Component::getAllignment() const
{
	return _allignment;
}

__UI Layout Component::getLayout() const
{
	return _layout;
}

int Component::getState() const
{
	return _state;
}

bool Component::isHovered() const
{
	return _hovering;
}

bool Component::isFocused() const
{
	return _focusing;
}

bool Component::isClicked() const
{
	return _clicking;
}

bool Component::isEnabled() const
{
	return _enabled;
}

bool Component::isVisible() const
{
	return _visible;
}

void * Component::getUserdata() const
{
	return _userdata;
}

__GRAPHICS Font * Component::getFont() const
{
	return _font;
}

int Component::getUIID() const
{
	return _guid;
}

__LIB String Component::getText() const
{
	return _text;
}

void Component::setLocalRegion(const __MATH Region & _Region)
{
	_local = _Region;
	_global.size = _local.size;
	_region_changed = true;
	OnModified( ).Invoke( this );
}

void Component::setLocalPosition(const __MATH Vector2 & _Position)
{
	_local.position = _Position;
	_region_changed = true;
	OnModified( ).Invoke( this );
}

void Component::setGlobalRegion(const __MATH Region & _Region)
{
	_global = _Region;
	_local.size = _global.size;
	_region_changed = true;
	OnModified( ).Invoke( this );
}

void Component::setGlobalPosition(const __MATH Vector2 & _Position)
{
	_global.position = _Position;
	_region_changed = true;
	OnModified( ).Invoke( this );
}

void Component::setSize(const __MATH Vector2 & _Size)
{
	_local.size = _Size;
	_global.size = _Size;
	_region_changed = true;
	OnModified( ).Invoke( this );
}

void Component::setStyle(const __UI StyleManager & _Style)
{
	_style = _Style;
	OnModified( ).Invoke( this );
}

void Component::setLeftOf(__UI Component * _Component)
{
	_leftOf = _Component;
	OnModified( ).Invoke( this );
}

void Component::setRightOf(__UI Component * _Component)
{
	_rightOf = _Component;
	OnModified( ).Invoke( this );
}

void Component::setBottomOf(__UI Component * _Component)
{
	_bottomOf = _Component;
	OnModified( ).Invoke( this );
}

void Component::setTopOf(__UI Component * _Component)
{
	_topOf = _Component;
	OnModified( ).Invoke( this );
}

void Component::setAllignedOf(__UI Component * _Component)
{
	_allignedOf = _Component;
	OnModified( ).Invoke( this );
}

void Component::setParent(__UI Component * _Parent)
{
	_parent = _Parent;
	OnModified( ).Invoke( this );
}

void Component::setAllignment(const __UI Allignment & _Allignment)
{
	_allignment = _Allignment;
	OnModified( ).Invoke( this );
}

void Component::setLayout(const __UI Layout & _Layout)
{
	_layout = _Layout;
	OnModified( ).Invoke( this );
}

void Component::setState( const int &_State )
{
	_state = _State;
	OnModified( ).Invoke( this );
}

void Component::setHovered(const bool & _Hovered)
{
	_hovering = _Hovered;
	OnModified( ).Invoke( this );
}

void Component::setFocused(const bool & _Focused)
{
	_focusing = _Focused;
	OnModified( ).Invoke( this );
}

void Component::setClicked(const bool & _Clicked)
{
	_clicking = _Clicked;
	OnModified( ).Invoke( this );
}

void Component::setEnabled(const bool & _Enabled)
{
	_enabled = _Enabled;
	OnModified( ).Invoke( this );
}

void Component::setVisible(const bool & _Visible)
{
	_visible = _Visible;
	OnModified( ).Invoke( this );
}

void Component::setUserdata(void * _Data)
{
	_userdata = _Data;
	OnModified( ).Invoke( this );
}

void Component::setFont(__GRAPHICS Font * _Font)
{
	this->_font = _Font;
	OnModified( ).Invoke( this );
}

void Component::setUIID(const int & _GUID)
{
	_guid = _GUID;
	OnModified( ).Invoke( this );
}

void Component::setText(const __LIB String & _Text)
{
	_text = _Text;
	OnModified( ).Invoke( this );
}

void Component::flipLayout()
{
	if ( _layout == Horizontal )
		setLayout( Vertical );
	else
		setLayout( Horizontal );

}

void Component::KeyDown(__GRAPHICS Window * _Sender, __GRAPHICS KeyDownArgs & _Args)
{
}

void Component::KeyUp(__GRAPHICS Window * _Sender, __GRAPHICS KeyUpArgs & _Args)
{
}

void Component::KeyDownChar(__GRAPHICS Window * _Sender, __GRAPHICS KeyDownCharArgs & _Args)
{
}

void Component::MouseMoved(__GRAPHICS Window * _Sender, __GRAPHICS MouseMovedArgs & _Args)
{
	if ( Collides( _Args.position ) && !_Args.handled )
	{
		if ( !this->_hovering )
		{
			this->_hovering = true;
			OnMouseEnter( ).Invoke( this );
		}
		_Args.handled = true;
	}
	else if (this->_hovering)
	{
		this->_hovering = false;
		OnMouseLeave( ).Invoke( this );
		_Args.handled = true;
	}
}

void Component::MouseClicked(__GRAPHICS Window * _Sender, __GRAPHICS MouseClickedArgs & _Args)
{
	if ( _Args.handled )
		return;

	if ( this->_hovering && !this->_clicking )
	{
		OnMousePressed( ).Invoke( this );
		this->_clicking = true;
		_Args.handled = true;
	}
	else
		this->_clicking = false;

}

void Component::MouseReleased(__GRAPHICS Window * _Sender, __GRAPHICS MouseReleasedArgs & _Args)
{
	if ( this->_hovering && this->_clicking ) {
		OnMouseReleased( ).Invoke( this );
		_Args.handled = true;
	}
	this->_clicking = false;
}

void Component::MouseScrolled(__GRAPHICS Window * _Sender, __GRAPHICS ScrollArgs & _Args)
{
}

void Component::Release(const bool & _ReleaseChildren)
{
	OnRelease( ).Invoke( this );
	if ( _ReleaseChildren )
	{
		for ( auto &x : _children )
			x->Release( _ReleaseChildren );
	}
}

bool Component::Collides(const __MATH Vector2 & _With)
{
	auto region = determineRegion( );

	return _With.Intersects( region );
}

bool Component::Collides(const __UI Component * _With)
{
	return Collides( _With->getLocalPosition( ) + _With->getGlobalPosition( ) );
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