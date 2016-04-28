#pragma once
#include "../../../dx.h"
#include "../../event.h"
#include "../../Math/Vector2.h"
#include "../../Math/Region.h"
#include "../Window/Window.h"
#include "../../string.h"
#include "Style.h"
#include "lib.h"

begin_GRAPHICS class Font; end_GRAPHICS

begin_UI


// Allignment enum
enum Alignment
{
	Center,
	Left,
	Right,
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
	virtual ~Component( );

public: // Accessors
	virtual ::dx::lib::Math::Region getLocalRegion( ) const;
	virtual ::dx::lib::Math::Vector2 getLocalPosition( ) const;
	virtual ::dx::lib::Math::Region getGlobalRegion( ) const;
	virtual ::dx::lib::Math::Region determineRegion( );
	virtual ::dx::lib::Math::Vector2 getGlobalPosition( ) const;
	virtual ::dx::lib::Math::Vector2 getSize( ) const;
	virtual  StyleManager getStyle( ) const;
	virtual  Component* getLeftOf( ) const;
	virtual  Component* getRightOf( ) const;
	virtual  Component* getBottomOf( ) const;
	virtual  Component* getTopOf( ) const;
	virtual  Component* getAlignedOf( ) const;
	virtual  Component* getParent( ) const;
	virtual  Alignment getAlignment( ) const;
	virtual  Layout getLayout( ) const;
	virtual int getState( ) const;
	virtual bool isHovered( ) const;
	virtual bool isFocused( ) const;
	virtual bool isClicked( ) const;
	virtual bool isEnabled( ) const;
	virtual bool isVisible( ) const;
	virtual void* getUserdata( ) const;
	virtual std::shared_ptr<Font> getFont( ) const;
	virtual int getUIID( ) const; 
	virtual  String getText( ) const;

public: // Modifiers
	virtual void setLocalRegion( const ::dx::lib::Math::Region &region );
	virtual void setLocalPosition( const ::dx::lib::Math::Vector2 &position );
	virtual void setGlobalRegion( const ::dx::lib::Math::Region &region );
	virtual void setGlobalPosition( const ::dx::lib::Math::Vector2 &position );
	virtual void setSize( const ::dx::lib::Math::Vector2 &size );
	virtual void setStyle( const  StyleManager &style );
	virtual void setLeftOf(  Component *component );
	virtual void setRightOf(  Component *component );
	virtual void setBottomOf(   Component *component );
	virtual void setTopOf(  Component *component );
	virtual void setAlignedOf(  Component *component );
	virtual void setParent(  Component *parent );
	virtual void setAlignment( const  Alignment &allignment );
	virtual void setLayout( const  Layout &layout );
	virtual void setState( const int &state );
	virtual void setHovered( const bool &hovered );
	virtual void setFocused( const bool &focused );
	virtual void setClicked( const bool &clicked );
	virtual void setEnabled( const bool &enabled );
	virtual void setVisible( const bool &visible );
	virtual void setUserdata( void *data );
	virtual void setFont( std::shared_ptr<Font> font );
	virtual void setUIID( const int &id );
	virtual void setText( const  String &text );
	virtual void flipLayout( );

public: // Virtuals/Logic
	virtual void Paint( Window* sender, BasePainter *painter ) = 0;
	virtual void KeyDown( Window* sender, KeyDownArgs &args );
	virtual void KeyUp( Window* sender, KeyUpArgs &args );
	virtual void KeyDownChar( Window* sender, KeyDownCharArgs &args );
	virtual void MouseMoved( Window* sender, MouseMovedArgs &args );
	virtual void MouseClicked( Window* sender, MouseClickedArgs &args );
	virtual void MouseReleased( Window* sender, MouseReleasedArgs &args );
	virtual void MouseScrolled( Window* sender, ScrollArgs &args );
	virtual void MouseDoubleClicked( Window* sender, MouseClickedArgs &args );
	virtual void Release( const bool &release_children = true );
	virtual bool Collides( const ::dx::lib::Math::Vector2 &with );
	virtual bool Collides( const Component *with );

public:
	///<summary>
	///	Raised when anything of this component was modified.
	///</summary>
	Event<void(Component*)>& OnModified( );

	///<summary>
	///	Raised when the mouse enters this Components defined region.
	///</summary>
	Event<void(Component*)>& OnMouseEnter( );

	///<summary>
	/// Raied when the mouse leaves this Components defined region.
	///</summary>
	Event<void(Component*)>& OnMouseLeave( );

	///<summary>
	///	Raised when the the mouse is pressed whilst it is inside this Components defined region.
	///</summary>
	Event<void(Component*)>& OnMousePressed( );

	///<summary>
	///	Raised when the the mouse is released whilst it is inside this Components defined region.
	///</summary>
	Event<void(Component*)>& OnMouseReleased( );

	///<summary>
	///	Raised before the component starts painting.
	///</summary>
	Event<void(Component*,  BasePainter*)>& OnPrePaint( );

	///<summary>
	///	Raised when the component has finished painting.
	///</summary>
	Event<void(Component*,  BasePainter*)>& OnPostPaint( );

	///<summary>
	///	Raised when the components 'Release' method is called.
	///</summary>
	Event<void(Component*)>& OnRelease( );

protected:
	 String text_;
	std::shared_ptr<Font> font_;
	::dx::lib::Math::Region local_, global_, determined_;
	 StyleManager style_;
	 Component *leftOf_, *rightOf_, *bottomOf_, *topOf_, *alignedOf_;
	 Component* parent_;
	std::vector< Component*> children_;
	 Alignment alignment_;
	 Layout layout_;
	int state_, uiid_;
	bool hovering_, focusing_, clicking_, enabled_, visible_, region_changed_;
	void *userdata_;

private: // Events
	 Event<void(Component*)> _OnModified, _OnMouseEnter, _OnMouseLeave, _OnMousePressed, _OnMouseReleased, _OnRelease;
	 Event<void(Component*,  BasePainter*)> _OnPrePaint, _OnPostPaint;
};

end_UI