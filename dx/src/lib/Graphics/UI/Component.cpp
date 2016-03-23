#include "Component.h"


begin_UI

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

void Component::setLocalRegion(const __MATH Region & _Region)
{
	OnModified( ).Invoke( this );
	_local = _Region;
	_global.size = _local.size;
}

void Component::setLocalPosition(const __MATH Vector2 & _Position)
{
	OnModified( ).Invoke( this );
	_local.position = _Position;
}

void Component::setGlobalRegion(const __MATH Region & _Region)
{
	OnModified( ).Invoke( this );
	_global = _Region;
	_local.size = _global.size;
}

void Component::setGlobalPosition(const __MATH Vector2 & _Position)
{
	OnModified( ).Invoke( this );
	_global.position = _Position;
}

void Component::setSize(const __MATH Vector2 & _Size)
{
	OnModified( ).Invoke( this );
	_local.size = _Size;
	_global.size = _Size;
}

void Component::setStyle(const __UI StyleManager & _Style)
{
	OnModified( ).Invoke( this );
	_style = _Style;
}

void Component::setLeftOf(__UI Component * _Component)
{
	OnModified( ).Invoke( this );
	_leftOf = _Component;
}

void Component::setRightOf(__UI Component * _Component)
{
	OnModified( ).Invoke( this );
	_rightOf = _Component;
}

void Component::setBottomOf(__UI Component * _Component)
{
	OnModified( ).Invoke( this );
	_bottomOf = _Component;
}

void Component::setTopOf(__UI Component * _Component)
{
	OnModified( ).Invoke( this );
	_topOf = _Component;
}

void Component::setParent(__UI Component * _Parent)
{
	OnModified( ).Invoke( this );
	_parent = _Parent;
}

void Component::setAllignment(const __UI Allignment & _Allignment)
{
	OnModified( ).Invoke( this );
	_allignment = _Allignment;
}

void Component::setLayout(const __UI Layout & _Layout)
{
	OnModified( ).Invoke( this );
	_layout = _Layout;
}

void Component::setState( const int &_State )
{
	OnModified( ).Invoke( this );
	_state = _State;
}

void Component::setHovered(const bool & _Hovered)
{
	OnModified( ).Invoke( this );
	_hovering = _Hovered;
}

void Component::setFocused(const bool & _Focused)
{
	OnModified( ).Invoke( this );
	_focusing = _Focused;
}

void Component::setClicked(const bool & _Clicked)
{
	OnModified( ).Invoke( this );
	_clicking = _Clicked;
}

void Component::setEnabled(const bool & _Enabled)
{
	OnModified( ).Invoke( this );
	_enabled = _Enabled;
}

void Component::setVisible(const bool & _Visible)
{
	OnModified( ).Invoke( this );
	_visible = _Visible;
}

void Component::setUserdata(void * _Data)
{
	OnModified( ).Invoke( this );
	_userdata = _Data;
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
	if ( Collides( _Args.position ) )
	{
		if ( !this->_hovering )
		{
			this->_hovering = true;
			OnMouseEnter( ).Invoke( this );
		}
	}
	else if (this->_hovering)
	{
		this->_hovering = false;
		OnMouseLeave( ).Invoke( this );
	}
}

void Component::MouseClicked(__GRAPHICS Window * _Sender, __GRAPHICS MouseClickedArgs & _Args)
{
	if ( this->_hovering && !this->_clicking )
	{
		OnMousePressed( ).Invoke( this );
		this->_clicking = true;
	}
}

void Component::MouseReleased(__GRAPHICS Window * _Sender, __GRAPHICS MouseReleasedArgs & _Args)
{
	if ( this->_hovering && this->_clicking )
		OnMouseReleased( ).Invoke( this );
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

bool Component::Collides(const __MATH Vector2 & _With) const
{
	auto abs_pos = this->_local.position + this->_global.position;
	auto size = this->getSize( );
	__MATH Region region{ abs_pos, size };

	return _With.Intersects( region );
}

bool Component::Collides(const __UI Component * _With) const
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