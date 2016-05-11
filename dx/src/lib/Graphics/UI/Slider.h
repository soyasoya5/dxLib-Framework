#pragma once
#include "Component.h"

begin_UI
class Textbox;
class RichLabel;

class Slider : public Component
{
public:
	Slider( );

	void Paint( Window *sender, BasePainter *painter ) override;

	void KeyDown( Window *sender, KeyDownArgs &_Args ) override;

	void KeyUp( Window *sender, KeyUpArgs &_Args ) override;

	void KeyDownChar( Window *sender, KeyDownCharArgs &args ) override;

	void MouseMoved( Window *sender, MouseMovedArgs &args ) override;

	void MouseClicked( Window *sender, MouseClickedArgs &args ) override;

	void MouseReleased( Window *sender, MouseReleasedArgs &args ) override;

	::dx::lib::Math::Vector2 getDelta( ) const;

	void setDelta( float delta );
	
	void setMaxDelta( const float &delta );

	float getMaxDelta( ) const;

	void setWheel( const float &delta );
	
	float getWheel( ) const;

	void setWheelSize( const ::dx::lib::Math::Vector2 &size );

	::dx::lib::Math::Vector2 getWheelSize( ) const;

	bool CollidesWheel( const ::dx::lib::Math::Vector2 &position );

	bool inScrollableRegion( const ::dx::lib::Math::Vector2 &cursor ) const;

	std::shared_ptr<Textbox> getTextbox( ) const;

	void moveWheelToDelta( );

private:
	::dx::lib::Math::Vector2 moved_, wheel_, wheelSize_, delta_;
	std::shared_ptr<Textbox> textbox_;
	bool changed_, dragging_;
	float maxDelta_;
};



end_UI




