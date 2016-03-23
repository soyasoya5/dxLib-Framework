#pragma once
#include "../../../dx.h"
#include "../../event.h"
#include "../../Math/Vector2.h"
#include "../../Math/Region.h"
#include "../Window/Window.h"
#include "Style.h"
#include "lib.h"


begin_UI

// Allignment enum
enum Allignment
{
	Center,
	Left,
	Right,
	Top = Left,
	Bottom = Right
};

enum Layout
{
	Horizontal,
	Vertical
};


// Base class for any UI Component
class Component
{
	/*
		Difference between Local region and Global region:

	
	*/

public:
	Component( );

public: // Accessors
	virtual __MATH Region getLocalRegion( ) const;
	virtual __MATH Vector2 getLocalPosition( ) const;
	virtual __MATH Region getGlobalRegion( ) const;
	virtual __MATH Vector2 getGlobalPosition( ) const;
	virtual __MATH Vector2 getSize( ) const;
	virtual __UI StyleManager getStyle( ) const;
	virtual __UI Component* getLeftOf( ) const;
	virtual __UI Component* getRightOf( ) const;
	virtual __UI Component* getBottomOf( ) const;
	virtual __UI Component* getTopOf( ) const;
	virtual __UI Component* getParent( ) const;
	virtual __UI Allignment getAllignment( ) const;
	virtual __UI Layout getLayout( ) const;
	virtual int getState( ) const;
	virtual bool isHovered( ) const;
	virtual bool isFocused( ) const;
	virtual bool isClicked( ) const;
	virtual bool isEnabled( ) const;
	virtual bool isVisible( ) const;
	virtual void* getUserdata( ) const;

public: // Modifiers
	virtual void setLocalRegion( const __MATH Region &_Region );
	virtual void setLocalPosition( const __MATH Vector2 &_Position );
	virtual void setGlobalRegion( const __MATH Region &_Region );
	virtual void setGlobalPosition( const __MATH Vector2 &_Position );
	virtual void setSize( const __MATH Vector2 &_Size );
	virtual void setStyle( const __UI StyleManager &_Style );
	virtual void setLeftOf( __UI Component *_Component );
	virtual void setRightOf( __UI Component *_Component );
	virtual void setBottomOf( __UI  Component *_Component );
	virtual void setTopOf( __UI Component *_Component );
	virtual void setParent( __UI Component *_Parent );
	virtual void setAllignment( const __UI Allignment &_Allignment );
	virtual void setLayout( const __UI Layout &_Layout );
	virtual void setState( const int &_State );
	virtual void setHovered( const bool &_Hovered );
	virtual void setFocused( const bool &_Focused );
	virtual void setClicked( const bool &_Clicked );
	virtual void setEnabled( const bool &_Enabled );
	virtual void setVisible( const bool &_Visible );
	virtual void setUserdata( void *_Data );

public: // Virtuals/Logic
	virtual void Paint( __GRAPHICS BasePainter *_Painter ) = 0;
	virtual void KeyDown( __GRAPHICS Window *_Sender, __GRAPHICS KeyDownArgs &_Args );
	virtual void KeyUp( __GRAPHICS Window *_Sender, __GRAPHICS KeyUpArgs &_Args );
	virtual void KeyDownChar( __GRAPHICS Window *_Sender, __GRAPHICS KeyDownCharArgs &_Args );
	virtual void MouseMoved( __GRAPHICS Window *_Sender, __GRAPHICS MouseMovedArgs &_Args );
	virtual void MouseClicked( __GRAPHICS Window *_Sender, __GRAPHICS MouseClickedArgs &_Args );
	virtual void MouseReleased( __GRAPHICS Window *_Sender, __GRAPHICS MouseReleasedArgs &_Args );
	virtual void MouseScrolled( __GRAPHICS Window *_Sender, __GRAPHICS ScrollArgs &_Args );
	virtual void Release( const bool &_ReleaseChildren = true );
	virtual bool Collides( const __MATH Vector2 &_With ) const;
	virtual bool Collides( const __UI Component *_With ) const;

public:
	///<summary>
	///	Raised when anything of this component was modified.
	///</summary>
	__LIB Event<void(Component*)>& OnModified( );

	///<summary>
	///	Raised when the mouse enters this Components defined region.
	///</summary>
	__LIB Event<void(Component*)>& OnMouseEnter( );

	///<summary>
	/// Raied when the mouse leaves this Components defined region.
	///</summary>
	__LIB Event<void(Component*)>& OnMouseLeave( );

	///<summary>
	///	Raised when the the mouse is pressed whilst it is inside this Components defined region.
	///</summary>
	__LIB Event<void(Component*)>& OnMousePressed( );

	///<summary>
	///	Raised when the the mouse is released whilst it is inside this Components defined region.
	///</summary>
	__LIB Event<void(Component*)>& OnMouseReleased( );

	///<summary>
	///	Raised before the component starts painting.
	///</summary>
	__LIB Event<void(Component*, __GRAPHICS BasePainter*)>& OnPrePaint( );

	///<summary>
	///	Raised when the component has finished painting.
	///</summary>
	__LIB Event<void(Component*, __GRAPHICS BasePainter*)>& OnPostPaint( );

	///<summary>
	///	Raised when the components 'Release' method is called.
	///</summary>
	__LIB Event<void(Component*)>& OnRelease( );

private:
	__MATH Region _local, _global;
	__UI StyleManager _style;
	__UI Component *_leftOf, *_rightOf, *_bottomOf, *_topOf;
	__UI Component* _parent;
	std::vector<__UI Component*> _children;
	__UI Allignment _allignment;
	__UI Layout _layout;
	int _state;
	bool _hovering, _focusing, _clicking, _enabled, _visible;
	void *_userdata;

private: // Events
	__LIB Event<void(Component*)> _OnModified, _OnMouseEnter, _OnMouseLeave, _OnMousePressed, _OnMouseReleased, _OnRelease;
	__LIB Event<void(Component*, __GRAPHICS BasePainter*)> _OnPrePaint, _OnPostPaint;
};

end_UI